# WPS+NFC tests
# Copyright (c) 2013, Jouni Malinen <j@w1.fi>
#
# This software may be distributed under the terms of the BSD license.
# See README for more details.

from remotehost import remote_compatible
import time
import subprocess
import logging
logger = logging.getLogger()

import hwsim_utils
import hostapd
from utils import alloc_fail, fail_test

def check_wpa2_connection(sta, ap, hapd, ssid, mixed=False):
    status = sta.get_status()
    if status['wpa_state'] != 'COMPLETED':
        raise Exception("Not fully connected")
    if status['bssid'] != ap['bssid']:
        raise Exception("Unexpected BSSID")
    if status['ssid'] != ssid:
        raise Exception("Unexpected SSID")
    if status['pairwise_cipher'] != 'CCMP':
        raise Exception("Unexpected encryption configuration")
    if status['group_cipher'] != 'CCMP' and not mixed:
        raise Exception("Unexpected encryption configuration")
    if status['key_mgmt'] != 'WPA2-PSK':
        raise Exception("Unexpected key_mgmt")
    hwsim_utils.test_connectivity(sta, hapd)

def ap_wps_params(ssid):
    return { "ssid": ssid, "eap_server": "1", "wps_state": "2",
             "wpa_passphrase": "12345678", "wpa": "2",
             "wpa_key_mgmt": "WPA-PSK", "rsn_pairwise": "CCMP"}

@remote_compatible
def test_nfc_wps_password_token_sta(dev, apdev):
    """NFC tag with password token on the station/Enrollee"""
    ssid = "test-wps-nfc-pw-token-conf"
    params = ap_wps_params(ssid)
    hapd = hostapd.add_ap(apdev[0], params)
    logger.info("WPS provisioning step using password token from station")
    wps = dev[0].request("WPS_NFC_TOKEN WPS").rstrip()
    if "FAIL" in wps:
        raise Exception("Failed to generate password token (WPS only)")
    pw = dev[0].request("WPS_NFC_TOKEN NDEF").rstrip()
    if "FAIL" in pw:
        raise Exception("Failed to generate password token")
    res = hapd.request("WPS_NFC_TAG_READ " + pw)
    if "FAIL" in res:
        raise Exception("Failed to provide NFC tag contents to hostapd")
    dev[0].dump_monitor()
    res = dev[0].request("WPS_NFC")
    if "FAIL" in res:
        raise Exception("Failed to start Enrollee using NFC password token")
    dev[0].wait_connected(timeout=30)
    check_wpa2_connection(dev[0], apdev[0], hapd, ssid)

def test_nfc_wps_config_token(dev, apdev):
    """NFC tag with configuration token from AP"""
    ssid = "test-wps-nfc-conf-token"
    params = ap_wps_params(ssid)
    hapd = hostapd.add_ap(apdev[0], params)
    logger.info("NFC configuration token from AP to station")
    conf = hapd.request("WPS_NFC_CONFIG_TOKEN NDEF").rstrip()
    if "FAIL" in conf:
        raise Exception("Failed to generate configuration token")
    dev[0].dump_monitor()
    res = dev[0].request("WPS_NFC_TAG_READ " + conf)
    if "FAIL" in res:
        raise Exception("Failed to provide NFC tag contents to wpa_supplicant")
    dev[0].wait_connected(timeout=15)
    check_wpa2_connection(dev[0], apdev[0], hapd, ssid)

    with alloc_fail(hapd, 1, "wps_get_oob_cred"):
        conf = hapd.request("WPS_NFC_CONFIG_TOKEN NDEF").rstrip()
        if "FAIL" not in conf:
            raise Exception("Unexpected configuration token received during OOM")

