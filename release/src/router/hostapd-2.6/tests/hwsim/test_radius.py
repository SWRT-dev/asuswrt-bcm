# RADIUS tests
# Copyright (c) 2013-2016, Jouni Malinen <j@w1.fi>
#
# This software may be distributed under the terms of the BSD license.
# See README for more details.

from remotehost import remote_compatible
import binascii
import hashlib
import hmac
import logging
logger = logging.getLogger()
import os
import select
import struct
import subprocess
import threading
import time

import hostapd
from utils import HwsimSkip, require_under_vm, skip_with_fips, fail_test
from test_ap_hs20 import build_dhcp_ack
from test_ap_ft import ft_params1

def connect(dev, ssid, wait_connect=True):
    dev.connect(ssid, key_mgmt="WPA-EAP", scan_freq="2412",
                eap="PSK", identity="psk.user@example.com",
                password_hex="0123456789abcdef0123456789abcdef",
                wait_connect=wait_connect)

@remote_compatible
def test_radius_auth_unreachable(dev, apdev):
    """RADIUS Authentication server unreachable"""
    params = hostapd.wpa2_eap_params(ssid="radius-auth")
    params['auth_server_port'] = "18139"
    hapd = hostapd.add_ap(apdev[0], params)
    connect(dev[0], "radius-auth", wait_connect=False)
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-STARTED"])
    if ev is None:
        raise Exception("Timeout on EAP start")
    logger.info("Checking for RADIUS retries")
    time.sleep(4)
    mib = hapd.get_mib()
    if "radiusAuthClientAccessRequests" not in mib:
        raise Exception("Missing MIB fields")
    if int(mib["radiusAuthClientAccessRetransmissions"]) < 1:
        raise Exception("Missing RADIUS Authentication retransmission")
    if int(mib["radiusAuthClientPendingRequests"]) < 1:
        raise Exception("Missing pending RADIUS Authentication request")

def test_radius_auth_unreachable2(dev, apdev):
    """RADIUS Authentication server unreachable (2)"""
    subprocess.call(['ip', 'ro', 'replace', '192.168.213.17', 'dev', 'lo'])
    params = hostapd.wpa2_eap_params(ssid="radius-auth")
    params['auth_server_addr'] = "192.168.213.17"
    params['auth_server_port'] = "18139"
    hapd = hostapd.add_ap(apdev[0], params)
    subprocess.call(['ip', 'ro', 'del', '192.168.213.17', 'dev', 'lo'])
    connect(dev[0], "radius-auth", wait_connect=False)
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-STARTED"])
    if ev is None:
        raise Exception("Timeout on EAP start")
    logger.info("Checking for RADIUS retries")
    time.sleep(4)
    mib = hapd.get_mib()
    if "radiusAuthClientAccessRequests" not in mib:
        raise Exception("Missing MIB fields")
    if int(mib["radiusAuthClientAccessRetransmissions"]) < 1:
        raise Exception("Missing RADIUS Authentication retransmission")

def test_radius_auth_unreachable3(dev, apdev):
    """RADIUS Authentication server initially unreachable, but then available"""
    subprocess.call(['ip', 'ro', 'replace', 'blackhole', '192.168.213.18'])
    params = hostapd.wpa2_eap_params(ssid="radius-auth")
    params['auth_server_addr'] = "192.168.213.18"
    hapd = hostapd.add_ap(apdev[0], params)
    connect(dev[0], "radius-auth", wait_connect=False)
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-STARTED"])
    if ev is None:
        raise Exception("Timeout on EAP start")
    subprocess.call(['ip', 'ro', 'del', 'blackhole', '192.168.213.18'])
    time.sleep(0.1)
    dev[0].request("DISCONNECT")
    hapd.set('auth_server_addr_replace', '127.0.0.1')
    dev[0].request("RECONNECT")

    dev[0].wait_connected()

def test_radius_acct_unreachable(dev, apdev):
    """RADIUS Accounting server unreachable"""
    params = hostapd.wpa2_eap_params(ssid="radius-acct")
    params['acct_server_addr'] = "127.0.0.1"
    params['acct_server_port'] = "18139"
    params['acct_server_shared_secret'] = "radius"
    hapd = hostapd.add_ap(apdev[0], params)
    connect(dev[0], "radius-acct")
    logger.info("Checking for RADIUS retries")
    time.sleep(4)
    mib = hapd.get_mib()
    if "radiusAccClientRetransmissions" not in mib:
        raise Exception("Missing MIB fields")
    if int(mib["radiusAccClientRetransmissions"]) < 2:
        raise Exception("Missing RADIUS Accounting retransmissions")
    if int(mib["radiusAccClientPendingRequests"]) < 2:
        raise Exception("Missing pending RADIUS Accounting requests")

def test_radius_acct_unreachable2(dev, apdev):
    """RADIUS Accounting server unreachable(2)"""
    subprocess.call(['ip', 'ro', 'replace', '192.168.213.17', 'dev', 'lo'])
    params = hostapd.wpa2_eap_params(ssid="radius-acct")
    params['acct_server_addr'] = "192.168.213.17"
    params['acct_server_port'] = "18139"
    params['acct_server_shared_secret'] = "radius"
    hapd = hostapd.add_ap(apdev[0], params)
    subprocess.call(['ip', 'ro', 'del', '192.168.213.17', 'dev', 'lo'])
    connect(dev[0], "radius-acct")
    logger.info("Checking for RADIUS retries")
    time.sleep(4)
    mib = hapd.get_mib()
    if "radiusAccClientRetransmissions" not in mib:
        raise Exception("Missing MIB fields")
    if int(mib["radiusAccClientRetransmissions"]) < 1 and int(mib["radiusAccClientPendingRequests"]) < 1:
        raise Exception("Missing pending or retransmitted RADIUS Accounting requests")

def test_radius_acct_unreachable3(dev, apdev):
    """RADIUS Accounting server initially unreachable, but then available"""
    require_under_vm()
    subprocess.call(['ip', 'ro', 'replace', 'blackhole', '192.168.213.18'])
    as_hapd = hostapd.Hostapd("as")
    as_mib_start = as_hapd.get_mib(param="radius_server")
    params = hostapd.wpa2_eap_params(ssid="radius-acct")
    params['acct_server_addr'] = "192.168.213.18"
    params['acct_server_port'] = "1813"
    params['acct_server_shared_secret'] = "radius"
    hapd = hostapd.add_ap(apdev[0], params)
    connect(dev[0], "radius-acct")
    subprocess.call(['ip', 'ro', 'del', 'blackhole', '192.168.213.18'])
    time.sleep(0.1)
    dev[0].request("DISCONNECT")
    hapd.set('acct_server_addr_replace', '127.0.0.1')
    dev[0].request("RECONNECT")
    dev[0].wait_connected()
    time.sleep(1)
    as_mib_end = as_hapd.get_mib(param="radius_server")
    req_s = int(as_mib_start['radiusAccServTotalResponses'])
    req_e = int(as_mib_end['radiusAccServTotalResponses'])
    if req_e <= req_s:
        raise Exception("Unexpected RADIUS server acct MIB value")

