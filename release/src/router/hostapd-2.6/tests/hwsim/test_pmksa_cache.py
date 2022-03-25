# WPA2-Enterprise PMKSA caching tests
# Copyright (c) 2013-2014, Jouni Malinen <j@w1.fi>
#
# This software may be distributed under the terms of the BSD license.
# See README for more details.

import logging
logger = logging.getLogger()
import subprocess
import time

import hostapd
import hwsim_utils
from wpasupplicant import WpaSupplicant
from utils import alloc_fail
from test_ap_eap import eap_connect

def test_pmksa_cache_on_roam_back(dev, apdev):
    """PMKSA cache to skip EAP on reassociation back to same AP"""
    params = hostapd.wpa2_eap_params(ssid="test-pmksa-cache")
    hostapd.add_ap(apdev[0], params)
    bssid = apdev[0]['bssid']
    dev[0].connect("test-pmksa-cache", proto="RSN", key_mgmt="WPA-EAP",
                   eap="GPSK", identity="gpsk user",
                   password="abcdefghijklmnop0123456789abcdef",
                   scan_freq="2412")
    pmksa = dev[0].get_pmksa(bssid)
    if pmksa is None:
        raise Exception("No PMKSA cache entry created")
    if pmksa['opportunistic'] != '0':
        raise Exception("Unexpected opportunistic PMKSA cache entry")

    hostapd.add_ap(apdev[1], params)
    bssid2 = apdev[1]['bssid']

    dev[0].dump_monitor()
    logger.info("Roam to AP2")
    # It can take some time for the second AP to become ready to reply to Probe
    # Request frames especially under heavy CPU load, so allow couple of rounds
    # of scanning to avoid reporting errors incorrectly just because of scans
    # not having seen the target AP.
    for i in range(0, 10):
        dev[0].scan(freq="2412")
        if dev[0].get_bss(bssid2) is not None:
            break
        logger.info("Scan again to find target AP")
    dev[0].request("ROAM " + bssid2)
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-SUCCESS"], timeout=10)
    if ev is None:
        raise Exception("EAP success timed out")
    dev[0].wait_connected(timeout=10, error="Roaming timed out")
    pmksa2 = dev[0].get_pmksa(bssid2)
    if pmksa2 is None:
        raise Exception("No PMKSA cache entry found")
    if pmksa2['opportunistic'] != '0':
        raise Exception("Unexpected opportunistic PMKSA cache entry")

    dev[0].dump_monitor()
    logger.info("Roam back to AP1")
    dev[0].scan(freq="2412")
    dev[0].request("ROAM " + bssid)
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-STARTED",
                            "CTRL-EVENT-CONNECTED"], timeout=10)
    if ev is None:
        raise Exception("Roaming with the AP timed out")
    if "CTRL-EVENT-EAP-STARTED" in ev:
        raise Exception("Unexpected EAP exchange")
    pmksa1b = dev[0].get_pmksa(bssid)
    if pmksa1b is None:
        raise Exception("No PMKSA cache entry found")
    if pmksa['pmkid'] != pmksa1b['pmkid']:
        raise Exception("Unexpected PMKID change for AP1")

    dev[0].dump_monitor()
    if "FAIL" in dev[0].request("PMKSA_FLUSH"):
        raise Exception("PMKSA_FLUSH failed")
    if dev[0].get_pmksa(bssid) is not None or dev[0].get_pmksa(bssid2) is not None:
        raise Exception("PMKSA_FLUSH did not remove PMKSA entries")
    dev[0].wait_disconnected(timeout=5)
    dev[0].wait_connected(timeout=15, error="Reconnection timed out")

def test_pmksa_cache_and_reauth(dev, apdev):
    """PMKSA caching and EAPOL reauthentication"""
    params = hostapd.wpa2_eap_params(ssid="test-pmksa-cache")
    hapd = hostapd.add_ap(apdev[0], params)
    bssid = apdev[0]['bssid']
    dev[0].connect("test-pmksa-cache", proto="RSN", key_mgmt="WPA-EAP",
                   eap="GPSK", identity="gpsk user",
                   password="abcdefghijklmnop0123456789abcdef",
                   scan_freq="2412")

    hostapd.add_ap(apdev[1], params)
    bssid2 = apdev[1]['bssid']

    dev[0].dump_monitor()
    logger.info("Roam to AP2")
    # It can take some time for the second AP to become ready to reply to Probe
    # Request frames especially under heavy CPU load, so allow couple of rounds
    # of scanning to avoid reporting errors incorrectly just because of scans
    # not having seen the target AP.
    for i in range(0, 10):
        dev[0].scan(freq="2412")
        if dev[0].get_bss(bssid2) is not None:
            break
        logger.info("Scan again to find target AP")
    dev[0].request("ROAM " + bssid2)
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-SUCCESS"], timeout=10)
    if ev is None:
        raise Exception("EAP success timed out")
    dev[0].wait_connected(timeout=10, error="Roaming timed out")

    dev[0].dump_monitor()
    logger.info("Roam back to AP1")
    dev[0].scan(freq="2412")
    dev[0].request("ROAM " + bssid)
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-STARTED",
                            "CTRL-EVENT-CONNECTED"], timeout=10)
    if ev is None:
        raise Exception("Roaming with the AP timed out")
    if "CTRL-EVENT-EAP-STARTED" in ev:
        raise Exception("Unexpected EAP exchange")

    # Verify EAPOL reauthentication after PMKSA caching
    hapd.request("EAPOL_REAUTH " + dev[0].own_addr())
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-STARTED"], timeout=5)
    if ev is None:
        raise Exception("EAP authentication did not start")
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-SUCCESS"], timeout=5)
    if ev is None:
        raise Exception("EAP authentication did not succeed")