def test_nfc_wps_config_token_init(dev, apdev):
    """NFC tag with configuration token from AP with auto configuration"""
    ssid = "test-wps-nfc-conf-token-init"
    hapd = hostapd.add_ap(apdev[0],
                          { "ssid": ssid, "eap_server": "1", "wps_state": "1" })
    logger.info("NFC configuration token from AP to station")
    conf = hapd.request("WPS_NFC_CONFIG_TOKEN NDEF").rstrip()
    if "FAIL" in conf:
        raise Exception("Failed to generate configuration token")
    dev[0].dump_monitor()
    res = dev[0].request("WPS_NFC_TAG_READ " + conf)
    if "FAIL" in res:
        raise Exception("Failed to provide NFC tag contents to wpa_supplicant")
    dev[0].wait_connected(timeout=15)
    check_wpa2_connection(dev[0], apdev[0], hapd, ssid, mixed=True)

@remote_compatible
def test_nfc_wps_password_token_sta_init(dev, apdev):
    """Initial AP configuration with first WPS NFC Enrollee"""
    ssid = "test-wps-nfc-pw-token-init"
    hapd = hostapd.add_ap(apdev[0],
                          { "ssid": ssid, "eap_server": "1", "wps_state": "1" })
    logger.info("WPS provisioning step using password token from station")
    pw = dev[0].request("WPS_NFC_TOKEN NDEF").rstrip()
    if "FAIL" in pw:
        raise Exception("Failed to generate password token")
    res = hapd.request("WPS_NFC_TAG_READ " + pw)
    if "FAIL" in res:
        raise Exception("Failed to provide NFC tag contents to hostapd")
    dev[0].dump_monitor()
    res = dev[0].request("WPS_NFC")
    if "FAIL" in res:
        raise Exception("Failed to start Enrollee using NFC password token")
    dev[0].wait_connected(timeout=30)
    check_wpa2_connection(dev[0], apdev[0], hapd, ssid, mixed=True)

@remote_compatible
def test_nfc_wps_password_token_ap(dev, apdev):
    """WPS registrar configuring an AP using AP password token"""
    ssid = "test-wps-nfc-pw-token-init"
    hapd = hostapd.add_ap(apdev[0],
                          { "ssid": ssid, "eap_server": "1", "wps_state": "1" })
    logger.info("WPS configuration step")
    pw = hapd.request("WPS_NFC_TOKEN NDEF").rstrip()
    if "FAIL" in pw:
        raise Exception("Failed to generate password token")
    res = hapd.request("WPS_NFC_TOKEN enable")
    if "FAIL" in pw:
        raise Exception("Failed to enable AP password token")
    res = dev[0].request("WPS_NFC_TAG_READ " + pw)
    if "FAIL" in res:
        raise Exception("Failed to provide NFC tag contents to wpa_supplicant")
    dev[0].dump_monitor()
    new_ssid = "test-wps-nfc-pw-token-new-ssid"
    new_passphrase = "1234567890"
    res = dev[0].request("WPS_REG " + apdev[0]['bssid'] + " nfc-pw " + new_ssid.encode("hex") + " WPA2PSK CCMP " + new_passphrase.encode("hex"))
    if "FAIL" in res:
        raise Exception("Failed to start Registrar using NFC password token")
    dev[0].wait_connected(timeout=30)
    check_wpa2_connection(dev[0], apdev[0], hapd, new_ssid, mixed=True)
    if "FAIL" in hapd.request("WPS_NFC_TOKEN disable"):
        raise Exception("Failed to disable AP password token")
    if "FAIL" in hapd.request("WPS_NFC_TOKEN WPS"):
        raise Exception("Unexpected WPS_NFC_TOKEN WPS failure")

    with fail_test(hapd, 1, "os_get_random;wps_nfc_token_gen"):
        if "FAIL" not in hapd.request("WPS_NFC_TOKEN WPS"):
            raise Exception("Unexpected WPS_NFC_TOKEN success")
    with fail_test(hapd, 2, "os_get_random;wps_nfc_token_gen"):
        if "FAIL" not in hapd.request("WPS_NFC_TOKEN WPS"):
            raise Exception("Unexpected WPS_NFC_TOKEN success")

def test_nfc_wps_handover_init(dev, apdev):
    """Connect to WPS AP with NFC connection handover and move to configured state"""
    try:
        _test_nfc_wps_handover_init(dev, apdev)
    finally:
        dev[0].request("SET ignore_old_scan_res 0")