def test_radius_acct_unreachable4(dev, apdev):
    """RADIUS Accounting server unreachable and multiple STAs"""
    params = hostapd.wpa2_eap_params(ssid="radius-acct")
    params['acct_server_addr'] = "127.0.0.1"
    params['acct_server_port'] = "18139"
    params['acct_server_shared_secret'] = "radius"
    hapd = hostapd.add_ap(apdev[0], params)
    for i in range(20):
        connect(dev[0], "radius-acct")
        dev[0].request("REMOVE_NETWORK all")
        dev[0].wait_disconnected()

def test_radius_acct(dev, apdev):
    """RADIUS Accounting"""
    as_hapd = hostapd.Hostapd("as")
    as_mib_start = as_hapd.get_mib(param="radius_server")
    params = hostapd.wpa2_eap_params(ssid="radius-acct")
    params['acct_server_addr'] = "127.0.0.1"
    params['acct_server_port'] = "1813"
    params['acct_server_shared_secret'] = "radius"
    params['radius_auth_req_attr'] = [ "126:s:Operator", "77:s:testing" ]
    params['radius_acct_req_attr'] = [ "126:s:Operator", "77:s:testing" ]
    hapd = hostapd.add_ap(apdev[0], params)
    connect(dev[0], "radius-acct")
    dev[1].connect("radius-acct", key_mgmt="WPA-EAP", scan_freq="2412",
                   eap="PAX", identity="test-class",
                   password_hex="0123456789abcdef0123456789abcdef")
    dev[2].connect("radius-acct", key_mgmt="WPA-EAP",
                   eap="GPSK", identity="gpsk-cui",
                   password="abcdefghijklmnop0123456789abcdef",
                   scan_freq="2412")
    logger.info("Checking for RADIUS counters")
    count = 0
    while True:
        mib = hapd.get_mib()
        if int(mib['radiusAccClientResponses']) >= 3:
            break
        time.sleep(0.1)
        count += 1
        if count > 10:
            raise Exception("Did not receive Accounting-Response packets")

    if int(mib['radiusAccClientRetransmissions']) > 0:
        raise Exception("Unexpected Accounting-Request retransmission")

    as_mib_end = as_hapd.get_mib(param="radius_server")

    req_s = int(as_mib_start['radiusAccServTotalRequests'])
    req_e = int(as_mib_end['radiusAccServTotalRequests'])
    if req_e < req_s + 2:
        raise Exception("Unexpected RADIUS server acct MIB value")

    acc_s = int(as_mib_start['radiusAuthServAccessAccepts'])
    acc_e = int(as_mib_end['radiusAuthServAccessAccepts'])
    if acc_e < acc_s + 1:
        raise Exception("Unexpected RADIUS server auth MIB value")

def test_radius_acct_non_ascii_ssid(dev, apdev):
    """RADIUS Accounting and non-ASCII SSID"""
    params = hostapd.wpa2_eap_params()
    params['acct_server_addr'] = "127.0.0.1"
    params['acct_server_port'] = "1813"
    params['acct_server_shared_secret'] = "radius"
    ssid2 = "740665007374"
    params['ssid2'] = ssid2
    hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid2=ssid2, key_mgmt="WPA-EAP", scan_freq="2412",
                   eap="PSK", identity="psk.user@example.com",
                   password_hex="0123456789abcdef0123456789abcdef")

def test_radius_acct_pmksa_caching(dev, apdev):
    """RADIUS Accounting with PMKSA caching"""
    as_hapd = hostapd.Hostapd("as")
    as_mib_start = as_hapd.get_mib(param="radius_server")
    params = hostapd.wpa2_eap_params(ssid="radius-acct")
    params['acct_server_addr'] = "127.0.0.1"
    params['acct_server_port'] = "1813"
    params['acct_server_shared_secret'] = "radius"
    hapd = hostapd.add_ap(apdev[0], params)
    connect(dev[0], "radius-acct")
    dev[1].connect("radius-acct", key_mgmt="WPA-EAP", scan_freq="2412",
                   eap="PAX", identity="test-class",
                   password_hex="0123456789abcdef0123456789abcdef")
    for d in [ dev[0], dev[1] ]:
        d.request("REASSOCIATE")
        d.wait_connected(timeout=15, error="Reassociation timed out")

    count = 0
    while True:
        mib = hapd.get_mib()
        if int(mib['radiusAccClientResponses']) >= 4:
            break
        time.sleep(0.1)
        count += 1
        if count > 10:
            raise Exception("Did not receive Accounting-Response packets")

    if int(mib['radiusAccClientRetransmissions']) > 0:
        raise Exception("Unexpected Accounting-Request retransmission")

    as_mib_end = as_hapd.get_mib(param="radius_server")

    req_s = int(as_mib_start['radiusAccServTotalRequests'])
    req_e = int(as_mib_end['radiusAccServTotalRequests'])
    if req_e < req_s + 2:
        raise Exception("Unexpected RADIUS server acct MIB value")

    acc_s = int(as_mib_start['radiusAuthServAccessAccepts'])
    acc_e = int(as_mib_end['radiusAuthServAccessAccepts'])
    if acc_e < acc_s + 1:
        raise Exception("Unexpected RADIUS server auth MIB value")

def test_radius_acct_interim(dev, apdev):
    """RADIUS Accounting interim update"""
    as_hapd = hostapd.Hostapd("as")
    params = hostapd.wpa2_eap_params(ssid="radius-acct")
    params['acct_server_addr'] = "127.0.0.1"
    params['acct_server_port'] = "1813"
    params['acct_server_shared_secret'] = "radius"
    params['radius_acct_interim_interval'] = "1"
    hapd = hostapd.add_ap(apdev[0], params)
    connect(dev[0], "radius-acct")
    logger.info("Checking for RADIUS counters")
    as_mib_start = as_hapd.get_mib(param="radius_server")
    time.sleep(3.1)
    as_mib_end = as_hapd.get_mib(param="radius_server")
    req_s = int(as_mib_start['radiusAccServTotalRequests'])
    req_e = int(as_mib_end['radiusAccServTotalRequests'])
    if req_e < req_s + 3:
        raise Exception("Unexpected RADIUS server acct MIB value")

def test_radius_acct_interim_unreachable(dev, apdev):
    """RADIUS Accounting interim update with unreachable server"""
    params = hostapd.wpa2_eap_params(ssid="radius-acct")
    params['acct_server_addr'] = "127.0.0.1"
    params['acct_server_port'] = "18139"
    params['acct_server_shared_secret'] = "radius"
    params['radius_acct_interim_interval'] = "1"
    hapd = hostapd.add_ap(apdev[0], params)
    start = hapd.get_mib()
    connect(dev[0], "radius-acct")
    logger.info("Waiting for interium accounting updates")
    time.sleep(3.1)
    end = hapd.get_mib()
    req_s = int(start['radiusAccClientTimeouts'])
    req_e = int(end['radiusAccClientTimeouts'])
    if req_e < req_s + 2:
        raise Exception("Unexpected RADIUS server acct MIB value")

