# Test various AP mode parameters
# Copyright (c) 2014, Qualcomm Atheros, Inc.
#
# This software may be distributed under the terms of the BSD license.
# See README for more details.

from remotehost import remote_compatible
import logging
logger = logging.getLogger()
import os

import hwsim_utils
import hostapd
from tshark import run_tshark
from utils import alloc_fail

@remote_compatible
def test_ap_fragmentation_rts_set_high(dev, apdev):
    """WPA2-PSK AP with fragmentation and RTS thresholds larger than frame length"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    params['rts_threshold'] = "1000"
    params['fragm_threshold'] = "2000"
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
    hwsim_utils.test_connectivity(dev[0], hapd)

@remote_compatible
def test_ap_fragmentation_open(dev, apdev):
    """Open AP with fragmentation threshold"""
    ssid = "fragmentation"
    params = {}
    params['ssid'] = ssid
    params['fragm_threshold'] = "1000"
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, key_mgmt="NONE", scan_freq="2412")
    hwsim_utils.test_connectivity(dev[0], hapd)

@remote_compatible
def test_ap_fragmentation_wpa2(dev, apdev):
    """WPA2-PSK AP with fragmentation threshold"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    params['fragm_threshold'] = "1000"
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
    hwsim_utils.test_connectivity(dev[0], hapd)

def test_ap_vendor_elements(dev, apdev):
    """WPA2-PSK AP with vendor elements added"""
    bssid = apdev[0]['bssid']
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    params['vendor_elements'] = "dd0411223301"
    params['assocresp_elements'] = "dd0411223302"
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
    bss = dev[0].get_bss(bssid)
    if "dd0411223301" not in bss['ie']:
        raise Exception("Vendor element not shown in scan results")

    hapd.set('vendor_elements', 'dd051122330203dd0400137400dd04001374ff')
    if "OK" not in hapd.request("UPDATE_BEACON"):
        raise Exception("UPDATE_BEACON failed")
    dev[1].scan_for_bss(apdev[0]['bssid'], freq="2412")
    bss = dev[1].get_bss(bssid)
    if "dd0411223301" in bss['ie']:
        raise Exception("Old vendor element still in scan results")
    if "dd051122330203" not in bss['ie']:
        raise Exception("New vendor element not shown in scan results")

def test_ap_element_parse(dev, apdev):
    """Information element parsing - extra coverage"""
    bssid = apdev[0]['bssid']
    ssid = "test-wpa2-psk"
    params = { 'ssid': ssid,
               'vendor_elements': "380501020304059e009e009e009e009e009e00" }
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].scan_for_bss(apdev[0]['bssid'], freq="2412")
    bss = dev[0].get_bss(bssid)
    if "38050102030405" not in bss['ie']:
        raise Exception("Timeout element not shown in scan results")

@remote_compatible
def test_ap_element_parse_oom(dev, apdev):
    """Information element parsing OOM"""
    bssid = apdev[0]['bssid']
    ssid = "test-wpa2-psk"
    params = { 'ssid': ssid,
               'vendor_elements': "dd0d506f9a0a00000600411c440028" }
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].scan_for_bss(apdev[0]['bssid'], freq="2412")
    with alloc_fail(dev[0], 1, "wpabuf_alloc;ieee802_11_vendor_ie_concat"):
        bss = dev[0].get_bss(bssid)
        logger.info(str(bss))

def test_ap_country(dev, apdev):
    """WPA2-PSK AP setting country code and using 5 GHz band"""
    try:
        hapd = None
        bssid = apdev[0]['bssid']
        ssid = "test-wpa2-psk"
        passphrase = 'qwertyuiop'
        params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
        params['country_code'] = 'FI'
        params['ieee80211d'] = '1'
        params['hw_mode'] = 'a'
        params['channel'] = '36'
        hapd = hostapd.add_ap(apdev[0], params)
        dev[0].connect(ssid, psk=passphrase, scan_freq="5180")
        hwsim_utils.test_connectivity(dev[0], hapd)
    finally:
        dev[0].request("DISCONNECT")
        if hapd:
            hapd.request("DISABLE")
        hostapd.cmd_execute(apdev[0], ['iw', 'reg', 'set', '00'])
        dev[0].flush_scan_cache()