def _test_nfc_wps_handover_init(dev, apdev):
    dev[0].request("SET ignore_old_scan_res 1")
    ssid = "test-wps-nfc-handover-init"
    hapd = hostapd.add_ap(apdev[0],
                          { "ssid": ssid, "eap_server": "1", "wps_state": "1" })
    logger.info("NFC connection handover")
    req = dev[0].request("NFC_GET_HANDOVER_REQ NDEF WPS-CR").rstrip()
    if "FAIL" in req:
        raise Exception("Failed to generate NFC connection handover request")
    sel = hapd.request("NFC_GET_HANDOVER_SEL NDEF WPS-CR").rstrip()
    if "FAIL" in sel:
        raise Exception("Failed to generate NFC connection handover select")
    res = hapd.request("NFC_REPORT_HANDOVER RESP WPS " + req + " " + sel)
    if "FAIL" in res:
        raise Exception("Failed to report NFC connection handover to to hostapd")
    dev[0].dump_monitor()
    res = dev[0].request("NFC_REPORT_HANDOVER INIT WPS " + req + " " + sel)
    if "FAIL" in res:
        raise Exception("Failed to report NFC connection handover to to wpa_supplicant")
    dev[0].wait_connected(timeout=15)
    check_wpa2_connection(dev[0], apdev[0], hapd, ssid, mixed=True)

    with alloc_fail(hapd, 1, "wps_build_nfc_handover_sel"):
        if "FAIL" not in hapd.request("NFC_GET_HANDOVER_SEL NDEF WPS-CR"):
            raise Exception("Unexpected NFC_GET_HANDOVER_SEL success during OOM")

@remote_compatible
def test_nfc_wps_handover_errors(dev, apdev):
    """WPS AP NFC handover report error cases"""
    ssid = "test-wps-nfc-handover"
    hapd = hostapd.add_ap(apdev[0],
                          { "ssid": ssid, "eap_server": "1", "wps_state": "1" })
    sel = hapd.request("NFC_GET_HANDOVER_SEL NDEF WPS-CR").rstrip()
    if "FAIL" in sel:
        raise Exception("Failed to generate NFC connection handover select")
    if "FAIL" not in hapd.request("NFC_REPORT_HANDOVER "):
        raise Exception("Unexpected handover report success")
    if "FAIL" not in hapd.request("NFC_REPORT_HANDOVER RESP"):
        raise Exception("Unexpected handover report success")
    if "FAIL" not in hapd.request("NFC_REPORT_HANDOVER RESP WPS"):
        raise Exception("Unexpected handover report success")
    if "FAIL" not in hapd.request("NFC_REPORT_HANDOVER RESP WPS 001122"):
        raise Exception("Unexpected handover report success")
    if "FAIL" not in hapd.request("NFC_REPORT_HANDOVER RESP WPS 001122 00"):
        raise Exception("Unexpected handover report success")
    if "FAIL" not in hapd.request("NFC_REPORT_HANDOVER RESP WPS 0 00"):
        raise Exception("Unexpected handover report success")
    if "FAIL" not in hapd.request("NFC_REPORT_HANDOVER RESP WPS 001122 0"):
        raise Exception("Unexpected handover report success")
    if "FAIL" not in hapd.request("NFC_REPORT_HANDOVER RESP WPS 00q122 001122"):
        raise Exception("Unexpected handover report success")
    if "FAIL" not in hapd.request("NFC_REPORT_HANDOVER RESP WPS 001122 001q22"):
        raise Exception("Unexpected handover report success")
    if "FAIL" not in hapd.request("NFC_REPORT_HANDOVER RESP FOO 001122 00"):
        raise Exception("Unexpected handover report success")