def test_radius_acct_interim_unreachable2(dev, apdev):
    """RADIUS Accounting interim update with unreachable server (retry)"""
    params = hostapd.wpa2_eap_params(ssid="radius-acct")
    params['acct_server_addr'] = "127.0.0.1"
    params['acct_server_port'] = "18139"
    params['acct_server_shared_secret'] = "radius"
    # Use long enough interim update interval to allow RADIUS retransmission
    # case (3 seconds) to trigger first.
    params['radius_acct_interim_interval'] = "4"
    hapd = hostapd.add_ap(apdev[0], params)
    start = hapd.get_mib()
    connect(dev[0], "radius-acct")
    logger.info("Waiting for interium accounting updates")
    time.sleep(7.5)
    end = hapd.get_mib()
    req_s = int(start['radiusAccClientTimeouts'])
    req_e = int(end['radiusAccClientTimeouts'])
    if req_e < req_s + 2:
        raise Exception("Unexpected RADIUS server acct MIB value")

def test_radius_acct_ipaddr(dev, apdev):
    """RADIUS Accounting and Framed-IP-Address"""
    try:
        _test_radius_acct_ipaddr(dev, apdev)
    finally:
        subprocess.call(['ip', 'link', 'set', 'dev', 'ap-br0', 'down'],
                        stderr=open('/dev/null', 'w'))
        subprocess.call(['brctl', 'delbr', 'ap-br0'],
                        stderr=open('/dev/null', 'w'))

def _test_radius_acct_ipaddr(dev, apdev):
    params = { "ssid": "radius-acct-open",
               'acct_server_addr': "127.0.0.1",
               'acct_server_port': "1813",
               'acct_server_shared_secret': "radius",
               'proxy_arp': '1',
               'ap_isolate': '1',
               'bridge': 'ap-br0' }
    hapd = hostapd.add_ap(apdev[0], params, no_enable=True)
    try:
        hapd.enable()
    except:
        # For now, do not report failures due to missing kernel support
        raise HwsimSkip("Could not start hostapd - assume proxyarp not supported in kernel version")
    bssid = apdev[0]['bssid']

    subprocess.call(['brctl', 'setfd', 'ap-br0', '0'])
    subprocess.call(['ip', 'link', 'set', 'dev', 'ap-br0', 'up'])

    dev[0].connect("radius-acct-open", key_mgmt="NONE", scan_freq="2412")
    addr0 = dev[0].own_addr()

    pkt = build_dhcp_ack(dst_ll="ff:ff:ff:ff:ff:ff", src_ll=bssid,
                         ip_src="192.168.1.1", ip_dst="255.255.255.255",
                         yiaddr="192.168.1.123", chaddr=addr0)
    if "OK" not in hapd.request("DATA_TEST_FRAME ifname=ap-br0 " + binascii.hexlify(pkt)):
        raise Exception("DATA_TEST_FRAME failed")

    dev[0].request("DISCONNECT")
    dev[0].wait_disconnected()
    hapd.disable()

def send_and_check_reply(srv, req, code, error_cause=0):
    reply = srv.SendPacket(req)
    logger.debug("RADIUS response from hostapd")
    for i in reply.keys():
        logger.debug("%s: %s" % (i, reply[i]))
    if reply.code != code:
        raise Exception("Unexpected response code")
    if error_cause:
        if 'Error-Cause' not in reply:
            raise Exception("Missing Error-Cause")
            if reply['Error-Cause'][0] != error_cause:
                raise Exception("Unexpected Error-Cause: {}".format(reply['Error-Cause']))

def test_radius_acct_psk(dev, apdev):
    """RADIUS Accounting - PSK"""
    as_hapd = hostapd.Hostapd("as")
    params = hostapd.wpa2_params(ssid="radius-acct", passphrase="12345678")
    params['acct_server_addr'] = "127.0.0.1"
    params['acct_server_port'] = "1813"
    params['acct_server_shared_secret'] = "radius"
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect("radius-acct", psk="12345678", scan_freq="2412")

def test_radius_acct_psk_sha256(dev, apdev):
    """RADIUS Accounting - PSK SHA256"""
    as_hapd = hostapd.Hostapd("as")
    params = hostapd.wpa2_params(ssid="radius-acct", passphrase="12345678")
    params["wpa_key_mgmt"] = "WPA-PSK-SHA256"
    params['acct_server_addr'] = "127.0.0.1"
    params['acct_server_port'] = "1813"
    params['acct_server_shared_secret'] = "radius"
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect("radius-acct", key_mgmt="WPA-PSK-SHA256",
                   psk="12345678", scan_freq="2412")

def test_radius_acct_ft_psk(dev, apdev):
    """RADIUS Accounting - FT-PSK"""
    as_hapd = hostapd.Hostapd("as")
    params = ft_params1(ssid="radius-acct", passphrase="12345678")
    params['acct_server_addr'] = "127.0.0.1"
    params['acct_server_port'] = "1813"
    params['acct_server_shared_secret'] = "radius"
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect("radius-acct", key_mgmt="FT-PSK",
                   psk="12345678", scan_freq="2412")

def test_radius_acct_ieee8021x(dev, apdev):
    """RADIUS Accounting - IEEE 802.1X"""
    skip_with_fips(dev[0])
    as_hapd = hostapd.Hostapd("as")
    params = hostapd.radius_params()
    params["ssid"] = "radius-acct-1x"
    params["ieee8021x"] = "1"
    params["wep_key_len_broadcast"] = "13"
    params["wep_key_len_unicast"] = "13"
    params['acct_server_addr'] = "127.0.0.1"
    params['acct_server_port'] = "1813"
    params['acct_server_shared_secret'] = "radius"
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect("radius-acct-1x", key_mgmt="IEEE8021X", eap="PSK",
                   identity="psk.user@example.com",
                   password_hex="0123456789abcdef0123456789abcdef",
                   scan_freq="2412")

