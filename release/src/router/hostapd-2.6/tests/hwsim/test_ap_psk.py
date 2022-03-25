# WPA2-Personal tests
# Copyright (c) 2014, Qualcomm Atheros, Inc.
#
# This software may be distributed under the terms of the BSD license.
# See README for more details.

from remotehost import remote_compatible
import binascii
from Crypto.Cipher import AES
import hashlib
import hmac
import logging
logger = logging.getLogger()
import os
import re
import struct
import subprocess
import time

import hostapd
from utils import HwsimSkip, fail_test, skip_with_fips
import hwsim_utils
from wpasupplicant import WpaSupplicant

def check_mib(dev, vals):
    mib = dev.get_mib()
    for v in vals:
        if mib[v[0]] != v[1]:
            raise Exception("Unexpected {} = {} (expected {})".format(v[0], mib[v[0]], v[1]))

@remote_compatible
def test_ap_wpa2_psk(dev, apdev):
    """WPA2-PSK AP with PSK instead of passphrase"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    psk = '602e323e077bc63bd80307ef4745b754b0ae0a925c2638ecd13a794b9527b9e6'
    params = hostapd.wpa2_params(ssid=ssid)
    params['wpa_psk'] = psk
    hapd = hostapd.add_ap(apdev[0], params)
    key_mgmt = hapd.get_config()['key_mgmt']
    if key_mgmt.split(' ')[0] != "WPA-PSK":
        raise Exception("Unexpected GET_CONFIG(key_mgmt): " + key_mgmt)
    dev[0].connect(ssid, raw_psk=psk, scan_freq="2412")
    dev[1].connect(ssid, psk=passphrase, scan_freq="2412")

    sig = dev[0].request("SIGNAL_POLL").splitlines()
    pkt = dev[0].request("PKTCNT_POLL").splitlines()
    if "FREQUENCY=2412" not in sig:
        raise Exception("Unexpected SIGNAL_POLL value: " + str(sig))
    if "TXBAD=0" not in pkt:
        raise Exception("Unexpected TXBAD value: " + str(pkt))

def test_ap_wpa2_psk_file(dev, apdev):
    """WPA2-PSK AP with PSK from a file"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    psk = '602e323e077bc63bd80307ef4745b754b0ae0a925c2638ecd13a794b9527b9e6'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    params['wpa_psk_file'] = 'hostapd.wpa_psk'
    hostapd.add_ap(apdev[0], params)
    dev[1].connect(ssid, psk="very secret", scan_freq="2412", wait_connect=False)
    dev[2].connect(ssid, raw_psk=psk, scan_freq="2412")
    dev[2].request("REMOVE_NETWORK all")
    dev[0].connect(ssid, psk="very secret", scan_freq="2412")
    dev[0].request("REMOVE_NETWORK all")
    dev[2].connect(ssid, psk="another passphrase for all STAs", scan_freq="2412")
    dev[0].connect(ssid, psk="another passphrase for all STAs", scan_freq="2412")
    ev = dev[1].wait_event(["WPA: 4-Way Handshake failed"], timeout=10)
    if ev is None:
        raise Exception("Timed out while waiting for failure report")
    dev[1].request("REMOVE_NETWORK all")

@remote_compatible
def test_ap_wpa2_psk_mem(dev, apdev):
    """WPA2-PSK AP with passphrase only in memory"""
    try:
        _test_ap_wpa2_psk_mem(dev, apdev)
    finally:
        dev[0].request("SCAN_INTERVAL 5")
        dev[1].request("SCAN_INTERVAL 5")

def _test_ap_wpa2_psk_mem(dev, apdev):
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    psk = '602e323e077bc63bd80307ef4745b754b0ae0a925c2638ecd13a794b9527b9e6'
    params = hostapd.wpa2_params(ssid=ssid)
    params['wpa_psk'] = psk
    hapd = hostapd.add_ap(apdev[0], params)

    dev[0].connect(ssid, mem_only_psk="1", scan_freq="2412", wait_connect=False)
    dev[0].request("SCAN_INTERVAL 1")
    ev = dev[0].wait_event(["CTRL-REQ-PSK_PASSPHRASE"], timeout=10)
    if ev is None:
        raise Exception("Request for PSK/passphrase timed out")
    id = ev.split(':')[0].split('-')[-1]
    dev[0].request("CTRL-RSP-PSK_PASSPHRASE-" + id + ':"' + passphrase + '"')
    dev[0].wait_connected(timeout=10)

    dev[1].connect(ssid, mem_only_psk="1", scan_freq="2412", wait_connect=False)
    dev[1].request("SCAN_INTERVAL 1")
    ev = dev[1].wait_event(["CTRL-REQ-PSK_PASSPHRASE"], timeout=10)
    if ev is None:
        raise Exception("Request for PSK/passphrase timed out(2)")
    id = ev.split(':')[0].split('-')[-1]
    dev[1].request("CTRL-RSP-PSK_PASSPHRASE-" + id + ':' + psk)
    dev[1].wait_connected(timeout=10)

@remote_compatible
def test_ap_wpa2_ptk_rekey(dev, apdev):
    """WPA2-PSK AP and PTK rekey enforced by station"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk=passphrase, wpa_ptk_rekey="1", scan_freq="2412")
    ev = dev[0].wait_event(["WPA: Key negotiation completed"])
    if ev is None:
        raise Exception("PTK rekey timed out")
    hwsim_utils.test_connectivity(dev[0], hapd)

@remote_compatible
def test_ap_wpa2_ptk_rekey_ap(dev, apdev):
    """WPA2-PSK AP and PTK rekey enforced by AP"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    params['wpa_ptk_rekey'] = '2'
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
    ev = dev[0].wait_event(["WPA: Key negotiation completed"])
    if ev is None:
        raise Exception("PTK rekey timed out")
    hwsim_utils.test_connectivity(dev[0], hapd)

@remote_compatible
def test_ap_wpa2_sha256_ptk_rekey(dev, apdev):
    """WPA2-PSK/SHA256 AKM AP and PTK rekey enforced by station"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    params["wpa_key_mgmt"] = "WPA-PSK-SHA256"
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk=passphrase, key_mgmt="WPA-PSK-SHA256",
                   wpa_ptk_rekey="1", scan_freq="2412")
    ev = dev[0].wait_event(["WPA: Key negotiation completed"])
    if ev is None:
        raise Exception("PTK rekey timed out")
    hwsim_utils.test_connectivity(dev[0], hapd)
    check_mib(dev[0], [ ("dot11RSNAAuthenticationSuiteRequested", "00-0f-ac-6"),
                        ("dot11RSNAAuthenticationSuiteSelected", "00-0f-ac-6") ])

@remote_compatible
def test_ap_wpa2_sha256_ptk_rekey_ap(dev, apdev):
    """WPA2-PSK/SHA256 AKM AP and PTK rekey enforced by AP"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    params["wpa_key_mgmt"] = "WPA-PSK-SHA256"
    params['wpa_ptk_rekey'] = '2'
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk=passphrase, key_mgmt="WPA-PSK-SHA256",
                   scan_freq="2412")
    ev = dev[0].wait_event(["WPA: Key negotiation completed"])
    if ev is None:
        raise Exception("PTK rekey timed out")
    hwsim_utils.test_connectivity(dev[0], hapd)
    check_mib(dev[0], [ ("dot11RSNAAuthenticationSuiteRequested", "00-0f-ac-6"),
                        ("dot11RSNAAuthenticationSuiteSelected", "00-0f-ac-6") ])

@remote_compatible
def test_ap_wpa_ptk_rekey(dev, apdev):
    """WPA-PSK/TKIP AP and PTK rekey enforced by station"""
    skip_with_fips(dev[0])
    ssid = "test-wpa-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa_params(ssid=ssid, passphrase=passphrase)
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk=passphrase, wpa_ptk_rekey="1", scan_freq="2412")
    if "[WPA-PSK-TKIP]" not in dev[0].request("SCAN_RESULTS"):
        raise Exception("Scan results missing WPA element info")
    ev = dev[0].wait_event(["WPA: Key negotiation completed"])
    if ev is None:
        raise Exception("PTK rekey timed out")
    hwsim_utils.test_connectivity(dev[0], hapd)

@remote_compatible
def test_ap_wpa_ptk_rekey_ap(dev, apdev):
    """WPA-PSK/TKIP AP and PTK rekey enforced by AP"""
    skip_with_fips(dev[0])
    ssid = "test-wpa-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa_params(ssid=ssid, passphrase=passphrase)
    params['wpa_ptk_rekey'] = '2'
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
    ev = dev[0].wait_event(["WPA: Key negotiation completed"], timeout=10)
    if ev is None:
        raise Exception("PTK rekey timed out")
    hwsim_utils.test_connectivity(dev[0], hapd)

@remote_compatible
def test_ap_wpa_ccmp(dev, apdev):
    """WPA-PSK/CCMP"""
    ssid = "test-wpa-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa_params(ssid=ssid, passphrase=passphrase)
    params['wpa_pairwise'] = "CCMP"
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
    hwsim_utils.test_connectivity(dev[0], hapd)
    check_mib(dev[0], [ ("dot11RSNAConfigGroupCipherSize", "128"),
                        ("dot11RSNAGroupCipherRequested", "00-50-f2-4"),
                        ("dot11RSNAPairwiseCipherRequested", "00-50-f2-4"),
                        ("dot11RSNAAuthenticationSuiteRequested", "00-50-f2-2"),
                        ("dot11RSNAGroupCipherSelected", "00-50-f2-4"),
                        ("dot11RSNAPairwiseCipherSelected", "00-50-f2-4"),
                        ("dot11RSNAAuthenticationSuiteSelected", "00-50-f2-2"),
                        ("dot1xSuppSuppControlledPortStatus", "Authorized") ])

def test_ap_wpa2_psk_file(dev, apdev):
    """WPA2-PSK AP with various PSK file error and success cases"""
    addr0 = dev[0].own_addr()
    addr1 = dev[1].own_addr()
    addr2 = dev[2].own_addr()
    ssid = "psk"
    pskfile = "/tmp/ap_wpa2_psk_file_errors.psk_file"
    try:
        os.remove(pskfile)
    except:
        pass

    params = { "ssid": ssid, "wpa": "2", "wpa_key_mgmt": "WPA-PSK",
               "rsn_pairwise": "CCMP", "wpa_psk_file": pskfile }

    try:
        # missing PSK file
        hapd = hostapd.add_ap(apdev[0], params, no_enable=True)
        if "FAIL" not in hapd.request("ENABLE"):
            raise Exception("Unexpected ENABLE success")
        hapd.request("DISABLE")

        # invalid MAC address
        with open(pskfile, "w") as f:
            f.write("\n")
            f.write("foo\n")
        if "FAIL" not in hapd.request("ENABLE"):
            raise Exception("Unexpected ENABLE success")
        hapd.request("DISABLE")

        # no PSK on line
        with open(pskfile, "w") as f:
            f.write("00:11:22:33:44:55\n")
        if "FAIL" not in hapd.request("ENABLE"):
            raise Exception("Unexpected ENABLE success")
        hapd.request("DISABLE")

        # invalid PSK
        with open(pskfile, "w") as f:
            f.write("00:11:22:33:44:55 1234567\n")
        if "FAIL" not in hapd.request("ENABLE"):
            raise Exception("Unexpected ENABLE success")
        hapd.request("DISABLE")

        # valid PSK file
        with open(pskfile, "w") as f:
            f.write("00:11:22:33:44:55 12345678\n")
            f.write(addr0 + " 123456789\n")
            f.write(addr1 + " 123456789a\n")
            f.write(addr2 + " 0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef\n")
        if "FAIL" in hapd.request("ENABLE"):
            raise Exception("Unexpected ENABLE failure")

        dev[0].connect(ssid, psk="123456789", scan_freq="2412")
        dev[1].connect(ssid, psk="123456789a", scan_freq="2412")
        dev[2].connect(ssid, raw_psk="0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef", scan_freq="2412")

    finally:
        try:
            os.remove(pskfile)
        except:
            pass