def test_pmksa_cache_opportunistic_only_on_sta(dev, apdev):
    """Opportunistic PMKSA caching enabled only on station"""
    params = hostapd.wpa2_eap_params(ssid="test-pmksa-cache")
    hostapd.add_ap(apdev[0], params)
    bssid = apdev[0]['bssid']
    dev[0].connect("test-pmksa-cache", proto="RSN", key_mgmt="WPA-EAP",
                   eap="GPSK", identity="gpsk user",
                   password="abcdefghijklmnop0123456789abcdef", okc=True,
                   scan_freq="2412")
    pmksa = dev[0].get_pmksa(bssid)
    if pmksa is None:
        raise Exception("No PMKSA cache entry created")
    if pmksa['opportunistic'] != '0':
        raise Exception("Unexpected opportunistic PMKSA cache entry")

    hostapd.add_ap(apdev[1], params)
    bssid2 = apdev[1]['bssid']

    dev[0].dump_monitor()
    logger.info("Roam to AP2")
    dev[0].scan(freq="2412")
    dev[0].request("ROAM " + bssid2)
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-SUCCESS"], timeout=10)
    if ev is None:
        raise Exception("EAP success timed out")
    dev[0].wait_connected(timeout=10, error="Roaming timed out")
    pmksa2 = dev[0].get_pmksa(bssid2)
    if pmksa2 is None:
        raise Exception("No PMKSA cache entry found")
    if pmksa2['opportunistic'] != '0':
        raise Exception("Unexpected opportunistic PMKSA cache entry")

    dev[0].dump_monitor()
    logger.info("Roam back to AP1")
    dev[0].scan(freq="2412")
    dev[0].request("ROAM " + bssid)
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-STARTED",
                            "CTRL-EVENT-CONNECTED"], timeout=10)
    if ev is None:
        raise Exception("Roaming with the AP timed out")
    if "CTRL-EVENT-EAP-STARTED" in ev:
        raise Exception("Unexpected EAP exchange")
    pmksa1b = dev[0].get_pmksa(bssid)
    if pmksa1b is None:
        raise Exception("No PMKSA cache entry found")
    if pmksa['pmkid'] != pmksa1b['pmkid']:
        raise Exception("Unexpected PMKID change for AP1")

def test_pmksa_cache_opportunistic(dev, apdev):
    """Opportunistic PMKSA caching"""
    params = hostapd.wpa2_eap_params(ssid="test-pmksa-cache")
    params['okc'] = "1"
    hostapd.add_ap(apdev[0], params)
    bssid = apdev[0]['bssid']
    dev[0].connect("test-pmksa-cache", proto="RSN", key_mgmt="WPA-EAP",
                   eap="GPSK", identity="gpsk user",
                   password="abcdefghijklmnop0123456789abcdef", okc=True,
                   scan_freq="2412")
    pmksa = dev[0].get_pmksa(bssid)
    if pmksa is None:
        raise Exception("No PMKSA cache entry created")
    if pmksa['opportunistic'] != '0':
        raise Exception("Unexpected opportunistic PMKSA cache entry")

    hostapd.add_ap(apdev[1], params)
    bssid2 = apdev[1]['bssid']

    dev[0].dump_monitor()
    logger.info("Roam to AP2")
    dev[0].scan(freq="2412")
    dev[0].request("ROAM " + bssid2)
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-STARTED",
                            "CTRL-EVENT-CONNECTED"], timeout=10)
    if ev is None:
        raise Exception("Roaming with the AP timed out")
    if "CTRL-EVENT-EAP-STARTED" in ev:
        raise Exception("Unexpected EAP exchange")
    pmksa2 = dev[0].get_pmksa(bssid2)
    if pmksa2 is None:
        raise Exception("No PMKSA cache entry created")

    dev[0].dump_monitor()
    logger.info("Roam back to AP1")
    dev[0].scan(freq="2412")
    dev[0].request("ROAM " + bssid)
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-STARTED",
                            "CTRL-EVENT-CONNECTED"], timeout=10)
    if ev is None:
        raise Exception("Roaming with the AP timed out")
    if "CTRL-EVENT-EAP-STARTED" in ev:
        raise Exception("Unexpected EAP exchange")

    pmksa1b = dev[0].get_pmksa(bssid)
    if pmksa1b is None:
        raise Exception("No PMKSA cache entry found")
    if pmksa['pmkid'] != pmksa1b['pmkid']:
        raise Exception("Unexpected PMKID change for AP1")

