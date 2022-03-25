# wpa_supplicant AP mode tests
# Copyright (c) 2014, Qualcomm Atheros, Inc.
#
# This software may be distributed under the terms of the BSD license.
# See README for more details.

from remotehost import remote_compatible
import time
import logging
logger = logging.getLogger()

import hwsim_utils
from utils import HwsimSkip, alloc_fail
from wpasupplicant import WpaSupplicant
from test_p2p_channel import set_country

def wait_ap_ready(dev):
    ev = dev.wait_event(["CTRL-EVENT-CONNECTED"])
    if ev is None:
        raise Exception("AP failed to start")

def test_wpas_ap_open(dev):
    """wpa_supplicant AP mode - open network"""
    if "FAIL" not in dev[0].request("DEAUTHENTICATE 00:11:22:33:44:55"):
        raise Exception("Unexpected DEAUTHENTICATE accepted")
    if "FAIL" not in dev[0].request("DISASSOCIATE 00:11:22:33:44:55"):
        raise Exception("Unexpected DISASSOCIATE accepted")
    if "FAIL" not in dev[0].request("CHAN_SWITCH 0 2432"):
        raise Exception("Unexpected CHAN_SWITCH accepted")

    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network_quoted(id, "ssid", "wpas-ap-open")
    dev[0].set_network(id, "key_mgmt", "NONE")
    dev[0].set_network(id, "frequency", "2412")
    dev[0].set_network(id, "scan_freq", "2412")
    dev[0].select_network(id)
    wait_ap_ready(dev[0])

    if "FAIL" not in dev[0].request("DEAUTHENTICATE foo"):
        raise Exception("Invalid DEAUTHENTICATE accepted")
    if "FAIL" not in dev[0].request("DISASSOCIATE foo"):
        raise Exception("Invalid DISASSOCIATE accepted")

    dev[1].connect("wpas-ap-open", key_mgmt="NONE", scan_freq="2412")
    dev[2].connect("wpas-ap-open", key_mgmt="NONE", scan_freq="2412")
    hwsim_utils.test_connectivity(dev[0], dev[1])
    hwsim_utils.test_connectivity(dev[1], dev[2])

    addr1 = dev[1].p2p_interface_addr()
    addr2 = dev[2].p2p_interface_addr()
    addrs = [ addr1, addr2 ]
    sta = dev[0].get_sta(None)
    if sta['addr'] not in addrs:
        raise Exception("Unexpected STA address")
    sta1 = dev[0].get_sta(sta['addr'])
    if sta1['addr'] not in addrs:
        raise Exception("Unexpected STA address")
    sta2 = dev[0].get_sta(sta['addr'], next=True)
    if sta2['addr'] not in addrs:
        raise Exception("Unexpected STA2 address")
    sta3 = dev[0].get_sta(sta2['addr'], next=True)
    if len(sta3) != 0:
        raise Exception("Unexpected STA iteration result (did not stop)")

    status = dev[0].get_status()
    if status['mode'] != "AP":
        raise Exception("Unexpected status mode")

    dev[1].dump_monitor()
    dev[2].dump_monitor()
    dev[0].request("DEAUTHENTICATE " + addr1)
    dev[0].request("DISASSOCIATE " + addr2)
    dev[1].wait_disconnected(timeout=10)
    dev[2].wait_disconnected(timeout=10)
    dev[1].wait_connected(timeout=10, error="Reconnection timed out")
    dev[2].wait_connected(timeout=10, error="Reconnection timed out")
    dev[1].request("DISCONNECT")
    dev[2].request("DISCONNECT")

@remote_compatible
def test_wpas_ap_wep(dev):
    """wpa_supplicant AP mode - WEP"""
    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network_quoted(id, "ssid", "wpas-ap-wep")
    dev[0].set_network(id, "key_mgmt", "NONE")
    dev[0].set_network(id, "frequency", "2412")
    dev[0].set_network(id, "scan_freq", "2412")
    dev[0].set_network_quoted(id, "wep_key0", "hello")
    dev[0].select_network(id)
    wait_ap_ready(dev[0])

    dev[1].connect("wpas-ap-wep", key_mgmt="NONE", wep_key0='"hello"',
                   scan_freq="2412")
    hwsim_utils.test_connectivity(dev[0], dev[1])
    dev[1].request("DISCONNECT")

