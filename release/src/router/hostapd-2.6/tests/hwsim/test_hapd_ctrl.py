# hostapd control interface
# Copyright (c) 2014, Qualcomm Atheros, Inc.
#
# This software may be distributed under the terms of the BSD license.
# See README for more details.

from remotehost import remote_compatible
import hostapd
import hwsim_utils
from utils import skip_with_fips

@remote_compatible
def test_hapd_ctrl_status(dev, apdev):
    """hostapd ctrl_iface STATUS commands"""
    ssid = "hapd-ctrl"
    bssid = apdev[0]['bssid']
    params = hostapd.wpa2_params(ssid=ssid, passphrase="12345678")
    hapd = hostapd.add_ap(apdev[0], params)
    status = hapd.get_status()
    driver = hapd.get_driver_status()

    if status['bss[0]'] != apdev[0]['ifname']:
        raise Exception("Unexpected bss[0]")
    if status['ssid[0]'] != ssid:
        raise Exception("Unexpected ssid[0]")
    if status['bssid[0]'] != bssid:
        raise Exception("Unexpected bssid[0]")
    if status['freq'] != "2412":
        raise Exception("Unexpected freq")

    if driver['beacon_set'] != "1":
        raise Exception("Unexpected beacon_set")
    if driver['addr'] != bssid:
        raise Exception("Unexpected addr")

@remote_compatible
def test_hapd_ctrl_p2p_manager(dev, apdev):
    """hostapd as P2P Device manager"""
    ssid = "hapd-p2p-mgr"
    passphrase = "12345678"
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    params['manage_p2p'] = '1'
    params['allow_cross_connection'] = '0'
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
    addr = dev[0].own_addr()
    if "OK" not in hapd.request("DEAUTHENTICATE " + addr + " p2p=2"):
        raise Exception("DEAUTHENTICATE command failed")
    dev[0].wait_disconnected(timeout=5)
    dev[0].wait_connected(timeout=10, error="Re-connection timed out")

    if "OK" not in hapd.request("DISASSOCIATE " + addr + " p2p=2"):
        raise Exception("DISASSOCIATE command failed")
    dev[0].wait_disconnected(timeout=5)
    dev[0].wait_connected(timeout=10, error="Re-connection timed out")

@remote_compatible
def test_hapd_ctrl_sta(dev, apdev):
    """hostapd and STA ctrl_iface commands"""
    ssid = "hapd-ctrl-sta"
    passphrase = "12345678"
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
    addr = dev[0].own_addr()
    if "FAIL" in hapd.request("STA " + addr):
        raise Exception("Unexpected STA failure")
    if "FAIL" not in hapd.request("STA " + addr + " eapol"):
        raise Exception("Unexpected STA-eapol success")
    if "FAIL" not in hapd.request("STA 00:11:22:33:44"):
        raise Exception("Unexpected STA success")
    if "FAIL" not in hapd.request("STA 00:11:22:33:44:55"):
        raise Exception("Unexpected STA success")

    if len(hapd.request("STA-NEXT " + addr).splitlines()) > 0:
        raise Exception("Unexpected STA-NEXT result")
    if "FAIL" not in hapd.request("STA-NEXT 00:11:22:33:44"):
        raise Exception("Unexpected STA-NEXT success")

@remote_compatible
def test_hapd_ctrl_disconnect(dev, apdev):
    """hostapd and disconnection ctrl_iface commands"""
    ssid = "hapd-ctrl"
    passphrase = "12345678"
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
    addr = dev[0].p2p_dev_addr()

    if "FAIL" not in hapd.request("DEAUTHENTICATE 00:11:22:33:44"):
        raise Exception("Unexpected DEAUTHENTICATE success")

    if "OK" not in hapd.request("DEAUTHENTICATE ff:ff:ff:ff:ff:ff"):
        raise Exception("Unexpected DEAUTHENTICATE failure")
    dev[0].wait_disconnected(timeout=5)
    dev[0].wait_connected(timeout=10, error="Re-connection timed out")

    if "FAIL" not in hapd.request("DISASSOCIATE 00:11:22:33:44"):
        raise Exception("Unexpected DISASSOCIATE success")

    if "OK" not in hapd.request("DISASSOCIATE ff:ff:ff:ff:ff:ff"):
        raise Exception("Unexpected DISASSOCIATE failure")
    dev[0].wait_disconnected(timeout=5)
    dev[0].wait_connected(timeout=10, error="Re-connection timed out")