def test_pmksa_cache_opportunistic_connect(dev, apdev):
    """Opportunistic PMKSA caching with connect API"""
    params = hostapd.wpa2_eap_params(ssid="test-pmksa-cache")
    params['okc'] = "1"
    hostapd.add_ap(apdev[0], params)
    bssid = apdev[0]['bssid']
    wpas = WpaSupplicant(global_iface='/tmp/wpas-wlan5')
    wpas.interface_add("wlan5", drv_params="force_connect_cmd=1")
    wpas.connect("test-pmksa-cache", proto="RSN", key_mgmt="WPA-EAP",
                 eap="GPSK", identity="gpsk user",
                 password="abcdefghijklmnop0123456789abcdef", okc=True,
                 scan_freq="2412")
    pmksa = wpas.get_pmksa(bssid)
    if pmksa is None:
        raise Exception("No PMKSA cache entry created")
    if pmksa['opportunistic'] != '0':
        raise Exception("Unexpected opportunistic PMKSA cache entry")

    hostapd.add_ap(apdev[1], params)
    bssid2 = apdev[1]['bssid']

    wpas.dump_monitor()
    logger.info("Roam to AP2")
    wpas.scan_for_bss(bssid2, freq="2412", force_scan=True)
    wpas.request("ROAM " + bssid2)
    ev = wpas.wait_event(["CTRL-EVENT-EAP-STARTED",
                            "CTRL-EVENT-CONNECTED"], timeout=10)
    if ev is None:
        raise Exception("Roaming with the AP timed out")
    if "CTRL-EVENT-EAP-STARTED" in ev:
        raise Exception("Unexpected EAP exchange")
    pmksa2 = wpas.get_pmksa(bssid2)
    if pmksa2 is None:
        raise Exception("No PMKSA cache entry created")

    wpas.dump_monitor()
    logger.info("Roam back to AP1")
    wpas.scan(freq="2412")
    wpas.request("ROAM " + bssid)
    ev = wpas.wait_event(["CTRL-EVENT-EAP-STARTED",
                            "CTRL-EVENT-CONNECTED"], timeout=10)
    if ev is None:
        raise Exception("Roaming with the AP timed out")
    if "CTRL-EVENT-EAP-STARTED" in ev:
        raise Exception("Unexpected EAP exchange")

    pmksa1b = wpas.get_pmksa(bssid)
    if pmksa1b is None:
        raise Exception("No PMKSA cache entry found")
    if pmksa['pmkid'] != pmksa1b['pmkid']:
        raise Exception("Unexpected PMKID change for AP1")

def test_pmksa_cache_expiration(dev, apdev):
    """PMKSA cache entry expiration"""
    params = hostapd.wpa2_eap_params(ssid="test-pmksa-cache")
    hostapd.add_ap(apdev[0], params)
    bssid = apdev[0]['bssid']
    dev[0].request("SET dot11RSNAConfigPMKLifetime 10")
    dev[0].connect("test-pmksa-cache", proto="RSN", key_mgmt="WPA-EAP",
                   eap="GPSK", identity="gpsk user",
                   password="abcdefghijklmnop0123456789abcdef",
                   scan_freq="2412")
    pmksa = dev[0].get_pmksa(bssid)
    if pmksa is None:
        raise Exception("No PMKSA cache entry created")
    logger.info("Wait for PMKSA cache entry to expire")
    ev = dev[0].wait_event(["WPA: Key negotiation completed",
                            "CTRL-EVENT-DISCONNECTED"], timeout=15)
    if ev is None:
        raise Exception("No EAP reauthentication seen")
    if "CTRL-EVENT-DISCONNECTED" in ev:
        raise Exception("Unexpected disconnection")
    pmksa2 = dev[0].get_pmksa(bssid)
    if pmksa['pmkid'] == pmksa2['pmkid']:
        raise Exception("PMKID did not change")

def test_pmksa_cache_expiration_disconnect(dev, apdev):
    """PMKSA cache entry expiration (disconnect)"""
    params = hostapd.wpa2_eap_params(ssid="test-pmksa-cache")
    hapd = hostapd.add_ap(apdev[0], params)
    bssid = apdev[0]['bssid']
    dev[0].request("SET dot11RSNAConfigPMKLifetime 2")
    dev[0].request("SET dot11RSNAConfigPMKReauthThreshold 100")
    dev[0].connect("test-pmksa-cache", proto="RSN", key_mgmt="WPA-EAP",
                   eap="GPSK", identity="gpsk user",
                   password="abcdefghijklmnop0123456789abcdef",
                   scan_freq="2412")
    pmksa = dev[0].get_pmksa(bssid)
    if pmksa is None:
        raise Exception("No PMKSA cache entry created")
    hapd.request("SET auth_server_shared_secret incorrect")
    logger.info("Wait for PMKSA cache entry to expire")
    ev = dev[0].wait_event(["WPA: Key negotiation completed",
                            "CTRL-EVENT-DISCONNECTED"], timeout=15)
    if ev is None:
        raise Exception("No EAP reauthentication seen")
    if "CTRL-EVENT-DISCONNECTED" not in ev:
        raise Exception("Missing disconnection")
    hapd.request("SET auth_server_shared_secret radius")
    ev = dev[0].wait_event(["WPA: Key negotiation completed"], timeout=15)
    if ev is None:
        raise Exception("No EAP reauthentication seen")
    pmksa2 = dev[0].get_pmksa(bssid)
    if pmksa['pmkid'] == pmksa2['pmkid']:
        raise Exception("PMKID did not change")

