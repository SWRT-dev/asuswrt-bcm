# Scanning tests
# Copyright (c) 2013-2015, Jouni Malinen <j@w1.fi>
#
# This software may be distributed under the terms of the BSD license.
# See README for more details.

from remotehost import remote_compatible
import time
import logging
logger = logging.getLogger()
import os
import subprocess

import hostapd
from wpasupplicant import WpaSupplicant
from utils import HwsimSkip, fail_test, alloc_fail, wait_fail_trigger
from tshark import run_tshark

def check_scan(dev, params, other_started=False, test_busy=False):
    if not other_started:
        dev.dump_monitor()
    id = dev.request("SCAN " + params)
    if "FAIL" in id:
        raise Exception("Failed to start scan")
    id = int(id)

    if test_busy:
        if "FAIL-BUSY" not in dev.request("SCAN"):
            raise Exception("SCAN command while already scanning not rejected")

    if other_started:
        ev = dev.wait_event(["CTRL-EVENT-SCAN-STARTED"])
        if ev is None:
            raise Exception("Other scan did not start")
        if "id=" + str(id) in ev:
            raise Exception("Own scan id unexpectedly included in start event")

        ev = dev.wait_event(["CTRL-EVENT-SCAN-RESULTS"])
        if ev is None:
            raise Exception("Other scan did not complete")
        if "id=" + str(id) in ev:
            raise Exception("Own scan id unexpectedly included in completed event")

    ev = dev.wait_event(["CTRL-EVENT-SCAN-STARTED"])
    if ev is None:
        raise Exception("Scan did not start")
    if "id=" + str(id) not in ev:
        raise Exception("Scan id not included in start event")
    if test_busy:
        if "FAIL-BUSY" not in dev.request("SCAN"):
            raise Exception("SCAN command while already scanning not rejected")

    ev = dev.wait_event(["CTRL-EVENT-SCAN-RESULTS"])
    if ev is None:
        raise Exception("Scan did not complete")
    if "id=" + str(id) not in ev:
        raise Exception("Scan id not included in completed event")

def check_scan_retry(dev, params, bssid):
    for i in range(0, 5):
        check_scan(dev, "freq=2412-2462,5180 use_id=1")
        if int(dev.get_bss(bssid)['age']) <= 1:
            return
    raise Exception("Unexpectedly old BSS entry")

@remote_compatible
def test_scan(dev, apdev):
    """Control interface behavior on scan parameters"""
    hostapd.add_ap(apdev[0], { "ssid": "test-scan" })
    bssid = apdev[0]['bssid']

    logger.info("Full scan")
    check_scan(dev[0], "use_id=1", test_busy=True)

    logger.info("Limited channel scan")
    check_scan_retry(dev[0], "freq=2412-2462,5180 use_id=1", bssid)

    # wait long enough to allow next scans to be verified not to find the AP
    time.sleep(2)

    logger.info("Passive single-channel scan")
    check_scan(dev[0], "freq=2457 passive=1 use_id=1")
    logger.info("Active single-channel scan")
    check_scan(dev[0], "freq=2452 passive=0 use_id=1")
    if int(dev[0].get_bss(bssid)['age']) < 2:
        raise Exception("Unexpectedly updated BSS entry")

    logger.info("Active single-channel scan on AP's operating channel")
    check_scan_retry(dev[0], "freq=2412 passive=0 use_id=1", bssid)

@remote_compatible
def test_scan_tsf(dev, apdev):
    """Scan and TSF updates from Beacon/Probe Response frames"""
    hostapd.add_ap(apdev[0], { "ssid": "test-scan",
                               'beacon_int': "100" })
    bssid = apdev[0]['bssid']

    tsf = []
    for passive in [ 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1 ]:
        check_scan(dev[0], "freq=2412 passive=%d use_id=1" % passive)
        bss = dev[0].get_bss(bssid)
        if bss:
            tsf.append(int(bss['tsf']))
            logger.info("TSF: " + bss['tsf'])
    if tsf[-3] <= tsf[-4]:
        # For now, only write this in the log without failing the test case
        # since mac80211_hwsim does not yet update the Timestamp field in
        # Probe Response frames.
        logger.info("Probe Response did not update TSF")
        #raise Exception("Probe Response did not update TSF")
    if tsf[-1] <= tsf[-3]:
        raise Exception("Beacon did not update TSF")
    if 0 in tsf:
        raise Exception("0 TSF reported")

@remote_compatible
def test_scan_only(dev, apdev):
    """Control interface behavior on scan parameters with type=only"""
    hostapd.add_ap(apdev[0], { "ssid": "test-scan" })
    bssid = apdev[0]['bssid']

    logger.info("Full scan")
    check_scan(dev[0], "type=only use_id=1")

    logger.info("Limited channel scan")
    check_scan_retry(dev[0], "type=only freq=2412-2462,5180 use_id=1", bssid)

    # wait long enough to allow next scans to be verified not to find the AP
    time.sleep(2)

    logger.info("Passive single-channel scan")
    check_scan(dev[0], "type=only freq=2457 passive=1 use_id=1")
    logger.info("Active single-channel scan")
    check_scan(dev[0], "type=only freq=2452 passive=0 use_id=1")
    if int(dev[0].get_bss(bssid)['age']) < 2:
        raise Exception("Unexpectedly updated BSS entry")

    logger.info("Active single-channel scan on AP's operating channel")
    check_scan_retry(dev[0], "type=only freq=2412 passive=0 use_id=1", bssid)

@remote_compatible
def test_scan_external_trigger(dev, apdev):
    """Avoid operations during externally triggered scan"""
    hostapd.add_ap(apdev[0], { "ssid": "test-scan" })
    bssid = apdev[0]['bssid']
    dev[0].cmd_execute(['iw', dev[0].ifname, 'scan', 'trigger'])
    check_scan(dev[0], "use_id=1", other_started=True)

def test_scan_bss_expiration_count(dev, apdev):
    """BSS entry expiration based on scan results without match"""
    if "FAIL" not in dev[0].request("BSS_EXPIRE_COUNT 0"):
        raise Exception("Invalid BSS_EXPIRE_COUNT accepted")
    if "OK" not in dev[0].request("BSS_EXPIRE_COUNT 2"):
        raise Exception("BSS_EXPIRE_COUNT failed")
    hapd = hostapd.add_ap(apdev[0], { "ssid": "test-scan" })
    bssid = apdev[0]['bssid']
    dev[0].scan(freq="2412", only_new=True)
    if bssid not in dev[0].request("SCAN_RESULTS"):
        raise Exception("BSS not found in initial scan")
    hapd.request("DISABLE")
    dev[0].scan(freq="2412", only_new=True)
    if bssid not in dev[0].request("SCAN_RESULTS"):
        raise Exception("BSS not found in first scan without match")
    dev[0].scan(freq="2412", only_new=True)
    if bssid in dev[0].request("SCAN_RESULTS"):
        raise Exception("BSS found after two scans without match")