@remote_compatible
def test_hapd_ctrl_chan_switch(dev, apdev):
    """hostapd and CHAN_SWITCH ctrl_iface command"""
    ssid = "hapd-ctrl"
    params = { "ssid": ssid }
    hapd = hostapd.add_ap(apdev[0], params)
    if "FAIL" not in hapd.request("CHAN_SWITCH "):
        raise Exception("Unexpected CHAN_SWITCH success")
    if "FAIL" not in hapd.request("CHAN_SWITCH qwerty 2422"):
        raise Exception("Unexpected CHAN_SWITCH success")
    if "FAIL" not in hapd.request("CHAN_SWITCH 5 qwerty"):
        raise Exception("Unexpected CHAN_SWITCH success")
    if "FAIL" not in hapd.request("CHAN_SWITCH 0 2432 center_freq1=123 center_freq2=234 bandwidth=1000 sec_channel_offset=20 ht vht"):
        raise Exception("Unexpected CHAN_SWITCH success")

@remote_compatible
def test_hapd_ctrl_level(dev, apdev):
    """hostapd and LEVEL ctrl_iface command"""
    ssid = "hapd-ctrl"
    params = { "ssid": ssid }
    hapd = hostapd.add_ap(apdev[0], params)
    if "FAIL" not in hapd.request("LEVEL 0"):
        raise Exception("Unexpected LEVEL success on non-monitor interface")

@remote_compatible
def test_hapd_ctrl_new_sta(dev, apdev):
    """hostapd and NEW_STA ctrl_iface command"""
    ssid = "hapd-ctrl"
    params = { "ssid": ssid }
    hapd = hostapd.add_ap(apdev[0], params)
    if "FAIL" not in hapd.request("NEW_STA 00:11:22:33:44"):
        raise Exception("Unexpected NEW_STA success")
    if "OK" not in hapd.request("NEW_STA 00:11:22:33:44:55"):
        raise Exception("Unexpected NEW_STA failure")
    if "AUTHORIZED" not in hapd.request("STA 00:11:22:33:44:55"):
        raise Exception("Unexpected NEW_STA STA status")

@remote_compatible
def test_hapd_ctrl_get(dev, apdev):
    """hostapd and GET ctrl_iface command"""
    ssid = "hapd-ctrl"
    params = { "ssid": ssid }
    hapd = hostapd.add_ap(apdev[0], params)
    if "FAIL" not in hapd.request("GET foo"):
        raise Exception("Unexpected GET success")
    if "FAIL" in hapd.request("GET version"):
        raise Exception("Unexpected GET version failure")

@remote_compatible
def test_hapd_ctrl_unknown(dev, apdev):
    """hostapd and unknown ctrl_iface command"""
    ssid = "hapd-ctrl"
    params = { "ssid": ssid }
    hapd = hostapd.add_ap(apdev[0], params)
    if "UNKNOWN COMMAND" not in hapd.request("FOO"):
        raise Exception("Unexpected response")

@remote_compatible
def test_hapd_ctrl_hs20_wnm_notif(dev, apdev):
    """hostapd and HS20_WNM_NOTIF ctrl_iface command"""
    ssid = "hapd-ctrl"
    params = { "ssid": ssid }
    hapd = hostapd.add_ap(apdev[0], params)
    if "FAIL" not in hapd.request("HS20_WNM_NOTIF 00:11:22:33:44 http://example.com/"):
        raise Exception("Unexpected HS20_WNM_NOTIF success")
    if "FAIL" not in hapd.request("HS20_WNM_NOTIF 00:11:22:33:44:55http://example.com/"):
        raise Exception("Unexpected HS20_WNM_NOTIF success")

@remote_compatible
def test_hapd_ctrl_hs20_deauth_req(dev, apdev):
    """hostapd and HS20_DEAUTH_REQ ctrl_iface command"""
    ssid = "hapd-ctrl"
    params = { "ssid": ssid }
    hapd = hostapd.add_ap(apdev[0], params)
    if "FAIL" not in hapd.request("HS20_DEAUTH_REQ 00:11:22:33:44 1 120 http://example.com/"):
        raise Exception("Unexpected HS20_DEAUTH_REQ success")
    if "FAIL" not in hapd.request("HS20_DEAUTH_REQ 00:11:22:33:44:55"):
        raise Exception("Unexpected HS20_DEAUTH_REQ success")
    if "FAIL" not in hapd.request("HS20_DEAUTH_REQ 00:11:22:33:44:55 1"):
        raise Exception("Unexpected HS20_DEAUTH_REQ success")