def test_pmksa_cache_and_cui(dev, apdev):
    """PMKSA cache and Chargeable-User-Identity"""
    params = hostapd.wpa2_eap_params(ssid="cui")
    params['radius_request_cui'] = '1'
    params['acct_server_addr'] = "127.0.0.1"
    params['acct_server_port'] = "1813"
    params['acct_server_shared_secret'] = "radius"
    hapd = hostapd.add_ap(apdev[0], params)
    bssid = apdev[0]['bssid']
    dev[0].connect("cui", proto="RSN", key_mgmt="WPA-EAP",
                   eap="GPSK", identity="gpsk-cui",
                   password="abcdefghijklmnop0123456789abcdef",
                   scan_freq="2412")
    pmksa = dev[0].get_pmksa(bssid)
    if pmksa is None:
        raise Exception("No PMKSA cache entry created")
    ev = hapd.wait_event([ "AP-STA-CONNECTED" ], timeout=5)
    if ev is None:
        raise Exception("No connection event received from hostapd")

    dev[0].dump_monitor()
    logger.info("Disconnect and reconnect to the same AP")
    dev[0].request("DISCONNECT")
    dev[0].wait_disconnected()
    dev[0].request("RECONNECT")
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-STARTED",
                            "CTRL-EVENT-CONNECTED"], timeout=10)
    if ev is None:
        raise Exception("Reconnect timed out")
    if "CTRL-EVENT-EAP-STARTED" in ev:
        raise Exception("Unexpected EAP exchange")
    pmksa1b = dev[0].get_pmksa(bssid)
    if pmksa1b is None:
        raise Exception("No PMKSA cache entry found")
    if pmksa['pmkid'] != pmksa1b['pmkid']:
        raise Exception("Unexpected PMKID change for AP1")

    dev[0].request("REAUTHENTICATE")
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-SUCCESS"], timeout=10)
    if ev is None:
        raise Exception("EAP success timed out")
    for i in range(0, 20):
        state = dev[0].get_status_field("wpa_state")
        if state == "COMPLETED":
            break
        time.sleep(0.1)
    if state != "COMPLETED":
        raise Exception("Reauthentication did not complete")

def generic_pmksa_cache_preauth(dev, apdev, extraparams, identity, databridge,
                                force_disconnect=False):
    if not extraparams:
        extraparams = [{}, {}]
    try:
        params = hostapd.wpa2_eap_params(ssid="test-wpa2-eap")
        params['bridge'] = 'ap-br0'
        for key, value in extraparams[0].iteritems():
            params[key] = value

        hapd = hostapd.add_ap(apdev[0], params)
        hapd.cmd_execute(['brctl', 'setfd', 'ap-br0', '0'])
        hapd.cmd_execute(['ip', 'link', 'set', 'dev', 'ap-br0', 'up'])
        eap_connect(dev[0], hapd, "PAX", identity,
                    password_hex="0123456789abcdef0123456789abcdef")

        # Verify connectivity in the correct VLAN
        hwsim_utils.test_connectivity_iface(dev[0], hapd, databridge)

        params = hostapd.wpa2_eap_params(ssid="test-wpa2-eap")
        params['bridge'] = 'ap-br0'
        params['rsn_preauth'] = '1'
        params['rsn_preauth_interfaces'] = databridge
        for key, value in extraparams[1].iteritems():
            params[key] = value
        hostapd.add_ap(apdev[1], params)
        bssid1 = apdev[1]['bssid']
        dev[0].scan(freq="2412")
        success = False
        status_seen = False
        for i in range(0, 50):
            if not status_seen:
                status = dev[0].request("STATUS")
                if "Pre-authentication EAPOL state machines:" in status:
                    status_seen = True
            time.sleep(0.1)
            pmksa = dev[0].get_pmksa(bssid1)
            if pmksa:
                success = True
                break
        if not success:
            raise Exception("No PMKSA cache entry created from pre-authentication")
        if not status_seen:
            raise Exception("Pre-authentication EAPOL status was not available")

        dev[0].scan(freq="2412")
        if "[WPA2-EAP-CCMP-preauth]" not in dev[0].request("SCAN_RESULTS"):
            raise Exception("Scan results missing RSN element info")
        dev[0].request("ROAM " + bssid1)
        ev = dev[0].wait_event(["CTRL-EVENT-EAP-STARTED",
                                "CTRL-EVENT-CONNECTED"], timeout=10)
        if ev is None:
            raise Exception("Roaming with the AP timed out")
        if "CTRL-EVENT-EAP-STARTED" in ev:
            raise Exception("Unexpected EAP exchange")
        pmksa2 = dev[0].get_pmksa(bssid1)
        if pmksa2 is None:
            raise Exception("No PMKSA cache entry")
        if pmksa['pmkid'] != pmksa2['pmkid']:
            raise Exception("Unexpected PMKID change")

        # Verify connectivity in the correct VLAN
        hwsim_utils.test_connectivity_iface(dev[0], hapd, databridge)

        if not force_disconnect:
            return

        # Disconnect the STA from both APs to avoid forceful ifdown by the
        # test script on a VLAN that this has an associated STA. That used to
        # trigger a mac80211 warning.
        dev[0].request("DISCONNECT")
        hapd.request("DISABLE")

    finally:
        hostapd.cmd_execute(apdev[0], ['ip', 'link', 'set', 'dev',
                                       'ap-br0', 'down', '2>', '/dev/null'],
                            shell=True)
        hostapd.cmd_execute(apdev[0], ['brctl', 'delbr', 'ap-br0',
                                       '2>', '/dev/null'], shell=True)