@remote_compatible
def test_wpas_ap_no_ssid(dev):
    """wpa_supplicant AP mode - invalid network configuration"""
    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network(id, "key_mgmt", "NONE")
    dev[0].set_network(id, "frequency", "2412")
    dev[0].set_network(id, "scan_freq", "2412")
    dev[0].select_network(id)
    ev = dev[0].wait_event(["CTRL-EVENT-CONNECTED"], timeout=1)
    if ev is not None:
        raise Exception("Unexpected AP start")

@remote_compatible
def test_wpas_ap_default_frequency(dev):
    """wpa_supplicant AP mode - default frequency"""
    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network_quoted(id, "ssid", "wpas-ap-open")
    dev[0].set_network(id, "key_mgmt", "NONE")
    dev[0].set_network(id, "scan_freq", "2412")
    dev[0].select_network(id)
    wait_ap_ready(dev[0])
    dev[1].connect("wpas-ap-open", key_mgmt="NONE", scan_freq="2462")
    dev[1].request("DISCONNECT")

@remote_compatible
def test_wpas_ap_invalid_frequency(dev):
    """wpa_supplicant AP mode - invalid frequency configuration"""
    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network_quoted(id, "ssid", "wpas-ap-open")
    dev[0].set_network(id, "key_mgmt", "NONE")
    dev[0].set_network(id, "frequency", "2413")
    dev[0].set_network(id, "scan_freq", "2412")
    dev[0].select_network(id)
    ev = dev[0].wait_event(["CTRL-EVENT-CONNECTED"], timeout=1)
    if ev is not None:
        raise Exception("Unexpected AP start")