@remote_compatible
def test_hapd_ctrl_disassoc_imminent(dev, apdev):
    """hostapd and DISASSOC_IMMINENT ctrl_iface command"""
    ssid = "hapd-ctrl"
    params = { "ssid": ssid }
    hapd = hostapd.add_ap(apdev[0], params)
    if "FAIL" not in hapd.request("DISASSOC_IMMINENT 00:11:22:33:44"):
        raise Exception("Unexpected DISASSOC_IMMINENT success")
    if "FAIL" not in hapd.request("DISASSOC_IMMINENT 00:11:22:33:44:55"):
        raise Exception("Unexpected DISASSOC_IMMINENT success")
    if "FAIL" not in hapd.request("DISASSOC_IMMINENT 00:11:22:33:44:55 2"):
        raise Exception("Unexpected DISASSOC_IMMINENT success")
    dev[0].connect(ssid, key_mgmt="NONE", scan_freq="2412")
    addr = dev[0].p2p_interface_addr()
    if "OK" not in hapd.request("DISASSOC_IMMINENT " + addr + " 2"):
        raise Exception("Unexpected DISASSOC_IMMINENT failure")
    ev = dev[0].wait_event(["CTRL-EVENT-SCAN-RESULTS"], 15)
    if ev is None:
        raise Exception("Scan timed out")

@remote_compatible
def test_hapd_ctrl_ess_disassoc(dev, apdev):
    """hostapd and ESS_DISASSOC ctrl_iface command"""
    ssid = "hapd-ctrl"
    params = { "ssid": ssid }
    hapd = hostapd.add_ap(apdev[0], params)
    if "FAIL" not in hapd.request("ESS_DISASSOC 00:11:22:33:44"):
        raise Exception("Unexpected ESS_DISASSOCT success")
    if "FAIL" not in hapd.request("ESS_DISASSOC 00:11:22:33:44:55"):
        raise Exception("Unexpected ESS_DISASSOC success")
    dev[0].connect(ssid, key_mgmt="NONE", scan_freq="2412")
    addr = dev[0].p2p_interface_addr()
    if "FAIL" not in hapd.request("ESS_DISASSOC " + addr):
        raise Exception("Unexpected ESS_DISASSOC success")
    if "FAIL" not in hapd.request("ESS_DISASSOC " + addr + " -1"):
        raise Exception("Unexpected ESS_DISASSOC success")
    if "FAIL" not in hapd.request("ESS_DISASSOC " + addr + " 1"):
        raise Exception("Unexpected ESS_DISASSOC success")
    if "OK" not in hapd.request("ESS_DISASSOC " + addr + " 20 http://example.com/"):
        raise Exception("Unexpected ESS_DISASSOC failure")
    ev = dev[0].wait_event(["CTRL-EVENT-SCAN-RESULTS"], 15)
    if ev is None:
        raise Exception("Scan timed out")

def test_hapd_ctrl_set_deny_mac_file(dev, apdev):
    """hostapd and SET deny_mac_file ctrl_iface command"""
    ssid = "hapd-ctrl"
    params = { "ssid": ssid }
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, key_mgmt="NONE", scan_freq="2412")
    dev[1].connect(ssid, key_mgmt="NONE", scan_freq="2412")
    if "OK" not in hapd.request("SET deny_mac_file hostapd.macaddr"):
        raise Exception("Unexpected SET failure")
    dev[0].wait_disconnected(timeout=15)
    ev = dev[1].wait_event(["CTRL-EVENT-DISCONNECTED"], 1)
    if ev is not None:
        raise Exception("Unexpected disconnection")

def test_hapd_ctrl_set_accept_mac_file(dev, apdev):
    """hostapd and SET accept_mac_file ctrl_iface command"""
    ssid = "hapd-ctrl"
    params = { "ssid": ssid }
    hapd = hostapd.add_ap(apdev[0], params)
    dev[0].connect(ssid, key_mgmt="NONE", scan_freq="2412")
    dev[1].connect(ssid, key_mgmt="NONE", scan_freq="2412")
    hapd.request("SET macaddr_acl 1")
    if "OK" not in hapd.request("SET accept_mac_file hostapd.macaddr"):
        raise Exception("Unexpected SET failure")
    dev[1].wait_disconnected(timeout=15)
    ev = dev[0].wait_event(["CTRL-EVENT-DISCONNECTED"], 1)
    if ev is not None:
        raise Exception("Unexpected disconnection")