def test_radius_das_disconnect(dev, apdev):
    """RADIUS Dynamic Authorization Extensions - Disconnect"""
    try:
        import pyrad.client
        import pyrad.packet
        import pyrad.dictionary
        import radius_das
    except ImportError:
        raise HwsimSkip("No pyrad modules available")

    params = hostapd.wpa2_eap_params(ssid="radius-das")
    params['radius_das_port'] = "3799"
    params['radius_das_client'] = "127.0.0.1 secret"
    params['radius_das_require_event_timestamp'] = "1"
    params['own_ip_addr'] = "127.0.0.1"
    params['nas_identifier'] = "nas.example.com"
    hapd = hostapd.add_ap(apdev[0], params)
    connect(dev[0], "radius-das")
    addr = dev[0].p2p_interface_addr()
    sta = hapd.get_sta(addr)
    id = sta['dot1xAuthSessionId']

    dict = pyrad.dictionary.Dictionary("dictionary.radius")

    srv = pyrad.client.Client(server="127.0.0.1", acctport=3799,
                              secret="secret", dict=dict)
    srv.retries = 1
    srv.timeout = 1

    logger.info("Disconnect-Request with incorrect secret")
    req = radius_das.DisconnectPacket(dict=dict, secret="incorrect",
                                      User_Name="foo",
                                      NAS_Identifier="localhost",
                                      Event_Timestamp=int(time.time()))
    logger.debug(req)
    try:
        reply = srv.SendPacket(req)
        raise Exception("Unexpected response to Disconnect-Request")
    except pyrad.client.Timeout:
        logger.info("Disconnect-Request with incorrect secret properly ignored")

    logger.info("Disconnect-Request without Event-Timestamp")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      User_Name="psk.user@example.com")
    logger.debug(req)
    try:
        reply = srv.SendPacket(req)
        raise Exception("Unexpected response to Disconnect-Request")
    except pyrad.client.Timeout:
        logger.info("Disconnect-Request without Event-Timestamp properly ignored")

    logger.info("Disconnect-Request with non-matching Event-Timestamp")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      User_Name="psk.user@example.com",
                                      Event_Timestamp=123456789)
    logger.debug(req)
    try:
        reply = srv.SendPacket(req)
        raise Exception("Unexpected response to Disconnect-Request")
    except pyrad.client.Timeout:
        logger.info("Disconnect-Request with non-matching Event-Timestamp properly ignored")

    logger.info("Disconnect-Request with unsupported attribute")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      User_Name="foo",
                                      User_Password="foo",
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectNAK, 401)

    logger.info("Disconnect-Request with invalid Calling-Station-Id")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      User_Name="foo",
                                      Calling_Station_Id="foo",
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectNAK, 407)

    logger.info("Disconnect-Request with mismatching User-Name")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      User_Name="foo",
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectNAK, 503)

    logger.info("Disconnect-Request with mismatching Calling-Station-Id")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      Calling_Station_Id="12:34:56:78:90:aa",
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectNAK, 503)

    logger.info("Disconnect-Request with mismatching Acct-Session-Id")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      Acct_Session_Id="12345678-87654321",
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectNAK, 503)

    logger.info("Disconnect-Request with mismatching Acct-Session-Id (len)")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      Acct_Session_Id="12345678",
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectNAK, 503)

    logger.info("Disconnect-Request with mismatching Acct-Multi-Session-Id")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      Acct_Multi_Session_Id="12345678+87654321",
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectNAK, 503)

    logger.info("Disconnect-Request with mismatching Acct-Multi-Session-Id (len)")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      Acct_Multi_Session_Id="12345678",
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectNAK, 503)

    logger.info("Disconnect-Request with no session identification attributes")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectNAK, 503)

    ev = dev[0].wait_event(["CTRL-EVENT-DISCONNECTED"], timeout=1)
    if ev is not None:
        raise Exception("Unexpected disconnection")

    logger.info("Disconnect-Request with mismatching NAS-IP-Address")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      NAS_IP_Address="192.168.3.4",
                                      Acct_Session_Id=id,
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectNAK, 403)

    logger.info("Disconnect-Request with mismatching NAS-Identifier")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      NAS_Identifier="unknown.example.com",
                                      Acct_Session_Id=id,
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectNAK, 403)

    ev = dev[0].wait_event(["CTRL-EVENT-DISCONNECTED"], timeout=1)
    if ev is not None:
        raise Exception("Unexpected disconnection")

    logger.info("Disconnect-Request with matching Acct-Session-Id")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      NAS_IP_Address="127.0.0.1",
                                      NAS_Identifier="nas.example.com",
                                      Acct_Session_Id=id,
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectACK)

    dev[0].wait_disconnected(timeout=10)
    dev[0].wait_connected(timeout=10, error="Re-connection timed out")

    logger.info("Disconnect-Request with matching Acct-Multi-Session-Id")
    sta = hapd.get_sta(addr)
    multi_sess_id = sta['authMultiSessionId']
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      NAS_IP_Address="127.0.0.1",
                                      NAS_Identifier="nas.example.com",
                                      Acct_Multi_Session_Id=multi_sess_id,
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectACK)

    dev[0].wait_disconnected(timeout=10)
    dev[0].wait_connected(timeout=10, error="Re-connection timed out")

    logger.info("Disconnect-Request with matching User-Name")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      NAS_Identifier="nas.example.com",
                                      User_Name="psk.user@example.com",
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectACK)

    dev[0].wait_disconnected(timeout=10)
    dev[0].wait_connected(timeout=10, error="Re-connection timed out")

    logger.info("Disconnect-Request with matching Calling-Station-Id")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      NAS_IP_Address="127.0.0.1",
                                      Calling_Station_Id=addr,
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectACK)

    dev[0].wait_disconnected(timeout=10)
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-STARTED", "CTRL-EVENT-CONNECTED"])
    if ev is None:
        raise Exception("Timeout while waiting for re-connection")
    if "CTRL-EVENT-EAP-STARTED" not in ev:
        raise Exception("Unexpected skipping of EAP authentication in reconnection")
    dev[0].wait_connected(timeout=10, error="Re-connection timed out")

    logger.info("Disconnect-Request with matching Calling-Station-Id and non-matching CUI")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      Calling_Station_Id=addr,
                                      Chargeable_User_Identity="foo@example.com",
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectNAK, error_cause=503)

    logger.info("Disconnect-Request with matching CUI")
    dev[1].connect("radius-das", key_mgmt="WPA-EAP",
                   eap="GPSK", identity="gpsk-cui",
                   password="abcdefghijklmnop0123456789abcdef",
                   scan_freq="2412")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      Chargeable_User_Identity="gpsk-chargeable-user-identity",
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectACK)

    dev[1].wait_disconnected(timeout=10)
    dev[1].wait_connected(timeout=10, error="Re-connection timed out")

    ev = dev[0].wait_event(["CTRL-EVENT-DISCONNECTED"], timeout=1)
    if ev is not None:
        raise Exception("Unexpected disconnection")

    connect(dev[2], "radius-das")

    logger.info("Disconnect-Request with matching User-Name - multiple sessions matching")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      NAS_Identifier="nas.example.com",
                                      User_Name="psk.user@example.com",
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectNAK, error_cause=508)

    logger.info("Disconnect-Request with User-Name matching multiple sessions, Calling-Station-Id only one")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      NAS_Identifier="nas.example.com",
                                      Calling_Station_Id=addr,
                                      User_Name="psk.user@example.com",
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectACK)

    dev[0].wait_disconnected(timeout=10)
    dev[0].wait_connected(timeout=10, error="Re-connection timed out")

    ev = dev[2].wait_event(["CTRL-EVENT-DISCONNECTED"], timeout=1)
    if ev is not None:
        raise Exception("Unexpected disconnection")

    logger.info("Disconnect-Request with matching Acct-Multi-Session-Id after disassociation")
    sta = hapd.get_sta(addr)
    multi_sess_id = sta['authMultiSessionId']
    dev[0].request("DISCONNECT")
    dev[0].wait_disconnected(timeout=10)
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      NAS_IP_Address="127.0.0.1",
                                      NAS_Identifier="nas.example.com",
                                      Acct_Multi_Session_Id=multi_sess_id,
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectACK)

    dev[0].request("RECONNECT")
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-STARTED"], timeout=15)
    if ev is None:
        raise Exception("Timeout on EAP start")
    dev[0].wait_connected(timeout=15)

    logger.info("Disconnect-Request with matching User-Name after disassociation")
    dev[0].request("DISCONNECT")
    dev[0].wait_disconnected(timeout=10)
    dev[2].request("DISCONNECT")
    dev[2].wait_disconnected(timeout=10)
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      NAS_IP_Address="127.0.0.1",
                                      NAS_Identifier="nas.example.com",
                                      User_Name="psk.user@example.com",
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectACK)

    logger.info("Disconnect-Request with matching CUI after disassociation")
    dev[1].request("DISCONNECT")
    dev[1].wait_disconnected(timeout=10)
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      NAS_IP_Address="127.0.0.1",
                                      NAS_Identifier="nas.example.com",
                                      Chargeable_User_Identity="gpsk-chargeable-user-identity",
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectACK)

    logger.info("Disconnect-Request with matching Calling-Station-Id after disassociation")
    dev[0].request("RECONNECT")
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-STARTED"], timeout=15)
    if ev is None:
        raise Exception("Timeout on EAP start")
    dev[0].wait_connected(timeout=15)
    dev[0].request("DISCONNECT")
    dev[0].wait_disconnected(timeout=10)
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      NAS_IP_Address="127.0.0.1",
                                      NAS_Identifier="nas.example.com",
                                      Calling_Station_Id=addr,
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectACK)

    logger.info("Disconnect-Request with mismatching Calling-Station-Id after disassociation")
    req = radius_das.DisconnectPacket(dict=dict, secret="secret",
                                      NAS_IP_Address="127.0.0.1",
                                      NAS_Identifier="nas.example.com",
                                      Calling_Station_Id=addr,
                                      Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.DisconnectNAK, error_cause=503)