def test_nfc_wps_handover(dev, apdev):
    """Connect to WPS AP with NFC connection handover"""
    ssid = "test-wps-nfc-handover"
    params = ap_wps_params(ssid)
    hapd = hostapd.add_ap(apdev[0], params)
    logger.info("NFC connection handover")
    req = dev[0].request("NFC_GET_HANDOVER_REQ NDEF WPS-CR").rstrip()
    if "FAIL" in req:
        raise Exception("Failed to generate NFC connection handover request")
    sel = hapd.request("NFC_GET_HANDOVER_SEL NDEF WPS-CR").rstrip()
    if "FAIL" in sel:
        raise Exception("Failed to generate NFC connection handover select")
    res = hapd.request("NFC_REPORT_HANDOVER RESP WPS " + req + " " + sel)
    if "FAIL" in res:
        raise Exception("Failed to report NFC connection handover to to hostapd")
    dev[0].dump_monitor()
    res = dev[0].request("NFC_REPORT_HANDOVER INIT WPS " + req + " " + sel)
    if "FAIL" in res:
        raise Exception("Failed to report NFC connection handover to to wpa_supplicant")
    dev[0].wait_connected(timeout=30)
    check_wpa2_connection(dev[0], apdev[0], hapd, ssid)

def test_nfc_wps_handover_5ghz(dev, apdev):
    """Connect to WPS AP with NFC connection handover on 5 GHz band"""
    hapd = None
    try:
        ssid = "test-wps-nfc-handover"
        params = ap_wps_params(ssid)
        params["country_code"] = "FI"
        params["hw_mode"] = "a"
        params["channel"] = "36"
        hapd = hostapd.add_ap(apdev[0], params)
        logger.info("NFC connection handover")
        req = dev[0].request("NFC_GET_HANDOVER_REQ NDEF WPS-CR").rstrip()
        if "FAIL" in req:
            raise Exception("Failed to generate NFC connection handover request")
        sel = hapd.request("NFC_GET_HANDOVER_SEL NDEF WPS-CR").rstrip()
        if "FAIL" in sel:
            raise Exception("Failed to generate NFC connection handover select")
        res = hapd.request("NFC_REPORT_HANDOVER RESP WPS " + req + " " + sel)
        if "FAIL" in res:
            raise Exception("Failed to report NFC connection handover to to hostapd")
        dev[0].dump_monitor()
        res = dev[0].request("NFC_REPORT_HANDOVER INIT WPS " + req + " " + sel)
        if "FAIL" in res:
            raise Exception("Failed to report NFC connection handover to to wpa_supplicant")
        dev[0].wait_connected(timeout=30)
        check_wpa2_connection(dev[0], apdev[0], hapd, ssid)
    finally:
        dev[0].request("DISCONNECT")
        if hapd:
            hapd.request("DISABLE")
        subprocess.call(['iw', 'reg', 'set', '00'])
        dev[0].flush_scan_cache()

def test_nfc_wps_handover_chan14(dev, apdev):
    """Connect to WPS AP with NFC connection handover on channel 14"""
    hapd = None
    try:
        ssid = "test-wps-nfc-handover"
        params = ap_wps_params(ssid)
        params["country_code"] = "JP"
        params["hw_mode"] = "b"
        params["channel"] = "14"
        hapd = hostapd.add_ap(apdev[0], params)
        logger.info("NFC connection handover")
        req = dev[0].request("NFC_GET_HANDOVER_REQ NDEF WPS-CR").rstrip()
        if "FAIL" in req:
            raise Exception("Failed to generate NFC connection handover request")
        sel = hapd.request("NFC_GET_HANDOVER_SEL NDEF WPS-CR").rstrip()
        if "FAIL" in sel:
            raise Exception("Failed to generate NFC connection handover select")
        res = hapd.request("NFC_REPORT_HANDOVER RESP WPS " + req + " " + sel)
        if "FAIL" in res:
            raise Exception("Failed to report NFC connection handover to to hostapd")
        dev[0].dump_monitor()
        res = dev[0].request("NFC_REPORT_HANDOVER INIT WPS " + req + " " + sel)
        if "FAIL" in res:
            raise Exception("Failed to report NFC connection handover to to wpa_supplicant")
        dev[0].wait_connected(timeout=30)
        check_wpa2_connection(dev[0], apdev[0], hapd, ssid)
    finally:
        dev[0].request("DISCONNECT")
        if hapd:
            hapd.request("DISABLE")
        subprocess.call(['iw', 'reg', 'set', '00'])
        dev[0].flush_scan_cache()