@remote_compatible
def test_hapd_ctrl_set_error_cases(dev, apdev):
    """hostapd and SET error cases"""
    ssid = "hapd-ctrl"
    params = { "ssid": ssid }
    hapd = hostapd.add_ap(apdev[0], params)
    errors = [ "wpa_key_mgmt FOO",
               "wpa_key_mgmt WPA-PSK   \t  FOO",
               "wpa_key_mgmt    \t  ",
               "wpa_pairwise FOO",
               "wpa_pairwise   \t   ",
               'wep_key0 "',
               'wep_key0 "abcde',
               "wep_key0 1",
               "wep_key0 12q3456789",
               "wep_key_len_broadcast 20",
               "wep_rekey_period -1",
               "wep_default_key 4",
               "r0kh 02:00:00:00:03:0q nas1.w1.fi 100102030405060708090a0b0c0d0e0f",
               "r0kh 02:00:00:00:03:00 12345678901234567890123456789012345678901234567890.nas1.w1.fi 100102030405060708090a0b0c0d0e0f",
               "r0kh 02:00:00:00:03:00 nas1.w1.fi 100q02030405060708090a0b0c0d0e0f",
               "r1kh 02:00:00:00:04:q0 00:01:02:03:04:06 200102030405060708090a0b0c0d0e0f",
               "r1kh 02:00:00:00:04:00 00:01:02:03:04:q6 200102030405060708090a0b0c0d0e0f",
               "r1kh 02:00:00:00:04:00 00:01:02:03:04:06 2q0102030405060708090a0b0c0d0e0f",
               "roaming_consortium 1",
               "roaming_consortium 12",
               "roaming_consortium 112233445566778899aabbccddeeff00",
               'venue_name P"engExample venue"',
               'venue_name P"engExample venue',
               "venue_name engExample venue",
               "venue_name e:Example venue",
               "venue_name eng1:Example venue",
               "venue_name eng:Example venue 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890",
               "anqp_3gpp_cell_net abc",
               "anqp_3gpp_cell_net ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;",
               "anqp_3gpp_cell_net 244",
               "anqp_3gpp_cell_net 24,123",
               "anqp_3gpp_cell_net 244,1",
               "anqp_3gpp_cell_net 244,1234",
               "nai_realm 0",
               "nai_realm 0,1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890.nas1.w1.fi",
               "nai_realm 0,example.org,1,2,3,4,5,6,7,8",
               "nai_realm 0,example.org,1[1:1][2:2][3:3][4:4][5:5]",
               "nai_realm 0,example.org,1[1]",
               "nai_realm 0,example.org,1[1:1",
               "nai_realm 0,a.example.org;b.example.org;c.example.org;d.example.org;e.example.org;f.example.org;g.example.org;h.example.org;i.example.org;j.example.org;k.example.org",
               "qos_map_set 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60",
               "qos_map_set 53,2,22,6,8,15,0,7,255,255,16,31,32,39,255,255,40,47,255,300",
               "qos_map_set 53,2,22,6,8,15,0,7,255,255,16,31,32,39,255,255,40,47,255,-1",
               "qos_map_set 53,2,22,6,8,15,0,7,255,255,16,31,32,39,255,255,40,47,255,255,1",
               "qos_map_set 1",
               "qos_map_set 1,2",
               "hs20_conn_capab 1",
               "hs20_conn_capab 6:22",
               "hs20_wan_metrics 0q:8000:1000:80:240:3000",
               "hs20_wan_metrics 01",
               "hs20_wan_metrics 01:8000",
               "hs20_wan_metrics 01:8000:1000",
               "hs20_wan_metrics 01:8000:1000:80",
               "hs20_wan_metrics 01:8000:1000:80:240",
               "hs20_oper_friendly_name eng1:Example",
               "hs20_icon 32",
               "hs20_icon 32:32",
               "hs20_icon 32:32:eng",
               "hs20_icon 32:32:eng:image/png",
               "hs20_icon 32:32:eng:image/png:icon32",
               "hs20_icon 32:32:eng:image/png:123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890:/tmp/icon32.png",
               "hs20_icon 32:32:eng:image/png:name:/tmp/123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890.png",
               "osu_ssid ",
               "osu_ssid P",
               'osu_ssid P"abc',
               'osu_ssid "1234567890123456789012345678901234567890"',
               "osu_friendly_name eng:Example",
               "osu_nai anonymous@example.com",
               "osu_method_list 1 0",
               "osu_icon foo",
               "osu_service_desc eng:Example services",
               "ssid 1234567890123456789012345678901234567890",
               "pac_opaque_encr_key 123456",
               "eap_fast_a_id 12345",
               "eap_fast_a_id 12345q",
               "own_ip_addr foo",
               "auth_server_addr foo2",
               "auth_server_shared_secret ",
               "acct_server_addr foo3",
               "acct_server_shared_secret ",
               "radius_auth_req_attr 123::",
               "radius_acct_req_attr 123::",
               "radius_das_client 192.168.1.123",
               "radius_das_client 192.168.1.1a foo",
               "auth_algs 0",
               "max_num_sta -1",
               "max_num_sta 1000000",
               "wpa_passphrase 1234567",
               "wpa_passphrase 1234567890123456789012345678901234567890123456789012345678901234",
               "wpa_psk 1234567890123456789012345678901234567890123456789012345678901234a",
               "wpa_psk 12345678901234567890123456789012345678901234567890123456789012",
               "wpa_psk_radius 123",
               "wpa_pairwise NONE",
               "wpa_pairwise WEP40",
               "wpa_pairwise WEP104",
               "rsn_pairwise NONE",
               "rsn_pairwise WEP40",
               "rsn_pairwise WEP104",
               "mobility_domain 01",
               "r1_key_holder 0011223344",
               "ctrl_interface_group nosuchgrouphere",
               "hw_mode foo",
               "wps_rf_bands foo",
               "beacon_int 0",
               "beacon_int 65536",
               "acs_num_scans 0",
               "acs_num_scans 101",
               "rts_threshold -2",
               "rts_threshold 65536",
               "fragm_threshold -2",
               "fragm_threshold 2347",
               "send_probe_response -1",
               "send_probe_response 2",
               "vlan_naming -1",
               "vlan_naming 10000000",
               "group_mgmt_cipher FOO",
               "assoc_sa_query_max_timeout 0",
               "assoc_sa_query_retry_timeout 0",
               "wps_state -1",
               "wps_state 3",
               "uuid FOO",
               "device_name 1234567890123456789012345678901234567890",
               "manufacturer 1234567890123456789012345678901234567890123456789012345678901234567890",
               "model_name 1234567890123456789012345678901234567890",
               "model_number 1234567890123456789012345678901234567890",
               "serial_number 1234567890123456789012345678901234567890",
               "device_type FOO",
               "os_version 1",
               "ap_settings /tmp/does/not/exist/ap-settings.foo",
               "wps_nfc_dev_pw_id 4",
               "wps_nfc_dev_pw_id 100000",
               "time_zone A",
               "access_network_type -1",
               "access_network_type 16",
               "hessid 00:11:22:33:44",
               "network_auth_type 0q",
               "ipaddr_type_availability 1q",
               "hs20_operating_class 0",
               "hs20_operating_class 0q",
               "bss_load_test ",
               "bss_load_test 12",
               "bss_load_test 12:80",
               "vendor_elements 0",
               "vendor_elements 0q",
               "assocresp_elements 0",
               "assocresp_elements 0q",
               "local_pwr_constraint -1",
               "local_pwr_constraint 256",
               "wmm_ac_bk_cwmin -1",
               "wmm_ac_be_cwmin 16",
               "wmm_ac_vi_cwmax -1",
               "wmm_ac_vo_cwmax 16",
               "wmm_ac_foo_cwmax 6",
               "wmm_ac_bk_aifs 0",
               "wmm_ac_bk_aifs 256",
               "wmm_ac_bk_txop_limit -1",
               "wmm_ac_bk_txop_limit 65536",
               "wmm_ac_bk_acm -1",
               "wmm_ac_bk_acm 2",
               "wmm_ac_bk_foo 2",
               "tx_queue_foo_aifs 3",
               "tx_queue_data3_cwmin 4",
               "tx_queue_data3_cwmax 4",
               "tx_queue_data3_aifs -4",
               "tx_queue_data3_foo 1" ]
    for e in errors:
        if "FAIL" not in hapd.request("SET " + e):
            raise Exception("Unexpected SET success: '%s'" % e)

    if "OK" not in hapd.request("SET osu_server_uri https://example.com/"):
        raise Exception("Unexpected SET osu_server_uri failure")
    if "OK" not in hapd.request("SET osu_friendly_name eng:Example"):
        raise Exception("Unexpected SET osu_friendly_name failure")

    errors = [ "osu_friendly_name eng1:Example",
               "osu_service_desc eng1:Example services" ]
    for e in errors:
        if "FAIL" not in hapd.request("SET " + e):
            raise Exception("Unexpected SET success: '%s'" % e)

    no_err = [ "wps_nfc_dh_pubkey 0",
               "wps_nfc_dh_privkey 0q",
               "wps_nfc_dev_pw 012",
               "manage_p2p 0",
               "disassoc_low_ack 0",
               "network_auth_type 01",
               "tdls_prohibit 0",
               "tdls_prohibit_chan_switch 0" ]
    for e in no_err:
        if "OK" not in hapd.request("SET " + e):
            raise Exception("Unexpected SET failure: '%s'" % e)