def test_ap_acl_accept(dev, apdev):
    """MAC ACL accept list"""
    ssid = "acl"
    params = {}
    params['ssid'] = ssid
    params['accept_mac_file'] = "hostapd.macaddr"
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].scan_for_bss(apdev[0]['bssid'], freq="2412")
    dev[0].connect(ssid, key_mgmt="NONE", scan_freq="2412")
    dev[1].scan_for_bss(apdev[0]['bssid'], freq="2412")
    dev[1].connect(ssid, key_mgmt="NONE", scan_freq="2412")
    dev[0].request("REMOVE_NETWORK all")
    dev[1].request("REMOVE_NETWORK all")
    hapd.request("SET macaddr_acl 1")
    dev[1].dump_monitor()
    dev[1].connect(ssid, key_mgmt="NONE", scan_freq="2412", wait_connect=False)
    dev[0].connect(ssid, key_mgmt="NONE", scan_freq="2412")
    ev = dev[1].wait_event(["CTRL-EVENT-CONNECTED"], timeout=1)
    if ev is not None:
        raise Exception("Unexpected association")

def test_ap_acl_deny(dev, apdev):
    """MAC ACL deny list"""
    ssid = "acl"
    params = {}
    params['ssid'] = ssid
    params['deny_mac_file'] = "hostapd.macaddr"
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].scan_for_bss(apdev[0]['bssid'], freq="2412")
    dev[0].connect(ssid, key_mgmt="NONE", scan_freq="2412", wait_connect=False)
    dev[1].scan_for_bss(apdev[0]['bssid'], freq="2412")
    dev[1].connect(ssid, key_mgmt="NONE", scan_freq="2412")
    ev = dev[0].wait_event(["CTRL-EVENT-CONNECTED"], timeout=1)
    if ev is not None:
        raise Exception("Unexpected association")

@remote_compatible
def test_ap_wds_sta(dev, apdev):
    """WPA2-PSK AP with STA using 4addr mode"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    params['wds_sta'] = "1"
    params['wds_bridge'] = "wds-br0"
    hapd = hostapd.add_ap(apdev[0], params)

    try:
        dev[0].cmd_execute(['brctl', 'addbr', 'wds-br0'])
        dev[0].cmd_execute(['brctl', 'setfd', 'wds-br0', '0'])
        dev[0].cmd_execute(['ip', 'link', 'set', 'dev', 'wds-br0', 'up'])
        dev[0].cmd_execute(['iw', dev[0].ifname, 'set', '4addr', 'on'])
        dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
        hwsim_utils.test_connectivity_iface(dev[0], hapd, "wds-br0",
                                            max_tries=15)
    finally:
        dev[0].cmd_execute(['iw', dev[0].ifname, 'set', '4addr', 'off'])
        dev[0].cmd_execute(['ip', 'link', 'set', 'dev', 'wds-br0', 'down'])
        dev[0].cmd_execute(['brctl', 'delbr', 'wds-br0'])

@remote_compatible
def test_ap_inactivity_poll(dev, apdev):
    """AP using inactivity poll"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    params['ap_max_inactivity'] = "1"
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
    hapd.set("ext_mgmt_frame_handling", "1")
    dev[0].request("DISCONNECT")
    ev = hapd.wait_event(["MGMT-RX"], timeout=5)
    if ev is None:
        raise Exception("MGMT RX wait timed out for Deauth")
    hapd.set("ext_mgmt_frame_handling", "0")
    ev = hapd.wait_event(["AP-STA-DISCONNECTED"], timeout=30)
    if ev is None:
        raise Exception("STA disconnection on inactivity was not reported")

@remote_compatible
def test_ap_inactivity_disconnect(dev, apdev):
    """AP using inactivity disconnect"""
    ssid = "test-wpa2-psk"
    passphrase = 'qwertyuiop'
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    params['ap_max_inactivity'] = "1"
    params['skip_inactivity_poll'] = "1"
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
    hapd.set("ext_mgmt_frame_handling", "1")
    dev[0].request("DISCONNECT")
    ev = hapd.wait_event(["MGMT-RX"], timeout=5)
    if ev is None:
        raise Exception("MGMT RX wait timed out for Deauth")
    hapd.set("ext_mgmt_frame_handling", "0")
    ev = hapd.wait_event(["AP-STA-DISCONNECTED"], timeout=30)
    if ev is None:
        raise Exception("STA disconnection on inactivity was not reported")

@remote_compatible
def test_ap_basic_rates(dev, apdev):
    """Open AP with lots of basic rates"""
    ssid = "basic rates"
    params = {}
    params['ssid'] = ssid
    params['basic_rates'] = "10 20 55 110 60 90 120 180 240 360 480 540"
    hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, key_mgmt="NONE", scan_freq="2412")