@remote_compatible
def test_scan_bss_expiration_age(dev, apdev):
    """BSS entry expiration based on age"""
    try:
        if "FAIL" not in dev[0].request("BSS_EXPIRE_AGE COUNT 9"):
            raise Exception("Invalid BSS_EXPIRE_AGE accepted")
        if "OK" not in dev[0].request("BSS_EXPIRE_AGE 10"):
            raise Exception("BSS_EXPIRE_AGE failed")
        hapd = hostapd.add_ap(apdev[0], { "ssid": "test-scan" })
        bssid = apdev[0]['bssid']
        # Allow couple more retries to avoid reporting errors during heavy load
        for i in range(5):
            dev[0].scan(freq="2412")
            if bssid in dev[0].request("SCAN_RESULTS"):
                break
        if bssid not in dev[0].request("SCAN_RESULTS"):
            raise Exception("BSS not found in initial scan")
        hapd.request("DISABLE")
        logger.info("Waiting for BSS entry to expire")
        time.sleep(7)
        if bssid not in dev[0].request("SCAN_RESULTS"):
            raise Exception("BSS expired too quickly")
        ev = dev[0].wait_event(["CTRL-EVENT-BSS-REMOVED"], timeout=15)
        if ev is None:
            raise Exception("BSS entry expiration timed out")
        if bssid in dev[0].request("SCAN_RESULTS"):
            raise Exception("BSS not removed after expiration time")
    finally:
        dev[0].request("BSS_EXPIRE_AGE 180")

@remote_compatible
def test_scan_filter(dev, apdev):
    """Filter scan results based on SSID"""
    try:
        if "OK" not in dev[0].request("SET filter_ssids 1"):
            raise Exception("SET failed")
        id = dev[0].connect("test-scan", key_mgmt="NONE", only_add_network=True)
        hostapd.add_ap(apdev[0], { "ssid": "test-scan" })
        bssid = apdev[0]['bssid']
        hostapd.add_ap(apdev[1], { "ssid": "test-scan2" })
        bssid2 = apdev[1]['bssid']
        dev[0].scan(freq="2412", only_new=True)
        if bssid not in dev[0].request("SCAN_RESULTS"):
            raise Exception("BSS not found in scan results")
        if bssid2 in dev[0].request("SCAN_RESULTS"):
            raise Exception("Unexpected BSS found in scan results")
        dev[0].set_network_quoted(id, "ssid", "")
        dev[0].scan(freq="2412")
        id2 = dev[0].connect("test", key_mgmt="NONE", only_add_network=True)
        dev[0].scan(freq="2412")
    finally:
        dev[0].request("SET filter_ssids 0")

@remote_compatible
def test_scan_int(dev, apdev):
    """scan interval configuration"""
    try:
        if "FAIL" not in dev[0].request("SCAN_INTERVAL -1"):
            raise Exception("Accepted invalid scan interval")
        if "OK" not in dev[0].request("SCAN_INTERVAL 1"):
            raise Exception("Failed to set scan interval")
        dev[0].connect("not-used", key_mgmt="NONE", scan_freq="2412",
                       wait_connect=False)
        times = {}
        for i in range(0, 3):
            logger.info("Waiting for scan to start")
            start = os.times()[4]
            ev = dev[0].wait_event(["CTRL-EVENT-SCAN-STARTED"], timeout=5)
            if ev is None:
                raise Exception("did not start a scan")
            stop = os.times()[4]
            times[i] = stop - start
            logger.info("Waiting for scan to complete")
            ev = dev[0].wait_event(["CTRL-EVENT-SCAN-RESULTS"], 10)
            if ev is None:
                raise Exception("did not complete a scan")
        logger.info("times=" + str(times))
        if times[0] > 1 or times[1] < 0.5 or times[1] > 1.5 or times[2] < 0.5 or times[2] > 1.5:
            raise Exception("Unexpected scan timing: " + str(times))
    finally:
        dev[0].request("SCAN_INTERVAL 5")

def test_scan_bss_operations(dev, apdev):
    """Control interface behavior on BSS parameters"""
    hostapd.add_ap(apdev[0], { "ssid": "test-scan" })
    bssid = apdev[0]['bssid']
    hostapd.add_ap(apdev[1], { "ssid": "test2-scan" })
    bssid2 = apdev[1]['bssid']

    dev[0].scan(freq="2412")
    dev[0].scan(freq="2412")
    dev[0].scan(freq="2412")

    id1 = dev[0].request("BSS FIRST MASK=0x1").splitlines()[0].split('=')[1]
    id2 = dev[0].request("BSS LAST MASK=0x1").splitlines()[0].split('=')[1]

    res = dev[0].request("BSS RANGE=ALL MASK=0x20001")
    if "id=" + id1 not in res:
        raise Exception("Missing BSS " + id1)
    if "id=" + id2 not in res:
        raise Exception("Missing BSS " + id2)
    if "====" not in res:
        raise Exception("Missing delim")
    if "####" not in res:
        raise Exception("Missing end")

    res = dev[0].request("BSS RANGE=ALL MASK=0")
    if "id=" + id1 not in res:
        raise Exception("Missing BSS " + id1)
    if "id=" + id2 not in res:
        raise Exception("Missing BSS " + id2)
    if "====" in res:
        raise Exception("Unexpected delim")
    if "####" in res:
        raise Exception("Unexpected end delim")

    res = dev[0].request("BSS RANGE=ALL MASK=0x1").splitlines()
    if len(res) != 2:
        raise Exception("Unexpected result: " + str(res))
    res = dev[0].request("BSS FIRST MASK=0x1")
    if "id=" + id1 not in res:
        raise Exception("Unexpected result: " + res)
    res = dev[0].request("BSS LAST MASK=0x1")
    if "id=" + id2 not in res:
        raise Exception("Unexpected result: " + res)
    res = dev[0].request("BSS ID-" + id1 + " MASK=0x1")
    if "id=" + id1 not in res:
        raise Exception("Unexpected result: " + res)
    res = dev[0].request("BSS NEXT-" + id1 + " MASK=0x1")
    if "id=" + id2 not in res:
        raise Exception("Unexpected result: " + res)
    res = dev[0].request("BSS NEXT-" + id2 + " MASK=0x1")
    if "id=" in res:
        raise Exception("Unexpected result: " + res)

    if len(dev[0].request("BSS RANGE=" + id2 + " MASK=0x1").splitlines()) != 0:
        raise Exception("Unexpected RANGE=1 result")
    if len(dev[0].request("BSS RANGE=" + id1 + "- MASK=0x1").splitlines()) != 2:
        raise Exception("Unexpected RANGE=0- result")
    if len(dev[0].request("BSS RANGE=-" + id2 + " MASK=0x1").splitlines()) != 2:
        raise Exception("Unexpected RANGE=-1 result")
    if len(dev[0].request("BSS RANGE=" + id1 + "-" + id2 + " MASK=0x1").splitlines()) != 2:
        raise Exception("Unexpected RANGE=0-1 result")
    if len(dev[0].request("BSS RANGE=" + id2 + "-" + id2 + " MASK=0x1").splitlines()) != 1:
        raise Exception("Unexpected RANGE=1-1 result")
    if len(dev[0].request("BSS RANGE=" + str(int(id2) + 1) + "-" + str(int(id2) + 10) + " MASK=0x1").splitlines()) != 0:
        raise Exception("Unexpected RANGE=2-10 result")
    if len(dev[0].request("BSS RANGE=0-" + str(int(id2) + 10) + " MASK=0x1").splitlines()) != 2:
        raise Exception("Unexpected RANGE=0-10 result")
    if len(dev[0].request("BSS RANGE=" + id1 + "-" + id1 + " MASK=0x1").splitlines()) != 1:
        raise Exception("Unexpected RANGE=0-0 result")

    res = dev[0].request("BSS p2p_dev_addr=FOO")
    if "FAIL" in res or "id=" in res:
        raise Exception("Unexpected result: " + res)
    res = dev[0].request("BSS p2p_dev_addr=00:11:22:33:44:55")
    if "FAIL" in res or "id=" in res:
        raise Exception("Unexpected result: " + res)

    dev[0].request("BSS_FLUSH 1000")
    res = dev[0].request("BSS RANGE=ALL MASK=0x1").splitlines()
    if len(res) != 2:
        raise Exception("Unexpected result after BSS_FLUSH 1000")
    dev[0].request("BSS_FLUSH 0")
    res = dev[0].request("BSS RANGE=ALL MASK=0x1").splitlines()
    if len(res) != 0:
        raise Exception("Unexpected result after BSS_FLUSH 0")