@remote_compatible
def test_hapd_ctrl_global(dev, apdev):
    """hostapd and GET ctrl_iface command"""
    ssid = "hapd-ctrl"
    params = { "ssid": ssid }
    ifname = apdev[0]['ifname']
    hapd = hostapd.add_ap(apdev[0], params)
    hapd_global = hostapd.HostapdGlobal(apdev[0])
    res = hapd_global.request("IFNAME=" + ifname + " PING")
    if "PONG" not in res:
            raise Exception("Could not ping hostapd interface " + ifname + " via global control interface")
    res = hapd_global.request("IFNAME=" + ifname + " GET version")
    if "FAIL" in res:
           raise Exception("Could not get hostapd version for " + ifname + " via global control interface")

def dup_network(hapd_global, src, dst, param):
    res = hapd_global.request("DUP_NETWORK %s %s %s" % (src, dst, param))
    if "OK" not in res:
        raise Exception("Could not dup %s param from %s to %s" % (param, src,
                                                                  dst))

def test_hapd_dup_network_global_wpa2(dev, apdev):
    """hostapd and DUP_NETWORK command (WPA2"""
    passphrase="12345678"
    src_ssid = "hapd-ctrl-src"
    dst_ssid = "hapd-ctrl-dst"

    src_params = hostapd.wpa2_params(ssid=src_ssid, passphrase=passphrase)
    src_ifname = apdev[0]['ifname']
    src_hapd = hostapd.add_ap(apdev[0], src_params)

    dst_params = { "ssid": dst_ssid }
    dst_ifname = apdev[1]['ifname']
    dst_hapd = hostapd.add_ap(apdev[1], dst_params, no_enable=True)

    hapd_global = hostapd.HostapdGlobal()

    for param in [ "wpa", "wpa_passphrase", "wpa_key_mgmt", "rsn_pairwise" ]:
        dup_network(hapd_global, src_ifname, dst_ifname, param)

    dst_hapd.enable()

    dev[0].connect(dst_ssid, psk=passphrase, proto="RSN", pairwise="CCMP",
                   scan_freq="2412")
    addr = dev[0].own_addr()
    if "FAIL" in dst_hapd.request("STA " + addr):
            raise Exception("Could not connect using duplicated wpa params")