@remote_compatible
def test_ap_short_preamble(dev, apdev):
    """Open AP with short preamble"""
    ssid = "short preamble"
    params = {}
    params['ssid'] = ssid
    params['preamble'] = "1"
    hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, key_mgmt="NONE", scan_freq="2412")

def test_ap_spectrum_management_required(dev, apdev):
    """Open AP with spectrum management required"""
    ssid = "spectrum mgmt"
    params = {}
    params['ssid'] = ssid
    params["country_code"] = "JP"
    params["hw_mode"] = "a"
    params["channel"] = "36"
    params["ieee80211d"] = "1"
    params["local_pwr_constraint"] = "3"
    params['spectrum_mgmt_required'] = "1"
    try:
        hapd = None
        hapd = hostapd.add_ap(apdev[0], params)
        dev[0].connect(ssid, key_mgmt="NONE", scan_freq="5180")
    finally:
        dev[0].request("DISCONNECT")
        if hapd:
            hapd.request("DISABLE")
        hostapd.cmd_execute(apdev[0], ['iw', 'reg', 'set', '00'])
        dev[0].flush_scan_cache()

@remote_compatible
def test_ap_max_listen_interval(dev, apdev):
    """Open AP with maximum listen interval limit"""
    ssid = "listen"
    params = {}
    params['ssid'] = ssid
    params['max_listen_interval'] = "1"
    hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, key_mgmt="NONE", scan_freq="2412", wait_connect=False)
    ev = dev[0].wait_event(["CTRL-EVENT-ASSOC-REJECT"])
    if ev is None:
        raise Exception("Association rejection not reported")
    if "status_code=51" not in ev:
        raise Exception("Unexpected ASSOC-REJECT reason")

@remote_compatible
def test_ap_max_num_sta(dev, apdev):
    """Open AP with maximum STA count"""
    ssid = "max"
    params = {}
    params['ssid'] = ssid
    params['max_num_sta'] = "1"
    hostapd.add_ap(apdev[0], params)
    dev[1].connect(ssid, key_mgmt="NONE", scan_freq="2412")
    dev[0].connect(ssid, key_mgmt="NONE", scan_freq="2412", wait_connect=False)
    ev = dev[0].wait_event(["CTRL-EVENT-CONNECTED"], timeout=1)
    if ev is not None:
        raise Exception("Unexpected association")

def test_ap_max_num_sta_no_probe_resp(dev, apdev, params):
    """Maximum STA count and limit on Probe Response frames"""
    logdir = params['logdir']
    dev[0].flush_scan_cache()
    ssid = "max"
    params = {}
    params['ssid'] = ssid
    params['beacon_int'] = "2000"
    params['max_num_sta'] = "1"
    params['no_probe_resp_if_max_sta'] = "1"
    hostapd.add_ap(apdev[0], params)
    dev[1].connect(ssid, key_mgmt="NONE", scan_freq="2412")
    dev[0].scan(freq=2412, type="ONLY")
    dev[0].scan(freq=2412, type="ONLY")
    seen = dev[0].get_bss(apdev[0]['bssid']) != None
    dev[1].scan(freq=2412, type="ONLY")
    if seen:
        out = run_tshark(os.path.join(logdir, "hwsim0.pcapng"),
                         "wlan.fc.type_subtype == 5", ["wlan.da" ])
        if out:
            if dev[0].own_addr() not in out:
                # Discovery happened through Beacon frame reception. That's not
                # an error case.
                seen = False
            if dev[1].own_addr() not in out:
                raise Exception("No Probe Response frames to dev[1] seen")
        if seen:
            raise Exception("AP found unexpectedly")

@remote_compatible
def test_ap_tx_queue_params(dev, apdev):
    """Open AP with TX queue params set"""
    ssid = "tx"
    params = {}
    params['ssid'] = ssid
    params['tx_queue_data2_aifs'] = "4"
    params['tx_queue_data2_cwmin'] = "7"
    params['tx_queue_data2_cwmax'] = "1023"
    params['tx_queue_data2_burst'] = "4.2"
    params['tx_queue_data1_aifs'] = "4"
    params['tx_queue_data1_cwmin'] = "7"
    params['tx_queue_data1_cwmax'] = "1023"
    params['tx_queue_data1_burst'] = "2"
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, key_mgmt="NONE", scan_freq="2412")
    hwsim_utils.test_connectivity(dev[0], hapd)