@remote_compatible
def test_scan_and_interface_disabled(dev, apdev):
    """Scan operation when interface gets disabled"""
    try:
        dev[0].request("SCAN")
        ev = dev[0].wait_event(["CTRL-EVENT-SCAN-STARTED"])
        if ev is None:
            raise Exception("Scan did not start")
        dev[0].request("DRIVER_EVENT INTERFACE_DISABLED")
        ev = dev[0].wait_event(["CTRL-EVENT-SCAN-RESULTS"], timeout=7)
        if ev is not None:
            raise Exception("Scan completed unexpectedly")

        # verify that scan is rejected
        if "FAIL" not in dev[0].request("SCAN"):
            raise Exception("New scan request was accepted unexpectedly")

        dev[0].request("DRIVER_EVENT INTERFACE_ENABLED")
        dev[0].scan(freq="2412")
    finally:
        dev[0].request("DRIVER_EVENT INTERFACE_ENABLED")

@remote_compatible
def test_scan_for_auth(dev, apdev):
    """cfg80211 workaround with scan-for-auth"""
    hapd = hostapd.add_ap(apdev[0], { "ssid": "open" })
    dev[0].scan_for_bss(apdev[0]['bssid'], freq="2412")
    # Block sme-connect radio work with an external radio work item, so that
    # SELECT_NETWORK can decide to use fast associate without a new scan while
    # cfg80211 still has the matching BSS entry, but the actual connection is
    # not yet started.
    id = dev[0].request("RADIO_WORK add block-work")
    ev = dev[0].wait_event(["EXT-RADIO-WORK-START"])
    if ev is None:
        raise Exception("Timeout while waiting radio work to start")
    dev[0].connect("open", key_mgmt="NONE", scan_freq="2412",
                   wait_connect=False)
    dev[0].dump_monitor()
    # Clear cfg80211 BSS table.
    res, data = dev[0].cmd_execute(['iw', dev[0].ifname, 'scan', 'trigger',
                                    'freq', '2457', 'flush'])
    if res != 0:
        raise HwsimSkip("iw scan trigger flush not supported")
    ev = dev[0].wait_event(["CTRL-EVENT-SCAN-RESULTS"], 5)
    if ev is None:
        raise Exception("External flush scan timed out")
    # Release blocking radio work to allow connection to go through with the
    # cfg80211 BSS entry missing.
    dev[0].request("RADIO_WORK done " + id)

    dev[0].wait_connected(timeout=15)

@remote_compatible
def test_scan_for_auth_fail(dev, apdev):
    """cfg80211 workaround with scan-for-auth failing"""
    hapd = hostapd.add_ap(apdev[0], { "ssid": "open" })
    dev[0].scan_for_bss(apdev[0]['bssid'], freq="2412")
    # Block sme-connect radio work with an external radio work item, so that
    # SELECT_NETWORK can decide to use fast associate without a new scan while
    # cfg80211 still has the matching BSS entry, but the actual connection is
    # not yet started.
    id = dev[0].request("RADIO_WORK add block-work")
    ev = dev[0].wait_event(["EXT-RADIO-WORK-START"])
    if ev is None:
        raise Exception("Timeout while waiting radio work to start")
    dev[0].connect("open", key_mgmt="NONE", scan_freq="2412",
                   wait_connect=False)
    dev[0].dump_monitor()
    hapd.disable()
    # Clear cfg80211 BSS table.
    res, data = dev[0].cmd_execute(['iw', dev[0].ifname, 'scan', 'trigger',
                                    'freq', '2457', 'flush'])
    if res != 0:
        raise HwsimSkip("iw scan trigger flush not supported")
    ev = dev[0].wait_event(["CTRL-EVENT-SCAN-RESULTS"], 5)
    if ev is None:
        raise Exception("External flush scan timed out")
    # Release blocking radio work to allow connection to go through with the
    # cfg80211 BSS entry missing.
    dev[0].request("RADIO_WORK done " + id)

    ev = dev[0].wait_event(["CTRL-EVENT-SCAN-RESULTS",
                            "CTRL-EVENT-CONNECTED"], 15)
    if ev is None:
        raise Exception("Scan event missing")
    if "CTRL-EVENT-CONNECTED" in ev:
        raise Exception("Unexpected connection")
    dev[0].request("DISCONNECT")