@remote_compatible
def test_ap_wpa2_psk_wildcard_ssid(dev, apdev):
    """WPA2-PSK AP and wildcard SSID configuration"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    psk = '602e323e077bc63bd80307ef4745b754b0ae0a925c2638ecd13a794b9527b9e6'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect("", bssid=apdev[0]['bssid'], psk=passphrase,
                   scan_freq="2412")
    dev[1].connect("", bssid=apdev[0]['bssid'], raw_psk=psk, scan_freq="2412")

@remote_compatible
def test_ap_wpa2_gtk_rekey(dev, apdev):
    """WPA2-PSK AP and GTK rekey enforced by AP"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    params['wpa_group_rekey'] = '1'
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
    ev = dev[0].wait_event(["WPA: Group rekeying completed"], timeout=2)
    if ev is None:
        raise Exception("GTK rekey timed out")
    hwsim_utils.test_connectivity(dev[0], hapd)

@remote_compatible
def test_ap_wpa_gtk_rekey(dev, apdev):
    """WPA-PSK/TKIP AP and GTK rekey enforced by AP"""
    skip_with_fips(dev[0])
    ssid = "test-wpa-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa_params(ssid=ssid, passphrase=passphrase)
    params['wpa_group_rekey'] = '1'
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
    ev = dev[0].wait_event(["WPA: Group rekeying completed"], timeout=2)
    if ev is None:
        raise Exception("GTK rekey timed out")
    hwsim_utils.test_connectivity(dev[0], hapd)

@remote_compatible
def test_ap_wpa2_gmk_rekey(dev, apdev):
    """WPA2-PSK AP and GMK and GTK rekey enforced by AP"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    params['wpa_group_rekey'] = '1'
    params['wpa_gmk_rekey'] = '2'
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
    for i in range(0, 3):
        ev = dev[0].wait_event(["WPA: Group rekeying completed"], timeout=2)
        if ev is None:
            raise Exception("GTK rekey timed out")
    hwsim_utils.test_connectivity(dev[0], hapd)

@remote_compatible
def test_ap_wpa2_strict_rekey(dev, apdev):
    """WPA2-PSK AP and strict GTK rekey enforced by AP"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    params['wpa_strict_rekey'] = '1'
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
    dev[1].connect(ssid, psk=passphrase, scan_freq="2412")
    dev[1].request("DISCONNECT")
    ev = dev[0].wait_event(["WPA: Group rekeying completed"], timeout=2)
    if ev is None:
        raise Exception("GTK rekey timed out")
    hwsim_utils.test_connectivity(dev[0], hapd)

@remote_compatible
def test_ap_wpa2_bridge_fdb(dev, apdev):
    """Bridge FDB entry removal"""
    hapd = None
    try:
        ssid = "test-wpa2-psk"
        passphrase = "12345678"
        params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
        params['bridge'] = 'ap-br0'
        hapd = hostapd.add_ap(apdev[0], params)
        hapd.cmd_execute(['brctl', 'setfd', 'ap-br0', '0'])
        hapd.cmd_execute(['ip', 'link', 'set', 'dev', 'ap-br0', 'up'])
        dev[0].connect(ssid, psk=passphrase, scan_freq="2412",
                       bssid=apdev[0]['bssid'])
        dev[1].connect(ssid, psk=passphrase, scan_freq="2412",
                       bssid=apdev[0]['bssid'])
        addr0 = dev[0].p2p_interface_addr()
        hwsim_utils.test_connectivity_sta(dev[0], dev[1])
        err, macs1 = hapd.cmd_execute(['brctl', 'showmacs', 'ap-br0'])
        hapd.cmd_execute(['brctl', 'setageing', 'ap-br0', '1'])
        dev[0].request("DISCONNECT")
        dev[1].request("DISCONNECT")
        time.sleep(1)
        err, macs2 = hapd.cmd_execute(['brctl', 'showmacs', 'ap-br0'])

        addr1 = dev[1].p2p_interface_addr()
        if addr0 not in macs1 or addr1 not in macs1:
            raise Exception("Bridge FDB entry missing")
        if addr0 in macs2 or addr1 in macs2:
            raise Exception("Bridge FDB entry was not removed")
    finally:
        hostapd.cmd_execute(apdev[0], ['ip', 'link', 'set', 'dev', 'ap-br0',
                                       'down'])
        hostapd.cmd_execute(apdev[0], ['brctl', 'delbr', 'ap-br0'])

@remote_compatible
def test_ap_wpa2_already_in_bridge(dev, apdev):
    """hostapd behavior with interface already in bridge"""
    ifname = apdev[0]['ifname']
    br_ifname = 'ext-ap-br0'
    try:
        ssid = "test-wpa2-psk"
        passphrase = "12345678"
        hostapd.cmd_execute(apdev[0], ['brctl', 'addbr', br_ifname])
        hostapd.cmd_execute(apdev[0], ['brctl', 'setfd', br_ifname, '0'])
        hostapd.cmd_execute(apdev[0], ['ip', 'link', 'set', 'dev', br_ifname,
                                       'up'])
        hostapd.cmd_execute(apdev[0], ['iw', ifname, 'set', 'type', '__ap'])
        hostapd.cmd_execute(apdev[0], ['brctl', 'addif', br_ifname, ifname])
        params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
        hapd = hostapd.add_ap(apdev[0], params)
        if hapd.get_driver_status_field('brname') != br_ifname:
            raise Exception("Bridge name not identified correctly")
        dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
    finally:
        hostapd.cmd_execute(apdev[0], ['ip', 'link', 'set', 'dev', br_ifname,
                                       'down'])
        hostapd.cmd_execute(apdev[0], ['brctl', 'delif', br_ifname, ifname])
        hostapd.cmd_execute(apdev[0], ['iw', ifname, 'set', 'type', 'station'])
        hostapd.cmd_execute(apdev[0], ['brctl', 'delbr', br_ifname])

@remote_compatible
def test_ap_wpa2_in_different_bridge(dev, apdev):
    """hostapd behavior with interface in different bridge"""
    ifname = apdev[0]['ifname']
    br_ifname = 'ext-ap-br0'
    try:
        ssid = "test-wpa2-psk"
        passphrase = "12345678"
        hostapd.cmd_execute(apdev[0], ['brctl', 'addbr', br_ifname])
        hostapd.cmd_execute(apdev[0], ['brctl', 'setfd', br_ifname, '0'])
        hostapd.cmd_execute(apdev[0], ['ip', 'link', 'set', 'dev', br_ifname,
                                       'up'])
        hostapd.cmd_execute(apdev[0], ['iw', ifname, 'set', 'type', '__ap'])
        hostapd.cmd_execute(apdev[0], ['brctl', 'addif', br_ifname, ifname])
        time.sleep(0.5)
        params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
        params['bridge'] = 'ap-br0'
        hapd = hostapd.add_ap(apdev[0], params)
        hostapd.cmd_execute(apdev[0], ['brctl', 'setfd', 'ap-br0', '0'])
        hostapd.cmd_execute(apdev[0], ['ip', 'link', 'set', 'dev', 'ap-br0',
                                       'up'])
        brname = hapd.get_driver_status_field('brname')
        if brname != 'ap-br0':
            raise Exception("Incorrect bridge: " + brname)
        dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
        hwsim_utils.test_connectivity_iface(dev[0], hapd, "ap-br0")
        if hapd.get_driver_status_field("added_bridge") != "1":
            raise Exception("Unexpected added_bridge value")
        if hapd.get_driver_status_field("added_if_into_bridge") != "1":
            raise Exception("Unexpected added_if_into_bridge value")
        dev[0].request("DISCONNECT")
        hapd.disable()
    finally:
        hostapd.cmd_execute(apdev[0], ['ip', 'link', 'set', 'dev', br_ifname,
                                       'down'])
        hostapd.cmd_execute(apdev[0], ['brctl', 'delif', br_ifname, ifname,
                                       "2>", "/dev/null"], shell=True)
        hostapd.cmd_execute(apdev[0], ['brctl', 'delbr', br_ifname])

@remote_compatible
def test_ap_wpa2_ext_add_to_bridge(dev, apdev):
    """hostapd behavior with interface added to bridge externally"""
    ifname = apdev[0]['ifname']
    br_ifname = 'ext-ap-br0'
    try:
        ssid = "test-wpa2-psk"
        passphrase = "12345678"
        params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
        hapd = hostapd.add_ap(apdev[0], params)

        hostapd.cmd_execute(apdev[0], ['brctl', 'addbr', br_ifname])
        hostapd.cmd_execute(apdev[0], ['brctl', 'setfd', br_ifname, '0'])
        hostapd.cmd_execute(apdev[0], ['ip', 'link', 'set', 'dev', br_ifname,
                                       'up'])
        hostapd.cmd_execute(apdev[0], ['brctl', 'addif', br_ifname, ifname])
        dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
        if hapd.get_driver_status_field('brname') != br_ifname:
            raise Exception("Bridge name not identified correctly")
    finally:
        hostapd.cmd_execute(apdev[0], ['ip', 'link', 'set', 'dev', br_ifname,
                                       'down'])
        hostapd.cmd_execute(apdev[0], ['brctl', 'delif', br_ifname, ifname])
        hostapd.cmd_execute(apdev[0], ['brctl', 'delbr', br_ifname])

def test_ap_wpa2_psk_ext(dev, apdev):
    """WPA2-PSK AP using external EAPOL I/O"""
    bssid = apdev[0]['bssid']
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    psk = '602e323e077bc63bd80307ef4745b754b0ae0a925c2638ecd13a794b9527b9e6'
    params = hostapd.wpa2_params(ssid=ssid)
    params['wpa_psk'] = psk
    hapd = hostapd.add_ap(apdev[0], params)
    hapd.request("SET ext_eapol_frame_io 1")
    dev[0].request("SET ext_eapol_frame_io 1")
    dev[0].connect(ssid, psk=passphrase, scan_freq="2412", wait_connect=False)
    addr = dev[0].p2p_interface_addr()
    while True:
        ev = hapd.wait_event(["EAPOL-TX", "AP-STA-CONNECTED"], timeout=15)
        if ev is None:
            raise Exception("Timeout on EAPOL-TX from hostapd")
        if "AP-STA-CONNECTED" in ev:
            dev[0].wait_connected(timeout=15)
            break
        res = dev[0].request("EAPOL_RX " + bssid + " " + ev.split(' ')[2])
        if "OK" not in res:
            raise Exception("EAPOL_RX to wpa_supplicant failed")
        ev = dev[0].wait_event(["EAPOL-TX", "CTRL-EVENT-CONNECTED"], timeout=15)
        if ev is None:
            raise Exception("Timeout on EAPOL-TX from wpa_supplicant")
        if "CTRL-EVENT-CONNECTED" in ev:
            break
        res = hapd.request("EAPOL_RX " + addr + " " + ev.split(' ')[2])
        if "OK" not in res:
            raise Exception("EAPOL_RX to hostapd failed")