def test_wpas_ap_wps(dev):
    """wpa_supplicant AP mode - WPS operations"""
    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network_quoted(id, "ssid", "wpas-ap-wps")
    dev[0].set_network_quoted(id, "psk", "1234567890")
    dev[0].set_network(id, "frequency", "2412")
    dev[0].set_network(id, "scan_freq", "2412")
    dev[0].select_network(id)
    wait_ap_ready(dev[0])
    bssid = dev[0].p2p_interface_addr()

    logger.info("Test PBC mode start/stop")
    if "FAIL" not in dev[0].request("WPS_CANCEL"):
        raise Exception("Unexpected WPS_CANCEL success")
    dev[0].request("WPS_PBC")
    ev = dev[0].wait_event(["WPS-PBC-ACTIVE"])
    if ev is None:
        raise Exception("PBC mode start timeout")
    if "OK" not in dev[0].request("WPS_CANCEL"):
        raise Exception("Unexpected WPS_CANCEL failure")
    ev = dev[0].wait_event(["WPS-TIMEOUT"])
    if ev is None:
        raise Exception("PBC mode disabling timeout")

    logger.info("Test PBC protocol run")
    dev[0].request("WPS_PBC")
    ev = dev[0].wait_event(["WPS-PBC-ACTIVE"])
    if ev is None:
        raise Exception("PBC mode start timeout")
    dev[1].request("WPS_PBC")
    dev[1].wait_connected(timeout=30, error="WPS PBC operation timed out")
    hwsim_utils.test_connectivity(dev[0], dev[1])

    logger.info("Test AP PIN to learn configuration")
    pin = dev[0].request("WPS_AP_PIN random")
    if "FAIL" in pin:
        raise Exception("Could not generate random AP PIN")
    if pin not in dev[0].request("WPS_AP_PIN get"):
        raise Exception("Could not fetch current AP PIN")
    dev[2].wps_reg(bssid, pin)
    hwsim_utils.test_connectivity(dev[1], dev[2])

    dev[1].request("REMOVE_NETWORK all")
    dev[2].request("REMOVE_NETWORK all")

    logger.info("Test AP PIN operations")
    dev[0].request("WPS_AP_PIN disable")
    dev[0].request("WPS_AP_PIN set " + pin + " 1")
    time.sleep(1.1)
    if "FAIL" not in dev[0].request("WPS_AP_PIN get"):
        raise Exception("AP PIN unexpectedly still enabled")

    pin = dev[1].wps_read_pin()
    dev[0].request("WPS_PIN any " + pin)
    dev[1].request("WPS_PIN any " + pin)
    dev[1].wait_connected(timeout=30)
    dev[1].request("REMOVE_NETWORK all")
    dev[1].dump_monitor()

    dev[0].request("WPS_PIN any " + pin + " 100")
    dev[1].request("WPS_PIN any " + pin)
    dev[1].wait_connected(timeout=30)
    dev[1].request("REMOVE_NETWORK all")
    dev[1].dump_monitor()

    dev[0].request("WPS_AP_PIN set 12345670")
    dev[0].dump_monitor()

    runs = ("88887777", "12340000", "00000000", "12345670")
    for pin in runs:
        logger.info("Try AP PIN " + pin)
        dev[2].dump_monitor()
        dev[2].request("WPS_REG " + bssid + " " + pin)
        ev = dev[2].wait_event(["WPS-SUCCESS", "WPS-FAIL msg"], timeout=15)
        if ev is None:
            raise Exception("WPS operation timed out")
        if "WPS-SUCCESS" in ev:
            raise Exception("WPS operation succeeded unexpectedly")
        dev[2].wait_disconnected(timeout=10)
        dev[2].request("WPS_CANCEL")
        dev[2].request("REMOVE_NETWORK all")
    ev = dev[0].wait_event(["WPS-AP-SETUP-LOCKED"])
    if ev is None:
        raise Exception("WPS AP PIN not locked")

    dev[0].dump_monitor()
    logger.info("Test random AP PIN timeout")
    pin = dev[0].request("WPS_AP_PIN random 1")
    if "FAIL" in pin:
        raise Exception("Could not generate random AP PIN")
    res = dev[0].request("WPS_AP_PIN get")
    if pin not in res:
        raise Exception("Could not fetch current AP PIN")
    for i in range(10):
        time.sleep(0.2)
        res = dev[0].request("WPS_AP_PIN get")
        if "FAIL" in res:
            break
    if "FAIL" not in res:
        raise Exception("WPS_AP_PIN random timeout did not work")

    if "FAIL" not in dev[0].request("WPS_AP_PIN foo"):
        raise Exception("Invalid WPS_AP_PIN command not rejected")
    if "FAIL" not in dev[0].request("WPS_AP_PIN set"):
        raise Exception("Invalid WPS_AP_PIN command not rejected")

def test_wpas_ap_wps_frag(dev):
    """wpa_supplicant AP mode - WPS operations with fragmentation"""
    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network_quoted(id, "ssid", "wpas-ap-wps")
    dev[0].set_network_quoted(id, "psk", "1234567890")
    dev[0].set_network(id, "frequency", "2412")
    dev[0].set_network(id, "scan_freq", "2412")
    dev[0].set_network(id, "fragment_size", "300")
    dev[0].select_network(id)
    wait_ap_ready(dev[0])
    bssid = dev[0].own_addr()

    pin = dev[1].wps_read_pin()
    dev[0].request("WPS_PIN any " + pin)
    dev[1].scan_for_bss(bssid, freq="2412")
    dev[1].request("WPS_PIN " + bssid + " " + pin)
    dev[1].wait_connected(timeout=30)