@remote_compatible
def test_scan_for_auth_wep(dev, apdev):
    """cfg80211 scan-for-auth workaround with WEP keys"""
    dev[0].flush_scan_cache()
    hapd = hostapd.add_ap(apdev[0],
                          { "ssid": "wep", "wep_key0": '"abcde"',
                            "auth_algs": "2" })
    dev[0].scan_for_bss(apdev[0]['bssid'], freq="2412")
    # Block sme-connect radio work with an external radio work item, so that
    # SELECT_NETWORK can decide to use fast associate without a new scan while
    # cfg80211 still has the matching BSS entry, but the actual connection is
    # not yet started.
    id = dev[0].request("RADIO_WORK add block-work")
    ev = dev[0].wait_event(["EXT-RADIO-WORK-START"])
    if ev is None:
        raise Exception("Timeout while waiting radio work to start")
    dev[0].connect("wep", key_mgmt="NONE", wep_key0='"abcde"',
                   auth_alg="SHARED", scan_freq="2412", wait_connect=False)
    dev[0].dump_monitor()
    # Clear cfg80211 BSS table.
    res, data = dev[0].cmd_execute(['iw', dev[0].ifname, 'scan', 'trigger',
                                    'freq', '2457', 'flush'])
    if res != 0:
        raise HwsimSkip("iw scan trigger flush not supported")
    ev = dev[0].wait_event(["CTRL-EVENT-SCAN-RESULTS"], 5)
    if ev is None:
        raise Exception("External flush scan timed out")
    # Release blocking radio work to allow connection to go through with the
    # cfg80211 BSS entry missing.
    dev[0].request("RADIO_WORK done " + id)

    dev[0].wait_connected(timeout=15)

@remote_compatible
def test_scan_hidden(dev, apdev):
    """Control interface behavior on scan parameters"""
    hapd = hostapd.add_ap(apdev[0], { "ssid": "test-scan",
                                      "ignore_broadcast_ssid": "1" })
    bssid = apdev[0]['bssid']

    check_scan(dev[0], "freq=2412 use_id=1")
    if "test-scan" in dev[0].request("SCAN_RESULTS"):
        raise Exception("BSS unexpectedly found in initial scan")

    id1 = dev[0].connect("foo", key_mgmt="NONE", scan_ssid="1",
                         only_add_network=True)
    id2 = dev[0].connect("test-scan", key_mgmt="NONE", scan_ssid="1",
                         only_add_network=True)
    id3 = dev[0].connect("bar", key_mgmt="NONE", only_add_network=True)

    check_scan(dev[0], "freq=2412 use_id=1")
    if "test-scan" in dev[0].request("SCAN_RESULTS"):
        raise Exception("BSS unexpectedly found in scan")

    # Allow multiple attempts to be more robust under heavy CPU load that can
    # result in Probe Response frames getting sent only after the station has
    # already stopped waiting for the response on the channel.
    found = False
    for i in range(10):
        check_scan(dev[0], "scan_id=%d,%d,%d freq=2412 use_id=1" % (id1, id2, id3))
        if "test-scan" in dev[0].request("SCAN_RESULTS"):
            found = True
            break
    if not found:
        raise Exception("BSS not found in scan")

    if "FAIL" not in dev[0].request("SCAN scan_id=1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17"):
        raise Exception("Too many scan_id values accepted")

    # Duplicate SSID removal
    check_scan(dev[0], "scan_id=%d,%d,%d freq=2412 use_id=1" % (id1, id1, id2))

    dev[0].request("REMOVE_NETWORK all")
    hapd.disable()
    dev[0].flush_scan_cache(freq=2432)
    dev[0].flush_scan_cache()

def test_scan_and_bss_entry_removed(dev, apdev):
    """Last scan result and connect work processing on BSS entry update"""
    hapd = hostapd.add_ap(apdev[0], { "ssid": "open",
                                      "eap_server": "1",
                                      "wps_state": "2" })
    bssid = apdev[0]['bssid']

    wpas = WpaSupplicant(global_iface='/tmp/wpas-wlan5')
    wpas.interface_add("wlan5", drv_params="force_connect_cmd=1")

    # Add a BSS entry
    dev[0].scan_for_bss(bssid, freq="2412")
    wpas.scan_for_bss(bssid, freq="2412")

    # Start a connect radio work with a blocking entry preventing this from
    # proceeding; this stores a pointer to the selected BSS entry.
    id = dev[0].request("RADIO_WORK add block-work")
    w_id = wpas.request("RADIO_WORK add block-work")
    dev[0].wait_event(["EXT-RADIO-WORK-START"], timeout=1)
    wpas.wait_event(["EXT-RADIO-WORK-START"], timeout=1)
    nid = dev[0].connect("open", key_mgmt="NONE", scan_freq="2412",
                         wait_connect=False)
    w_nid = wpas.connect("open", key_mgmt="NONE", scan_freq="2412",
                         wait_connect=False)
    time.sleep(0.1)

    # Remove the BSS entry
    dev[0].request("BSS_FLUSH 0")
    wpas.request("BSS_FLUSH 0")

    # Allow the connect radio work to continue. The bss entry stored in the
    # pending connect work is now stale. This will result in the connection
    # attempt failing since the BSS entry does not exist.
    dev[0].request("RADIO_WORK done " + id)
    wpas.request("RADIO_WORK done " + w_id)

    ev = dev[0].wait_event(["CTRL-EVENT-CONNECTED"], timeout=1)
    if ev is not None:
        raise Exception("Unexpected connection")
    dev[0].remove_network(nid)
    ev = wpas.wait_event(["CTRL-EVENT-CONNECTED"], timeout=1)
    if ev is not None:
        raise Exception("Unexpected connection")
    wpas.remove_network(w_nid)
    time.sleep(0.5)
    dev[0].request("BSS_FLUSH 0")
    wpas.request("BSS_FLUSH 0")

    # Add a BSS entry
    dev[0].scan_for_bss(bssid, freq="2412")
    wpas.scan_for_bss(bssid, freq="2412")

    # Start a connect radio work with a blocking entry preventing this from
    # proceeding; this stores a pointer to the selected BSS entry.
    id = dev[0].request("RADIO_WORK add block-work")
    w_id = wpas.request("RADIO_WORK add block-work")
    dev[0].wait_event(["EXT-RADIO-WORK-START"], timeout=1)
    wpas.wait_event(["EXT-RADIO-WORK-START"], timeout=1)

    # Schedule a connection based on the current BSS entry.
    dev[0].connect("open", key_mgmt="NONE", scan_freq="2412",
                   wait_connect=False)
    wpas.connect("open", key_mgmt="NONE", scan_freq="2412",
                 wait_connect=False)

    # Update scan results with results that have longer set of IEs so that new
    # memory needs to be allocated for the BSS entry.
    hapd.request("WPS_PBC")
    time.sleep(0.1)
    subprocess.call(['iw', dev[0].ifname, 'scan', 'trigger', 'freq', '2412'])
    subprocess.call(['iw', wpas.ifname, 'scan', 'trigger', 'freq', '2412'])
    time.sleep(0.1)

    # Allow the connect radio work to continue. The bss entry stored in the
    # pending connect work becomes stale during the scan and it must have been
    # updated for the connection to work.
    dev[0].request("RADIO_WORK done " + id)
    wpas.request("RADIO_WORK done " + w_id)

    dev[0].wait_connected(timeout=15, error="No connection (sme-connect)")
    wpas.wait_connected(timeout=15, error="No connection (connect)")
    dev[0].request("DISCONNECT")
    wpas.request("DISCONNECT")
    dev[0].flush_scan_cache()
    wpas.flush_scan_cache()