def test_hapd_dup_network_global_wpa(dev, apdev):
    """hostapd and DUP_NETWORK command (WPA)"""
    skip_with_fips(dev[0])
    psk = '602e323e077bc63bd80307ef4745b754b0ae0a925c2638ecd13a794b9527b9e6'
    src_ssid = "hapd-ctrl-src"
    dst_ssid = "hapd-ctrl-dst"

    src_params = hostapd.wpa_params(ssid=src_ssid)
    src_params['wpa_psk'] = psk
    src_ifname = apdev[0]['ifname']
    src_hapd = hostapd.add_ap(apdev[0], src_params)

    dst_params = { "ssid": dst_ssid }
    dst_ifname = apdev[1]['ifname']
    dst_hapd = hostapd.add_ap(apdev[1], dst_params, no_enable=True)

    hapd_global = hostapd.HostapdGlobal()

    for param in [ "wpa", "wpa_psk", "wpa_key_mgmt", "wpa_pairwise" ]:
        dup_network(hapd_global, src_ifname, dst_ifname, param)

    dst_hapd.enable()

    dev[0].connect(dst_ssid, raw_psk=psk, proto="WPA", pairwise="TKIP",
                   scan_freq="2412")
    addr = dev[0].own_addr()
    if "FAIL" in dst_hapd.request("STA " + addr):
            raise Exception("Could not connect using duplicated wpa params")