def test_wpas_ap_wps_pbc_overlap(dev):
    """wpa_supplicant AP mode - WPS operations with PBC overlap"""
    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network_quoted(id, "ssid", "wpas-ap-wps")
    dev[0].set_network_quoted(id, "psk", "1234567890")
    dev[0].set_network(id, "frequency", "2412")
    dev[0].set_network(id, "scan_freq", "2412")
    dev[0].select_network(id)
    wait_ap_ready(dev[0])
    bssid = dev[0].p2p_interface_addr()

    dev[1].scan_for_bss(bssid, freq="2412")
    dev[1].dump_monitor()
    dev[2].scan_for_bss(bssid, freq="2412")
    dev[2].dump_monitor()
    dev[0].request("WPS_PBC")
    dev[1].request("WPS_PBC " + bssid)
    dev[2].request("WPS_PBC " + bssid)

    ev = dev[1].wait_event(["WPS-M2D"], timeout=15)
    if ev is None:
        raise Exception("PBC session overlap not detected (dev1)")
    if "config_error=12" not in ev:
        raise Exception("PBC session overlap not correctly reported (dev1)")

    ev = dev[2].wait_event(["WPS-M2D"], timeout=15)
    if ev is None:
        raise Exception("PBC session overlap not detected (dev2)")
    if "config_error=12" not in ev:
        raise Exception("PBC session overlap not correctly reported (dev2)")

    if "FAIL-PBC-OVERLAP" not in dev[0].request("WPS_PBC"):
        raise Exception("WPS_PBC(AP) accepted during overlap")
    if "FAIL-PBC-OVERLAP" not in dev[0].request("WPS_PBC any"):
        raise Exception("WPS_PBC(AP) accepted during overlap")
    dev[0].request("WPS_CANCEL")
    dev[1].request("WPS_CANCEL")
    dev[2].request("WPS_CANCEL")

@remote_compatible
def test_wpas_ap_wps_disabled(dev):
    """wpa_supplicant AP mode - WPS disabled"""
    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network_quoted(id, "ssid", "wpas-ap-no-wps")
    dev[0].set_network_quoted(id, "psk", "12345678")
    dev[0].set_network(id, "frequency", "2412")
    dev[0].set_network(id, "scan_freq", "2412")
    dev[0].set_network(id, "wps_disabled", "1")
    dev[0].select_network(id)
    wait_ap_ready(dev[0])

    dev[1].connect("wpas-ap-no-wps", psk="12345678", scan_freq="2412")
    dev[1].request("DISCONNECT")
    dev[1].wait_disconnected()

def test_wpas_ap_dfs(dev):
    """wpa_supplicant AP mode - DFS"""
    if dev[0].get_mcc() > 1:
        raise HwsimSkip("DFS is not supported with multi channel contexts")

    try:
        _test_wpas_ap_dfs(dev)
    finally:
        set_country("00")
        dev[0].request("SET country 00")
        dev[1].flush_scan_cache()

def _test_wpas_ap_dfs(dev):
    set_country("US")
    dev[0].request("SET country US")
    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network_quoted(id, "ssid", "wpas-ap-dfs")
    dev[0].set_network(id, "key_mgmt", "NONE")
    dev[0].set_network(id, "frequency", "5260")
    dev[0].set_network(id, "scan_freq", "5260")
    dev[0].select_network(id)

    ev = dev[0].wait_event(["DFS-CAC-START"])
    if ev is None:
        # For now, assume DFS is not supported by all kernel builds.
        raise HwsimSkip("CAC did not start - assume not supported")

    ev = dev[0].wait_event(["DFS-CAC-COMPLETED"], timeout=70)
    if ev is None:
        raise Exception("CAC did not complete")
    if "success=1" not in ev:
        raise Exception("CAC failed")
    if "freq=5260" not in ev:
        raise Exception("Unexpected DFS freq result")

    ev = dev[0].wait_event(["CTRL-EVENT-CONNECTED"])
    if ev is None:
        raise Exception("AP failed to start")

    dev[1].connect("wpas-ap-dfs", key_mgmt="NONE")

@remote_compatible
def test_wpas_ap_disable(dev):
    """wpa_supplicant AP mode - DISABLE_NETWORK"""
    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network_quoted(id, "ssid", "wpas-ap-open")
    dev[0].set_network(id, "key_mgmt", "NONE")
    dev[0].set_network(id, "scan_freq", "2412")
    dev[0].select_network(id)

    ev = dev[0].wait_event(["AP-ENABLED"])
    if ev is None:
        raise Exception("AP-ENABLED event not seen")
    wait_ap_ready(dev[0])
    dev[0].request("DISABLE_NETWORK %d" % id)
    ev = dev[0].wait_event(["AP-DISABLED"])
    if ev is None:
        raise Exception("AP-DISABLED event not seen")
    dev[0].wait_disconnected()