@remote_compatible
def test_scan_reqs_with_non_scan_radio_work(dev, apdev):
    """SCAN commands while non-scan radio_work is in progress"""
    id = dev[0].request("RADIO_WORK add test-work-a")
    ev = dev[0].wait_event(["EXT-RADIO-WORK-START"])
    if ev is None:
        raise Exception("Timeout while waiting radio work to start")

    if "OK" not in dev[0].request("SCAN"):
        raise Exception("SCAN failed")
    if "FAIL-BUSY" not in dev[0].request("SCAN"):
        raise Exception("SCAN accepted while one is already pending")
    if "FAIL-BUSY" not in dev[0].request("SCAN"):
        raise Exception("SCAN accepted while one is already pending")

    res = dev[0].request("RADIO_WORK show").splitlines()
    count = 0
    for l in res:
        if "scan" in l:
            count += 1
    if count != 1:
        logger.info(res)
        raise Exception("Unexpected number of scan radio work items")

    dev[0].dump_monitor()
    dev[0].request("RADIO_WORK done " + id)
    ev = dev[0].wait_event(["CTRL-EVENT-SCAN-STARTED"], timeout=5)
    if ev is None:
        raise Exception("Scan did not start")
    if "FAIL-BUSY" not in dev[0].request("SCAN"):
        raise Exception("SCAN accepted while one is already in progress")

    ev = dev[0].wait_event(["CTRL-EVENT-SCAN-RESULTS"], timeout=10)
    if ev is None:
        print "Scan did not complete"
    ev = dev[0].wait_event(["CTRL-EVENT-SCAN-STARTED"], timeout=0.2)
    if ev is not None:
        raise Exception("Unexpected scan started")

def test_scan_setband(dev, apdev):
    """Band selection for scan operations"""
    try:
        hapd = None
        hapd2 = None
        params = { "ssid": "test-setband",
                   "hw_mode": "a",
                   "channel": "36",
                   "country_code": "US" }
        hapd = hostapd.add_ap(apdev[0], params)
        bssid = apdev[0]['bssid']

        params = { "ssid": "test-setband",
                   "hw_mode": "g",
                   "channel": "1" }
        hapd2 = hostapd.add_ap(apdev[1], params)
        bssid2 = apdev[1]['bssid']

        if "FAIL" not in dev[0].request("SET setband FOO"):
            raise Exception("Invalid set setband accepted")
        if "OK" not in dev[0].request("SET setband AUTO"):
            raise Exception("Failed to set setband")
        if "OK" not in dev[1].request("SET setband 5G"):
            raise Exception("Failed to set setband")
        if "OK" not in dev[2].request("SET setband 2G"):
            raise Exception("Failed to set setband")

        # Allow a retry to avoid reporting errors during heavy load
        for j in range(5):
            for i in range(3):
                dev[i].request("SCAN only_new=1")

            for i in range(3):
                ev = dev[i].wait_event(["CTRL-EVENT-SCAN-RESULTS"], 15)
                if ev is None:
                    raise Exception("Scan timed out")

            res0 = dev[0].request("SCAN_RESULTS")
            res1 = dev[1].request("SCAN_RESULTS")
            res2 = dev[2].request("SCAN_RESULTS")
            if bssid in res0 and bssid2 in res0 and bssid in res1 and bssid2 in res2:
                break

        res = dev[0].request("SCAN_RESULTS")
        if bssid not in res or bssid2 not in res:
            raise Exception("Missing scan result(0)")

        res = dev[1].request("SCAN_RESULTS")
        if bssid not in res:
            raise Exception("Missing scan result(1)")
        if bssid2 in res:
            raise Exception("Unexpected scan result(1)")

        res = dev[2].request("SCAN_RESULTS")
        if bssid2 not in res:
            raise Exception("Missing scan result(2)")
        if bssid in res:
            raise Exception("Unexpected scan result(2)")
    finally:
        if hapd:
            hapd.request("DISABLE")
        if hapd2:
            hapd2.request("DISABLE")
        subprocess.call(['iw', 'reg', 'set', '00'])
        for i in range(3):
            dev[i].request("SET setband AUTO")
            dev[i].flush_scan_cache()

@remote_compatible
def test_scan_hidden_many(dev, apdev):
    """scan_ssid=1 with large number of profile with hidden SSID"""
    try:
        _test_scan_hidden_many(dev, apdev)
    finally:
        dev[0].flush_scan_cache(freq=2432)
        dev[0].flush_scan_cache()
        dev[0].request("SCAN_INTERVAL 5")

def _test_scan_hidden_many(dev, apdev):
    hapd = hostapd.add_ap(apdev[0], { "ssid": "test-scan-ssid",
                                      "ignore_broadcast_ssid": "1" })
    bssid = apdev[0]['bssid']

    dev[0].request("SCAN_INTERVAL 1")

    for i in range(5):
        id = dev[0].add_network()
        dev[0].set_network_quoted(id, "ssid", "foo")
        dev[0].set_network(id, "key_mgmt", "NONE")
        dev[0].set_network(id, "disabled", "0")
        dev[0].set_network(id, "scan_freq", "2412")
        dev[0].set_network(id, "scan_ssid", "1")

    dev[0].set_network_quoted(id, "ssid", "test-scan-ssid")
    dev[0].set_network(id, "key_mgmt", "NONE")
    dev[0].set_network(id, "disabled", "0")
    dev[0].set_network(id, "scan_freq", "2412")
    dev[0].set_network(id, "scan_ssid", "1")

    for i in range(5):
        id = dev[0].add_network()
        dev[0].set_network_quoted(id, "ssid", "foo")
        dev[0].set_network(id, "key_mgmt", "NONE")
        dev[0].set_network(id, "disabled", "0")
        dev[0].set_network(id, "scan_freq", "2412")
        dev[0].set_network(id, "scan_ssid", "1")

    dev[0].request("REASSOCIATE")
    dev[0].wait_connected(timeout=30)
    dev[0].request("REMOVE_NETWORK all")
    hapd.disable()