def test_nfc_wps_handover_with_pw_token_set(dev, apdev):
    """Connect to WPS AP with NFC connection handover (wps_nfc_* set)"""
    ssid = "test-wps-nfc-handover2"
    params = ap_wps_params(ssid)
    hapd = hostapd.add_ap(apdev[0], params)
    # enable a password token (which won't be used in this test case)
    pw = hapd.request("WPS_NFC_TOKEN NDEF").rstrip()
    if "FAIL" in pw:
        raise Exception("Failed to generate password token")
    res = hapd.request("WPS_NFC_TOKEN enable")
    if "FAIL" in pw:
        raise Exception("Failed to enable AP password token")
    logger.info("NFC connection handover")
    req = dev[0].request("NFC_GET_HANDOVER_REQ NDEF WPS-CR").rstrip()
    if "FAIL" in req:
        raise Exception("Failed to generate NFC connection handover request")
    sel = hapd.request("NFC_GET_HANDOVER_SEL NDEF WPS-CR").rstrip()
    if "FAIL" in sel:
        raise Exception("Failed to generate NFC connection handover select")
    res = hapd.request("NFC_REPORT_HANDOVER RESP WPS " + req + " " + sel)
    if "FAIL" in res:
        raise Exception("Failed to report NFC connection handover to to hostapd")
    dev[0].dump_monitor()
    res = dev[0].request("NFC_REPORT_HANDOVER INIT WPS " + req + " " + sel)
    if "FAIL" in res:
        raise Exception("Failed to report NFC connection handover to to wpa_supplicant")
    dev[0].wait_connected(timeout=15)
    check_wpa2_connection(dev[0], apdev[0], hapd, ssid)

def test_nfc_wps_handover_pk_hash_mismatch_sta(dev, apdev):
    """WPS NFC connection handover with invalid pkhash from station (negative)"""
    ssid = "wps-nfc-handover-pkhash-sta"
    if "FAIL" in dev[0].request("SET wps_corrupt_pkhash 1"):
        raise Exception("Could not enable wps_corrupt_pkhash")
    params = ap_wps_params(ssid)
    hapd = hostapd.add_ap(apdev[0], params)
    logger.info("NFC connection handover")
    req = dev[0].request("NFC_GET_HANDOVER_REQ NDEF WPS-CR").rstrip()
    if "FAIL" in req:
        raise Exception("Failed to generate NFC connection handover request")
    sel = hapd.request("NFC_GET_HANDOVER_SEL NDEF WPS-CR").rstrip()
    if "FAIL" in sel:
        raise Exception("Failed to generate NFC connection handover select")
    res = hapd.request("NFC_REPORT_HANDOVER RESP WPS " + req + " " + sel)
    if "FAIL" in res:
        raise Exception("Failed to report NFC connection handover to to hostapd")
    dev[0].dump_monitor()
    res = dev[0].request("NFC_REPORT_HANDOVER INIT WPS " + req + " " + sel)
    if "FAIL" in res:
        raise Exception("Failed to report NFC connection handover to to wpa_supplicant")
    ev = dev[0].wait_event(["CTRL-EVENT-CONNECTED", "WPS-FAIL"], timeout=15)
    if ev is None:
        raise Exception("Timed out")
    if "WPS-FAIL" not in ev:
        raise Exception("Public key hash mismatch not detected")