def test_wpas_ap_acs(dev):
    """wpa_supplicant AP mode - ACS"""
    res = dev[0].get_capability("acs")
    if res is None or "ACS" not in res:
        raise HwsimSkip("ACS not supported")

    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network_quoted(id, "ssid", "wpas-ap-open")
    dev[0].set_network(id, "key_mgmt", "NONE")
    dev[0].set_network(id, "frequency", "2417")
    dev[0].set_network(id, "scan_freq", "2417")
    dev[0].set_network(id, "acs", "1")
    dev[0].select_network(id)
    wait_ap_ready(dev[0])

    # ACS prefers channels 1, 6, 11
    freq = dev[0].get_status_field('freq')
    if freq == "2417":
        raise Exception("Unexpected operating channel selected")

    dev[1].connect("wpas-ap-open", key_mgmt="NONE", scan_freq=freq)

@remote_compatible
def test_wpas_ap_and_assoc_req_p2p_ie(dev):
    """wpa_supplicant AP mode - unexpected P2P IE in Association Request"""
    try:
        _test_wpas_ap_and_assoc_req_p2p_ie(dev)
    finally:
        dev[1].request("VENDOR_ELEM_REMOVE 13 *")
        dev[0].request("P2P_SET disabled 0")

def _test_wpas_ap_and_assoc_req_p2p_ie(dev):
    dev[0].request("P2P_SET disabled 1")
    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network_quoted(id, "ssid", "wpas-ap-open")
    dev[0].set_network(id, "key_mgmt", "NONE")
    dev[0].set_network(id, "frequency", "2412")
    dev[0].set_network(id, "scan_freq", "2412")
    dev[0].select_network(id)
    wait_ap_ready(dev[0])

    dev[1].request("VENDOR_ELEM_ADD 13 dd04506f9a09")
    dev[1].connect("wpas-ap-open", key_mgmt="NONE", scan_freq="2412")
    dev[1].request("DISCONNECT")
    dev[1].wait_disconnected()

    dev[0].request("DISCONNECT")
    dev[0].wait_disconnected()

@remote_compatible
def test_wpas_ap_open_ht_disabled(dev):
    """wpa_supplicant AP mode - open network and HT disabled"""
    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network_quoted(id, "ssid", "wpas-ap-open")
    dev[0].set_network(id, "key_mgmt", "NONE")
    dev[0].set_network(id, "frequency", "2412")
    dev[0].set_network(id, "scan_freq", "2412")
    dev[0].set_network(id, "disable_ht", "1")
    dev[0].select_network(id)
    wait_ap_ready(dev[0])

    dev[1].connect("wpas-ap-open", key_mgmt="NONE", scan_freq="2412")
    hwsim_utils.test_connectivity(dev[0], dev[1])

def test_wpas_ap_failures(dev):
    """wpa_supplicant AP mode - failures"""
    # No SSID configured for AP mode
    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network(id, "key_mgmt", "NONE")
    dev[0].set_network(id, "frequency", "2412")
    dev[0].set_network(id, "scan_freq", "2412")
    dev[0].select_network(id)
    ev = dev[0].wait_event([ "CTRL-EVENT-CONNECTED" ], timeout=0.1)
    if ev is not None:
        raise Exception("Unexpected connection event")
    dev[0].request("REMOVE_NETWORK all")

    # Invalid pbss value(2) for AP mode
    dev[0].dump_monitor()
    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network_quoted(id, "ssid", "wpas-ap-open")
    dev[0].set_network(id, "key_mgmt", "NONE")
    dev[0].set_network(id, "frequency", "2412")
    dev[0].set_network(id, "scan_freq", "2412")
    dev[0].set_network(id, "pbss", "2")
    dev[0].select_network(id)
    ev = dev[0].wait_event([ "CTRL-EVENT-CONNECTED",
                             "CTRL-EVENT-DISCONNECTED" ], timeout=0.1)
    if ev is not None and "CTRL-EVENT-CONNECTED" in ev:
        raise Exception("Unexpected connection event(2)")
    dev[0].request("REMOVE_NETWORK all")