def test_scan_random_mac(dev, apdev, params):
    """Random MAC address in scans"""
    try:
        _test_scan_random_mac(dev, apdev, params)
    finally:
        dev[0].request("MAC_RAND_SCAN all enable=0")

def _test_scan_random_mac(dev, apdev, params):
    hostapd.add_ap(apdev[0], { "ssid": "test-scan" })
    bssid = apdev[0]['bssid']

    tests = [ "",
              "addr=foo",
              "mask=foo",
              "enable=1",
              "all enable=1 mask=00:11:22:33:44:55",
              "all enable=1 addr=00:11:22:33:44:55",
              "all enable=1 addr=01:11:22:33:44:55 mask=ff:ff:ff:ff:ff:ff",
              "all enable=1 addr=00:11:22:33:44:55 mask=fe:ff:ff:ff:ff:ff",
              "enable=2 scan sched pno all",
              "pno enable=1",
              "all enable=2",
              "foo" ]
    for args in tests:
        if "FAIL" not in dev[0].request("MAC_RAND_SCAN " + args):
            raise Exception("Invalid MAC_RAND_SCAN accepted: " + args)

    if dev[0].get_driver_status_field('capa.mac_addr_rand_scan_supported') != '1':
        raise HwsimSkip("Driver does not support random MAC address for scanning")

    tests = [ "all enable=1",
              "all enable=1 addr=f2:11:22:33:44:55 mask=ff:ff:ff:ff:ff:ff",
              "all enable=1 addr=f2:11:33:00:00:00 mask=ff:ff:ff:00:00:00" ]
    for args in tests:
        dev[0].request("MAC_RAND_SCAN " + args)
        dev[0].scan_for_bss(bssid, freq=2412, force_scan=True)

    out = run_tshark(os.path.join(params['logdir'], "hwsim0.pcapng"),
                     "wlan.fc.type_subtype == 4", ["wlan.ta" ])
    if out is not None:
        addr = out.splitlines()
        logger.info("Probe Request frames seen from: " + str(addr))
        if dev[0].own_addr() in addr:
            raise Exception("Real address used to transmit Probe Request frame")
        if "f2:11:22:33:44:55" not in addr:
            raise Exception("Fully configured random address not seen")
        found = False
        for a in addr:
            if a.startswith('f2:11:33'):
                found = True
                break
        if not found:
            raise Exception("Fixed OUI random address not seen")

@remote_compatible
def test_scan_trigger_failure(dev, apdev):
    """Scan trigger to the driver failing"""
    hostapd.add_ap(apdev[0], { "ssid": "test-scan" })
    bssid = apdev[0]['bssid']

    if "OK" not in dev[0].request("SET test_failure 1"):
        raise Exception("Failed to set test_failure")

    if "OK" not in dev[0].request("SCAN"):
        raise Exception("SCAN command failed")
    ev = dev[0].wait_event(["CTRL-EVENT-SCAN-FAILED"], timeout=10)
    if ev is None:
        raise Exception("Did not receive CTRL-EVENT-SCAN-FAILED event")
    if "retry=1" in ev:
        raise Exception("Unexpected scan retry indicated")
    if dev[0].get_status_field('wpa_state') == "SCANNING":
        raise Exception("wpa_state SCANNING not cleared")

    id = dev[0].connect("test-scan", key_mgmt="NONE", scan_freq="2412",
                        only_add_network=True)
    dev[0].select_network(id)
    ev = dev[0].wait_event(["CTRL-EVENT-SCAN-FAILED"], timeout=10)
    if ev is None:
        raise Exception("Did not receive CTRL-EVENT-SCAN-FAILED event")
    if "retry=1" not in ev:
        raise Exception("No scan retry indicated for connection")
    if dev[0].get_status_field('wpa_state') == "SCANNING":
        raise Exception("wpa_state SCANNING not cleared")
    dev[0].request("SET test_failure 0")
    dev[0].wait_connected()

    dev[0].request("SET test_failure 1")
    if "OK" not in dev[0].request("SCAN"):
        raise Exception("SCAN command failed")
    ev = dev[0].wait_event(["CTRL-EVENT-SCAN-FAILED"], timeout=10)
    if ev is None:
        raise Exception("Did not receive CTRL-EVENT-SCAN-FAILED event")
    if "retry=1" in ev:
        raise Exception("Unexpected scan retry indicated")
    if dev[0].get_status_field('wpa_state') != "COMPLETED":
        raise Exception("wpa_state COMPLETED not restored")
    dev[0].request("SET test_failure 0")

@remote_compatible
def test_scan_specify_ssid(dev, apdev):
    """Control interface behavior on scan SSID parameter"""
    dev[0].flush_scan_cache()
    hapd = hostapd.add_ap(apdev[0], { "ssid": "test-hidden",
                                      "ignore_broadcast_ssid": "1" })
    bssid = apdev[0]['bssid']
    check_scan(dev[0], "freq=2412 use_id=1 ssid 414243")
    bss = dev[0].get_bss(bssid)
    if bss is not None and bss['ssid'] == 'test-hidden':
        raise Exception("BSS entry for hidden AP present unexpectedly")
    # Allow couple more retries to avoid reporting errors during heavy load
    for i in range(5):
        check_scan(dev[0], "freq=2412 ssid 414243 ssid 746573742d68696464656e ssid 616263313233 use_id=1")
        bss = dev[0].get_bss(bssid)
        if bss and 'test-hidden' in dev[0].request("SCAN_RESULTS"):
            break
    if bss is None:
        raise Exception("BSS entry for hidden AP not found")
    if 'test-hidden' not in dev[0].request("SCAN_RESULTS"):
        raise Exception("Expected SSID not included in the scan results")

    hapd.disable()
    dev[0].flush_scan_cache(freq=2432)
    dev[0].flush_scan_cache()

    if "FAIL" not in dev[0].request("SCAN ssid foo"):
        raise Exception("Invalid SCAN command accepted")

@remote_compatible
def test_scan_ap_scan_2_ap_mode(dev, apdev):
    """AP_SCAN 2 AP mode and scan()"""
    try:
        _test_scan_ap_scan_2_ap_mode(dev, apdev)
    finally:
        dev[0].request("AP_SCAN 1")