def test_ap_wpa2_psk_ext_retry_msg_3(dev, apdev):
    """WPA2-PSK AP using external EAPOL I/O and retry for EAPOL-Key msg 3/4"""
    bssid = apdev[0]['bssid']
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    psk = '602e323e077bc63bd80307ef4745b754b0ae0a925c2638ecd13a794b9527b9e6'
    params = hostapd.wpa2_params(ssid=ssid)
    params['wpa_psk'] = psk
    hapd = hostapd.add_ap(apdev[0], params)
    hapd.request("SET ext_eapol_frame_io 1")
    dev[0].request("SET ext_eapol_frame_io 1")
    dev[0].connect(ssid, psk=passphrase, scan_freq="2412", wait_connect=False)
    addr = dev[0].p2p_interface_addr()

    # EAPOL-Key msg 1/4
    ev = hapd.wait_event(["EAPOL-TX"], timeout=15)
    if ev is None:
        raise Exception("Timeout on EAPOL-TX from hostapd")
    res = dev[0].request("EAPOL_RX " + bssid + " " + ev.split(' ')[2])
    if "OK" not in res:
        raise Exception("EAPOL_RX to wpa_supplicant failed")

    # EAPOL-Key msg 2/4
    ev = dev[0].wait_event(["EAPOL-TX"], timeout=15)
    if ev is None:
        raise Exception("Timeout on EAPOL-TX from wpa_supplicant")
    res = hapd.request("EAPOL_RX " + addr + " " + ev.split(' ')[2])
    if "OK" not in res:
        raise Exception("EAPOL_RX to hostapd failed")

    # EAPOL-Key msg 3/4
    ev = hapd.wait_event(["EAPOL-TX"], timeout=15)
    if ev is None:
        raise Exception("Timeout on EAPOL-TX from hostapd")
    res = dev[0].request("EAPOL_RX " + bssid + " " + ev.split(' ')[2])
    if "OK" not in res:
        raise Exception("EAPOL_RX to wpa_supplicant failed")

    # EAPOL-Key msg 4/4
    ev = dev[0].wait_event(["EAPOL-TX"], timeout=15)
    if ev is None:
        raise Exception("Timeout on EAPOL-TX from wpa_supplicant")
    # Do not send to the AP
    dev[0].wait_connected(timeout=15)

    # EAPOL-Key msg 3/4 (retry)
    ev = hapd.wait_event(["EAPOL-TX"], timeout=15)
    if ev is None:
        raise Exception("Timeout on EAPOL-TX from hostapd")
    res = dev[0].request("EAPOL_RX " + bssid + " " + ev.split(' ')[2])
    if "OK" not in res:
        raise Exception("EAPOL_RX to wpa_supplicant failed")

    # EAPOL-Key msg 4/4
    ev = dev[0].wait_event(["EAPOL-TX"], timeout=15)
    if ev is None:
        raise Exception("Timeout on EAPOL-TX from wpa_supplicant")
    res = hapd.request("EAPOL_RX " + addr + " " + ev.split(' ')[2])
    if "OK" not in res:
        raise Exception("EAPOL_RX to hostapd failed")

    ev = hapd.wait_event(["AP-STA-CONNECTED"], timeout=15)
    if ev is None:
        raise Exception("Timeout on AP-STA-CONNECTED from hostapd")

    hwsim_utils.test_connectivity(dev[0], hapd)

def parse_eapol(data):
    (version, type, length) = struct.unpack('>BBH', data[0:4])
    payload = data[4:]
    if length > len(payload):
        raise Exception("Invalid EAPOL length")
    if length < len(payload):
        payload = payload[0:length]
    eapol = {}
    eapol['version'] = version
    eapol['type'] = type
    eapol['length'] = length
    eapol['payload'] = payload
    if type == 3:
        # EAPOL-Key
        (eapol['descr_type'],) = struct.unpack('B', payload[0:1])
        payload = payload[1:]
        if eapol['descr_type'] == 2 or eapol['descr_type'] == 254:
            # RSN EAPOL-Key
            (key_info, key_len) = struct.unpack('>HH', payload[0:4])
            eapol['rsn_key_info'] = key_info
            eapol['rsn_key_len'] = key_len
            eapol['rsn_replay_counter'] = payload[4:12]
            eapol['rsn_key_nonce'] = payload[12:44]
            eapol['rsn_key_iv'] = payload[44:60]
            eapol['rsn_key_rsc'] = payload[60:68]
            eapol['rsn_key_id'] = payload[68:76]
            eapol['rsn_key_mic'] = payload[76:92]
            payload = payload[92:]
            (eapol['rsn_key_data_len'],) = struct.unpack('>H', payload[0:2])
            payload = payload[2:]
            eapol['rsn_key_data'] = payload
    return eapol

def build_eapol(msg):
    data = struct.pack(">BBH", msg['version'], msg['type'], msg['length'])
    if msg['type'] == 3:
        data += struct.pack('>BHH', msg['descr_type'], msg['rsn_key_info'],
                            msg['rsn_key_len'])
        data += msg['rsn_replay_counter']
        data += msg['rsn_key_nonce']
        data += msg['rsn_key_iv']
        data += msg['rsn_key_rsc']
        data += msg['rsn_key_id']
        data += msg['rsn_key_mic']
        data += struct.pack('>H', msg['rsn_key_data_len'])
        data += msg['rsn_key_data']
    else:
        data += msg['payload']
    return data

def sha1_prf(key, label, data, outlen):
    res = ''
    counter = 0
    while outlen > 0:
        m = hmac.new(key, label, hashlib.sha1)
        m.update(struct.pack('B', 0))
        m.update(data)
        m.update(struct.pack('B', counter))
        counter += 1
        hash = m.digest()
        if outlen > len(hash):
            res += hash
            outlen -= len(hash)
        else:
            res += hash[0:outlen]
            outlen = 0
    return res

def pmk_to_ptk(pmk, addr1, addr2, nonce1, nonce2):
    if addr1 < addr2:
        data = binascii.unhexlify(addr1.replace(':','')) + binascii.unhexlify(addr2.replace(':',''))
    else:
        data = binascii.unhexlify(addr2.replace(':','')) + binascii.unhexlify(addr1.replace(':',''))
    if nonce1 < nonce2:
        data += nonce1 + nonce2
    else:
        data += nonce2 + nonce1
    label = "Pairwise key expansion"
    ptk = sha1_prf(pmk, label, data, 48)
    kck = ptk[0:16]
    kek = ptk[16:32]
    return (ptk, kck, kek)

def eapol_key_mic(kck, msg):
    msg['rsn_key_mic'] = binascii.unhexlify('00000000000000000000000000000000')
    data = build_eapol(msg)
    m = hmac.new(kck, data, hashlib.sha1)
    msg['rsn_key_mic'] = m.digest()[0:16]

def rsn_eapol_key_set(msg, key_info, key_len, nonce, data):
    msg['rsn_key_info'] = key_info
    msg['rsn_key_len'] = key_len
    if nonce:
        msg['rsn_key_nonce'] = nonce
    else:
        msg['rsn_key_nonce'] = binascii.unhexlify('0000000000000000000000000000000000000000000000000000000000000000')
    if data:
        msg['rsn_key_data_len'] = len(data)
        msg['rsn_key_data'] = data
        msg['length'] = 95 + len(data)
    else:
        msg['rsn_key_data_len'] = 0
        msg['rsn_key_data'] = ''
        msg['length'] = 95

def recv_eapol(hapd):
    ev = hapd.wait_event(["EAPOL-TX"], timeout=15)
    if ev is None:
        raise Exception("Timeout on EAPOL-TX from hostapd")
    eapol = binascii.unhexlify(ev.split(' ')[2])
    return parse_eapol(eapol)

def send_eapol(hapd, addr, data):
    res = hapd.request("EAPOL_RX " + addr + " " + binascii.hexlify(data))
    if "OK" not in res:
        raise Exception("EAPOL_RX to hostapd failed")

def reply_eapol(info, hapd, addr, msg, key_info, nonce, data, kck):
    logger.info("Send EAPOL-Key msg " + info)
    rsn_eapol_key_set(msg, key_info, 0, nonce, data)
    eapol_key_mic(kck, msg)
    send_eapol(hapd, addr, build_eapol(msg))

def hapd_connected(hapd):
    ev = hapd.wait_event(["AP-STA-CONNECTED"], timeout=15)
    if ev is None:
        raise Exception("Timeout on AP-STA-CONNECTED from hostapd")

def eapol_test(apdev, dev, wpa2=True):
    bssid = apdev['bssid']
    if wpa2:
        ssid = "test-wpa2-psk"
    else:
        ssid = "test-wpa-psk"
    psk = '602e323e077bc63bd80307ef4745b754b0ae0a925c2638ecd13a794b9527b9e6'
    pmk = binascii.unhexlify(psk)
    if wpa2:
        params = hostapd.wpa2_params(ssid=ssid)
    else:
        params = hostapd.wpa_params(ssid=ssid)
    params['wpa_psk'] = psk
    hapd = hostapd.add_ap(apdev, params)
    hapd.request("SET ext_eapol_frame_io 1")
    dev.request("SET ext_eapol_frame_io 1")
    dev.connect(ssid, raw_psk=psk, scan_freq="2412", wait_connect=False)
    addr = dev.p2p_interface_addr()
    if wpa2:
        rsne = binascii.unhexlify('30140100000fac040100000fac040100000fac020000')
    else:
        rsne = binascii.unhexlify('dd160050f20101000050f20201000050f20201000050f202')
    snonce = binascii.unhexlify('1111111111111111111111111111111111111111111111111111111111111111')
    return (bssid,ssid,hapd,snonce,pmk,addr,rsne)

@remote_compatible
def test_ap_wpa2_psk_ext_eapol(dev, apdev):
    """WPA2-PSK AP using external EAPOL supplicant"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    msg = recv_eapol(hapd)
    anonce = msg['rsn_key_nonce']
    logger.info("Replay same data back")
    send_eapol(hapd, addr, build_eapol(msg))

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)

    logger.info("Truncated Key Data in EAPOL-Key msg 2/4")
    rsn_eapol_key_set(msg, 0x0101, 0, snonce, rsne)
    msg['length'] = 95 + 22 - 1
    send_eapol(hapd, addr, build_eapol(msg))

    reply_eapol("2/4", hapd, addr, msg, 0x010a, snonce, rsne, kck)

    msg = recv_eapol(hapd)
    if anonce != msg['rsn_key_nonce']:
        raise Exception("ANonce changed")
    logger.info("Replay same data back")
    send_eapol(hapd, addr, build_eapol(msg))

    reply_eapol("4/4", hapd, addr, msg, 0x030a, None, None, kck)
    hapd_connected(hapd)

@remote_compatible
def test_ap_wpa2_psk_ext_eapol_retry1(dev, apdev):
    """WPA2 4-way handshake with EAPOL-Key 1/4 retransmitted"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    msg1 = recv_eapol(hapd)
    anonce = msg1['rsn_key_nonce']

    msg2 = recv_eapol(hapd)
    if anonce != msg2['rsn_key_nonce']:
        raise Exception("ANonce changed")

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)

    logger.info("Send EAPOL-Key msg 2/4")
    msg = msg2
    rsn_eapol_key_set(msg, 0x010a, 0, snonce, rsne)
    eapol_key_mic(kck, msg)
    send_eapol(hapd, addr, build_eapol(msg))

    msg = recv_eapol(hapd)
    if anonce != msg['rsn_key_nonce']:
        raise Exception("ANonce changed")

    reply_eapol("4/4", hapd, addr, msg, 0x030a, None, None, kck)
    hapd_connected(hapd)