def test_nfc_wps_handover_pk_hash_mismatch_ap(dev, apdev):
    """WPS NFC connection handover with invalid pkhash from AP (negative)"""
    ssid = "wps-nfc-handover-pkhash-ap"
    params = ap_wps_params(ssid)
    hapd = hostapd.add_ap(apdev[0], params)
    if "FAIL" in hapd.request("SET wps_corrupt_pkhash 1"):
        raise Exception("Could not enable wps_corrupt_pkhash")
    logger.info("NFC connection handover")
    req = dev[0].request("NFC_GET_HANDOVER_REQ NDEF WPS-CR").rstrip()
    if "FAIL" in req:
        raise Exception("Failed to generate NFC connection handover request")
    sel = hapd.request("NFC_GET_HANDOVER_SEL NDEF WPS-CR").rstrip()
    if "FAIL" in sel:
        raise Exception("Failed to generate NFC connection handover select")
    res = hapd.request("NFC_REPORT_HANDOVER RESP WPS " + req + " " + sel)
    if "FAIL" in res:
        raise Exception("Failed to report NFC connection handover to to hostapd")
    dev[0].dump_monitor()
    res = dev[0].request("NFC_REPORT_HANDOVER INIT WPS " + req + " " + sel)
    if "FAIL" in res:
        raise Exception("Failed to report NFC connection handover to to wpa_supplicant")
    ev = dev[0].wait_event(["CTRL-EVENT-CONNECTED", "WPS-FAIL"], timeout=15)
    if ev is None:
        raise Exception("Timed out")
    if "WPS-FAIL" not in ev:
        raise Exception("Public key hash mismatch not detected")

def start_ap_er(er, ap, ssid):
    ap_pin = "12345670"
    ap_uuid = "27ea801a-9e5c-4e73-bd82-f89cbcd10d7e"
    params = { "ssid": ssid, "eap_server": "1", "wps_state": "2",
               "wpa_passphrase": "12345678", "wpa": "2",
               "wpa_key_mgmt": "WPA-PSK", "rsn_pairwise": "CCMP",
               "device_name": "Wireless AP", "manufacturer": "Company",
               "model_name": "WAP", "model_number": "123",
               "serial_number": "12345", "device_type": "6-0050F204-1",
               "os_version": "01020300",
               "config_methods": "label push_button",
               "ap_pin": ap_pin, "uuid": ap_uuid, "upnp_iface": "lo"}
    hapd = hostapd.add_ap(ap, params)
    logger.info("Learn AP configuration")
    er.dump_monitor()
    try:
        er.request("SET ignore_old_scan_res 1")
        er.wps_reg(ap['bssid'], ap_pin)
    finally:
        er.request("SET ignore_old_scan_res 0")

    logger.info("Start ER")
    er.request("WPS_ER_STOP")
    time.sleep(1)
    er.request("WPS_ER_START ifname=lo")
    ev = er.wait_event(["WPS-ER-AP-ADD"], timeout=15)
    if ev is None:
        raise Exception("AP discovery timed out")
    if ap_uuid not in ev:
        raise Exception("Expected AP UUID not found")

    logger.info("Use learned network configuration on ER")
    er.request("WPS_ER_SET_CONFIG " + ap_uuid + " 0")
    return hapd

@remote_compatible
def test_nfc_wps_er_pw_token(dev, apdev):
    """WPS NFC password token from Enrollee to ER"""
    try:
        _test_nfc_wps_er_pw_token(dev, apdev)
    finally:
        dev[0].request("WPS_ER_STOP")
        dev[1].request("SET ignore_old_scan_res 0")

def _test_nfc_wps_er_pw_token(dev, apdev):
    ssid = "wps-nfc-er-pw-token"
    hapd = start_ap_er(dev[0], apdev[0], ssid)
    logger.info("WPS provisioning step using password token from station")
    dev[1].request("SET ignore_old_scan_res 1")
    pw = dev[1].request("WPS_NFC_TOKEN NDEF").rstrip()
    if "FAIL" in pw:
        raise Exception("Failed to generate password token")
    res = dev[0].request("WPS_NFC_TAG_READ " + pw)
    if "FAIL" in res:
        raise Exception("Failed to provide NFC tag contents to WPS ER")
    dev[0].dump_monitor()
    res = dev[1].request("WPS_NFC")
    if "FAIL" in res:
        raise Exception("Failed to start Enrollee using NFC password token")
    ev = dev[0].wait_event(["WPS-SUCCESS"], timeout=15)
    if ev is None:
        raise Exception("WPS ER did not report success")
    dev[1].wait_connected(timeout=15)
    check_wpa2_connection(dev[1], apdev[0], hapd, ssid)