def _test_scan_ap_scan_2_ap_mode(dev, apdev):
    if "OK" not in dev[0].request("AP_SCAN 2"):
        raise Exception("Failed to set AP_SCAN 2")

    id = dev[0].add_network()
    dev[0].set_network(id, "mode", "2")
    dev[0].set_network_quoted(id, "ssid", "wpas-ap-open")
    dev[0].set_network(id, "key_mgmt", "NONE")
    dev[0].set_network(id, "frequency", "2412")
    dev[0].set_network(id, "scan_freq", "2412")
    dev[0].set_network(id, "disabled", "0")
    dev[0].select_network(id)
    ev = dev[0].wait_event(["CTRL-EVENT-CONNECTED"], timeout=5)
    if ev is None:
        raise Exception("AP failed to start")

    with fail_test(dev[0], 1, "wpa_driver_nl80211_scan"):
        if "OK" not in dev[0].request("SCAN freq=2412"):
            raise Exception("SCAN command failed unexpectedly")
        ev = dev[0].wait_event(["CTRL-EVENT-SCAN-FAILED",
                                "AP-DISABLED"], timeout=5)
        if ev is None:
            raise Exception("CTRL-EVENT-SCAN-FAILED not seen")
        if "AP-DISABLED" in ev:
            raise Exception("Unexpected AP-DISABLED event")
        if "retry=1" in ev:
            # Wait for the retry to scan happen
            ev = dev[0].wait_event(["CTRL-EVENT-SCAN-FAILED",
                                    "AP-DISABLED"], timeout=5)
            if ev is None:
                raise Exception("CTRL-EVENT-SCAN-FAILED not seen - retry")
            if "AP-DISABLED" in ev:
                raise Exception("Unexpected AP-DISABLED event - retry")

    dev[1].connect("wpas-ap-open", key_mgmt="NONE", scan_freq="2412")
    dev[1].request("DISCONNECT")
    dev[1].wait_disconnected()
    dev[0].request("DISCONNECT")
    dev[0].wait_disconnected()

def test_scan_bss_expiration_on_ssid_change(dev, apdev):
    """BSS entry expiration when AP changes SSID"""
    dev[0].flush_scan_cache()
    hapd = hostapd.add_ap(apdev[0], { "ssid": "test-scan" })
    bssid = apdev[0]['bssid']
    dev[0].scan_for_bss(apdev[0]['bssid'], freq="2412")

    hapd.request("DISABLE")
    hapd = hostapd.add_ap(apdev[0], { "ssid": "open" })
    if "OK" not in dev[0].request("BSS_EXPIRE_COUNT 3"):
        raise Exception("BSS_EXPIRE_COUNT failed")
    dev[0].scan(freq="2412")
    dev[0].scan(freq="2412")
    if "OK" not in dev[0].request("BSS_EXPIRE_COUNT 2"):
        raise Exception("BSS_EXPIRE_COUNT failed")
    res = dev[0].request("SCAN_RESULTS")
    if "test-scan" not in res:
        raise Exception("The first SSID not in scan results")
    if "open" not in res:
        raise Exception("The second SSID not in scan results")
    dev[0].connect("open", key_mgmt="NONE")

    dev[0].request("BSS_FLUSH 0")
    res = dev[0].request("SCAN_RESULTS")
    if "test-scan" in res:
        raise Exception("The BSS entry with the old SSID was not removed")
    dev[0].request("DISCONNECT")
    dev[0].wait_disconnected()

def test_scan_dfs(dev, apdev, params):
    """Scan on DFS channels"""
    try:
        _test_scan_dfs(dev, apdev, params)
    finally:
        subprocess.call(['iw', 'reg', 'set', '00'])

def _test_scan_dfs(dev, apdev, params):
    subprocess.call(['iw', 'reg', 'set', 'US'])
    for i in range(2):
        for j in range(5):
            ev = dev[i].wait_event(["CTRL-EVENT-REGDOM-CHANGE"], timeout=5)
            if ev is None:
                raise Exception("No regdom change event")
            if "alpha2=US" in ev:
                break
        dev[i].dump_monitor()

    if "OK" not in dev[0].request("SCAN"):
        raise Exception("SCAN command failed")
    ev = dev[0].wait_event(["CTRL-EVENT-SCAN-RESULTS"])
    if ev is None:
        raise Exception("Scan did not complete")

    if "OK" not in dev[0].request("SCAN freq=2412,5180,5260,5500,5600,5745"):
        raise Exception("SCAN command failed")
    ev = dev[0].wait_event(["CTRL-EVENT-SCAN-RESULTS"])
    if ev is None:
        raise Exception("Scan did not complete")

    out = run_tshark(os.path.join(params['logdir'], "hwsim0.pcapng"),
                     "wlan.fc.type_subtype == 4", [ "radiotap.channel.freq" ])
    if out is not None:
        freq = out.splitlines()
        freq = [int(f) for f in freq]
        freq = list(set(freq))
        freq.sort()
        logger.info("Active scan seen on channels: " + str(freq))
        for f in freq:
            if (f >= 5260 and f <= 5320) or (f >= 5500 and f <= 5700):
                raise Exception("Active scan on DFS channel: %d" % f)
            if f in [ 2467, 2472 ]:
                raise Exception("Active scan on US-disallowed channel: %d" % f)

@remote_compatible
def test_scan_abort(dev, apdev):
    """Aborting a full scan"""
    dev[0].request("SCAN")
    ev = dev[0].wait_event(["CTRL-EVENT-SCAN-STARTED"])
    if ev is None:
        raise Exception("Scan did not start")
    if "OK" not in dev[0].request("ABORT_SCAN"):
        raise Exception("ABORT_SCAN command failed")
    ev = dev[0].wait_event(["CTRL-EVENT-SCAN-RESULTS"], timeout=2)
    if ev is None:
        raise Exception("Scan did not terminate")

@remote_compatible
def test_scan_abort_on_connect(dev, apdev):
    """Aborting a full scan on connection request"""
    hostapd.add_ap(apdev[0], { "ssid": "test-scan" })
    bssid = apdev[0]['bssid']

    dev[0].scan_for_bss(apdev[0]['bssid'], freq="2412")
    dev[0].dump_monitor()
    dev[0].request("SCAN")
    ev = dev[0].wait_event(["CTRL-EVENT-SCAN-STARTED"])
    if ev is None:
        raise Exception("Scan did not start")
    dev[0].connect("test-scan", key_mgmt="NONE")