def test_pmksa_cache_preauth(dev, apdev):
    """RSN pre-authentication to generate PMKSA cache entry"""
    generic_pmksa_cache_preauth(dev, apdev, None,
                                "pax.user@example.com", "ap-br0")

def test_pmksa_cache_preauth_per_sta_vif(dev, apdev):
    """RSN pre-authentication to generate PMKSA cache entry with per_sta_vif"""
    extraparams = [{}, {}]
    extraparams[0]['per_sta_vif'] = "1"
    extraparams[1]['per_sta_vif'] = "1"
    generic_pmksa_cache_preauth(dev, apdev, extraparams,
                                "pax.user@example.com", "ap-br0")

def test_pmksa_cache_preauth_vlan_enabled(dev, apdev):
    """RSN pre-authentication to generate PMKSA cache entry (dynamic_vlan optional but station without VLAN set)"""
    extraparams = [{}, {}]
    extraparams[0]['dynamic_vlan'] = '1'
    extraparams[1]['dynamic_vlan'] = '1'
    generic_pmksa_cache_preauth(dev, apdev, extraparams,
                                "pax.user@example.com", "ap-br0")

def test_pmksa_cache_preauth_vlan_enabled_per_sta_vif(dev, apdev):
    """RSN pre-authentication to generate PMKSA cache entry (dynamic_vlan optional but station without VLAN set, with per_sta_vif enabled)"""
    extraparams = [{}, {}]
    extraparams[0]['per_sta_vif'] = "1"
    extraparams[1]['per_sta_vif'] = "1"
    extraparams[0]['dynamic_vlan'] = '1'
    extraparams[1]['dynamic_vlan'] = '1'
    generic_pmksa_cache_preauth(dev, apdev, extraparams,
                                "pax.user@example.com", "ap-br0")

def test_pmksa_cache_preauth_vlan_used(dev, apdev):
    """RSN pre-authentication to generate PMKSA cache entry (station with VLAN set)"""
    run_pmksa_cache_preauth_vlan_used(dev, apdev, None, force_disconnect=True)

def run_pmksa_cache_preauth_vlan_used(dev, apdev, extraparams=None,
                                      force_disconnect=False):
    try:
        subprocess.call(['brctl', 'addbr', 'brvlan1'])
        subprocess.call(['brctl', 'setfd', 'brvlan1', '0'])
        if not extraparams:
            extraparams = [{}, {}]
        extraparams[0]['dynamic_vlan'] = '1'
        extraparams[0]['vlan_file'] = 'hostapd.wlan3.vlan'
        extraparams[1]['dynamic_vlan'] = '1'
        extraparams[1]['vlan_file'] = 'hostapd.wlan4.vlan'
        generic_pmksa_cache_preauth(dev, apdev, extraparams,
                                    "vlan1", "brvlan1",
                                    force_disconnect=force_disconnect)
    finally:
        subprocess.call(['ip', 'link', 'set', 'dev', 'brvlan1', 'down'])
        subprocess.call(['ip', 'link', 'set', 'dev', 'wlan3.1', 'down'],
                        stderr=open('/dev/null', 'w'))
        subprocess.call(['ip', 'link', 'set', 'dev', 'wlan4.1', 'down'],
                        stderr=open('/dev/null', 'w'))
        subprocess.call(['brctl', 'delif', 'brvlan1', 'wlan3.1'],
                        stderr=open('/dev/null', 'w'))
        subprocess.call(['brctl', 'delif', 'brvlan1', 'wlan4.1'],
                        stderr=open('/dev/null', 'w'))
        subprocess.call(['brctl', 'delbr', 'brvlan1'])

def test_pmksa_cache_preauth_vlan_used_per_sta_vif(dev, apdev):
    """RSN pre-authentication to generate PMKSA cache entry (station with VLAN set, per_sta_vif=1)"""
    extraparams = [{}, {}]
    extraparams[0]['per_sta_vif'] = "1"
    extraparams[1]['per_sta_vif'] = "1"
    run_pmksa_cache_preauth_vlan_used(dev, apdev, extraparams)

def test_pmksa_cache_disabled(dev, apdev):
    """PMKSA cache disabling on AP"""
    params = hostapd.wpa2_eap_params(ssid="test-pmksa-cache")
    params['disable_pmksa_caching'] = '1'
    hostapd.add_ap(apdev[0], params)
    bssid = apdev[0]['bssid']
    dev[0].connect("test-pmksa-cache", proto="RSN", key_mgmt="WPA-EAP",
                   eap="GPSK", identity="gpsk user",
                   password="abcdefghijklmnop0123456789abcdef",
                   scan_freq="2412")

    hostapd.add_ap(apdev[1], params)
    bssid2 = apdev[1]['bssid']

    dev[0].dump_monitor()
    logger.info("Roam to AP2")
    dev[0].scan_for_bss(bssid2, freq="2412")
    dev[0].request("ROAM " + bssid2)
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-SUCCESS"], timeout=10)
    if ev is None:
        raise Exception("EAP success timed out")
    dev[0].wait_connected(timeout=10, error="Roaming timed out")

    dev[0].dump_monitor()
    logger.info("Roam back to AP1")
    dev[0].scan(freq="2412")
    dev[0].request("ROAM " + bssid)
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-STARTED",
                            "CTRL-EVENT-CONNECTED"], timeout=20)
    if ev is None:
        raise Exception("Roaming with the AP timed out")
    if "CTRL-EVENT-CONNECTED" in ev:
        raise Exception("EAP exchange missing")
    ev = dev[0].wait_event(["CTRL-EVENT-CONNECTED"], timeout=20)
    if ev is None:
        raise Exception("Roaming with the AP timed out")