def test_radius_das_coa(dev, apdev):
    """RADIUS Dynamic Authorization Extensions - CoA"""
    try:
        import pyrad.client
        import pyrad.packet
        import pyrad.dictionary
        import radius_das
    except ImportError:
        raise HwsimSkip("No pyrad modules available")

    params = hostapd.wpa2_eap_params(ssid="radius-das")
    params['radius_das_port'] = "3799"
    params['radius_das_client'] = "127.0.0.1 secret"
    params['radius_das_require_event_timestamp'] = "1"
    hapd = hostapd.add_ap(apdev[0], params)
    connect(dev[0], "radius-das")
    addr = dev[0].p2p_interface_addr()
    sta = hapd.get_sta(addr)
    id = sta['dot1xAuthSessionId']

    dict = pyrad.dictionary.Dictionary("dictionary.radius")

    srv = pyrad.client.Client(server="127.0.0.1", acctport=3799,
                              secret="secret", dict=dict)
    srv.retries = 1
    srv.timeout = 1

    # hostapd does not currently support CoA-Request, so NAK is expected
    logger.info("CoA-Request with matching Acct-Session-Id")
    req = radius_das.CoAPacket(dict=dict, secret="secret",
                               Acct_Session_Id=id,
                               Event_Timestamp=int(time.time()))
    send_and_check_reply(srv, req, pyrad.packet.CoANAK, error_cause=405)

def test_radius_ipv6(dev, apdev):
    """RADIUS connection over IPv6"""
    params = {}
    params['ssid'] = 'as'
    params['beacon_int'] = '2000'
    params['radius_server_clients'] = 'auth_serv/radius_clients_ipv6.conf'
    params['radius_server_ipv6'] = '1'
    params['radius_server_auth_port'] = '18129'
    params['radius_server_acct_port'] = '18139'
    params['eap_server'] = '1'
    params['eap_user_file'] = 'auth_serv/eap_user.conf'
    params['ca_cert'] = 'auth_serv/ca.pem'
    params['server_cert'] = 'auth_serv/server.pem'
    params['private_key'] = 'auth_serv/server.key'
    hostapd.add_ap(apdev[1], params)

    params = hostapd.wpa2_eap_params(ssid="radius-ipv6")
    params['auth_server_addr'] = "::0"
    params['auth_server_port'] = "18129"
    params['acct_server_addr'] = "::0"
    params['acct_server_port'] = "18139"
    params['acct_server_shared_secret'] = "radius"
    params['own_ip_addr'] = "::0"
    hostapd.add_ap(apdev[0], params)
    connect(dev[0], "radius-ipv6")

def test_radius_macacl(dev, apdev):
    """RADIUS MAC ACL"""
    params = hostapd.radius_params()
    params["ssid"] = "radius"
    params["macaddr_acl"] = "2"
    hostapd.add_ap(apdev[0], params)
    dev[0].connect("radius", key_mgmt="NONE", scan_freq="2412")

def test_radius_macacl_acct(dev, apdev):
    """RADIUS MAC ACL and accounting enabled"""
    params = hostapd.radius_params()
    params["ssid"] = "radius"
    params["macaddr_acl"] = "2"
    params['acct_server_addr'] = "127.0.0.1"
    params['acct_server_port'] = "1813"
    params['acct_server_shared_secret'] = "radius"
    hostapd.add_ap(apdev[0], params)
    dev[0].connect("radius", key_mgmt="NONE", scan_freq="2412")
    dev[1].connect("radius", key_mgmt="NONE", scan_freq="2412")
    dev[1].request("DISCONNECT")
    dev[1].wait_disconnected()
    dev[1].request("RECONNECT")