@remote_compatible
def test_ap_wpa2_psk_ext_eapol_retry1b(dev, apdev):
    """WPA2 4-way handshake with EAPOL-Key 1/4 and 2/4 retransmitted"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    msg1 = recv_eapol(hapd)
    anonce = msg1['rsn_key_nonce']
    msg2 = recv_eapol(hapd)
    if anonce != msg2['rsn_key_nonce']:
        raise Exception("ANonce changed")

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)
    reply_eapol("2/4 (a)", hapd, addr, msg1, 0x010a, snonce, rsne, kck)
    reply_eapol("2/4 (b)", hapd, addr, msg2, 0x010a, snonce, rsne, kck)

    msg = recv_eapol(hapd)
    if anonce != msg['rsn_key_nonce']:
        raise Exception("ANonce changed")

    reply_eapol("4/4", hapd, addr, msg, 0x030a, None, None, kck)
    hapd_connected(hapd)

@remote_compatible
def test_ap_wpa2_psk_ext_eapol_retry1c(dev, apdev):
    """WPA2 4-way handshake with EAPOL-Key 1/4 and 2/4 retransmitted and SNonce changing"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    msg1 = recv_eapol(hapd)
    anonce = msg1['rsn_key_nonce']

    msg2 = recv_eapol(hapd)
    if anonce != msg2['rsn_key_nonce']:
        raise Exception("ANonce changed")
    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)
    reply_eapol("2/4 (a)", hapd, addr, msg1, 0x010a, snonce, rsne, kck)

    snonce2 = binascii.unhexlify('2222222222222222222222222222222222222222222222222222222222222222')
    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce2, anonce)
    reply_eapol("2/4 (b)", hapd, addr, msg2, 0x010a, snonce2, rsne, kck)

    msg = recv_eapol(hapd)
    if anonce != msg['rsn_key_nonce']:
        raise Exception("ANonce changed")
    reply_eapol("4/4", hapd, addr, msg, 0x030a, None, None, kck)
    hapd_connected(hapd)

@remote_compatible
def test_ap_wpa2_psk_ext_eapol_retry1d(dev, apdev):
    """WPA2 4-way handshake with EAPOL-Key 1/4 and 2/4 retransmitted and SNonce changing and older used"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    msg1 = recv_eapol(hapd)
    anonce = msg1['rsn_key_nonce']
    msg2 = recv_eapol(hapd)
    if anonce != msg2['rsn_key_nonce']:
        raise Exception("ANonce changed")

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)
    reply_eapol("2/4 (a)", hapd, addr, msg1, 0x010a, snonce, rsne, kck)

    snonce2 = binascii.unhexlify('2222222222222222222222222222222222222222222222222222222222222222')
    (ptk2, kck2, kek2) = pmk_to_ptk(pmk, addr, bssid, snonce2, anonce)

    reply_eapol("2/4 (b)", hapd, addr, msg2, 0x010a, snonce2, rsne, kck2)
    msg = recv_eapol(hapd)
    if anonce != msg['rsn_key_nonce']:
        raise Exception("ANonce changed")
    reply_eapol("4/4", hapd, addr, msg, 0x030a, None, None, kck)
    hapd_connected(hapd)

@remote_compatible
def test_ap_wpa2_psk_ext_eapol_type_diff(dev, apdev):
    """WPA2 4-way handshake using external EAPOL supplicant"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    msg = recv_eapol(hapd)
    anonce = msg['rsn_key_nonce']

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)

    # Incorrect descriptor type (frame dropped)
    msg['descr_type'] = 253
    rsn_eapol_key_set(msg, 0x010a, 0, snonce, rsne)
    eapol_key_mic(kck, msg)
    send_eapol(hapd, addr, build_eapol(msg))

    # Incorrect descriptor type, but with a workaround (frame processed)
    msg['descr_type'] = 254
    rsn_eapol_key_set(msg, 0x010a, 0, snonce, rsne)
    eapol_key_mic(kck, msg)
    send_eapol(hapd, addr, build_eapol(msg))

    msg = recv_eapol(hapd)
    if anonce != msg['rsn_key_nonce']:
        raise Exception("ANonce changed")
    logger.info("Replay same data back")
    send_eapol(hapd, addr, build_eapol(msg))

    reply_eapol("4/4", hapd, addr, msg, 0x030a, None, None, kck)
    hapd_connected(hapd)

@remote_compatible
def test_ap_wpa_psk_ext_eapol(dev, apdev):
    """WPA2-PSK AP using external EAPOL supplicant"""
    (bssid,ssid,hapd,snonce,pmk,addr,wpae) = eapol_test(apdev[0], dev[0],
                                                        wpa2=False)

    msg = recv_eapol(hapd)
    anonce = msg['rsn_key_nonce']
    logger.info("Replay same data back")
    send_eapol(hapd, addr, build_eapol(msg))
    logger.info("Too short data")
    send_eapol(hapd, addr, build_eapol(msg)[0:98])

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)
    msg['descr_type'] = 2
    reply_eapol("2/4(invalid type)", hapd, addr, msg, 0x010a, snonce, wpae, kck)
    msg['descr_type'] = 254
    reply_eapol("2/4", hapd, addr, msg, 0x010a, snonce, wpae, kck)

    msg = recv_eapol(hapd)
    if anonce != msg['rsn_key_nonce']:
        raise Exception("ANonce changed")
    logger.info("Replay same data back")
    send_eapol(hapd, addr, build_eapol(msg))

    reply_eapol("4/4", hapd, addr, msg, 0x030a, None, None, kck)
    hapd_connected(hapd)