def test_pmksa_cache_ap_expiration(dev, apdev):
    """PMKSA cache entry expiring on AP"""
    params = hostapd.wpa2_eap_params(ssid="test-pmksa-cache")
    hapd = hostapd.add_ap(apdev[0], params)
    bssid = apdev[0]['bssid']
    dev[0].connect("test-pmksa-cache", proto="RSN", key_mgmt="WPA-EAP",
                   eap="GPSK", identity="gpsk-user-session-timeout",
                   password="abcdefghijklmnop0123456789abcdef",
                   scan_freq="2412")
    ev = hapd.wait_event([ "AP-STA-CONNECTED" ], timeout=5)
    if ev is None:
        raise Exception("No connection event received from hostapd")
    dev[0].request("DISCONNECT")
    time.sleep(5)
    dev[0].dump_monitor()
    dev[0].request("RECONNECT")
    ev = dev[0].wait_event(["CTRL-EVENT-EAP-STARTED",
                            "CTRL-EVENT-CONNECTED"], timeout=20)
    if ev is None:
        raise Exception("Roaming with the AP timed out")
    if "CTRL-EVENT-CONNECTED" in ev:
        raise Exception("EAP exchange missing")
    dev[0].wait_connected(timeout=20, error="Reconnect timed out")
    dev[0].dump_monitor()
    dev[0].wait_disconnected(timeout=20)
    dev[0].wait_connected(timeout=20, error="Reassociation timed out")

def test_pmksa_cache_multiple_sta(dev, apdev):
    """PMKSA cache with multiple stations"""
    params = hostapd.wpa2_eap_params(ssid="test-pmksa-cache")
    hostapd.add_ap(apdev[0], params)
    bssid = apdev[0]['bssid']
    for d in dev:
        d.flush_scan_cache()
    dev[0].connect("test-pmksa-cache", proto="RSN", key_mgmt="WPA-EAP",
                   eap="GPSK", identity="gpsk-user-session-timeout",
                   password="abcdefghijklmnop0123456789abcdef",
                   scan_freq="2412")
    dev[1].connect("test-pmksa-cache", proto="RSN", key_mgmt="WPA-EAP",
                   eap="GPSK", identity="gpsk user",
                   password="abcdefghijklmnop0123456789abcdef",
                   scan_freq="2412")
    dev[2].connect("test-pmksa-cache", proto="RSN", key_mgmt="WPA-EAP",
                   eap="GPSK", identity="gpsk-user-session-timeout",
                   password="abcdefghijklmnop0123456789abcdef",
                   scan_freq="2412")

    wpas = WpaSupplicant(global_iface='/tmp/wpas-wlan5')
    wpas.interface_add("wlan5")
    wpas.flush_scan_cache()
    wpas.connect("test-pmksa-cache", proto="RSN", key_mgmt="WPA-EAP",
                 eap="GPSK", identity="gpsk user",
                 password="abcdefghijklmnop0123456789abcdef",
                 scan_freq="2412")

    hostapd.add_ap(apdev[1], params)
    bssid2 = apdev[1]['bssid']

    logger.info("Roam to AP2")
    for sta in [ dev[1], dev[0], dev[2], wpas ]:
        sta.dump_monitor()
        sta.scan_for_bss(bssid2, freq="2412")
        if "OK" not in sta.request("ROAM " + bssid2):
            raise Exception("ROAM command failed (" + sta.ifname + ")")
        ev = sta.wait_event(["CTRL-EVENT-EAP-SUCCESS"], timeout=10)
        if ev is None:
            raise Exception("EAP success timed out")
        sta.wait_connected(timeout=10, error="Roaming timed out")
        sta.dump_monitor()

    logger.info("Roam back to AP1")
    for sta in [ dev[1], wpas, dev[0], dev[2] ]:
        sta.dump_monitor()
        sta.scan(freq="2412")
        sta.dump_monitor()
        sta.request("ROAM " + bssid)
        sta.wait_connected(timeout=10, error="Roaming timed out")
        sta.dump_monitor()

    time.sleep(4)

    logger.info("Roam back to AP2")
    for sta in [ dev[1], wpas, dev[0], dev[2] ]:
        sta.dump_monitor()
        sta.scan(freq="2412")
        sta.dump_monitor()
        sta.request("ROAM " + bssid2)
        sta.wait_connected(timeout=10, error="Roaming timed out")
        sta.dump_monitor()