def test_radius_failover(dev, apdev):
    """RADIUS Authentication and Accounting server failover"""
    subprocess.call(['ip', 'ro', 'replace', '192.168.213.17', 'dev', 'lo'])
    as_hapd = hostapd.Hostapd("as")
    as_mib_start = as_hapd.get_mib(param="radius_server")
    params = hostapd.wpa2_eap_params(ssid="radius-failover")
    params["auth_server_addr"] = "192.168.213.17"
    params["auth_server_port"] = "1812"
    params["auth_server_shared_secret"] = "testing"
    params['acct_server_addr'] = "192.168.213.17"
    params['acct_server_port'] = "1813"
    params['acct_server_shared_secret'] = "testing"
    params['radius_retry_primary_interval'] = "20"
    hapd = hostapd.add_ap(apdev[0], params, no_enable=True)
    hapd.set("auth_server_addr", "127.0.0.1")
    hapd.set("auth_server_port", "1812")
    hapd.set("auth_server_shared_secret", "radius")
    hapd.set('acct_server_addr', "127.0.0.1")
    hapd.set('acct_server_port', "1813")
    hapd.set('acct_server_shared_secret', "radius")
    hapd.enable()
    ev = hapd.wait_event(["AP-ENABLED", "AP-DISABLED"], timeout=30)
    if ev is None:
        raise Exception("AP startup timed out")
        if "AP-ENABLED" not in ev:
            raise Exception("AP startup failed")
    start = os.times()[4]

    try:
        subprocess.call(['ip', 'ro', 'replace', 'prohibit', '192.168.213.17'])
        dev[0].request("SET EAPOL::authPeriod 5")
        connect(dev[0], "radius-failover", wait_connect=False)
        dev[0].wait_connected(timeout=20)
    finally:
        dev[0].request("SET EAPOL::authPeriod 30")
        subprocess.call(['ip', 'ro', 'del', '192.168.213.17'])

    as_mib_end = as_hapd.get_mib(param="radius_server")
    req_s = int(as_mib_start['radiusAccServTotalRequests'])
    req_e = int(as_mib_end['radiusAccServTotalRequests'])
    if req_e <= req_s:
        raise Exception("Unexpected RADIUS server acct MIB value")

    end = os.times()[4]
    try:
        subprocess.call(['ip', 'ro', 'replace', 'prohibit', '192.168.213.17'])
        dev[1].request("SET EAPOL::authPeriod 5")
        if end - start < 21:
            time.sleep(21 - (end - start))
        connect(dev[1], "radius-failover", wait_connect=False)
        dev[1].wait_connected(timeout=20)
    finally:
        dev[1].request("SET EAPOL::authPeriod 30")
        subprocess.call(['ip', 'ro', 'del', '192.168.213.17'])

def run_pyrad_server(srv, t_events):
    srv.RunWithStop(t_events)

def test_radius_protocol(dev, apdev):
    """RADIUS Authentication protocol tests with a fake server"""
    try:
        import pyrad.server
        import pyrad.packet
        import pyrad.dictionary
    except ImportError:
        raise HwsimSkip("No pyrad modules available")

    class TestServer(pyrad.server.Server):
        def _HandleAuthPacket(self, pkt):
            pyrad.server.Server._HandleAuthPacket(self, pkt)
            logger.info("Received authentication request")
            reply = self.CreateReplyPacket(pkt)
            reply.code = pyrad.packet.AccessAccept
            if self.t_events['msg_auth'].is_set():
                logger.info("Add Message-Authenticator")
                if self.t_events['wrong_secret'].is_set():
                    logger.info("Use incorrect RADIUS shared secret")
                    pw = "incorrect"
                else:
                    pw = reply.secret
                hmac_obj = hmac.new(pw)
                hmac_obj.update(struct.pack("B", reply.code))
                hmac_obj.update(struct.pack("B", reply.id))

                # reply attributes
                reply.AddAttribute("Message-Authenticator",
                                   "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00")
                attrs = reply._PktEncodeAttributes()

                # Length
                flen = 4 + 16 + len(attrs)
                hmac_obj.update(struct.pack(">H", flen))
                hmac_obj.update(pkt.authenticator)
                hmac_obj.update(attrs)
                if self.t_events['double_msg_auth'].is_set():
                    logger.info("Include two Message-Authenticator attributes")
                else:
                    del reply[80]
                reply.AddAttribute("Message-Authenticator", hmac_obj.digest())
            self.SendReplyPacket(pkt.fd, reply)

        def RunWithStop(self, t_events):
            self._poll = select.poll()
            self._fdmap = {}
            self._PrepareSockets()
            self.t_events = t_events

            while not t_events['stop'].is_set():
                for (fd, event) in self._poll.poll(1000):
                    if event == select.POLLIN:
                        try:
                            fdo = self._fdmap[fd]
                            self._ProcessInput(fdo)
                        except pyrad.server.ServerPacketError as err:
                            logger.info("pyrad server dropping packet: " + str(err))
                        except pyrad.packet.PacketError as err:
                            logger.info("pyrad server received invalid packet: " + str(err))
                    else:
                        logger.error("Unexpected event in pyrad server main loop")

    srv = TestServer(dict=pyrad.dictionary.Dictionary("dictionary.radius"),
                     authport=18138, acctport=18139)
    srv.hosts["127.0.0.1"] = pyrad.server.RemoteHost("127.0.0.1",
                                                     "radius",
                                                     "localhost")
    srv.BindToAddress("")
    t_events = {}
    t_events['stop'] = threading.Event()
    t_events['msg_auth'] = threading.Event()
    t_events['wrong_secret'] = threading.Event()
    t_events['double_msg_auth'] = threading.Event()
    t = threading.Thread(target=run_pyrad_server, args=(srv, t_events))
    t.start()

    try:
        params = hostapd.wpa2_eap_params(ssid="radius-test")
        params['auth_server_port'] = "18138"
        hapd = hostapd.add_ap(apdev[0], params)
        connect(dev[0], "radius-test", wait_connect=False)
        ev = dev[0].wait_event(["CTRL-EVENT-EAP-STARTED"], timeout=15)
        if ev is None:
            raise Exception("Timeout on EAP start")
        time.sleep(1)
        dev[0].request("REMOVE_NETWORK all")
        time.sleep(0.1)
        dev[0].dump_monitor()
        t_events['msg_auth'].set()
        t_events['wrong_secret'].set()
        connect(dev[0], "radius-test", wait_connect=False)
        time.sleep(1)
        dev[0].request("REMOVE_NETWORK all")
        time.sleep(0.1)
        dev[0].dump_monitor()
        t_events['wrong_secret'].clear()
        connect(dev[0], "radius-test", wait_connect=False)
        time.sleep(1)
        dev[0].request("REMOVE_NETWORK all")
        time.sleep(0.1)
        dev[0].dump_monitor()
        t_events['double_msg_auth'].set()
        connect(dev[0], "radius-test", wait_connect=False)
        time.sleep(1)
    finally:
        t_events['stop'].set()
        t.join()