@remote_compatible
def test_scan_ext(dev, apdev):
    """Custom IE in Probe Request frame"""
    hostapd.add_ap(apdev[0], { "ssid": "test-scan" })
    bssid = apdev[0]['bssid']

    try:
        if "OK" not in dev[0].request("VENDOR_ELEM_ADD 14 dd050011223300"):
            raise Exception("VENDOR_ELEM_ADD failed")
        check_scan(dev[0], "freq=2412 use_id=1")
    finally:
        dev[0].request("VENDOR_ELEM_REMOVE 14 *")

def test_scan_fail(dev, apdev):
    """Scan failures"""
    with fail_test(dev[0], 1, "wpa_driver_nl80211_scan"):
        dev[0].request("DISCONNECT")
        if "OK" not in dev[0].request("SCAN freq=2412"):
            raise Exception("SCAN failed")
        ev = dev[0].wait_event(["CTRL-EVENT-SCAN-FAILED"], timeout=5)
        if ev is None:
            raise Exception("Did not see scan failure event")
    dev[0].dump_monitor()

    for i in range(1, 5):
        with alloc_fail(dev[0], i,
                        "wpa_scan_clone_params;wpa_supplicant_trigger_scan"):
            if "OK" not in dev[0].request("SCAN ssid 112233 freq=2412"):
                raise Exception("SCAN failed")
            ev = dev[0].wait_event(["CTRL-EVENT-SCAN-FAILED"], timeout=5)
            if ev is None:
                raise Exception("Did not see scan failure event")
        dev[0].dump_monitor()

    with alloc_fail(dev[0], 1, "radio_add_work;wpa_supplicant_trigger_scan"):
        if "OK" not in dev[0].request("SCAN freq=2412"):
            raise Exception("SCAN failed")
        ev = dev[0].wait_event(["CTRL-EVENT-SCAN-FAILED"], timeout=5)
        if ev is None:
            raise Exception("Did not see scan failure event")
    dev[0].dump_monitor()

    try:
        if "OK" not in dev[0].request("SET filter_ssids 1"):
            raise Exception("SET failed")
        id = dev[0].connect("test-scan", key_mgmt="NONE", only_add_network=True)
        with alloc_fail(dev[0], 1, "wpa_supplicant_build_filter_ssids"):
            # While the filter list cannot be created due to memory allocation
            # failure, this scan is expected to be completed without SSID
            # filtering.
            if "OK" not in dev[0].request("SCAN freq=2412"):
                raise Exception("SCAN failed")
            ev = dev[0].wait_event(["CTRL-EVENT-SCAN-RESULTS"])
            if ev is None:
                raise Exception("Scan did not complete")
        dev[0].remove_network(id)
    finally:
        dev[0].request("SET filter_ssids 0")
    dev[0].dump_monitor()

    with alloc_fail(dev[0], 1, "nl80211_get_scan_results"):
        if "OK" not in dev[0].request("SCAN freq=2412"):
            raise Exception("SCAN failed")
        ev = dev[0].wait_event(["CTRL-EVENT-SCAN-STARTED"], timeout=5)
        if ev is None:
            raise Exception("Did not see scan started event")
        wait_fail_trigger(dev[0], "GET_ALLOC_FAIL")
    dev[0].dump_monitor()

    try:
        if "OK" not in dev[0].request("SET setband 2G"):
            raise Exception("SET setband failed")
        with alloc_fail(dev[0], 1, "=wpa_setband_scan_freqs_list"):
            # While the frequency list cannot be created due to memory
            # allocation failure, this scan is expected to be completed without
            # frequency filtering.
            if "OK" not in dev[0].request("SCAN"):
                raise Exception("SCAN failed")
            wait_fail_trigger(dev[0], "GET_ALLOC_FAIL")
            dev[0].request("ABORT_SCAN")
            ev = dev[0].wait_event(["CTRL-EVENT-SCAN-RESULTS"])
            if ev is None:
                raise Exception("Scan did not complete")
    finally:
        dev[0].request("SET setband AUTO")
    dev[0].dump_monitor()

    wpas = WpaSupplicant(global_iface='/tmp/wpas-wlan5')
    wpas.interface_add("wlan5")
    wpas.request("SET preassoc_mac_addr 1")
    with fail_test(wpas, 1, "nl80211_set_mac_addr;wpas_trigger_scan_cb"):
        if "OK" not in wpas.request("SCAN freq=2412"):
            raise Exception("SCAN failed")
        ev = wpas.wait_event(["CTRL-EVENT-SCAN-FAILED"], timeout=5)
        if ev is None:
            raise Exception("Did not see scan failure event")
    wpas.request("SET preassoc_mac_addr 0")
    wpas.dump_monitor()

    hapd = hostapd.add_ap(apdev[0], { "ssid": "open" })
    with alloc_fail(dev[0], 1, "wpa_bss_add"):
        dev[0].scan_for_bss(apdev[0]['bssid'], freq="2412")

@remote_compatible
def test_scan_freq_list(dev, apdev):
    """Scan with SET freq_list and scan_cur_freq"""
    try:
        if "OK" not in dev[0].request("SET freq_list 2412 2417"):
            raise Exception("SET freq_list failed")
        check_scan(dev[0], "use_id=1")
    finally:
        dev[0].request("SET freq_list ")

    hapd = hostapd.add_ap(apdev[0], { "ssid": "test-scan" })
    dev[0].connect("test-scan", key_mgmt="NONE", scan_freq="2412")
    try:
        if "OK" not in dev[0].request("SET scan_cur_freq 1"):
            raise Exception("SET scan_cur_freq failed")
        check_scan(dev[0], "use_id=1")
    finally:
        dev[0].request("SET scan_cur_freq 0")
    dev[0].request("REMOVE_NETWORK all")
    dev[0].wait_disconnected()

def test_scan_bss_limit(dev, apdev):
    """Scan and wpa_supplicant BSS entry limit"""
    try:
        _test_scan_bss_limit(dev, apdev)
    finally:
        dev[0].request("SET bss_max_count 200")
        pass

def _test_scan_bss_limit(dev, apdev):
    # Trigger 'Increasing the MAX BSS count to 2 because all BSSes are in use.
    # We should normally not get here!' message by limiting the maximum BSS
    # count to one so that the second AP would not fit in the BSS list and the
    # first AP cannot be removed from the list since it is still in use.
    dev[0].request("SET bss_max_count 1")
    hapd = hostapd.add_ap(apdev[0], { "ssid": "test-scan" })
    dev[0].connect("test-scan", key_mgmt="NONE", scan_freq="2412")
    hapd2 = hostapd.add_ap(apdev[1], { "ssid": "test-scan-2",
                                       "channel": "6" })
    dev[0].scan_for_bss(apdev[1]['bssid'], freq=2437, force_scan=True)