def test_pmksa_cache_opportunistic_multiple_sta(dev, apdev):
    """Opportunistic PMKSA caching with multiple stations"""
    params = hostapd.wpa2_eap_params(ssid="test-pmksa-cache")
    params['okc'] = "1"
    hostapd.add_ap(apdev[0], params)
    bssid = apdev[0]['bssid']
    for d in dev:
        d.flush_scan_cache()
    wpas = WpaSupplicant(global_iface='/tmp/wpas-wlan5')
    wpas.interface_add("wlan5")
    wpas.flush_scan_cache()
    for sta in [ dev[0], dev[1], dev[2], wpas ]:
        sta.connect("test-pmksa-cache", proto="RSN", key_mgmt="WPA-EAP",
                    eap="GPSK", identity="gpsk user",
                    password="abcdefghijklmnop0123456789abcdef", okc=True,
                    scan_freq="2412")

    hostapd.add_ap(apdev[1], params)
    bssid2 = apdev[1]['bssid']

    logger.info("Roam to AP2")
    for sta in [ dev[2], dev[0], wpas, dev[1] ]:
        sta.dump_monitor()
        sta.scan_for_bss(bssid2, freq="2412")
        if "OK" not in sta.request("ROAM " + bssid2):
            raise Exception("ROAM command failed")
        ev = sta.wait_event(["CTRL-EVENT-EAP-STARTED",
                             "CTRL-EVENT-CONNECTED"], timeout=10)
        if ev is None:
            raise Exception("Roaming with the AP timed out")
        if "CTRL-EVENT-EAP-STARTED" in ev:
            raise Exception("Unexpected EAP exchange")
        pmksa2 = sta.get_pmksa(bssid2)
        if pmksa2 is None:
            raise Exception("No PMKSA cache entry created")
        sta.dump_monitor()

    logger.info("Roam back to AP1")
    for sta in [ dev[0], dev[1], dev[2], wpas ]:
        sta.dump_monitor()
        sta.scan_for_bss(bssid, freq="2412")
        sta.request("ROAM " + bssid)
        ev = sta.wait_event(["CTRL-EVENT-EAP-STARTED",
                             "CTRL-EVENT-CONNECTED"], timeout=10)
        if ev is None:
            raise Exception("Roaming with the AP timed out")
        if "CTRL-EVENT-EAP-STARTED" in ev:
            raise Exception("Unexpected EAP exchange")

def test_pmksa_cache_preauth_oom(dev, apdev):
    """RSN pre-authentication to generate PMKSA cache entry and OOM"""
    try:
        _test_pmksa_cache_preauth_oom(dev, apdev)
    finally:
        hostapd.cmd_execute(apdev[0], ['ip', 'link', 'set', 'dev', 'ap-br0',
                                       'down'])
        hostapd.cmd_execute(apdev[0], ['brctl', 'delbr', 'ap-br0'])

def _test_pmksa_cache_preauth_oom(dev, apdev):
    params = hostapd.wpa2_eap_params(ssid="test-wpa2-eap")
    params['bridge'] = 'ap-br0'
    hapd = hostapd.add_ap(apdev[0], params)
    hostapd.cmd_execute(apdev[0], ['brctl', 'setfd', 'ap-br0', '0'])
    hostapd.cmd_execute(apdev[0], ['ip', 'link', 'set', 'dev', 'ap-br0', 'up'])
    eap_connect(dev[0], hapd, "PAX", "pax.user@example.com",
                password_hex="0123456789abcdef0123456789abcdef",
                bssid=apdev[0]['bssid'])

    params = hostapd.wpa2_eap_params(ssid="test-wpa2-eap")
    params['bridge'] = 'ap-br0'
    params['rsn_preauth'] = '1'
    params['rsn_preauth_interfaces'] = 'ap-br0'
    hapd = hostapd.add_ap(apdev[1], params)
    bssid1 = apdev[1]['bssid']

    tests = [ (1, "rsn_preauth_receive"),
              (2, "rsn_preauth_receive"),
              (1, "rsn_preauth_send") ]
    for test in tests:
        with alloc_fail(hapd, test[0], test[1]):
            dev[0].scan_for_bss(bssid1, freq="2412")
            if "OK" not in dev[0].request("PREAUTH " + bssid1):
                raise Exception("PREAUTH failed")

            success = False
            count = 0
            for i in range(50):
                time.sleep(0.1)
                pmksa = dev[0].get_pmksa(bssid1)
                if pmksa:
                    success = True
                    break
                state = hapd.request('GET_ALLOC_FAIL')
                if state.startswith('0:'):
                    count += 1
                    if count > 2:
                        break
            logger.info("PMKSA cache success: " + str(success))

            dev[0].request("PMKSA_FLUSH")
            dev[0].wait_disconnected()
            dev[0].wait_connected()
            dev[0].dump_monitor()

def test_pmksa_cache_size_limit(dev, apdev):
    """PMKSA cache size limit in wpa_supplicant"""
    try:
        _test_pmksa_cache_size_limit(dev, apdev)
    finally:
        try:
            hapd = hostapd.HostapdGlobal(apdev[0])
            hapd.flush()
            hapd.remove(apdev[0]['ifname'])
        except:
            pass
        params = hostapd.wpa2_eap_params(ssid="test-pmksa-cache")
        bssid = apdev[0]['bssid']
        params['bssid'] = bssid
        hostapd.add_ap(apdev[0], params)