def test_radius_psk(dev, apdev):
    """WPA2 with PSK from RADIUS"""
    try:
        import pyrad.server
        import pyrad.packet
        import pyrad.dictionary
    except ImportError:
        raise HwsimSkip("No pyrad modules available")

    class TestServer(pyrad.server.Server):
        def _HandleAuthPacket(self, pkt):
            pyrad.server.Server._HandleAuthPacket(self, pkt)
            logger.info("Received authentication request")
            reply = self.CreateReplyPacket(pkt)
            reply.code = pyrad.packet.AccessAccept
            a = "\xab\xcd"
            secret = reply.secret
            if self.t_events['long'].is_set():
                p = b'\x10' + "0123456789abcdef" + 15 * b'\x00'
                b = hashlib.md5(secret + pkt.authenticator + a).digest()
                pp = bytearray(p[0:16])
                bb = bytearray(b)
                cc = bytearray(pp[i] ^ bb[i] for i in range(len(bb)))

                b = hashlib.md5(reply.secret + bytes(cc)).digest()
                pp = bytearray(p[16:32])
                bb = bytearray(b)
                cc += bytearray(pp[i] ^ bb[i] for i in range(len(bb)))

                data = '\x00' + a + bytes(cc)
            else:
                p = b'\x08' + "12345678" + 7 * b'\x00'
                b = hashlib.md5(secret + pkt.authenticator + a).digest()
                pp = bytearray(p)
                bb = bytearray(b)
                cc = bytearray(pp[i] ^ bb[i] for i in range(len(bb)))
                data = '\x00' + a + bytes(cc)
            reply.AddAttribute("Tunnel-Password", data)
            self.SendReplyPacket(pkt.fd, reply)

        def RunWithStop(self, t_events):
            self._poll = select.poll()
            self._fdmap = {}
            self._PrepareSockets()
            self.t_events = t_events

            while not t_events['stop'].is_set():
                for (fd, event) in self._poll.poll(1000):
                    if event == select.POLLIN:
                        try:
                            fdo = self._fdmap[fd]
                            self._ProcessInput(fdo)
                        except pyrad.server.ServerPacketError as err:
                            logger.info("pyrad server dropping packet: " + str(err))
                        except pyrad.packet.PacketError as err:
                            logger.info("pyrad server received invalid packet: " + str(err))
                    else:
                        logger.error("Unexpected event in pyrad server main loop")

    srv = TestServer(dict=pyrad.dictionary.Dictionary("dictionary.radius"),
                     authport=18138, acctport=18139)
    srv.hosts["127.0.0.1"] = pyrad.server.RemoteHost("127.0.0.1",
                                                     "radius",
                                                     "localhost")
    srv.BindToAddress("")
    t_events = {}
    t_events['stop'] = threading.Event()
    t_events['long'] = threading.Event()
    t = threading.Thread(target=run_pyrad_server, args=(srv, t_events))
    t.start()

    try:
        ssid = "test-wpa2-psk"
        params = hostapd.radius_params()
        params['ssid'] = ssid
        params["wpa"] = "2"
        params["wpa_key_mgmt"] = "WPA-PSK"
        params["rsn_pairwise"] = "CCMP"
        params['macaddr_acl'] = '2'
        params['wpa_psk_radius'] = '2'
        params['auth_server_port'] = "18138"
        hapd = hostapd.add_ap(apdev[0], params)
        dev[0].connect(ssid, psk="12345678", scan_freq="2412")
        t_events['long'].set()
        dev[1].connect(ssid, psk="0123456789abcdef", scan_freq="2412")
    finally:
        t_events['stop'].set()
        t.join()

def test_radius_psk_invalid(dev, apdev):
    """WPA2 with invalid PSK from RADIUS"""
    try:
        import pyrad.server
        import pyrad.packet
        import pyrad.dictionary
    except ImportError:
        raise HwsimSkip("No pyrad modules available")

    class TestServer(pyrad.server.Server):
        def _HandleAuthPacket(self, pkt):
            pyrad.server.Server._HandleAuthPacket(self, pkt)
            logger.info("Received authentication request")
            reply = self.CreateReplyPacket(pkt)
            reply.code = pyrad.packet.AccessAccept
            a = "\xab\xcd"
            secret = reply.secret
            p = b'\x07' + "1234567" + 8 * b'\x00'
            b = hashlib.md5(secret + pkt.authenticator + a).digest()
            pp = bytearray(p)
            bb = bytearray(b)
            cc = bytearray(pp[i] ^ bb[i] for i in range(len(bb)))
            data = '\x00' + a + bytes(cc)
            reply.AddAttribute("Tunnel-Password", data)
            self.SendReplyPacket(pkt.fd, reply)

        def RunWithStop(self, t_events):
            self._poll = select.poll()
            self._fdmap = {}
            self._PrepareSockets()
            self.t_events = t_events

            while not t_events['stop'].is_set():
                for (fd, event) in self._poll.poll(1000):
                    if event == select.POLLIN:
                        try:
                            fdo = self._fdmap[fd]
                            self._ProcessInput(fdo)
                        except pyrad.server.ServerPacketError as err:
                            logger.info("pyrad server dropping packet: " + str(err))
                        except pyrad.packet.PacketError as err:
                            logger.info("pyrad server received invalid packet: " + str(err))
                    else:
                        logger.error("Unexpected event in pyrad server main loop")

    srv = TestServer(dict=pyrad.dictionary.Dictionary("dictionary.radius"),
                     authport=18138, acctport=18139)
    srv.hosts["127.0.0.1"] = pyrad.server.RemoteHost("127.0.0.1",
                                                     "radius",
                                                     "localhost")
    srv.BindToAddress("")
    t_events = {}
    t_events['stop'] = threading.Event()
    t = threading.Thread(target=run_pyrad_server, args=(srv, t_events))
    t.start()

    try:
        ssid = "test-wpa2-psk"
        params = hostapd.radius_params()
        params['ssid'] = ssid
        params["wpa"] = "2"
        params["wpa_key_mgmt"] = "WPA-PSK"
        params["rsn_pairwise"] = "CCMP"
        params['macaddr_acl'] = '2'
        params['wpa_psk_radius'] = '2'
        params['auth_server_port'] = "18138"
        hapd = hostapd.add_ap(apdev[0], params)
        dev[0].connect(ssid, psk="12345678", scan_freq="2412",
                       wait_connect=False)
        time.sleep(1)
    finally:
        t_events['stop'].set()
        t.join()

def test_radius_auth_force_client_addr(dev, apdev):
    """RADIUS client address specified"""
    params = hostapd.wpa2_eap_params(ssid="radius-auth")
    params['radius_client_addr'] = "127.0.0.1"
    hapd = hostapd.add_ap(apdev[0], params)
    connect(dev[0], "radius-auth")

@remote_compatible
def test_radius_auth_force_invalid_client_addr(dev, apdev):
    """RADIUS client address specified and invalid address"""
    params = hostapd.wpa2_eap_params(ssid="radius-auth")
    #params['radius_client_addr'] = "10.11.12.14"
    params['radius_client_addr'] = "1::2"
    hapd = hostapd.add_ap(apdev[0], params)
    connect(dev[0], "radius-auth", wait_connect=False)
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-STARTED"])
    if ev is None:
        raise Exception("Timeout on EAP start")
    ev = dev[0].wait_event(["CTRL-EVENT-CONNECTED"], timeout=1)
    if ev is not None:
        raise Exception("Unexpected connection")

def add_message_auth(req):
    req.authenticator = req.CreateAuthenticator()
    hmac_obj = hmac.new(req.secret)
    hmac_obj.update(struct.pack("B", req.code))
    hmac_obj.update(struct.pack("B", req.id))

    # request attributes
    req.AddAttribute("Message-Authenticator",
                     "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00")
    attrs = req._PktEncodeAttributes()

    # Length
    flen = 4 + 16 + len(attrs)
    hmac_obj.update(struct.pack(">H", flen))
    hmac_obj.update(req.authenticator)
    hmac_obj.update(attrs)
    del req[80]
    req.AddAttribute("Message-Authenticator", hmac_obj.digest())