@remote_compatible
def test_hapd_ctrl_log_level(dev, apdev):
    """hostapd ctrl_iface LOG_LEVEL"""
    hapd = hostapd.add_ap(apdev[0], { "ssid": "open" })
    level = hapd.request("LOG_LEVEL")
    if "Current level: MSGDUMP" not in level:
        raise Exception("Unexpected debug level(1): " + level)
    if "Timestamp: 1" not in level:
        raise Exception("Unexpected timestamp(1): " + level)

    if "OK" not in hapd.request("LOG_LEVEL  MSGDUMP  0"):
        raise Exception("LOG_LEVEL failed")
    level = hapd.request("LOG_LEVEL")
    if "Current level: MSGDUMP" not in level:
        raise Exception("Unexpected debug level(2): " + level)
    if "Timestamp: 0" not in level:
        raise Exception("Unexpected timestamp(2): " + level)

    if "OK" not in hapd.request("LOG_LEVEL  MSGDUMP  1"):
        raise Exception("LOG_LEVEL failed")
    level = hapd.request("LOG_LEVEL")
    if "Current level: MSGDUMP" not in level:
        raise Exception("Unexpected debug level(3): " + level)
    if "Timestamp: 1" not in level:
        raise Exception("Unexpected timestamp(3): " + level)

    if "FAIL" not in hapd.request("LOG_LEVEL FOO"):
        raise Exception("Invalid LOG_LEVEL accepted")

    for lev in [ "EXCESSIVE", "MSGDUMP", "DEBUG", "INFO", "WARNING", "ERROR" ]:
        if "OK" not in hapd.request("LOG_LEVEL " + lev):
            raise Exception("LOG_LEVEL failed for " + lev)
        level = hapd.request("LOG_LEVEL")
        if "Current level: " + lev not in level:
            raise Exception("Unexpected debug level: " + level)

    if "OK" not in hapd.request("LOG_LEVEL  MSGDUMP  1"):
        raise Exception("LOG_LEVEL failed")
    level = hapd.request("LOG_LEVEL")
    if "Current level: MSGDUMP" not in level:
        raise Exception("Unexpected debug level(3): " + level)
    if "Timestamp: 1" not in level:
        raise Exception("Unexpected timestamp(3): " + level)

@remote_compatible
def test_hapd_ctrl_disconnect_no_tx(dev, apdev):
    """hostapd disconnecting STA without transmitting Deauth/Disassoc"""
    ssid = "hapd-test"
    passphrase = "12345678"
    params = hostapd.wpa2_params(ssid=ssid, passphrase=passphrase)
    hapd = hostapd.add_ap(apdev[0], params)
    bssid = apdev[0]['bssid']
    dev[0].connect(ssid, psk=passphrase, scan_freq="2412")
    addr0 = dev[0].own_addr()
    dev[1].connect(ssid, psk=passphrase, scan_freq="2412")
    addr1 = dev[1].own_addr()

    # Disconnect the STA without sending out Deauthentication frame
    if "OK" not in hapd.request("DEAUTHENTICATE " + addr0 + " tx=0"):
        raise Exception("DEAUTHENTICATE command failed")
    # Force disconnection due to AP receiving a frame from not-asssociated STA
    dev[0].request("DATA_TEST_CONFIG 1")
    dev[0].request("DATA_TEST_TX " + bssid + " " + addr0)
    ev = dev[0].wait_event(["CTRL-EVENT-DISCONNECTED"], timeout=5)
    dev[0].request("DATA_TEST_CONFIG 0")
    if ev is None:
        raise Exception("Disconnection event not seen after TX attempt")
    if "reason=7" not in ev:
        raise Exception("Unexpected disconnection reason: " + ev)

    # Disconnect the STA without sending out Disassociation frame
    if "OK" not in hapd.request("DISASSOCIATE " + addr1 + " tx=0"):
        raise Exception("DISASSOCIATE command failed")
    # Force disconnection due to AP receiving a frame from not-asssociated STA
    dev[1].request("DATA_TEST_CONFIG 1")
    dev[1].request("DATA_TEST_TX " + bssid + " " + addr1)
    ev = dev[1].wait_event(["CTRL-EVENT-DISCONNECTED"], timeout=5)
    dev[1].request("DATA_TEST_CONFIG 0")
    if ev is None:
        raise Exception("Disconnection event not seen after TX attempt")
    if "reason=7" not in ev:
        raise Exception("Unexpected disconnection reason: " + ev)

def test_hapd_ctrl_mib(dev, apdev):
    """hostapd and MIB ctrl_iface command with open network"""
    ssid = "hapd-ctrl"
    params = { "ssid": ssid }
    hapd = hostapd.add_ap(apdev[0], params)

    mib = hapd.request("MIB")
    if len(mib) != 0:
        raise Exception("Unexpected MIB response: " + mib)

    mib = hapd.request("MIB radius_server")
    if len(mib) != 0:
        raise Exception("Unexpected 'MIB radius_server' response: " + mib)

    if "FAIL" not in hapd.request("MIB foo"):
        raise Exception("'MIB foo' succeeded")

    dev[0].connect(ssid, key_mgmt="NONE", scan_freq="2412")

    mib = hapd.request("MIB")
    if "FAIL" in mib:
        raise Exception("Unexpected MIB response: " + mib)

    mib = hapd.request("MIB radius_server")
    if len(mib) != 0:
        raise Exception("Unexpected 'MIB radius_server' response: " + mib)

    if "FAIL" not in hapd.request("MIB foo"):
        raise Exception("'MIB foo' succeeded")