@remote_compatible
def test_ap_wpa2_psk_ext_eapol_key_info(dev, apdev):
    """WPA2-PSK 4-way handshake with strange key info values"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    msg = recv_eapol(hapd)
    anonce = msg['rsn_key_nonce']

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)
    rsn_eapol_key_set(msg, 0x0000, 0, snonce, rsne)
    send_eapol(hapd, addr, build_eapol(msg))
    rsn_eapol_key_set(msg, 0xffff, 0, snonce, rsne)
    send_eapol(hapd, addr, build_eapol(msg))
    # SMK M1
    rsn_eapol_key_set(msg, 0x2802, 0, snonce, rsne)
    send_eapol(hapd, addr, build_eapol(msg))
    # SMK M3
    rsn_eapol_key_set(msg, 0x2002, 0, snonce, rsne)
    send_eapol(hapd, addr, build_eapol(msg))
    # Request
    rsn_eapol_key_set(msg, 0x0902, 0, snonce, rsne)
    send_eapol(hapd, addr, build_eapol(msg))
    # Request
    rsn_eapol_key_set(msg, 0x0902, 0, snonce, rsne)
    tmp_kck = binascii.unhexlify('00000000000000000000000000000000')
    eapol_key_mic(tmp_kck, msg)
    send_eapol(hapd, addr, build_eapol(msg))

    reply_eapol("2/4", hapd, addr, msg, 0x010a, snonce, rsne, kck)

    msg = recv_eapol(hapd)
    if anonce != msg['rsn_key_nonce']:
        raise Exception("ANonce changed")

    # Request (valic MIC)
    rsn_eapol_key_set(msg, 0x0902, 0, snonce, rsne)
    eapol_key_mic(kck, msg)
    send_eapol(hapd, addr, build_eapol(msg))
    # Request (valid MIC, replayed counter)
    rsn_eapol_key_set(msg, 0x0902, 0, snonce, rsne)
    eapol_key_mic(kck, msg)
    send_eapol(hapd, addr, build_eapol(msg))

    reply_eapol("4/4", hapd, addr, msg, 0x030a, None, None, kck)
    hapd_connected(hapd)

def build_eapol_key_1_4(anonce, replay_counter=1, key_data='', key_len=16):
    msg = {}
    msg['version'] = 2
    msg['type'] = 3
    msg['length'] = 95 + len(key_data)

    msg['descr_type'] = 2
    msg['rsn_key_info'] = 0x8a
    msg['rsn_key_len'] = key_len
    msg['rsn_replay_counter'] = struct.pack('>Q', replay_counter)
    msg['rsn_key_nonce'] = anonce
    msg['rsn_key_iv'] = binascii.unhexlify('00000000000000000000000000000000')
    msg['rsn_key_rsc'] = binascii.unhexlify('0000000000000000')
    msg['rsn_key_id'] = binascii.unhexlify('0000000000000000')
    msg['rsn_key_mic'] = binascii.unhexlify('00000000000000000000000000000000')
    msg['rsn_key_data_len'] = len(key_data)
    msg['rsn_key_data'] = key_data
    return msg

def build_eapol_key_3_4(anonce, kck, key_data, replay_counter=2,
                        key_info=0x13ca, extra_len=0, descr_type=2, key_len=16):
    msg = {}
    msg['version'] = 2
    msg['type'] = 3
    msg['length'] = 95 + len(key_data) + extra_len

    msg['descr_type'] = descr_type
    msg['rsn_key_info'] = key_info
    msg['rsn_key_len'] = key_len
    msg['rsn_replay_counter'] = struct.pack('>Q', replay_counter)
    msg['rsn_key_nonce'] = anonce
    msg['rsn_key_iv'] = binascii.unhexlify('00000000000000000000000000000000')
    msg['rsn_key_rsc'] = binascii.unhexlify('0000000000000000')
    msg['rsn_key_id'] = binascii.unhexlify('0000000000000000')
    msg['rsn_key_data_len'] = len(key_data)
    msg['rsn_key_data'] = key_data
    eapol_key_mic(kck, msg)
    return msg

def aes_wrap(kek, plain):
    n = len(plain) / 8
    a = 0xa6a6a6a6a6a6a6a6
    enc = AES.new(kek).encrypt
    r = [plain[i * 8:(i + 1) * 8] for i in range(0, n)]
    for j in range(6):
        for i in range(1, n + 1):
            b = enc(struct.pack('>Q', a) + r[i - 1])
            a = struct.unpack('>Q', b[:8])[0] ^ (n * j + i)
            r[i - 1] =b[8:]
    return struct.pack('>Q', a) + ''.join(r)

def pad_key_data(plain):
    pad_len = len(plain) % 8
    if pad_len:
        pad_len = 8 - pad_len
        plain += '\xdd'
        pad_len -= 1
        plain += pad_len * '\0'
    return plain

def test_ap_wpa2_psk_supp_proto(dev, apdev):
    """WPA2-PSK 4-way handshake protocol testing for supplicant"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    # Wait for EAPOL-Key msg 1/4 from hostapd to determine when associated
    msg = recv_eapol(hapd)
    dev[0].dump_monitor()

    # Build own EAPOL-Key msg 1/4
    anonce = binascii.unhexlify('2222222222222222222222222222222222222222222222222222222222222222')
    counter = 1
    msg = build_eapol_key_1_4(anonce, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    msg = recv_eapol(dev[0])
    snonce = msg['rsn_key_nonce']

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)

    logger.debug("Invalid AES wrap data length 0")
    dev[0].dump_monitor()
    msg = build_eapol_key_3_4(anonce, kck, '', replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: Unsupported AES-WRAP len 0"])
    if ev is None:
        raise Exception("Unsupported AES-WRAP len 0 not reported")

    logger.debug("Invalid AES wrap data length 1")
    dev[0].dump_monitor()
    msg = build_eapol_key_3_4(anonce, kck, '1', replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: Unsupported AES-WRAP len 1"])
    if ev is None:
        raise Exception("Unsupported AES-WRAP len 1 not reported")

    logger.debug("Invalid AES wrap data length 9")
    dev[0].dump_monitor()
    msg = build_eapol_key_3_4(anonce, kck, '123456789', replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: Unsupported AES-WRAP len 9"])
    if ev is None:
        raise Exception("Unsupported AES-WRAP len 9 not reported")

    logger.debug("Invalid AES wrap data payload")
    dev[0].dump_monitor()
    msg = build_eapol_key_3_4(anonce, kck, '12345678', replay_counter=counter)
    # do not increment counter to test replay protection
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: AES unwrap failed"])
    if ev is None:
        raise Exception("AES unwrap failure not reported")

    logger.debug("Replay Count not increasing")
    dev[0].dump_monitor()
    msg = build_eapol_key_3_4(anonce, kck, '12345678', replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: EAPOL-Key Replay Counter did not increase"])
    if ev is None:
        raise Exception("Replay Counter replay not reported")

    logger.debug("Missing Ack bit in key info")
    dev[0].dump_monitor()
    msg = build_eapol_key_3_4(anonce, kck, '12345678', replay_counter=counter,
                              key_info=0x134a)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: No Ack bit in key_info"])
    if ev is None:
        raise Exception("Missing Ack bit not reported")

    logger.debug("Unexpected Request bit in key info")
    dev[0].dump_monitor()
    msg = build_eapol_key_3_4(anonce, kck, '12345678', replay_counter=counter,
                              key_info=0x1bca)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: EAPOL-Key with Request bit"])
    if ev is None:
        raise Exception("Request bit not reported")

    logger.debug("Unsupported key descriptor version 0")
    dev[0].dump_monitor()
    msg = build_eapol_key_3_4(anonce, kck, '0123456789abcdef',
                              replay_counter=counter, key_info=0x13c8)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: Unsupported EAPOL-Key descriptor version 0"])
    if ev is None:
        raise Exception("Unsupported EAPOL-Key descriptor version 0 not reported")

    logger.debug("Key descriptor version 1 not allowed with CCMP")
    dev[0].dump_monitor()
    msg = build_eapol_key_3_4(anonce, kck, '0123456789abcdef',
                              replay_counter=counter, key_info=0x13c9)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: CCMP is used, but EAPOL-Key descriptor version (1) is not 2"])
    if ev is None:
        raise Exception("Not allowed EAPOL-Key descriptor version not reported")

    logger.debug("Invalid AES wrap payload with key descriptor version 2")
    dev[0].dump_monitor()
    msg = build_eapol_key_3_4(anonce, kck, '0123456789abcdef',
                              replay_counter=counter, key_info=0x13ca)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: AES unwrap failed"])
    if ev is None:
        raise Exception("AES unwrap failure not reported")

    logger.debug("Key descriptor version 3 workaround")
    dev[0].dump_monitor()
    msg = build_eapol_key_3_4(anonce, kck, '0123456789abcdef',
                              replay_counter=counter, key_info=0x13cb)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: CCMP is used, but EAPOL-Key descriptor version (3) is not 2"])
    if ev is None:
        raise Exception("CCMP key descriptor mismatch not reported")
    ev = dev[0].wait_event(["WPA: Interoperability workaround"])
    if ev is None:
        raise Exception("AES-128-CMAC workaround not reported")
    ev = dev[0].wait_event(["WPA: Invalid EAPOL-Key MIC - dropping packet"])
    if ev is None:
        raise Exception("MIC failure with AES-128-CMAC workaround not reported")

    logger.debug("Unsupported key descriptor version 4")
    dev[0].dump_monitor()
    msg = build_eapol_key_3_4(anonce, kck, '0123456789abcdef',
                              replay_counter=counter, key_info=0x13cc)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: Unsupported EAPOL-Key descriptor version 4"])
    if ev is None:
        raise Exception("Unsupported EAPOL-Key descriptor version 4 not reported")

    logger.debug("Unsupported key descriptor version 7")
    dev[0].dump_monitor()
    msg = build_eapol_key_3_4(anonce, kck, '0123456789abcdef',
                              replay_counter=counter, key_info=0x13cf)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: Unsupported EAPOL-Key descriptor version 7"])
    if ev is None:
        raise Exception("Unsupported EAPOL-Key descriptor version 7 not reported")

    logger.debug("Too short EAPOL header length")
    dev[0].dump_monitor()
    msg = build_eapol_key_3_4(anonce, kck, '12345678', replay_counter=counter,
                              extra_len=-1)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: Invalid EAPOL-Key frame - key_data overflow (8 > 7)"])
    if ev is None:
        raise Exception("Key data overflow not reported")

    logger.debug("Too long EAPOL header length")
    msg = build_eapol_key_3_4(anonce, kck, '12345678', replay_counter=counter,
                              extra_len=1)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))

    logger.debug("Unsupported descriptor type 0")
    msg = build_eapol_key_3_4(anonce, kck, '12345678', replay_counter=counter,
                              descr_type=0)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))

    logger.debug("WPA descriptor type 0")
    msg = build_eapol_key_3_4(anonce, kck, '12345678', replay_counter=counter,
                              descr_type=254)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))

    logger.debug("Non-zero key index for pairwise key")
    dev[0].dump_monitor()
    wrapped = aes_wrap(kek, 16*'z')
    msg = build_eapol_key_3_4(anonce, kck, wrapped, replay_counter=counter,
                              key_info=0x13ea)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: Ignored EAPOL-Key (Pairwise) with non-zero key index"])
    if ev is None:
        raise Exception("Non-zero key index not reported")

    logger.debug("Invalid Key Data plaintext payload --> disconnect")
    dev[0].dump_monitor()
    wrapped = aes_wrap(kek, 16*'z')
    msg = build_eapol_key_3_4(anonce, kck, wrapped, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    dev[0].wait_disconnected(timeout=1)

def test_ap_wpa2_psk_supp_proto_no_ie(dev, apdev):
    """WPA2-PSK supplicant protocol testing: IE not included"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    # Wait for EAPOL-Key msg 1/4 from hostapd to determine when associated
    msg = recv_eapol(hapd)
    dev[0].dump_monitor()

    # Build own EAPOL-Key msg 1/4
    anonce = binascii.unhexlify('2222222222222222222222222222222222222222222222222222222222222222')
    counter = 1
    msg = build_eapol_key_1_4(anonce, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    msg = recv_eapol(dev[0])
    snonce = msg['rsn_key_nonce']

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)

    logger.debug("No IEs in msg 3/4 --> disconnect")
    dev[0].dump_monitor()
    wrapped = aes_wrap(kek, 16*'\0')
    msg = build_eapol_key_3_4(anonce, kck, wrapped, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    dev[0].wait_disconnected(timeout=1)

def test_ap_wpa2_psk_supp_proto_ie_mismatch(dev, apdev):
    """WPA2-PSK supplicant protocol testing: IE mismatch"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    # Wait for EAPOL-Key msg 1/4 from hostapd to determine when associated
    msg = recv_eapol(hapd)
    dev[0].dump_monitor()

    # Build own EAPOL-Key msg 1/4
    anonce = binascii.unhexlify('2222222222222222222222222222222222222222222222222222222222222222')
    counter = 1
    msg = build_eapol_key_1_4(anonce, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    msg = recv_eapol(dev[0])
    snonce = msg['rsn_key_nonce']

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)

    logger.debug("Msg 3/4 with mismatching IE")
    dev[0].dump_monitor()
    wrapped = aes_wrap(kek, pad_key_data(binascii.unhexlify('30060100000fac04dd16000fac010100dc11188831bf4aa4a8678d2b41498618')))
    msg = build_eapol_key_3_4(anonce, kck, wrapped, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    dev[0].wait_disconnected(timeout=1)

def test_ap_wpa2_psk_supp_proto_ok(dev, apdev):
    """WPA2-PSK supplicant protocol testing: success"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    # Wait for EAPOL-Key msg 1/4 from hostapd to determine when associated
    msg = recv_eapol(hapd)
    dev[0].dump_monitor()

    # Build own EAPOL-Key msg 1/4
    anonce = binascii.unhexlify('2222222222222222222222222222222222222222222222222222222222222222')
    counter = 1
    msg = build_eapol_key_1_4(anonce, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    msg = recv_eapol(dev[0])
    snonce = msg['rsn_key_nonce']

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)

    logger.debug("Valid EAPOL-Key msg 3/4")
    dev[0].dump_monitor()
    plain = binascii.unhexlify('30140100000fac040100000fac040100000fac020c00dd16000fac010100dc11188831bf4aa4a8678d2b41498618')
    wrapped = aes_wrap(kek, pad_key_data(plain))
    msg = build_eapol_key_3_4(anonce, kck, wrapped, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    dev[0].wait_connected(timeout=1)

def test_ap_wpa2_psk_supp_proto_no_gtk(dev, apdev):
    """WPA2-PSK supplicant protocol testing: no GTK"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    # Wait for EAPOL-Key msg 1/4 from hostapd to determine when associated
    msg = recv_eapol(hapd)
    dev[0].dump_monitor()

    # Build own EAPOL-Key msg 1/4
    anonce = binascii.unhexlify('2222222222222222222222222222222222222222222222222222222222222222')
    counter = 1
    msg = build_eapol_key_1_4(anonce, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    msg = recv_eapol(dev[0])
    snonce = msg['rsn_key_nonce']

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)

    logger.debug("EAPOL-Key msg 3/4 without GTK KDE")
    dev[0].dump_monitor()
    plain = binascii.unhexlify('30140100000fac040100000fac040100000fac020c00')
    wrapped = aes_wrap(kek, pad_key_data(plain))
    msg = build_eapol_key_3_4(anonce, kck, wrapped, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["CTRL-EVENT-CONNECTED"], timeout=0.1)
    if ev is not None:
        raise Exception("Unexpected connection completion reported")

def test_ap_wpa2_psk_supp_proto_anonce_change(dev, apdev):
    """WPA2-PSK supplicant protocol testing: ANonce change"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    # Wait for EAPOL-Key msg 1/4 from hostapd to determine when associated
    msg = recv_eapol(hapd)
    dev[0].dump_monitor()

    # Build own EAPOL-Key msg 1/4
    anonce = binascii.unhexlify('2222222222222222222222222222222222222222222222222222222222222222')
    counter = 1
    msg = build_eapol_key_1_4(anonce, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    msg = recv_eapol(dev[0])
    snonce = msg['rsn_key_nonce']

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)

    logger.debug("Valid EAPOL-Key msg 3/4")
    dev[0].dump_monitor()
    anonce2 = binascii.unhexlify('3333333333333333333333333333333333333333333333333333333333333333')
    plain = binascii.unhexlify('30140100000fac040100000fac040100000fac020c00dd16000fac010100dc11188831bf4aa4a8678d2b41498618')
    wrapped = aes_wrap(kek, pad_key_data(plain))
    msg = build_eapol_key_3_4(anonce2, kck, wrapped, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: ANonce from message 1 of 4-Way Handshake differs from 3 of 4-Way Handshake"])
    if ev is None:
        raise Exception("ANonce change not reported")

def test_ap_wpa2_psk_supp_proto_unexpected_group_msg(dev, apdev):
    """WPA2-PSK supplicant protocol testing: unexpected group message"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    # Wait for EAPOL-Key msg 1/4 from hostapd to determine when associated
    msg = recv_eapol(hapd)
    dev[0].dump_monitor()

    # Build own EAPOL-Key msg 1/4
    anonce = binascii.unhexlify('2222222222222222222222222222222222222222222222222222222222222222')
    counter = 1
    msg = build_eapol_key_1_4(anonce, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    msg = recv_eapol(dev[0])
    snonce = msg['rsn_key_nonce']

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)

    logger.debug("Group key 1/2 instead of msg 3/4")
    dev[0].dump_monitor()
    wrapped = aes_wrap(kek, binascii.unhexlify('dd16000fac010100dc11188831bf4aa4a8678d2b41498618'))
    msg = build_eapol_key_3_4(anonce, kck, wrapped, replay_counter=counter,
                              key_info=0x13c2)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: Group Key Handshake started prior to completion of 4-way handshake"])
    if ev is None:
        raise Exception("Unexpected group key message not reported")
    dev[0].wait_disconnected(timeout=1)

@remote_compatible
def test_ap_wpa2_psk_supp_proto_msg_1_invalid_kde(dev, apdev):
    """WPA2-PSK supplicant protocol testing: invalid KDE in msg 1/4"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    # Wait for EAPOL-Key msg 1/4 from hostapd to determine when associated
    msg = recv_eapol(hapd)
    dev[0].dump_monitor()

    # Build own EAPOL-Key msg 1/4 with invalid KDE
    anonce = binascii.unhexlify('2222222222222222222222222222222222222222222222222222222222222222')
    counter = 1
    msg = build_eapol_key_1_4(anonce, replay_counter=counter,
                              key_data=binascii.unhexlify('5555'))
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    dev[0].wait_disconnected(timeout=1)

def test_ap_wpa2_psk_supp_proto_wrong_pairwise_key_len(dev, apdev):
    """WPA2-PSK supplicant protocol testing: wrong pairwise key length"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    # Wait for EAPOL-Key msg 1/4 from hostapd to determine when associated
    msg = recv_eapol(hapd)
    dev[0].dump_monitor()

    # Build own EAPOL-Key msg 1/4
    anonce = binascii.unhexlify('2222222222222222222222222222222222222222222222222222222222222222')
    counter = 1
    msg = build_eapol_key_1_4(anonce, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    msg = recv_eapol(dev[0])
    snonce = msg['rsn_key_nonce']

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)

    logger.debug("Valid EAPOL-Key msg 3/4")
    dev[0].dump_monitor()
    plain = binascii.unhexlify('30140100000fac040100000fac040100000fac020c00dd16000fac010100dc11188831bf4aa4a8678d2b41498618')
    wrapped = aes_wrap(kek, pad_key_data(plain))
    msg = build_eapol_key_3_4(anonce, kck, wrapped, replay_counter=counter,
                              key_len=15)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: Invalid CCMP key length 15"])
    if ev is None:
        raise Exception("Invalid CCMP key length not reported")
    dev[0].wait_disconnected(timeout=1)

def test_ap_wpa2_psk_supp_proto_wrong_group_key_len(dev, apdev):
    """WPA2-PSK supplicant protocol testing: wrong group key length"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    # Wait for EAPOL-Key msg 1/4 from hostapd to determine when associated
    msg = recv_eapol(hapd)
    dev[0].dump_monitor()

    # Build own EAPOL-Key msg 1/4
    anonce = binascii.unhexlify('2222222222222222222222222222222222222222222222222222222222222222')
    counter = 1
    msg = build_eapol_key_1_4(anonce, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    msg = recv_eapol(dev[0])
    snonce = msg['rsn_key_nonce']

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)

    logger.debug("Valid EAPOL-Key msg 3/4")
    dev[0].dump_monitor()
    plain = binascii.unhexlify('30140100000fac040100000fac040100000fac020c00dd15000fac010100dc11188831bf4aa4a8678d2b414986')
    wrapped = aes_wrap(kek, pad_key_data(plain))
    msg = build_eapol_key_3_4(anonce, kck, wrapped, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: Unsupported CCMP Group Cipher key length 15"])
    if ev is None:
        raise Exception("Invalid CCMP key length not reported")
    dev[0].wait_disconnected(timeout=1)

def test_ap_wpa2_psk_supp_proto_gtk_tx_bit_workaround(dev, apdev):
    """WPA2-PSK supplicant protocol testing: GTK TX bit workaround"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    # Wait for EAPOL-Key msg 1/4 from hostapd to determine when associated
    msg = recv_eapol(hapd)
    dev[0].dump_monitor()

    # Build own EAPOL-Key msg 1/4
    anonce = binascii.unhexlify('2222222222222222222222222222222222222222222222222222222222222222')
    counter = 1
    msg = build_eapol_key_1_4(anonce, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    msg = recv_eapol(dev[0])
    snonce = msg['rsn_key_nonce']

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)

    logger.debug("Valid EAPOL-Key msg 3/4")
    dev[0].dump_monitor()
    plain = binascii.unhexlify('30140100000fac040100000fac040100000fac020c00dd16000fac010500dc11188831bf4aa4a8678d2b41498618')
    wrapped = aes_wrap(kek, pad_key_data(plain))
    msg = build_eapol_key_3_4(anonce, kck, wrapped, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: Tx bit set for GTK, but pairwise keys are used - ignore Tx bit"])
    if ev is None:
        raise Exception("GTK Tx bit workaround not reported")
    dev[0].wait_connected(timeout=1)

def test_ap_wpa2_psk_supp_proto_gtk_keyidx_0_and_3(dev, apdev):
    """WPA2-PSK supplicant protocol testing: GTK key index 0 and 3"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    # Wait for EAPOL-Key msg 1/4 from hostapd to determine when associated
    msg = recv_eapol(hapd)
    dev[0].dump_monitor()

    # Build own EAPOL-Key msg 1/4
    anonce = binascii.unhexlify('2222222222222222222222222222222222222222222222222222222222222222')
    counter = 1
    msg = build_eapol_key_1_4(anonce, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    msg = recv_eapol(dev[0])
    snonce = msg['rsn_key_nonce']

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)

    logger.debug("Valid EAPOL-Key msg 3/4 (GTK keyidx 0)")
    dev[0].dump_monitor()
    plain = binascii.unhexlify('30140100000fac040100000fac040100000fac020c00dd16000fac010000dc11188831bf4aa4a8678d2b41498618')
    wrapped = aes_wrap(kek, pad_key_data(plain))
    msg = build_eapol_key_3_4(anonce, kck, wrapped, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    dev[0].wait_connected(timeout=1)

    logger.debug("Valid EAPOL-Key group msg 1/2 (GTK keyidx 3)")
    dev[0].dump_monitor()
    plain = binascii.unhexlify('dd16000fac010300dc11188831bf4aa4a8678d2b41498618')
    wrapped = aes_wrap(kek, pad_key_data(plain))
    msg = build_eapol_key_3_4(anonce, kck, wrapped, replay_counter=counter,
                              key_info=0x13c2)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    msg = recv_eapol(dev[0])
    ev = dev[0].wait_event(["WPA: Group rekeying completed"])
    if ev is None:
        raise Exception("GTK rekeing not reported")

    logger.debug("Unencrypted GTK KDE in group msg 1/2")
    dev[0].dump_monitor()
    plain = binascii.unhexlify('dd16000fac010300dc11188831bf4aa4a8678d2b41498618')
    msg = build_eapol_key_3_4(anonce, kck, plain, replay_counter=counter,
                              key_info=0x03c2)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: GTK IE in unencrypted key data"])
    if ev is None:
        raise Exception("Unencrypted GTK KDE not reported")
    dev[0].wait_disconnected(timeout=1)

def test_ap_wpa2_psk_supp_proto_no_gtk_in_group_msg(dev, apdev):
    """WPA2-PSK supplicant protocol testing: GTK KDE missing from group msg"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    # Wait for EAPOL-Key msg 1/4 from hostapd to determine when associated
    msg = recv_eapol(hapd)
    dev[0].dump_monitor()

    # Build own EAPOL-Key msg 1/4
    anonce = binascii.unhexlify('2222222222222222222222222222222222222222222222222222222222222222')
    counter = 1
    msg = build_eapol_key_1_4(anonce, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    msg = recv_eapol(dev[0])
    snonce = msg['rsn_key_nonce']

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)

    logger.debug("Valid EAPOL-Key msg 3/4 (GTK keyidx 0)")
    dev[0].dump_monitor()
    plain = binascii.unhexlify('30140100000fac040100000fac040100000fac020c00dd16000fac010000dc11188831bf4aa4a8678d2b41498618')
    wrapped = aes_wrap(kek, pad_key_data(plain))
    msg = build_eapol_key_3_4(anonce, kck, wrapped, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    dev[0].wait_connected(timeout=1)

    logger.debug("No GTK KDE in EAPOL-Key group msg 1/2")
    dev[0].dump_monitor()
    plain = binascii.unhexlify('dd00dd00dd00dd00dd00dd00dd00dd00')
    wrapped = aes_wrap(kek, pad_key_data(plain))
    msg = build_eapol_key_3_4(anonce, kck, wrapped, replay_counter=counter,
                              key_info=0x13c2)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: No GTK IE in Group Key msg 1/2"])
    if ev is None:
        raise Exception("Missing GTK KDE not reported")
    dev[0].wait_disconnected(timeout=1)

def test_ap_wpa2_psk_supp_proto_too_long_gtk_in_group_msg(dev, apdev):
    """WPA2-PSK supplicant protocol testing: too long GTK KDE in group msg"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    # Wait for EAPOL-Key msg 1/4 from hostapd to determine when associated
    msg = recv_eapol(hapd)
    dev[0].dump_monitor()

    # Build own EAPOL-Key msg 1/4
    anonce = binascii.unhexlify('2222222222222222222222222222222222222222222222222222222222222222')
    counter = 1
    msg = build_eapol_key_1_4(anonce, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    msg = recv_eapol(dev[0])
    snonce = msg['rsn_key_nonce']

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)

    logger.debug("Valid EAPOL-Key msg 3/4 (GTK keyidx 0)")
    dev[0].dump_monitor()
    plain = binascii.unhexlify('30140100000fac040100000fac040100000fac020c00dd16000fac010000dc11188831bf4aa4a8678d2b41498618')
    wrapped = aes_wrap(kek, pad_key_data(plain))
    msg = build_eapol_key_3_4(anonce, kck, wrapped, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    dev[0].wait_connected(timeout=1)

    logger.debug("EAPOL-Key group msg 1/2 with too long GTK KDE")
    dev[0].dump_monitor()
    plain = binascii.unhexlify('dd27000fac010100ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff')
    wrapped = aes_wrap(kek, pad_key_data(plain))
    msg = build_eapol_key_3_4(anonce, kck, wrapped, replay_counter=counter,
                              key_info=0x13c2)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: Unsupported CCMP Group Cipher key length 33"])
    if ev is None:
        raise Exception("Too long GTK KDE not reported")
    dev[0].wait_disconnected(timeout=1)

def test_ap_wpa2_psk_supp_proto_too_long_gtk_kde(dev, apdev):
    """WPA2-PSK supplicant protocol testing: too long GTK KDE"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    # Wait for EAPOL-Key msg 1/4 from hostapd to determine when associated
    msg = recv_eapol(hapd)
    dev[0].dump_monitor()

    # Build own EAPOL-Key msg 1/4
    anonce = binascii.unhexlify('2222222222222222222222222222222222222222222222222222222222222222')
    counter = 1
    msg = build_eapol_key_1_4(anonce, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    msg = recv_eapol(dev[0])
    snonce = msg['rsn_key_nonce']

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)

    logger.debug("EAPOL-Key msg 3/4 with too short GTK KDE")
    dev[0].dump_monitor()
    plain = binascii.unhexlify('30140100000fac040100000fac040100000fac020c00dd27000fac010100ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff')
    wrapped = aes_wrap(kek, pad_key_data(plain))
    msg = build_eapol_key_3_4(anonce, kck, wrapped, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    dev[0].wait_disconnected(timeout=1)

def test_ap_wpa2_psk_supp_proto_gtk_not_encrypted(dev, apdev):
    """WPA2-PSK supplicant protocol testing: GTK KDE not encrypted"""
    (bssid,ssid,hapd,snonce,pmk,addr,rsne) = eapol_test(apdev[0], dev[0])

    # Wait for EAPOL-Key msg 1/4 from hostapd to determine when associated
    msg = recv_eapol(hapd)
    dev[0].dump_monitor()

    # Build own EAPOL-Key msg 1/4
    anonce = binascii.unhexlify('2222222222222222222222222222222222222222222222222222222222222222')
    counter = 1
    msg = build_eapol_key_1_4(anonce, replay_counter=counter)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    msg = recv_eapol(dev[0])
    snonce = msg['rsn_key_nonce']

    (ptk, kck, kek) = pmk_to_ptk(pmk, addr, bssid, snonce, anonce)

    logger.debug("Valid EAPOL-Key msg 3/4")
    dev[0].dump_monitor()
    plain = binascii.unhexlify('30140100000fac040100000fac040100000fac020c00dd16000fac010100dc11188831bf4aa4a8678d2b41498618')
    msg = build_eapol_key_3_4(anonce, kck, plain, replay_counter=counter,
                              key_info=0x03ca)
    counter += 1
    send_eapol(dev[0], addr, build_eapol(msg))
    ev = dev[0].wait_event(["WPA: GTK IE in unencrypted key data"])
    if ev is None:
        raise Exception("Unencrypted GTK KDE not reported")
    dev[0].wait_disconnected(timeout=1)

def find_wpas_process(dev):
    ifname = dev.ifname
    err, data = dev.cmd_execute(['ps', 'ax'])
    for l in data.splitlines():
        if "wpa_supplicant" not in l:
            continue
        if "-i" + ifname not in l:
            continue
        return int(l.strip().split(' ')[0])
    raise Exception("Could not find wpa_supplicant process")

def read_process_memory(pid, key=None):
    buf = bytes()
    logger.info("Reading process memory (pid=%d)" % pid)
    with open('/proc/%d/maps' % pid, 'r') as maps, \
         open('/proc/%d/mem' % pid, 'r') as mem:
        for l in maps.readlines():
            m = re.match(r'([0-9a-f]+)-([0-9a-f]+) ([-r][-w][-x][-p])', l)
            if not m:
                continue
            start = int(m.group(1), 16)
            end = int(m.group(2), 16)
            perm = m.group(3)
            if start > 0xffffffffffff:
                continue
            if end < start:
                continue
            if not perm.startswith('rw'):
                continue
            for name in [ "[heap]", "[stack]" ]:
                if name in l:
                    logger.info("%s 0x%x-0x%x is at %d-%d" % (name, start, end, len(buf), len(buf) + (end - start)))
            mem.seek(start)
            data = mem.read(end - start)
            buf += data
            if key and key in data:
                logger.info("Key found in " + l)
    logger.info("Total process memory read: %d bytes" % len(buf))
    return buf

def verify_not_present(buf, key, fname, keyname):
    pos = buf.find(key)
    if pos < 0:
        return

    prefix = 2048 if pos > 2048 else pos
    with open(fname + keyname, 'w') as f:
        f.write(buf[pos - prefix:pos + 2048])
    raise Exception(keyname + " found after disassociation")

def get_key_locations(buf, key, keyname):
    count = 0
    pos = 0
    while True:
        pos = buf.find(key, pos)
        if pos < 0:
            break
        logger.info("Found %s at %d" % (keyname, pos))
        context = 128
        start = pos - context if pos > context else 0
        before = binascii.hexlify(buf[start:pos])
        context += len(key)
        end = pos + context if pos < len(buf) - context else len(buf) - context
        after = binascii.hexlify(buf[pos + len(key):end])
        logger.debug("Memory context %d-%d: %s|%s|%s" % (start, end, before, binascii.hexlify(key), after))
        count += 1
        pos += len(key)
    return count

def test_wpa2_psk_key_lifetime_in_memory(dev, apdev, params):
    """WPA2-PSK and PSK/PTK lifetime in memory"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    psk = '602e323e077bc63bd80307ef4745b754b0ae0a925c2638ecd13a794b9527b9e6'
    pmk = binascii.unhexlify(psk)
    p = hostapd.wpa2_params(ssid=ssid)
    p['wpa_psk'] = psk
    hapd = hostapd.add_ap(apdev[0], p)

    pid = find_wpas_process(dev[0])

    id = dev[0].connect(ssid, raw_psk=psk, scan_freq="2412",
                        only_add_network=True)

    logger.info("Checking keys in memory after network profile configuration")
    buf = read_process_memory(pid, pmk)
    get_key_locations(buf, pmk, "PMK")

    dev[0].request("REMOVE_NETWORK all")
    logger.info("Checking keys in memory after network profile removal")
    buf = read_process_memory(pid, pmk)
    get_key_locations(buf, pmk, "PMK")

    id = dev[0].connect(ssid, psk=passphrase, scan_freq="2412",
                        only_add_network=True)

    logger.info("Checking keys in memory before connection")
    buf = read_process_memory(pid, pmk)
    get_key_locations(buf, pmk, "PMK")

    dev[0].connect_network(id, timeout=20)
    # The decrypted copy of GTK is freed only after the CTRL-EVENT-CONNECTED
    # event has been delivered, so verify that wpa_supplicant has returned to
    # eloop before reading process memory.
    time.sleep(1)
    dev[0].ping()

    buf = read_process_memory(pid, pmk)

    dev[0].request("DISCONNECT")
    dev[0].wait_disconnected()

    dev[0].relog()
    ptk = None
    gtk = None
    with open(os.path.join(params['logdir'], 'log0'), 'r') as f:
        for l in f.readlines():
            if "WPA: PTK - hexdump" in l:
                val = l.strip().split(':')[3].replace(' ', '')
                ptk = binascii.unhexlify(val)
            if "WPA: Group Key - hexdump" in l:
                val = l.strip().split(':')[3].replace(' ', '')
                gtk = binascii.unhexlify(val)
    if not pmk or not ptk or not gtk:
        raise Exception("Could not find keys from debug log")
    if len(gtk) != 16:
        raise Exception("Unexpected GTK length")

    kck = ptk[0:16]
    kek = ptk[16:32]
    tk = ptk[32:48]

    logger.info("Checking keys in memory while associated")
    get_key_locations(buf, pmk, "PMK")
    if pmk not in buf:
        raise HwsimSkip("PMK not found while associated")
    if kck not in buf:
        raise Exception("KCK not found while associated")
    if kek not in buf:
        raise Exception("KEK not found while associated")
    if tk in buf:
        raise Exception("TK found from memory")
    if gtk in buf:
        get_key_locations(buf, gtk, "GTK")
        raise Exception("GTK found from memory")

    logger.info("Checking keys in memory after disassociation")
    buf = read_process_memory(pid, pmk)
    get_key_locations(buf, pmk, "PMK")

    # Note: PMK/PSK is still present in network configuration

    fname = os.path.join(params['logdir'],
                         'wpa2_psk_key_lifetime_in_memory.memctx-')
    verify_not_present(buf, kck, fname, "KCK")
    verify_not_present(buf, kek, fname, "KEK")
    verify_not_present(buf, tk, fname, "TK")
    verify_not_present(buf, gtk, fname, "GTK")

    dev[0].request("REMOVE_NETWORK all")

    logger.info("Checking keys in memory after network profile removal")
    buf = read_process_memory(pid, pmk)
    get_key_locations(buf, pmk, "PMK")

    verify_not_present(buf, pmk, fname, "PMK")
    verify_not_present(buf, kck, fname, "KCK")
    verify_not_present(buf, kek, fname, "KEK")
    verify_not_present(buf, tk, fname, "TK")
    verify_not_present(buf, gtk, fname, "GTK")

@remote_compatible
def test_ap_wpa2_psk_wep(dev, apdev):
    """WPA2-PSK AP and WEP enabled"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    hapd = hostapd.add_ap(apdev[0], params)
    try:
        hapd.set('wep_key0', '"hello"')
        raise Exception("WEP key accepted to WPA2 network")
    except Exception:
        pass

def test_ap_wpa2_psk_wpas_in_bridge(dev, apdev):
    """WPA2-PSK AP and wpas interface in a bridge"""
    br_ifname='sta-br0'
    ifname='wlan5'
    try:
        _test_ap_wpa2_psk_wpas_in_bridge(dev, apdev)
    finally:
        subprocess.call(['ip', 'link', 'set', 'dev', br_ifname, 'down'])
        subprocess.call(['brctl', 'delif', br_ifname, ifname])
        subprocess.call(['brctl', 'delbr', br_ifname])
        subprocess.call(['iw', ifname, 'set', '4addr', 'off'])

def _test_ap_wpa2_psk_wpas_in_bridge(dev, apdev):
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    hapd = hostapd.add_ap(apdev[0], params)

    br_ifname='sta-br0'
    ifname='wlan5'
    wpas = WpaSupplicant(global_iface='/tmp/wpas-wlan5')
    subprocess.call(['brctl', 'addbr', br_ifname])
    subprocess.call(['brctl', 'setfd', br_ifname, '0'])
    subprocess.call(['ip', 'link', 'set', 'dev', br_ifname, 'up'])
    subprocess.call(['iw', ifname, 'set', '4addr', 'on'])
    subprocess.check_call(['brctl', 'addif', br_ifname, ifname])
    wpas.interface_add(ifname, br_ifname=br_ifname)
    wpas.dump_monitor()

    wpas.connect(ssid, psk=passphrase, scan_freq="2412")
    wpas.dump_monitor()

@remote_compatible
def test_ap_wpa2_psk_ifdown(dev, apdev):
    """AP with open mode and external ifconfig down"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    hapd = hostapd.add_ap(apdev[0], params)
    bssid = apdev[0]['bssid']

    dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
    hapd.cmd_execute(['ip', 'link', 'set', 'dev', apdev[0]['ifname'], 'down'])
    ev = hapd.wait_event(["INTERFACE-DISABLED"], timeout=10)
    if ev is None:
        raise Exception("No INTERFACE-DISABLED event")
    # this wait tests beacon loss detection in mac80211
    dev[0].wait_disconnected()
    hapd.cmd_execute(['ip', 'link', 'set', 'dev', apdev[0]['ifname'], 'up'])
    ev = hapd.wait_event(["INTERFACE-ENABLED"], timeout=10)
    if ev is None:
        raise Exception("No INTERFACE-ENABLED event")
    dev[0].wait_connected()
    hwsim_utils.test_connectivity(dev[0], hapd)

def test_ap_wpa2_psk_drop_first_msg_4(dev, apdev):
    """WPA2-PSK and first EAPOL-Key msg 4/4 dropped"""
    bssid = apdev[0]['bssid']
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    psk = '602e323e077bc63bd80307ef4745b754b0ae0a925c2638ecd13a794b9527b9e6'
    params = hostapd.wpa2_params(ssid=ssid)
    params['wpa_psk'] = psk
    hapd = hostapd.add_ap(apdev[0], params)
    hapd.request("SET ext_eapol_frame_io 1")
    dev[0].request("SET ext_eapol_frame_io 1")
    dev[0].connect(ssid, psk=passphrase, scan_freq="2412", wait_connect=False)
    addr = dev[0].own_addr()

    # EAPOL-Key msg 1/4
    ev = hapd.wait_event(["EAPOL-TX"], timeout=15)
    if ev is None:
        raise Exception("Timeout on EAPOL-TX from hostapd")
    res = dev[0].request("EAPOL_RX " + bssid + " " + ev.split(' ')[2])
    if "OK" not in res:
        raise Exception("EAPOL_RX to wpa_supplicant failed")

    # EAPOL-Key msg 2/4
    ev = dev[0].wait_event(["EAPOL-TX"], timeout=15)
    if ev is None:
        raise Exception("Timeout on EAPOL-TX from wpa_supplicant")
    res = hapd.request("EAPOL_RX " + addr + " " + ev.split(' ')[2])
    if "OK" not in res:
        raise Exception("EAPOL_RX to hostapd failed")

    # EAPOL-Key msg 3/4
    ev = hapd.wait_event(["EAPOL-TX"], timeout=15)
    if ev is None:
        raise Exception("Timeout on EAPOL-TX from hostapd")
    res = dev[0].request("EAPOL_RX " + bssid + " " + ev.split(' ')[2])
    if "OK" not in res:
        raise Exception("EAPOL_RX to wpa_supplicant failed")

    # EAPOL-Key msg 4/4
    ev = dev[0].wait_event(["EAPOL-TX"], timeout=15)
    if ev is None:
        raise Exception("Timeout on EAPOL-TX from wpa_supplicant")
    logger.info("Drop the first EAPOL-Key msg 4/4")

    # wpa_supplicant believes now that 4-way handshake succeeded; hostapd
    # doesn't. Use normal EAPOL TX/RX to handle retries.
    hapd.request("SET ext_eapol_frame_io 0")
    dev[0].request("SET ext_eapol_frame_io 0")
    dev[0].wait_connected()

    ev = hapd.wait_event(["AP-STA-CONNECTED"], timeout=15)
    if ev is None:
        raise Exception("Timeout on AP-STA-CONNECTED from hostapd")

    ev = dev[0].wait_event(["CTRL-EVENT-DISCONNECTED"], timeout=0.1)
    if ev is not None:
        logger.info("Disconnection detected")
        # The EAPOL-Key retries are supposed to allow the connection to be
        # established without having to reassociate. However, this does not
        # currently work since mac80211 ends up encrypting EAPOL-Key msg 4/4
        # after the pairwise key has been configured and AP will drop those and
        # disconnect the station after reaching retransmission limit. Connection
        # is then established after reassociation. Once that behavior has been
        # optimized to prevent EAPOL-Key frame encryption for retransmission
        # case, this exception can be uncommented here.
        #raise Exception("Unexpected disconnection")

@remote_compatible
def test_ap_wpa2_psk_disable_enable(dev, apdev):
    """WPA2-PSK AP getting disabled and re-enabled"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    psk = '602e323e077bc63bd80307ef4745b754b0ae0a925c2638ecd13a794b9527b9e6'
    params = hostapd.wpa2_params(ssid=ssid)
    params['wpa_psk'] = psk
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, raw_psk=psk, scan_freq="2412")

    for i in range(2):
        hapd.request("DISABLE")
        dev[0].wait_disconnected()
        hapd.request("ENABLE")
        dev[0].wait_connected()
        hwsim_utils.test_connectivity(dev[0], hapd)

@remote_compatible
def test_ap_wpa2_psk_incorrect_passphrase(dev, apdev):
    """WPA2-PSK AP and station using incorrect passphrase"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk="incorrect passphrase", scan_freq="2412",
                   wait_connect=False)
    ev = hapd.wait_event(["AP-STA-POSSIBLE-PSK-MISMATCH"], timeout=10)
    if ev is None:
        raise Exception("No AP-STA-POSSIBLE-PSK-MISMATCH reported")
    dev[0].dump_monitor()

    hapd.disable()
    hapd.set("wpa_passphrase", "incorrect passphrase")
    hapd.enable()

    dev[0].wait_connected(timeout=20)

@remote_compatible
def test_ap_wpa_ie_parsing(dev, apdev):
    """WPA IE parsing"""
    skip_with_fips(dev[0])
    ssid = "test-wpa-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa_params(ssid=ssid, passphrase=passphrase)
    hapd = hostapd.add_ap(apdev[0], params)
    id = dev[0].connect(ssid, psk=passphrase, scan_freq="2412",
                        only_add_network=True)

    tests = [ "dd040050f201",
              "dd050050f20101",
              "dd060050f2010100",
              "dd060050f2010001",
              "dd070050f201010000",
              "dd080050f20101000050",
              "dd090050f20101000050f2",
              "dd0a0050f20101000050f202",
              "dd0b0050f20101000050f20201",
              "dd0c0050f20101000050f2020100",
              "dd0c0050f20101000050f2020000",
              "dd0c0050f20101000050f202ffff",
              "dd0d0050f20101000050f202010000",
              "dd0e0050f20101000050f20201000050",
              "dd0f0050f20101000050f20201000050f2",
              "dd100050f20101000050f20201000050f202",
              "dd110050f20101000050f20201000050f20201",
              "dd120050f20101000050f20201000050f2020100",
              "dd120050f20101000050f20201000050f2020000",
              "dd120050f20101000050f20201000050f202ffff",
              "dd130050f20101000050f20201000050f202010000",
              "dd140050f20101000050f20201000050f20201000050",
              "dd150050f20101000050f20201000050f20201000050f2" ]
    for t in tests:
        try:
            if "OK" not in dev[0].request("VENDOR_ELEM_ADD 13 " + t):
                raise Exception("VENDOR_ELEM_ADD failed")
            dev[0].select_network(id)
            ev = dev[0].wait_event(["CTRL-EVENT-ASSOC-REJECT"], timeout=10)
            if ev is None:
                raise Exception("Association rejection not reported")
            dev[0].request("DISCONNECT")
            dev[0].dump_monitor()
        finally:
            dev[0].request("VENDOR_ELEM_REMOVE 13 *")

    tests = [ "dd170050f20101000050f20201000050f20201000050f202ff",
              "dd180050f20101000050f20201000050f20201000050f202ffff",
              "dd190050f20101000050f20201000050f20201000050f202ffffff" ]
    for t in tests:
        try:
            if "OK" not in dev[0].request("VENDOR_ELEM_ADD 13 " + t):
                raise Exception("VENDOR_ELEM_ADD failed")
            dev[0].select_network(id)
            dev[0].wait_connected()
            dev[0].request("DISCONNECT")
            dev[0].dump_monitor()
        finally:
            dev[0].request("VENDOR_ELEM_REMOVE 13 *")

@remote_compatible
def test_ap_wpa2_psk_no_random(dev, apdev):
    """WPA2-PSK AP and no random numbers available"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    psk = '602e323e077bc63bd80307ef4745b754b0ae0a925c2638ecd13a794b9527b9e6'
    params = hostapd.wpa2_params(ssid=ssid)
    params['wpa_psk'] = psk
    hapd = hostapd.add_ap(apdev[0], params)
    with fail_test(hapd, 1, "wpa_gmk_to_gtk"):
        id = dev[0].connect(ssid, raw_psk=psk, scan_freq="2412",
                            wait_connect=False)
        ev = dev[0].wait_event(["CTRL-EVENT-DISCONNECTED"], timeout=15)
        if ev is None:
            raise Exception("Disconnection event not reported")
        dev[0].request("DISCONNECT")
        dev[0].select_network(id, freq=2412)
        dev[0].wait_connected()

@remote_compatible
def test_rsn_ie_proto_psk_sta(dev, apdev):
    """RSN element protocol testing for PSK cases on STA side"""
    bssid = apdev[0]['bssid']
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    # This is the RSN element used normally by hostapd
    params['own_ie_override'] = '30140100000fac040100000fac040100000fac020c00'
    hapd = hostapd.add_ap(apdev[0], params)
    if "FAIL" not in hapd.request("SET own_ie_override qwerty"):
        raise Exception("Invalid own_ie_override value accepted")
    id = dev[0].connect(ssid, psk=passphrase, scan_freq="2412")

    tests = [ ('No RSN Capabilities field',
               '30120100000fac040100000fac040100000fac02'),
              ('Reserved RSN Capabilities bits set',
               '30140100000fac040100000fac040100000fac023cff'),
              ('Extra pairwise cipher suite (unsupported)',
               '30180100000fac040200ffffffff000fac040100000fac020c00'),
              ('Extra AKM suite (unsupported)',
               '30180100000fac040100000fac040200ffffffff000fac020c00'),
              ('PMKIDCount field included',
               '30160100000fac040100000fac040100000fac020c000000'),
              ('Unexpected Group Management Cipher Suite with PMF disabled',
               '301a0100000fac040100000fac040100000fac020c000000000fac06'),
              ('Extra octet after defined fields (future extensibility)',
               '301b0100000fac040100000fac040100000fac020c000000000fac0600') ]
    for txt,ie in tests:
        dev[0].request("DISCONNECT")
        dev[0].wait_disconnected()
        logger.info(txt)
        hapd.disable()
        hapd.set('own_ie_override', ie)
        hapd.enable()
        dev[0].request("BSS_FLUSH 0")
        dev[0].scan_for_bss(bssid, 2412, force_scan=True, only_new=True)
        dev[0].select_network(id, freq=2412)
        dev[0].wait_connected()

@remote_compatible
def test_ap_cli_order(dev, apdev):
    ssid = "test-rsn-setup"
    passphrase = 'zzzzzzzz'

    hapd = hostapd.add_ap(apdev[0], {}, no_enable=True)
    hapd.set('ssid', ssid)
    hapd.set('wpa_passphrase', passphrase)
    hapd.set('rsn_pairwise', 'CCMP')
    hapd.set('wpa_key_mgmt', 'WPA-PSK')
    hapd.set('wpa', '2')
    hapd.enable()
    cfg = hapd.get_config()
    if cfg['group_cipher'] != 'CCMP':
        raise Exception("Unexpected group_cipher: " + cfg['group_cipher'])
    if cfg['rsn_pairwise_cipher'] != 'CCMP':
        raise Exception("Unexpected rsn_pairwise_cipher: " + cfg['rsn_pairwise_cipher'])

    ev = hapd.wait_event(["AP-ENABLED", "AP-DISABLED"], timeout=30)
    if ev is None:
        raise Exception("AP startup timed out")
    if "AP-ENABLED" not in ev:
        raise Exception("AP startup failed")

    dev[0].connect(ssid, psk=passphrase, scan_freq="2412")

def set_test_assoc_ie(dev, ie):
    if "OK" not in dev.request("TEST_ASSOC_IE " + ie):
        raise Exception("Could not set TEST_ASSOC_IE")

@remote_compatible
def test_ap_wpa2_psk_assoc_rsn(dev, apdev):
    """WPA2-PSK AP and association request RSN IE differences"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    hapd = hostapd.add_ap(apdev[0], params)

    tests = [ ("Normal wpa_supplicant assoc req RSN IE",
               "30140100000fac040100000fac040100000fac020000"),
              ("RSN IE without RSN Capabilities",
               "30120100000fac040100000fac040100000fac02") ]
    for title, ie in tests:
        logger.info(title)
        set_test_assoc_ie(dev[0], ie)
        dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
        dev[0].request("REMOVE_NETWORK all")
        dev[0].wait_disconnected()

    tests = [ ("WPA IE instead of RSN IE and only RSN enabled on AP",
               "dd160050f20101000050f20201000050f20201000050f202", 40),
              ("Empty RSN IE", "3000", 40),
              ("RSN IE with truncated Version", "300101", 40),
              ("RSN IE with only Version", "30020100", 43) ]
    for title, ie, status in tests:
        logger.info(title)
        set_test_assoc_ie(dev[0], ie)
        dev[0].connect(ssid, psk=passphrase, scan_freq="2412",
                       wait_connect=False)
        ev = dev[0].wait_event(["CTRL-EVENT-ASSOC-REJECT"])
        if ev is None:
            raise Exception("Association rejection not reported")
        if "status_code=" + str(status) not in ev:
            raise Exception("Unexpected status code: " + ev)
        dev[0].request("REMOVE_NETWORK all")
        dev[0].dump_monitor()

def test_ap_wpa_psk_rsn_pairwise(dev, apdev):
    """WPA-PSK AP and only rsn_pairwise set"""
    params = { "ssid": "wpapsk", "wpa": "1", "wpa_key_mgmt": "WPA-PSK",
               "rsn_pairwise": "TKIP", "wpa_passphrase": "1234567890" }
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect("wpapsk", psk="1234567890", proto="WPA", pairwise="TKIP",
                   scan_freq="2412")