def test_radius_server_failures(dev, apdev):
    """RADIUS server failure cases"""
    try:
        import pyrad.client
        import pyrad.packet
        import pyrad.dictionary
    except ImportError:
        raise HwsimSkip("No pyrad modules available")

    dict = pyrad.dictionary.Dictionary("dictionary.radius")
    client = pyrad.client.Client(server="127.0.0.1", authport=1812,
                                 secret="radius", dict=dict)
    client.retries = 1
    client.timeout = 1

    # unexpected State
    req = client.CreateAuthPacket(code=pyrad.packet.AccessRequest,
                                  User_Name="foo")
    req['State'] = 'foo-state'
    add_message_auth(req)
    reply = client.SendPacket(req)
    if reply.code != pyrad.packet.AccessReject:
        raise Exception("Unexpected RADIUS response code " + str(reply.code))

    # no EAP-Message
    req = client.CreateAuthPacket(code=pyrad.packet.AccessRequest,
                                  User_Name="foo")
    add_message_auth(req)
    try:
        reply = client.SendPacket(req)
        raise Exception("Unexpected response")
    except pyrad.client.Timeout:
        pass

def test_ap_vlan_wpa2_psk_radius_required(dev, apdev):
    """AP VLAN with WPA2-PSK and RADIUS attributes required"""
    try:
        import pyrad.server
        import pyrad.packet
        import pyrad.dictionary
    except ImportError:
        raise HwsimSkip("No pyrad modules available")

    class TestServer(pyrad.server.Server):
        def _HandleAuthPacket(self, pkt):
            pyrad.server.Server._HandleAuthPacket(self, pkt)
            logger.info("Received authentication request")
            reply = self.CreateReplyPacket(pkt)
            reply.code = pyrad.packet.AccessAccept
            secret = reply.secret
            if self.t_events['extra'].is_set():
                reply.AddAttribute("Chargeable-User-Identity", "test-cui")
                reply.AddAttribute("User-Name", "test-user")
            if self.t_events['long'].is_set():
                reply.AddAttribute("Tunnel-Type", 13)
                reply.AddAttribute("Tunnel-Medium-Type", 6)
                reply.AddAttribute("Tunnel-Private-Group-ID", "1")
            self.SendReplyPacket(pkt.fd, reply)

        def RunWithStop(self, t_events):
            self._poll = select.poll()
            self._fdmap = {}
            self._PrepareSockets()
            self.t_events = t_events

            while not t_events['stop'].is_set():
                for (fd, event) in self._poll.poll(1000):
                    if event == select.POLLIN:
                        try:
                            fdo = self._fdmap[fd]
                            self._ProcessInput(fdo)
                        except pyrad.server.ServerPacketError as err:
                            logger.info("pyrad server dropping packet: " + str(err))
                        except pyrad.packet.PacketError as err:
                            logger.info("pyrad server received invalid packet: " + str(err))
                    else:
                        logger.error("Unexpected event in pyrad server main loop")

    srv = TestServer(dict=pyrad.dictionary.Dictionary("dictionary.radius"),
                     authport=18138, acctport=18139)
    srv.hosts["127.0.0.1"] = pyrad.server.RemoteHost("127.0.0.1",
                                                     "radius",
                                                     "localhost")
    srv.BindToAddress("")
    t_events = {}
    t_events['stop'] = threading.Event()
    t_events['long'] = threading.Event()
    t_events['extra'] = threading.Event()
    t = threading.Thread(target=run_pyrad_server, args=(srv, t_events))
    t.start()

    try:
        ssid = "test-wpa2-psk"
        params = hostapd.radius_params()
        params['ssid'] = ssid
        params["wpa"] = "2"
        params["wpa_key_mgmt"] = "WPA-PSK"
        params["rsn_pairwise"] = "CCMP"
        params['macaddr_acl'] = '2'
        params['dynamic_vlan'] = "2"
        params['wpa_passphrase'] = '0123456789abcdefghi'
        params['auth_server_port'] = "18138"
        hapd = hostapd.add_ap(apdev[0], params)

        logger.info("connecting without VLAN")
        dev[0].connect(ssid, psk="0123456789abcdefghi", scan_freq="2412",
                       wait_connect=False)
        ev = dev[0].wait_event(["CTRL-EVENT-CONNECTED",
                                "CTRL-EVENT-SSID-TEMP-DISABLED"], timeout=20)
        if ev is None:
            raise Exception("Timeout on connection attempt")
        if "CTRL-EVENT-CONNECTED" in ev:
            raise Exception("Unexpected success without vlan parameters")
        logger.info("connecting without VLAN failed as expected")

        logger.info("connecting without VLAN (CUI/User-Name)")
        t_events['extra'].set()
        dev[1].connect(ssid, psk="0123456789abcdefghi", scan_freq="2412",
                       wait_connect=False)
        ev = dev[1].wait_event(["CTRL-EVENT-CONNECTED",
                                "CTRL-EVENT-SSID-TEMP-DISABLED"], timeout=20)
        if ev is None:
            raise Exception("Timeout on connection attempt")
        if "CTRL-EVENT-CONNECTED" in ev:
            raise Exception("Unexpected success without vlan parameters(2)")
        logger.info("connecting without VLAN failed as expected(2)")
        t_events['extra'].clear()

        t_events['long'].set()
        logger.info("connecting with VLAN")
        dev[2].connect(ssid, psk="0123456789abcdefghi", scan_freq="2412",
                       wait_connect=False)
        ev = dev[2].wait_event(["CTRL-EVENT-CONNECTED",
                                "CTRL-EVENT-SSID-TEMP-DISABLED"], timeout=20)
        if ev is None:
            raise Exception("Timeout on connection attempt")
        if "CTRL-EVENT-SSID-TEMP-DISABLED" in ev:
            raise Exception("Unexpected failure with vlan parameters")
        logger.info("connecting with VLAN succeeded as expected")
    finally:
        t_events['stop'].set()
        t.join()

def test_radius_mppe_failure(dev, apdev):
    """RADIUS failure when adding MPPE keys"""
    params = { "ssid": "as", "beacon_int": "2000",
               "radius_server_clients": "auth_serv/radius_clients.conf",
               "radius_server_auth_port": '18127',
               "eap_server": "1",
               "eap_user_file": "auth_serv/eap_user.conf",
               "ca_cert": "auth_serv/ca.pem",
               "server_cert": "auth_serv/server.pem",
               "private_key": "auth_serv/server.key" }
    authsrv = hostapd.add_ap(apdev[1], params)

    params = hostapd.wpa2_eap_params(ssid="test-wpa2-eap")
    params['auth_server_port'] = "18127"
    hapd = hostapd.add_ap(apdev[0], params)

    with fail_test(authsrv, 1, "os_get_random;radius_msg_add_mppe_keys"):
        dev[0].connect("test-wpa2-eap", key_mgmt="WPA-EAP", eap="TTLS",
                       identity="user", anonymous_identity="ttls",
                       password="password",
                       ca_cert="auth_serv/ca.pem", phase2="autheap=GTC",
                       wait_connect=False, scan_freq="2412")
        dev[0].wait_disconnected()
        dev[0].request("REMOVE_NETWORK all")