def test_wpas_ap_oom(dev):
    """wpa_supplicant AP mode - OOM"""
    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network_quoted(id, "ssid", "wpas-ap")
    dev[0].set_network_quoted(id, "psk", "1234567890")
    dev[0].set_network(id, "frequency", "2412")
    dev[0].set_network(id, "scan_freq", "2412")
    with alloc_fail(dev[0], 1, "=wpa_supplicant_conf_ap"):
        dev[0].select_network(id)
        dev[0].wait_disconnected()
    dev[0].request("REMOVE_NETWORK all")

    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network_quoted(id, "ssid", "wpas-ap")
    dev[0].set_network(id, "psk", "1234567890abcdef1234567890abcdef1234567890abcdef1234567890abcdef")
    dev[0].set_network(id, "frequency", "2412")
    dev[0].set_network(id, "scan_freq", "2412")
    with alloc_fail(dev[0], 1, "=wpa_supplicant_conf_ap"):
        dev[0].select_network(id)
        dev[0].wait_disconnected()
    dev[0].request("REMOVE_NETWORK all")

    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network_quoted(id, "ssid", "wpas-ap")
    dev[0].set_network(id, "key_mgmt", "NONE")
    dev[0].set_network_quoted(id, "wep_key0", "hello")
    dev[0].set_network(id, "frequency", "2412")
    dev[0].set_network(id, "scan_freq", "2412")
    with alloc_fail(dev[0], 1, "=wpa_supplicant_conf_ap"):
        dev[0].select_network(id)
        dev[0].wait_disconnected()
    dev[0].request("REMOVE_NETWORK all")

    wpas = WpaSupplicant(global_iface='/tmp/wpas-wlan5')
    wpas.interface_add("wlan5")
    wpas.request("SET manufacturer test")
    wpas.request("SET model_name test")
    wpas.request("SET model_number test")
    wpas.request("SET serial_number test")
    wpas.request("SET serial_number test")
    wpas.request("SET serial_number test")
    wpas.request("SET ap_vendor_elements dd0411223301")
    id = wpas.add_network()
    wpas.set_network(id, "mode", "2")
    wpas.set_network_quoted(id, "ssid", "wpas-ap")
    wpas.set_network(id, "key_mgmt", "NONE")
    wpas.set_network(id, "frequency", "2412")
    wpas.set_network(id, "scan_freq", "2412")

    for i in range(5):
        with alloc_fail(wpas, i, "=wpa_supplicant_conf_ap"):
            wpas.select_network(id)
            ev = dev[0].wait_event([ "CTRL-EVENT-CONNECTED",
                                     "CTRL-EVENT-DISCONNECTED" ], timeout=1)
        wpas.request("DISCONNECT")
        wpas.wait_disconnected()

def test_wpas_ap_params(dev):
    """wpa_supplicant AP mode - parameters"""
    wpas = WpaSupplicant(global_iface='/tmp/wpas-wlan5')
    wpas.interface_add("wlan5")
    wpas.request("SET manufacturer test")
    wpas.request("SET model_name test")
    wpas.request("SET model_number test")
    wpas.request("SET serial_number test")
    wpas.request("SET serial_number test")
    wpas.request("SET serial_number test")
    wpas.request("SET ap_vendor_elements dd0411223301")
    id = wpas.add_network()
    wpas.set_network(id, "mode", "2")
    wpas.set_network_quoted(id, "ssid", "wpas-ap")
    wpas.set_network(id, "key_mgmt", "NONE")
    wpas.set_network(id, "frequency", "2412")
    wpas.set_network(id, "scan_freq", "2412")
    wpas.select_network(id)
    wpas.wait_connected()
    wpas.request("DISCONNECT")
    wpas.wait_disconnected()

    wpas.request("SET beacon_int 200 3")
    wpas.request("SET dtim_period 3")
    wpas.select_network(id)
    wpas.wait_connected()
    wpas.request("DISCONNECT")
    wpas.wait_disconnected()

    wpas.set_network(id, "beacon_int", "300")
    wpas.set_network(id, "dtim_period", "2")
    wpas.select_network(id)
    wpas.wait_connected()
    if "---- AP ----" not in wpas.request("PMKSA"):
        raise Exception("AP section missing from PMKSA output")
    if "OK" not in wpas.request("PMKSA_FLUSH"):
        raise Exception("PMKSA_FLUSH failed")
    wpas.request("DISCONNECT")
    wpas.wait_disconnected()