@remote_compatible
def test_nfc_wps_er_config_token(dev, apdev):
    """WPS NFC configuration token from ER to Enrollee"""
    try:
        _test_nfc_wps_er_config_token(dev, apdev)
    finally:
        dev[0].request("WPS_ER_STOP")
        dev[1].request("SET ignore_old_scan_res 0")

def _test_nfc_wps_er_config_token(dev, apdev):
    ssid = "wps-nfc-er-config-token"
    hapd = start_ap_er(dev[0], apdev[0], ssid)
    logger.info("WPS provisioning step using configuration token from ER")
    wps = dev[0].request("WPS_ER_NFC_CONFIG_TOKEN WPS " + apdev[0]['bssid']).rstrip()
    if "FAIL" in wps:
        raise Exception("Failed to generate configuration token (WPS format)")
    conf = dev[0].request("WPS_ER_NFC_CONFIG_TOKEN NDEF " + apdev[0]['bssid']).rstrip()
    if "FAIL" in conf:
        raise Exception("Failed to generate configuration token")
    dev[1].request("SET ignore_old_scan_res 1")
    res = dev[1].request("WPS_NFC_TAG_READ " + conf)
    if "FAIL" in res:
        raise Exception("Failed to provide NFC tag contents to wpa_supplicant")
    dev[1].wait_connected(timeout=15)
    check_wpa2_connection(dev[1], apdev[0], hapd, ssid)

def test_nfc_wps_er_handover(dev, apdev):
    """WPS NFC connection handover between Enrollee and ER"""
    try:
        _test_nfc_wps_er_handover(dev, apdev)
    finally:
        dev[0].request("WPS_ER_STOP")

def _test_nfc_wps_er_handover(dev, apdev):
    ssid = "wps-nfc-er-handover"
    hapd = start_ap_er(dev[0], apdev[0], ssid)
    logger.info("WPS provisioning step using connection handover")
    req = dev[1].request("NFC_GET_HANDOVER_REQ NDEF WPS-CR").rstrip()
    if "FAIL" in req:
        raise Exception("Failed to generate NFC connection handover request")
    sel = dev[0].request("NFC_GET_HANDOVER_SEL NDEF WPS-CR " + apdev[0]['bssid']).rstrip()
    if "FAIL" in sel:
        raise Exception("Failed to generate NFC connection handover select")
    res = dev[0].request("NFC_REPORT_HANDOVER RESP WPS " + req + " " + sel)
    if "FAIL" in res:
        raise Exception("Failed to report NFC connection handover to to hostapd")
    dev[1].dump_monitor()
    res = dev[1].request("NFC_REPORT_HANDOVER INIT WPS " + req + " " + sel)
    if "FAIL" in res:
        raise Exception("Failed to report NFC connection handover to to wpa_supplicant")
    dev[1].wait_connected(timeout=15)
    check_wpa2_connection(dev[1], apdev[0], hapd, ssid)

def test_nfc_wps_er_handover_pk_hash_mismatch_sta(dev, apdev):
    """WPS NFC connection handover with invalid pkhash from station to ER (negative)"""
    try:
        _test_nfc_wps_er_handover_pk_hash_mismatch_sta(dev, apdev)
    finally:
        dev[0].request("WPS_ER_STOP")
        dev[1].request("SET ignore_old_scan_res 0")

