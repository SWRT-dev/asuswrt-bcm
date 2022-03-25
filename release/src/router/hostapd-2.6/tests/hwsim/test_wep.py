# WEP tests
# Copyright (c) 2014, Jouni Malinen <j@w1.fi>
#
# This software may be distributed under the terms of the BSD license.
# See README for more details.

import logging
logger = logging.getLogger()
import subprocess

from remotehost import remote_compatible
import hostapd
import hwsim_utils

@remote_compatible
def test_wep_open_auth(dev, apdev):
    """WEP Open System authentication"""
    hapd = hostapd.add_ap(apdev[0],
                          { "ssid": "wep-open",
                            "wep_key0": '"hello"' })
    dev[0].flush_scan_cache()
    dev[0].connect("wep-open", key_mgmt="NONE", wep_key0='"hello"',
                   scan_freq="2412")
    hwsim_utils.test_connectivity(dev[0], hapd)
    if "[WEP]" not in dev[0].request("SCAN_RESULTS"):
        raise Exception("WEP flag not indicated in scan results")

    bss = dev[0].get_bss(apdev[0]['bssid'])
    if 'flags' not in bss:
        raise Exception("Could not get BSS flags from BSS table")
    if "[WEP]" not in bss['flags']:
        raise Exception("Unexpected BSS flags: " + bss['flags'])

@remote_compatible
def test_wep_shared_key_auth(dev, apdev):
    """WEP Shared Key authentication"""
    hapd = hostapd.add_ap(apdev[0],
                          { "ssid": "wep-shared-key",
                            "wep_key0": '"hello12345678"',
                            "auth_algs": "2" })
    dev[0].connect("wep-shared-key", key_mgmt="NONE", auth_alg="SHARED",
                   wep_key0='"hello12345678"',
                   scan_freq="2412")
    hwsim_utils.test_connectivity(dev[0], hapd)
    dev[1].connect("wep-shared-key", key_mgmt="NONE", auth_alg="OPEN SHARED",
                   wep_key0='"hello12345678"',
                   scan_freq="2412")

@remote_compatible
def test_wep_shared_key_auth_not_allowed(dev, apdev):
    """WEP Shared Key authentication not allowed"""
    hostapd.add_ap(apdev[0],
                   { "ssid": "wep-shared-key",
                     "wep_key0": '"hello12345678"',
                     "auth_algs": "1" })
    dev[0].connect("wep-shared-key", key_mgmt="NONE", auth_alg="SHARED",
                   wep_key0='"hello12345678"',
                   scan_freq="2412", wait_connect=False)
    ev = dev[0].wait_event(["CTRL-EVENT-CONNECTED"], timeout=1)
    if ev is not None:
        raise Exception("Unexpected association")

def test_wep_shared_key_auth_multi_key(dev, apdev):
    """WEP Shared Key authentication with multiple keys"""
    hapd = hostapd.add_ap(apdev[0],
                          { "ssid": "wep-shared-key",
                            "wep_key0": '"hello12345678"',
                            "wep_key1": '"other12345678"',
                            "auth_algs": "2" })
    dev[0].connect("wep-shared-key", key_mgmt="NONE", auth_alg="SHARED",
                   wep_key0='"hello12345678"',
                   scan_freq="2412")
    dev[1].connect("wep-shared-key", key_mgmt="NONE", auth_alg="SHARED",
                   wep_key0='"hello12345678"',
                   wep_key1='"other12345678"',
                   wep_tx_keyidx="1",
                   scan_freq="2412")
    id = dev[2].connect("wep-shared-key", key_mgmt="NONE", auth_alg="SHARED",
                        wep_key0='"hello12345678"',
                        wep_key1='"other12345678"',
                        wep_tx_keyidx="0",
                        scan_freq="2412")
    hwsim_utils.test_connectivity(dev[0], hapd)
    hwsim_utils.test_connectivity(dev[1], hapd)
    hwsim_utils.test_connectivity(dev[2], hapd)

    dev[2].set_network(id, "wep_tx_keyidx", "1")
    dev[2].request("REASSOCIATE")
    dev[2].wait_connected(timeout=10, error="Reassociation timed out")
    hwsim_utils.test_connectivity(dev[2], hapd)

def test_wep_ht_vht(dev, apdev):
    """WEP and HT/VHT"""
    dev[0].flush_scan_cache()
    try:
        hapd = None
        params = { "ssid": "test-vht40-wep",
                   "country_code": "SE",
                   "hw_mode": "a",
                   "channel": "36",
                   "ieee80211n": "1",
                   "ieee80211ac": "1",
                   "ht_capab": "[HT40+]",
                   "vht_capab": "",
                   "vht_oper_chwidth": "0",
                   "vht_oper_centr_freq_seg0_idx": "0",
                   "wep_key0": '"hello"' }
        hapd = hostapd.add_ap(apdev[0], params)
        dev[0].connect("test-vht40-wep", scan_freq="5180", key_mgmt="NONE",
                       wep_key0='"hello"')
        hwsim_utils.test_connectivity(dev[0], hapd)
        status = hapd.get_status()
        logger.info("hostapd STATUS: " + str(status))
        if status["ieee80211n"] != "0":
            raise Exception("Unexpected STATUS ieee80211n value")
        if status["ieee80211ac"] != "0":
            raise Exception("Unexpected STATUS ieee80211ac value")
        if status["secondary_channel"] != "0":
            raise Exception("Unexpected STATUS secondary_channel value")
    finally:
        dev[0].request("DISCONNECT")
        if hapd:
            hapd.request("DISABLE")
        subprocess.call(['iw', 'reg', 'set', '00'])
        dev[0].flush_scan_cache()