def _test_pmksa_cache_size_limit(dev, apdev):
    params = hostapd.wpa2_eap_params(ssid="test-pmksa-cache")
    id = dev[0].connect("test-pmksa-cache", proto="RSN", key_mgmt="WPA-EAP",
                        eap="GPSK", identity="gpsk user",
                        password="abcdefghijklmnop0123456789abcdef",
                        scan_freq="2412", only_add_network=True)
    for i in range(33):
        bssid = apdev[0]['bssid'][0:15] + "%02x" % i
        logger.info("Iteration with BSSID " + bssid)
        params['bssid'] = bssid
        hostapd.add_ap(apdev[0], params)
        dev[0].request("BSS_FLUSH 0")
        dev[0].scan_for_bss(bssid, freq=2412, only_new=True)
        dev[0].select_network(id)
        dev[0].wait_connected()
        dev[0].request("DISCONNECT")
        dev[0].wait_disconnected()
        dev[0].dump_monitor()
        entries = len(dev[0].request("PMKSA").splitlines()) - 1
        if i == 32:
            if entries != 32:
                raise Exception("Unexpected number of PMKSA entries after expected removal of the oldest entry")
        elif i + 1 != entries:
            raise Exception("Unexpected number of PMKSA entries")

        hapd = hostapd.HostapdGlobal(apdev[0])
        hapd.flush()
        hapd.remove(apdev[0]['ifname'])

def test_pmksa_cache_preauth_timeout(dev, apdev):
    """RSN pre-authentication timing out"""
    try:
        _test_pmksa_cache_preauth_timeout(dev, apdev)
    finally:
        dev[0].request("SET dot11RSNAConfigSATimeout 60")

def _test_pmksa_cache_preauth_timeout(dev, apdev):
    dev[0].request("SET dot11RSNAConfigSATimeout 1")
    params = hostapd.wpa2_eap_params(ssid="test-wpa2-eap")
    hapd = hostapd.add_ap(apdev[0], params)
    eap_connect(dev[0], hapd, "PAX", "pax.user@example.com",
                password_hex="0123456789abcdef0123456789abcdef",
                bssid=apdev[0]['bssid'])
    if "OK" not in dev[0].request("PREAUTH f2:11:22:33:44:55"):
        raise Exception("PREAUTH failed")
    ev = dev[0].wait_event(["RSN: pre-authentication with"], timeout=5)
    if ev is None:
        raise Exception("No timeout event seen")
    if "timed out" not in ev:
        raise Exception("Unexpected event: " + ev)

def test_pmksa_cache_preauth_wpas_oom(dev, apdev):
    """RSN pre-authentication OOM in wpa_supplicant"""
    params = hostapd.wpa2_eap_params(ssid="test-wpa2-eap")
    hapd = hostapd.add_ap(apdev[0], params)
    eap_connect(dev[0], hapd, "PAX", "pax.user@example.com",
                password_hex="0123456789abcdef0123456789abcdef",
                bssid=apdev[0]['bssid'])
    for i in range(1, 11):
        with alloc_fail(dev[0], i, "rsn_preauth_init"):
            res = dev[0].request("PREAUTH f2:11:22:33:44:55").strip()
            logger.info("Iteration %d - PREAUTH command results: %s" % (i, res))
            for j in range(10):
                state = dev[0].request('GET_ALLOC_FAIL')
                if state.startswith('0:'):
                    break
                time.sleep(0.05)

def test_pmksa_cache_ctrl(dev, apdev):
    """PMKSA cache control interface operations"""
    params = hostapd.wpa2_eap_params(ssid="test-pmksa-cache")
    hapd = hostapd.add_ap(apdev[0], params)
    bssid = apdev[0]['bssid']
    addr = dev[0].own_addr()

    dev[0].connect("test-pmksa-cache", proto="RSN", key_mgmt="WPA-EAP",
                   eap="GPSK", identity="gpsk user",
                   password="abcdefghijklmnop0123456789abcdef",
                   scan_freq="2412")

    pmksa_sta = dev[0].get_pmksa(bssid)
    if pmksa_sta is None:
        raise Exception("No PMKSA cache entry created on STA")
    pmksa_ap = hapd.get_pmksa(addr)
    if pmksa_ap is None:
        raise Exception("No PMKSA cache entry created on AP")
    if pmksa_sta['pmkid'] != pmksa_ap['pmkid']:
        raise Exception("PMKID mismatch in PMKSA cache entries")

    if "OK" not in hapd.request("PMKSA_FLUSH"):
        raise Exception("PMKSA_FLUSH failed")
    pmksa_ap = hapd.get_pmksa(addr)
    if pmksa_ap is not None:
        raise Exception("PMKSA cache entry was not removed on AP")

    dev[0].request("DISCONNECT")
    dev[0].wait_disconnected()
    dev[0].request("RECONNECT")
    dev[0].wait_connected()

    pmksa_sta2 = dev[0].get_pmksa(bssid)
    if pmksa_sta2 is None:
        raise Exception("No PMKSA cache entry created on STA after reconnect")
    pmksa_ap2 = hapd.get_pmksa(addr)
    if pmksa_ap2 is None:
        raise Exception("No PMKSA cache entry created on AP after reconnect")
    if pmksa_sta2['pmkid'] != pmksa_ap2['pmkid']:
        raise Exception("PMKID mismatch in PMKSA cache entries after reconnect")
    if pmksa_sta2['pmkid'] == pmksa_sta['pmkid']:
        raise Exception("PMKID did not change after reconnect")