def _test_nfc_wps_er_handover_pk_hash_mismatch_sta(dev, apdev):
    ssid = "wps-nfc-er-handover-pkhash-sta"
    hapd = start_ap_er(dev[0], apdev[0], ssid)
    logger.info("WPS provisioning step using connection handover")
    if "FAIL" in dev[1].request("SET wps_corrupt_pkhash 1"):
        raise Exception("Could not enable wps_corrupt_pkhash")
    dev[1].request("SET ignore_old_scan_res 1")
    req = dev[1].request("NFC_GET_HANDOVER_REQ NDEF WPS-CR").rstrip()
    if "FAIL" in req:
        raise Exception("Failed to generate NFC connection handover request")
    sel = dev[0].request("NFC_GET_HANDOVER_SEL NDEF WPS-CR " + apdev[0]['bssid']).rstrip()
    if "FAIL" in sel:
        raise Exception("Failed to generate NFC connection handover select")
    res = dev[0].request("NFC_REPORT_HANDOVER RESP WPS " + req + " " + sel)
    if "FAIL" in res:
        raise Exception("Failed to report NFC connection handover to to hostapd")
    dev[1].dump_monitor()
    res = dev[1].request("NFC_REPORT_HANDOVER INIT WPS " + req + " " + sel)
    if "FAIL" in res:
        raise Exception("Failed to report NFC connection handover to to wpa_supplicant")
    ev = dev[1].wait_event(["CTRL-EVENT-CONNECTED", "WPS-FAIL"], timeout=15)
    if ev is None:
        raise Exception("Timed out")
    if "WPS-FAIL" not in ev:
        raise Exception("Public key hash mismatch not detected")

def test_nfc_wps_er_handover_pk_hash_mismatch_er(dev, apdev):
    """WPS NFC connection handover with invalid pkhash from ER to station (negative)"""
    try:
        _test_nfc_wps_er_handover_pk_hash_mismatch_er(dev, apdev)
    finally:
        dev[0].request("WPS_ER_STOP")
        dev[1].request("SET ignore_old_scan_res 0")

def _test_nfc_wps_er_handover_pk_hash_mismatch_er(dev, apdev):
    ssid = "wps-nfc-er-handover-pkhash-er"
    hapd = start_ap_er(dev[0], apdev[0], ssid)
    logger.info("WPS provisioning step using connection handover")
    if "FAIL" in dev[0].request("SET wps_corrupt_pkhash 1"):
        raise Exception("Could not enable wps_corrupt_pkhash")
    dev[1].request("SET ignore_old_scan_res 1")
    req = dev[1].request("NFC_GET_HANDOVER_REQ NDEF WPS-CR").rstrip()
    if "FAIL" in req:
        raise Exception("Failed to generate NFC connection handover request")
    sel = dev[0].request("NFC_GET_HANDOVER_SEL NDEF WPS-CR " + apdev[0]['bssid']).rstrip()
    if "FAIL" in sel:
        raise Exception("Failed to generate NFC connection handover select")
    res = dev[0].request("NFC_REPORT_HANDOVER RESP WPS " + req + " " + sel)
    if "FAIL" in res:
        raise Exception("Failed to report NFC connection handover to to hostapd")
    dev[1].dump_monitor()
    res = dev[1].request("NFC_REPORT_HANDOVER INIT WPS " + req + " " + sel)
    if "FAIL" in res:
        raise Exception("Failed to report NFC connection handover to to wpa_supplicant")
    ev = dev[1].wait_event(["CTRL-EVENT-CONNECTED", "WPS-FAIL"], timeout=15)
    if ev is None:
        raise Exception("Timed out")
    if "WPS-FAIL" not in ev:
        raise Exception("Public key hash mismatch not detected")

@remote_compatible
def test_nfc_invalid_ndef_record(dev, apdev):
    """Invalid NFC NDEF record handling"""
    tests = [ "11223344",
              "00112233",
              "0000112233445566",
              "0800112233445566",
              "080011223344",
              "18000000",
              "18010000",
              "90000050",
              "9000005000",
              "9001013344",
              "98010101334455",
              "0017ffffffe3",
              "0017ffffffe4",
              "0017ffffffe9",
              "0000fffffffa",
              "0017ffffffe46170706c69636174696f6e2f766e642e7766612e777363",
              "0017ffffffff6170706c69636174696f6e2f766e642e7766612e777363",
              "0017000000006170706c69636174696f6e2f766e642e7766612e7773ff",
              "080000000000" ]
    for test in tests:
        if "FAIL" not in dev[0].request("WPS_NFC_TAG_READ " + test):
            raise Exception("Invalid tag accepted: " + test)