def test_hapd_ctrl_not_yet_fully_enabled(dev, apdev):
    """hostapd and ctrl_iface commands when BSS not yet fully enabled"""
    ssid = "hapd-ctrl"
    params = { "ssid": ssid }
    hapd = hostapd.add_ap(apdev[0], params, no_enable=True)

    if not hapd.ping():
        raise Exception("PING failed")
    if "FAIL" in hapd.request("MIB"):
        raise Exception("MIB failed")
    if len(hapd.request("MIB radius_server")) != 0:
        raise Exception("Unexpected 'MIB radius_server' response")
    if "state=UNINITIALIZED" not in hapd.request("STATUS"):
        raise Exception("Unexpected STATUS response")
    if "FAIL" not in hapd.request("STATUS-DRIVER"):
        raise Exception("Unexpected response to STATUS-DRIVER")
    if len(hapd.request("STA-FIRST")) != 0:
        raise Exception("Unexpected response to STA-FIRST")
    if "FAIL" not in hapd.request("STA ff:ff:ff:ff:ff:ff"):
        raise Exception("Unexpected response to STA")
    cmds = [ "NEW_STA 02:ff:ff:ff:ff:ff",
             "DEAUTHENTICATE 02:ff:ff:ff:ff:ff",
             "DEAUTHENTICATE 02:ff:ff:ff:ff:ff test=0",
             "DEAUTHENTICATE 02:ff:ff:ff:ff:ff p2p=0",
             "DEAUTHENTICATE 02:ff:ff:ff:ff:ff tx=0",
             "DISASSOCIATE 02:ff:ff:ff:ff:ff",
             "DISASSOCIATE 02:ff:ff:ff:ff:ff test=0",
             "DISASSOCIATE 02:ff:ff:ff:ff:ff p2p=0",
             "DISASSOCIATE 02:ff:ff:ff:ff:ff tx=0",
             "SA_QUERY 02:ff:ff:ff:ff:ff",
             "WPS_PIN any 12345670",
             "WPS_PBC",
             "WPS_CANCEL",
             "WPS_AP_PIN random",
             "WPS_AP_PIN disable",
             "WPS_CHECK_PIN 123456789",
             "WPS_GET_STATUS",
             "WPS_NFC_TAG_READ 00",
             "WPS_NFC_CONFIG_TOKEN NDEF",
             "WPS_NFC_TOKEN WPS",
             "NFC_GET_HANDOVER_SEL NDEF WPS-CR",
             "NFC_REPORT_HANDOVER RESP WPS 00 00",
             "SET_QOS_MAP_SET 22,6,8,15,0,7,255,255,16,31,32,39,255,255,40,47,48,55",
             "SEND_QOS_MAP_CONF 02:ff:ff:ff:ff:ff",
             "HS20_WNM_NOTIF 02:ff:ff:ff:ff:ff https://example.com/",
             "HS20_DEAUTH_REQ 02:ff:ff:ff:ff:ff 1 120 https://example.com/",
             "DISASSOC_IMMINENT 02:ff:ff:ff:ff:ff 10",
             "ESS_DISASSOC 02:ff:ff:ff:ff:ff 10 https://example.com/",
             "BSS_TM_REQ 02:ff:ff:ff:ff:ff",
             "GET_CONFIG",
             "RADAR DETECTED freq=5260 ht_enabled=1 chan_width=1",
             "CHAN_SWITCH 5 5200 ht sec_channel_offset=-1 bandwidth=40",
             "TRACK_STA_LIST",
             "PMKSA",
             "PMKSA_FLUSH",
             "SET_NEIGHBOR 00:11:22:33:44:55 ssid=\"test1\"",
             "REMOVE_NEIGHBOR 00:11:22:33:44:55 ssid=\"test1\"",
             "REQ_LCI 00:11:22:33:44:55",
             "REQ_RANGE 00:11:22:33:44:55",
             "DRIVER_FLAGS",
             "STOP_AP" ]
    for cmd in cmds:
        hapd.request(cmd)
