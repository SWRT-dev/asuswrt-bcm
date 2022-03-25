/*
 * hostapd / Hardware feature query and different modes
 * Copyright 2002-2003, Instant802 Networks, Inc.
 * Copyright 2005-2006, Devicescape Software, Inc.
 * Copyright (c) 2008-2012, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#include "utils/includes.h"

#include "utils/common.h"
#include "utils/eloop.h"
#include "common/ieee802_11_defs.h"
#include "common/ieee802_11_common.h"
#include "common/wpa_ctrl.h"
#include "common/hw_features_common.h"
#include "hostapd.h"
#include "ap_config.h"
#include "ap_drv_ops.h"
#include "acs.h"
#include "ieee802_11.h"
#include "beacon.h"
#include "hw_features.h"


void hostapd_free_hw_features(struct hostapd_hw_modes *hw_features,
			      size_t num_hw_features)
{
	size_t i;

	if (hw_features == NULL)
		return;

	for (i = 0; i < num_hw_features; i++) {
		os_free(hw_features[i].channels);
		os_free(hw_features[i].rates);
	}

	os_free(hw_features);
}


#ifndef CONFIG_NO_STDOUT_DEBUG
char * dfs_info(struct hostapd_channel_data *chan)
{
	static char info[256];
	char *state;

	switch (chan->flag & HOSTAPD_CHAN_DFS_MASK) {
	case HOSTAPD_CHAN_DFS_UNKNOWN:
		state = "unknown";
		break;
	case HOSTAPD_CHAN_DFS_USABLE:
		state = "usable";
		break;
	case HOSTAPD_CHAN_DFS_UNAVAILABLE:
		state = "unavailable";
		break;
	case HOSTAPD_CHAN_DFS_AVAILABLE:
		state = "available";
		break;
	default:
		return "";
	}
	os_snprintf(info, sizeof(info), " (DFS state = %s)", state);
	info[sizeof(info) - 1] = '\0';

	return info;
}
#endif /* CONFIG_NO_STDOUT_DEBUG */


int hostapd_get_hw_features(struct hostapd_iface *iface)
{
	struct hostapd_data *hapd = iface->bss[0];
	int i, j;
	u16 num_modes, flags;
	struct hostapd_hw_modes *modes;
	int acs_sta_chan_is_set = 0;

	if (hostapd_drv_none(hapd))
		return -1;
	modes = hostapd_get_hw_feature_data(hapd, &num_modes, &flags);
	if (modes == NULL) {
		hostapd_logger(hapd, NULL, HOSTAPD_MODULE_IEEE80211,
			       HOSTAPD_LEVEL_DEBUG,
			       "Fetching hardware channel/rate support not "
			       "supported.");
		return -1;
	}

	iface->hw_flags = flags;

	hostapd_free_hw_features(iface->hw_features, iface->num_hw_features);
	iface->hw_features = modes;
	iface->num_hw_features = num_modes;

	for (i = 0; i < num_modes; i++) {
		struct hostapd_hw_modes *feature = &modes[i];
		int dfs_enabled = hapd->iconf->ieee80211h &&
			(iface->drv_flags & WPA_DRIVER_FLAGS_RADAR);

		/* set flag for channels we can use in current regulatory
		 * domain */
		for (j = 0; j < feature->num_channels; j++) {
			int dfs = 0;

			/*
			 * Disable all channels that are marked not to allow
			 * to initiate radiation (a.k.a. passive scan and no
			 * IBSS).
			 * Use radar channels only if the driver supports DFS.
			 */
			if ((feature->channels[j].flag &
			     HOSTAPD_CHAN_RADAR) && dfs_enabled) {
				dfs = 1;
			} else if (((feature->channels[j].flag &
				     HOSTAPD_CHAN_RADAR) &&
				    !(iface->drv_flags &
				      WPA_DRIVER_FLAGS_DFS_OFFLOAD)) ||
				   (feature->channels[j].flag &
				    HOSTAPD_CHAN_NO_IR)) {
				feature->channels[j].flag |=
					HOSTAPD_CHAN_DISABLED;
			}

			if (feature->channels[j].flag & HOSTAPD_CHAN_DISABLED)
				continue;

			wpa_printf(MSG_MSGDUMP, "Allowed channel: mode=%d "
				   "chan=%d freq=%d MHz max_tx_power=%d dBm%s",
				   feature->mode,
				   feature->channels[j].chan,
				   feature->channels[j].freq,
				   feature->channels[j].max_tx_power,
				   dfs ? dfs_info(&feature->channels[j]) : "");

			if (iface->conf->acs_algo == ACS_ALGO_STA &&
			    iface->conf->hw_mode == feature->mode &&
			    !acs_sta_chan_is_set && !dfs) {
				iface->conf->channel = feature->channels[j].chan;
				iface->conf->secondary_channel = 0;
				iface->conf->vht_oper_chwidth = VHT_CHANWIDTH_USE_HT;
				iface->conf->vht_oper_centr_freq_seg0_idx = 0;
				iface->conf->ignore_40_mhz_intolerant = 1;
				acs_sta_chan_is_set = 1;
			}
		}
	}

	return 0;
}


int hostapd_prepare_rates(struct hostapd_iface *iface,
			  struct hostapd_hw_modes *mode)
{
	int i, num_basic_rates = 0;
	int basic_rates_a[] = { 60, 120, 240, -1 };
	int basic_rates_b[] = { 10, 20, -1 };
	int basic_rates_g[] = { 10, 20, 55, 110, -1 };
	int *basic_rates;

	if (iface->conf->basic_rates)
		basic_rates = iface->conf->basic_rates;
	else switch (mode->mode) {
	case HOSTAPD_MODE_IEEE80211A:
		basic_rates = basic_rates_a;
		break;
	case HOSTAPD_MODE_IEEE80211B:
		basic_rates = basic_rates_b;
		break;
	case HOSTAPD_MODE_IEEE80211G:
		basic_rates = basic_rates_g;
		break;
	case HOSTAPD_MODE_IEEE80211AD:
		return 0; /* No basic rates for 11ad */
	default:
		return -1;
	}

	i = 0;
	while (basic_rates[i] >= 0)
		i++;
	if (i)
		i++; /* -1 termination */
	os_free(iface->basic_rates);
	iface->basic_rates = os_malloc(i * sizeof(int));
	if (iface->basic_rates)
		os_memcpy(iface->basic_rates, basic_rates, i * sizeof(int));

	os_free(iface->current_rates);
	iface->num_rates = 0;

	iface->current_rates =
		os_calloc(mode->num_rates, sizeof(struct hostapd_rate_data));
	if (!iface->current_rates) {
		wpa_printf(MSG_ERROR, "Failed to allocate memory for rate "
			   "table.");
		return -1;
	}

	for (i = 0; i < mode->num_rates; i++) {
		struct hostapd_rate_data *rate;

		if (iface->conf->supported_rates &&
		    !hostapd_rate_found(iface->conf->supported_rates,
					mode->rates[i]))
			continue;

		rate = &iface->current_rates[iface->num_rates];
		rate->rate = mode->rates[i];
		if (hostapd_rate_found(basic_rates, rate->rate)) {
			rate->flags |= HOSTAPD_RATE_BASIC;
			num_basic_rates++;
		}
		wpa_printf(MSG_DEBUG, "RATE[%d] rate=%d flags=0x%x",
			   iface->num_rates, rate->rate, rate->flags);
		iface->num_rates++;
	}

	if ((iface->num_rates == 0 || num_basic_rates == 0) &&
	    (!iface->conf->ieee80211n || !iface->conf->require_ht)) {
		wpa_printf(MSG_ERROR, "No rates remaining in supported/basic "
			   "rate sets (%d,%d).",
			   iface->num_rates, num_basic_rates);
		return -1;
	}

	return 0;
}


#ifdef CONFIG_IEEE80211N
static int ieee80211n_is_allowed_ht40_channel(struct hostapd_iface *iface, int channel)
{
	struct hostapd_data *hapd = iface->bss[0];
	int i, j;
	u16 num_modes, flags;
	struct hostapd_hw_modes *modes;

	modes = hostapd_get_hw_feature_data(hapd, &num_modes, &flags);
	if (modes == NULL) {
		hostapd_logger(hapd, NULL, HOSTAPD_MODULE_IEEE80211,
			       HOSTAPD_LEVEL_DEBUG,
			       "Fetching hardware channel/rate support not "
			       "supported.");
		return 0;
	}

	for (i = 0; i < num_modes; i++) {
		struct hostapd_hw_modes *feature = &modes[i];
		for (j = 0; j < feature->num_channels; j++) {
			if (feature->channels[j].flag & HOSTAPD_CHAN_DISABLED)
				continue;
			if (feature->channels[j].chan == channel) {
				wpa_printf(MSG_MSGDUMP, "Allowed channel found: channel=%d", channel);
				return 1;
			}
		}
	}
	return 0;
}

static int ap_allowed_ht40_channel_pair(struct hostapd_iface *iface, int pri_chan,
			      int sec_chan)
{
	int ok, j, first;
	struct hostapd_hw_modes *mode = iface->current_mode;

	if (pri_chan == sec_chan || !sec_chan)
		return 1; /* HT40 not used */

	wpa_printf(MSG_DEBUG,
		   "HT40: control channel: %d  secondary channel: %d",
		   pri_chan, sec_chan);

	/* Verify that HT40 secondary channel is an allowed 20 MHz
	 * channel */
	ok = 0;
	for (j = 0; j < mode->num_channels; j++) {
		struct hostapd_channel_data *chan = &mode->channels[j];
		if (!(chan->flag & HOSTAPD_CHAN_DISABLED) &&
		    chan->chan == sec_chan) {
			ok = 1;
			break;
		}
	}
	if (!ok) {
		wpa_printf(MSG_ERROR, "HT40 secondary channel %d not allowed",
			   sec_chan);
		return 0;
	}

	/*
	 * Verify that HT40 primary,secondary channel pair is allowed per
	 * IEEE 802.11n Annex J. This is only needed for 5 GHz band since
	 * 2.4 GHz rules allow all cases where the secondary channel fits into
	 * the list of allowed channels (already checked above).
	 */
	if (mode->mode != HOSTAPD_MODE_IEEE80211A)
		return 1;

	first = pri_chan < sec_chan ? pri_chan : sec_chan;
	ok = ieee80211n_is_allowed_ht40_channel(iface, first);
	
	if (!ok) {
		wpa_printf(MSG_ERROR, "HT40 channel pair (%d, %d) not allowed",
			   pri_chan, sec_chan);
		return 0;
	}

	return 1;
}

static int ieee80211n_allowed_ht40_channel_pair(struct hostapd_iface *iface)
{
	int pri_chan, sec_chan;

	if (!iface->conf->secondary_channel)
		return 1; /* HT40 not used */

	pri_chan = iface->conf->channel;
	sec_chan = pri_chan + iface->conf->secondary_channel * 4;

	return ap_allowed_ht40_channel_pair(iface, pri_chan, sec_chan);
}


static void ieee80211n_switch_pri_sec(struct hostapd_iface *iface)
{
	if (iface->conf->secondary_channel > 0) {
		iface->conf->channel += 4;
		iface->conf->secondary_channel = -1;
	} else {
		iface->conf->channel -= 4;
		iface->conf->secondary_channel = 1;
	}
}

static int ap_check_40mhz_5g(struct hostapd_iface *iface,
		   struct wpa_scan_results *scan_res, int pri_chan,
		   int sec_chan)
{
	int pri_freq, sec_freq, pri_bss, sec_bss;
	int bss_pri_chan, bss_sec_chan;
	size_t i;
	int match;
	struct hostapd_hw_modes *mode = iface->current_mode;

	if (!mode || !scan_res || !pri_chan || !sec_chan ||
	    pri_chan == sec_chan)
		return 0;

	pri_freq = hw_get_freq(mode, pri_chan);
	sec_freq = hw_get_freq(mode, sec_chan);

	/*
	 * Switch PRI/SEC channels if Beacons were detected on selected SEC
	 * channel, but not on selected PRI channel.
	 */
	pri_bss = sec_bss = 0;
	for (i = 0; i < scan_res->num; i++) {
		struct wpa_scan_res *bss = scan_res->res[i];
		/* skip bss if it's signal level too low */
		if (iface->conf->obss_beacon_rssi_threshold > bss->level)
			continue;
		if (bss->freq == pri_freq)
			pri_bss++;
		else if (bss->freq == sec_freq)
			sec_bss++;
	}
	if (sec_bss && !pri_bss) {
		wpa_printf(MSG_INFO,
			   "Switch own primary and secondary channel to get secondary channel with no Beacons from other BSSes");
		return 2;
	}

	/*
	 * Match PRI/SEC channel with any existing HT40 BSS on the same
	 * channels that we are about to use (if already mixed order in
	 * existing BSSes, use own preference).
	 */
	match = 0;
	for (i = 0; i < scan_res->num; i++) {
		struct wpa_scan_res *bss = scan_res->res[i];
		/* skip bss if it's signal level too low */
		if (iface->conf->obss_beacon_rssi_threshold > bss->level)
			continue;
		get_pri_sec_chan(bss, &bss_pri_chan, &bss_sec_chan);
		if (pri_chan == bss_pri_chan &&
		    sec_chan == bss_sec_chan) {
			match = 1;
			break;
		}
	}
	if (!match) {
		for (i = 0; i < scan_res->num; i++) {
			struct wpa_scan_res *bss = scan_res->res[i];
			/* skip bss if it's signal level too low */
			if (iface->conf->obss_beacon_rssi_threshold > bss->level)
				continue;
			get_pri_sec_chan(bss, &bss_pri_chan, &bss_sec_chan);
			if (pri_chan == bss_sec_chan &&
			    sec_chan == bss_pri_chan) {
				wpa_printf(MSG_INFO, "Switch own primary and "
					   "secondary channel due to BSS "
					   "overlap with " MACSTR,
					   MAC2STR(bss->bssid));
				return 2;
			}
		}
	}

	return 1;
}

static int ieee80211n_check_40mhz_5g(struct hostapd_iface *iface,
				     struct wpa_scan_results *scan_res)
{
	int pri_chan, sec_chan;
	int res;

	pri_chan = iface->conf->channel;
	sec_chan = pri_chan + iface->conf->secondary_channel * 4;

	res = ap_check_40mhz_5g(iface, scan_res, pri_chan, sec_chan);

	if (res == 2) {
		if (iface->conf->no_pri_sec_switch) {
			wpa_printf(MSG_DEBUG,
				   "Cannot switch PRI/SEC channels due to local constraint");
		} else {
			ieee80211n_switch_pri_sec(iface);
		}
	}

	return !!res;
}

static int ap_check_40mhz_2g4(struct hostapd_iface *iface,
		    struct wpa_scan_results *scan_res, int pri_chan,
		    int sec_chan)
{
	int pri_freq, sec_freq;
	int affected_start, affected_end;
	size_t i;
	struct hostapd_hw_modes *mode = iface->current_mode;

	if (!mode || !scan_res || !pri_chan || !sec_chan ||
	    pri_chan == sec_chan)
		return 0;

	pri_freq = hw_get_freq(mode, pri_chan);
	sec_freq = hw_get_freq(mode, sec_chan);

	affected_start = (pri_freq + sec_freq) / 2 - 25;
	affected_end = (pri_freq + sec_freq) / 2 + 25;
	wpa_printf(MSG_DEBUG, "40 MHz affected channel range: [%d,%d] MHz",
		   affected_start, affected_end);
	for (i = 0; i < scan_res->num; i++) {
		struct wpa_scan_res *bss = scan_res->res[i];
		int pri = bss->freq;
		int sec = pri;
		struct ieee802_11_elems elems;

		/* skip bss if it's signal level too low */
		if (iface->conf->obss_beacon_rssi_threshold > bss->level)
			continue;

		/* Check for overlapping 20 MHz BSS */
		if (check_20mhz_bss(bss, pri_freq, affected_start,
				    affected_end)) {
			wpa_printf(MSG_DEBUG,
				   "Overlapping 20 MHz BSS is found");
			return 0;
		}

		get_pri_sec_chan(bss, &pri_chan, &sec_chan);

		if (sec_chan) {
			if (sec_chan < pri_chan)
				sec = pri - 20;
			else
				sec = pri + 20;
		}

		if ((pri < affected_start || pri > affected_end) &&
		    (sec < affected_start || sec > affected_end))
			continue; /* not within affected channel range */

		wpa_printf(MSG_DEBUG, "Neighboring BSS: " MACSTR
			   " freq=%d pri=%d sec=%d",
			   MAC2STR(bss->bssid), bss->freq, pri_chan, sec_chan);

		if (sec_chan) {
			if (pri_freq != pri || sec_freq != sec) {
				wpa_printf(MSG_DEBUG,
					   "40 MHz pri/sec mismatch with BSS "
					   MACSTR
					   " <%d,%d> (chan=%d%c) vs. <%d,%d>",
					   MAC2STR(bss->bssid),
					   pri, sec, pri_chan,
					   sec > pri ? '+' : '-',
					   pri_freq, sec_freq);
				return 0;
			}
		}

		ieee802_11_parse_elems((u8 *) (bss + 1), bss->ie_len, &elems,
				       0);
		if (elems.ht_capabilities) {
			struct ieee80211_ht_capabilities *ht_cap =
				(struct ieee80211_ht_capabilities *)
				elems.ht_capabilities;

			if (le_to_host16(ht_cap->ht_capabilities_info) &
			    HT_CAP_INFO_40MHZ_INTOLERANT) {
				wpa_printf(MSG_DEBUG,
					   "40 MHz Intolerant is set on channel %d in BSS "
					   MACSTR, pri, MAC2STR(bss->bssid));
				return 0;
			}
		}
	}

	return 1;
}

static int ieee80211n_check_40mhz_2g4(struct hostapd_iface *iface,
				      struct wpa_scan_results *scan_res)
{
	int pri_chan, sec_chan;

	pri_chan = iface->conf->channel;
	sec_chan = pri_chan + iface->conf->secondary_channel * 4;

	return ap_check_40mhz_2g4(iface, scan_res, pri_chan,
			       sec_chan);
}


static void ieee80211n_check_scan(struct hostapd_iface *iface)
{
	struct wpa_scan_results *scan_res;
	int oper40;
	int res;

	/* Check list of neighboring BSSes (from scan) to see whether 40 MHz is
	 * allowed per IEEE Std 802.11-2012, 10.15.3.2 */

	iface->scan_cb = NULL;

	scan_res = hostapd_driver_get_scan_results(iface->bss[0]);
	if (scan_res == NULL) {
		hostapd_setup_interface_complete(iface, 1);
		return;
	}

	if (iface->current_mode->mode == HOSTAPD_MODE_IEEE80211A)
		oper40 = ieee80211n_check_40mhz_5g(iface, scan_res);
	else
		oper40 = ieee80211n_check_40mhz_2g4(iface, scan_res);
	wpa_scan_results_free(scan_res);

	iface->secondary_ch = iface->conf->secondary_channel;
	if (!oper40) {
#ifdef CONFIG_ACS
    if ((iface->conf->acs_algo == ACS_ALGO_SMART) && iface->conf->acs_init_done) {
      acs_update_intolerant_channels(iface, iface->conf->channel);
      acs_switch_intolerant(iface);
      return;
    }
#endif
		wpa_printf(MSG_INFO, "20/40 MHz operation not permitted on "
			   "channel pri=%d sec=%d based on overlapping BSSes",
			   iface->conf->channel,
			   iface->conf->channel +
			   iface->conf->secondary_channel * 4);
		iface->conf->secondary_channel = 0;
		if (iface->drv_flags & WPA_DRIVER_FLAGS_HT_2040_COEX) {
			/*
			 * TODO: Could consider scheduling another scan to check
			 * if channel width can be changed if no coex reports
			 * are received from associating stations.
			 */
		}
	}

	res = ieee80211n_allowed_ht40_channel_pair(iface);
	if (!res) {
		iface->conf->secondary_channel = 0;
		res = 1;
		wpa_printf(MSG_INFO, "Fallback to 20 MHz");
	}

	hostapd_setup_interface_complete(iface, !res);
}


static void ieee80211n_scan_channels_2g4(struct hostapd_iface *iface,
					 struct wpa_driver_scan_params *params)
{
	/* Scan only the affected frequency range */
	int pri_freq, sec_freq;
	int affected_start, affected_end;
	int i, pos;
	struct hostapd_hw_modes *mode;

	if (iface->current_mode == NULL)
		return;

	pri_freq = hostapd_hw_get_freq(iface->bss[0], iface->conf->channel);
	if (iface->conf->secondary_channel > 0)
		sec_freq = pri_freq + 20;
	else
		sec_freq = pri_freq - 20;
	/*
	 * Note: Need to find the PRI channel also in cases where the affected
	 * channel is the SEC channel of a 40 MHz BSS, so need to include the
	 * scanning coverage here to be 40 MHz from the center frequency.
	 */
	affected_start = (pri_freq + sec_freq) / 2 - 40;
	affected_end = (pri_freq + sec_freq) / 2 + 40;
	wpa_printf(MSG_DEBUG, "40 MHz affected channel range: [%d,%d] MHz",
		   affected_start, affected_end);

	mode = iface->current_mode;
	params->freqs = os_calloc(mode->num_channels + 1, sizeof(int));
	if (params->freqs == NULL)
		return;
	pos = 0;

	for (i = 0; i < mode->num_channels; i++) {
		struct hostapd_channel_data *chan = &mode->channels[i];
		if (chan->flag & HOSTAPD_CHAN_DISABLED)
			continue;
		if (chan->freq < affected_start ||
		    chan->freq > affected_end)
			continue;
		params->freqs[pos++] = chan->freq;
	}
}


static void ieee80211n_scan_channels_5g(struct hostapd_iface *iface,
					struct wpa_driver_scan_params *params)
{
	/* Scan only the affected frequency range */
	int pri_freq;
	int affected_start, affected_end;
	int i, pos;
	struct hostapd_hw_modes *mode;

	if (iface->current_mode == NULL)
		return;

	pri_freq = hostapd_hw_get_freq(iface->bss[0], iface->conf->channel);
  /* If VHT channel used, trigger scan for all channels in chanwidth to calibrate all those channels */
	if (iface->conf->ieee80211ac && iface->conf->vht_oper_chwidth == VHT_CHANWIDTH_80MHZ) {
		int low_freq = hostapd_hw_get_freq(iface->bss[0], iface->conf->vht_oper_centr_freq_seg0_idx - 6);
		affected_start = low_freq - 10;
		affected_end = low_freq + 70;
	} else {
		if (iface->conf->secondary_channel > 0) {
			affected_start = pri_freq - 10;
			affected_end = pri_freq + 30;
		} else {
			affected_start = pri_freq - 30;
			affected_end = pri_freq + 10;
		}
	}
	wpa_printf(MSG_DEBUG, "40 MHz affected channel range: [%d,%d] MHz",
		   affected_start, affected_end);

	mode = iface->current_mode;
	params->freqs = os_calloc(mode->num_channels + 1, sizeof(int));
	if (params->freqs == NULL)
		return;
	pos = 0;

	for (i = 0; i < mode->num_channels; i++) {
		struct hostapd_channel_data *chan = &mode->channels[i];
		if (chan->flag & HOSTAPD_CHAN_DISABLED)
			continue;
		if (chan->freq < affected_start ||
		    chan->freq > affected_end)
			continue;
		params->freqs[pos++] = chan->freq;
	}
}


static void ap_ht40_scan_retry(void *eloop_data, void *user_data)
{
#define HT2040_COEX_SCAN_RETRY 15
	struct hostapd_iface *iface = eloop_data;
	struct wpa_driver_scan_params params;
	int ret;

	os_memset(&params, 0, sizeof(params));
	if (iface->current_mode->mode == HOSTAPD_MODE_IEEE80211G)
		ieee80211n_scan_channels_2g4(iface, &params);
	else
		ieee80211n_scan_channels_5g(iface, &params);

  iface->in_scan = 1;
	ret = hostapd_driver_scan(iface->bss[0], &params);
	iface->num_ht40_scan_tries++;
	os_free(params.freqs);

	if (ret == -EBUSY &&
	    iface->num_ht40_scan_tries < HT2040_COEX_SCAN_RETRY) {
    iface->in_scan = 0;
		wpa_printf(MSG_ERROR,
			   "Failed to request a scan of neighboring BSSes ret=%d (%s) - try to scan again (attempt %d)",
			   ret, strerror(-ret), iface->num_ht40_scan_tries);
		eloop_register_timeout(1, 0, ap_ht40_scan_retry, iface, NULL);
		return;
	}

	if (ret == 0) {
		iface->scan_cb = ieee80211n_check_scan;
		return;
	}

	wpa_printf(MSG_DEBUG,
		   "Failed to request a scan in device, bringing up in HT20 mode");
	iface->conf->secondary_channel = 0;
	iface->conf->ht_capab &= ~HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET;
	hostapd_setup_interface_complete(iface, 0);
}


void hostapd_stop_setup_timers(struct hostapd_iface *iface)
{
	eloop_cancel_timeout(ap_ht40_scan_retry, iface, NULL);
}


static int ieee80211n_check_40mhz(struct hostapd_iface *iface)
{
	struct wpa_driver_scan_params params;
	int ret;

	/* Check that HT40 is used and PRI / SEC switch is allowed */
	if (!iface->conf->secondary_channel || iface->conf->no_pri_sec_switch)
		return 0;

	if (iface->conf->ignore_40_mhz_intolerant)
		return 0;

#ifdef CONFIG_ACS
	/* ACS smart already includes these checks */
	if (iface->conf->acs_algo == ACS_ALGO_SMART && iface->conf->acs_init_done)
		return 0;
#endif /* CONFIG_ACS */

	hostapd_set_state(iface, HAPD_IFACE_HT_SCAN);
	wpa_printf(MSG_DEBUG, "Scan for neighboring BSSes prior to enabling "
		   "40 MHz channel");
	os_memset(&params, 0, sizeof(params));
	if (iface->current_mode->mode == HOSTAPD_MODE_IEEE80211G)
		ieee80211n_scan_channels_2g4(iface, &params);
	else
		ieee80211n_scan_channels_5g(iface, &params);

  iface->in_scan = 1;
	ret = hostapd_driver_scan(iface->bss[0], &params);
	os_free(params.freqs);

	if (ret == -EBUSY) {
		wpa_printf(MSG_ERROR,
			   "Failed to request a scan of neighboring BSSes ret=%d (%s) - try to scan again",
			   ret, strerror(-ret));
    iface->in_scan = 0;
		iface->num_ht40_scan_tries = 1;
		eloop_cancel_timeout(ap_ht40_scan_retry, iface, NULL);
		eloop_register_timeout(1, 0, ap_ht40_scan_retry, iface, NULL);
		return 1;
	}

	if (ret < 0) {
		wpa_printf(MSG_ERROR,
			   "Failed to request a scan of neighboring BSSes ret=%d (%s)",
			   ret, strerror(-ret));
		return -1;
	}

	iface->scan_cb = ieee80211n_check_scan;
	return 1;
}


static int ieee80211n_supported_ht_capab(struct hostapd_iface *iface)
{
	u16 hw = iface->current_mode->ht_capab;
	u16 conf = iface->conf->ht_capab;

	if ((conf & HT_CAP_INFO_LDPC_CODING_CAP) &&
	    !(hw & HT_CAP_INFO_LDPC_CODING_CAP)) {
		wpa_printf(MSG_ERROR, "Driver does not support configured "
			   "HT capability [LDPC]");
		return 0;
	}

	/*
	 * Driver ACS chosen channel may not be HT40 due to internal driver
	 * restrictions.
	 */
	if (!iface->conf->acs && (conf & HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET) &&
	    !(hw & HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET)) {
		wpa_printf(MSG_ERROR, "Driver does not support configured "
			   "HT capability [HT40*]");
		return 0;
	}

	switch (conf & HT_CAP_INFO_SMPS_MASK) {
	case HT_CAP_INFO_SMPS_STATIC:
		if (!(iface->smps_modes & WPA_DRIVER_SMPS_MODE_STATIC)) {
			wpa_printf(MSG_ERROR,
				   "Driver does not support configured HT capability [SMPS-STATIC]");
			return 0;
		}
		break;
	case HT_CAP_INFO_SMPS_DYNAMIC:
		if (!(iface->smps_modes & WPA_DRIVER_SMPS_MODE_DYNAMIC)) {
			wpa_printf(MSG_ERROR,
				   "Driver does not support configured HT capability [SMPS-DYNAMIC]");
			return 0;
		}
		break;
	case HT_CAP_INFO_SMPS_DISABLED:
	default:
		break;
	}

	if ((conf & HT_CAP_INFO_GREEN_FIELD) &&
	    !(hw & HT_CAP_INFO_GREEN_FIELD)) {
		wpa_printf(MSG_ERROR, "Driver does not support configured "
			   "HT capability [GF]");
		return 0;
	}

	if ((conf & HT_CAP_INFO_SHORT_GI20MHZ) &&
	    !(hw & HT_CAP_INFO_SHORT_GI20MHZ)) {
		wpa_printf(MSG_ERROR, "Driver does not support configured "
			   "HT capability [SHORT-GI-20]");
		return 0;
	}

	if ((conf & HT_CAP_INFO_SHORT_GI40MHZ) &&
	    !(hw & HT_CAP_INFO_SHORT_GI40MHZ)) {
		wpa_printf(MSG_ERROR, "Driver does not support configured "
			   "HT capability [SHORT-GI-40]");
		return 0;
	}

	if ((conf & HT_CAP_INFO_TX_STBC) && !(hw & HT_CAP_INFO_TX_STBC)) {
		wpa_printf(MSG_ERROR, "Driver does not support configured "
			   "HT capability [TX-STBC]");
		return 0;
	}

	if ((conf & HT_CAP_INFO_RX_STBC_MASK) >
	    (hw & HT_CAP_INFO_RX_STBC_MASK)) {
		wpa_printf(MSG_ERROR, "Driver does not support configured "
			   "HT capability [RX-STBC*]");
		return 0;
	}

	if ((conf & HT_CAP_INFO_DELAYED_BA) &&
	    !(hw & HT_CAP_INFO_DELAYED_BA)) {
		wpa_printf(MSG_ERROR, "Driver does not support configured "
			   "HT capability [DELAYED-BA]");
		return 0;
	}

	if ((conf & HT_CAP_INFO_MAX_AMSDU_SIZE) &&
	    !(hw & HT_CAP_INFO_MAX_AMSDU_SIZE)) {
		wpa_printf(MSG_ERROR, "Driver does not support configured "
			   "HT capability [MAX-AMSDU-7935]");
		return 0;
	}

	if ((conf & HT_CAP_INFO_DSSS_CCK40MHZ) &&
	    !(hw & HT_CAP_INFO_DSSS_CCK40MHZ)) {
		wpa_printf(MSG_ERROR, "Driver does not support configured "
			   "HT capability [DSSS_CCK-40]");
		return 0;
	}

	if ((conf & HT_CAP_INFO_LSIG_TXOP_PROTECT_SUPPORT) &&
	    !(hw & HT_CAP_INFO_LSIG_TXOP_PROTECT_SUPPORT)) {
		wpa_printf(MSG_ERROR, "Driver does not support configured "
			   "HT capability [LSIG-TXOP-PROT]");
		return 0;
	}

	return 1;
}


static int ieee80211n_tx_bf_cap_check(u32 hw, u32 conf, const u32 cap, const char *name)
{
	if ((conf & cap) && !(hw & cap)) {
		wpa_printf(MSG_ERROR, "Driver does not support configured HT TXBF capability %s (supported:%.8x)", name, hw);
		return 0;
	}
	return 1;
}

static int ieee80211n_tx_bf_cap_check_max(u32 hw, u32 conf, u32 cap_mask, const char *name)
{
#if 0
	u32 hw_max = hw & cap_mask;
	u32 conf_val = conf & cap_mask;

	if (conf_val > hw_max) {
		int offset = find_first_bit(cap_mask);
		wpa_printf(MSG_ERROR, "Configured HT TXBF capability %s exceeds max value supported by the driver (%d > %d)",
			   name, conf_val >> offset, hw_max >> offset);
		return 0;
	}
	return 1;
#endif
}

static int ieee80211n_supported_ht_tx_bf_capab(struct hostapd_iface *iface)
{
#if 0
#define TXBF_CAP_CHECK(cap, name) \
	do { if (!ieee80211n_tx_bf_cap_check(hw, conf, cap, name)) return 0; } while (0)

#define TXBF_CAP_CHECK_MAX(cap, name) \
	do { if (!ieee80211n_tx_bf_cap_check_max(hw, conf, cap, name)) return 0; } while (0)

	u32 hw = iface->current_mode->ht_tx_bf_capab;
	u32 conf = iface->conf->ht_tx_bf_capab;
	wpa_printf(MSG_DEBUG, "hw txbf capab: 0x%x, conf txbf capab: 0x%x", hw, conf);

	TXBF_CAP_CHECK(TX_BF_CAP_IMPLICIT_TXBF_RX_CAP, 					"[IMPL-TXBF-RX]");
	TXBF_CAP_CHECK(TX_BF_CAP_RX_STAGGERED_SOUNDING_CAP, 			"[RX-STAG-SND]");
	TXBF_CAP_CHECK(TX_BF_CAP_TX_STAGGERED_SOUNDING_CAP, 			"[TX-STAG-SND]");
	TXBF_CAP_CHECK(TX_BF_CAP_RX_NDP_CAP,							"[RX-NDP]");
	TXBF_CAP_CHECK(TX_BF_CAP_TX_NDP_CAP,							"[TX-NDP]");
	TXBF_CAP_CHECK(TX_BF_CAP_IMPLICIT_TX_BF_CAP,					"[IMPL-TXBF]");
	TXBF_CAP_CHECK_MAX(TX_BF_CAP_CALIBRATION_MASK,					"[CALIB-*]");
	TXBF_CAP_CHECK(TX_BF_CAP_EXPLICIT_CSI_TXBF_CAP,					"[EXPL-CSI-TXBF]");
	TXBF_CAP_CHECK(TX_BF_CAP_EXPLICIT_NONCOMPR_STEERING_CAP,		"[EXPL-NONCOMPR-STEER]");
	TXBF_CAP_CHECK(TX_BF_CAP_EXPLICIT_COMPR_STEERING_CAP,			"[EXPL-COMPR-STEER]");
	TXBF_CAP_CHECK_MAX(TX_BF_CAP_EXPLICIT_TX_BF_CSI_FEEDBACK_MASK,	"[EXPL-TXBF-CSI-FBACK-*]");

	TXBF_CAP_CHECK_MAX(TX_BF_CAP_EXPLICIT_UNCOMPR_STEERING_MATRIX_FEEDBACK_MASK,	"[EXPL-NONCOMPR-FB-FBACK-*]");
	TXBF_CAP_CHECK_MAX(TX_BF_CAP_EXPLICIT_COMPRESSED_STEERING_MATRIX_FEEDBACK_MASK, "[EXPL-COMPR-FB-FBACK-*]");
	TXBF_CAP_CHECK_MAX(TX_BF_CAP_MINIMAL_GROUPING_MASK,								"[MIN-GROUP-*]");
	TXBF_CAP_CHECK_MAX(TX_BF_CAP_CSI_NUM_BEAMFORMER_ANT_MASK,						"[CSI-BF-ANT-*]");
	TXBF_CAP_CHECK_MAX(TX_BF_CAP_UNCOMPRESSED_STEERING_MATRIX_BEAMFORMER_ANT_MASK,	"[NONCOMPS-BF-ANT-*]");
	TXBF_CAP_CHECK_MAX(TX_BF_CAP_COMPRESSED_STEERING_MATRIX_BEAMFORMER_ANT_MASK,	"[COMPS-BF-ANT-*]");
	TXBF_CAP_CHECK_MAX(TX_BF_CAP_SCI_MAX_OF_ROWS_BEANFORMER_SUPPORTED_MASK,			"[CSI-MAX-ROWS-BF-*]");
	TXBF_CAP_CHECK_MAX(TX_BF_CAP_CHANNEL_ESTIMATION_CAP_MASK,						"[CHE-SPACE-TIME-STR-*]");
	return 1;

#undef TXBF_CAP_CHECK
#undef TXBF_CAP_CHECK_MAX

#else
	/* FIXME: Currently we cannot to read TXBF capabilities from driver, so we always return 1.
	 * The Linux Kernel headers have to be modified to be able to implement this checking.
	 */
	return 1;
#endif
}

#ifdef CONFIG_IEEE80211AC

static int ieee80211ac_cap_check(u32 hw, u32 conf, u32 cap, const char *name)
{
	u32 req_cap = conf & cap;

	/*
	 * Make sure we support all requested capabilities.
	 * NOTE: We assume that 'cap' represents a capability mask,
	 * not a discrete value.
	 */
	if ((hw & req_cap) != req_cap) {
		wpa_printf(MSG_ERROR, "Driver does not support configured VHT capability [%s]",
			   name);
		return 0;
	}
	return 1;
}


static int ieee80211ac_cap_check_max(u32 hw, u32 conf, u32 mask,
				     unsigned int shift,
				     const char *name)
{
	u32 hw_max = hw & mask;
	u32 conf_val = conf & mask;

	if (conf_val > hw_max) {
		wpa_printf(MSG_ERROR, "Configured VHT capability [%s] exceeds max value supported by the driver (%d > %d)",
			   name, conf_val >> shift, hw_max >> shift);
		return 0;
	}
	return 1;
}


static int ieee80211ac_supported_vht_capab(struct hostapd_iface *iface)
{
	struct hostapd_hw_modes *mode = iface->current_mode;
	u32 hw = mode->vht_capab;
	u32 conf = iface->conf->vht_capab;

	wpa_printf(MSG_DEBUG, "hw vht capab: 0x%x, conf vht capab: 0x%x",
		   hw, conf);

	if (mode->mode == HOSTAPD_MODE_IEEE80211G &&
	    iface->conf->bss[0]->vendor_vht &&
	    mode->vht_capab == 0 && iface->hw_features) {
		int i;

		for (i = 0; i < iface->num_hw_features; i++) {
			if (iface->hw_features[i].mode ==
			    HOSTAPD_MODE_IEEE80211A) {
				mode = &iface->hw_features[i];
				hw = mode->vht_capab;
				wpa_printf(MSG_DEBUG,
					   "update hw vht capab based on 5 GHz band: 0x%x",
					   hw);
				break;
			}
		}
	}

#define VHT_CAP_CHECK(cap) \
	do { \
		if (!ieee80211ac_cap_check(hw, conf, cap, #cap)) \
			return 0; \
	} while (0)

#define VHT_CAP_CHECK_MAX(cap) \
	do { \
		if (!ieee80211ac_cap_check_max(hw, conf, cap, cap ## _SHIFT, \
					       #cap)) \
			return 0; \
	} while (0)

	VHT_CAP_CHECK_MAX(VHT_CAP_MAX_MPDU_LENGTH_MASK);
	VHT_CAP_CHECK(VHT_CAP_SUPP_CHAN_WIDTH_160MHZ);
	VHT_CAP_CHECK(VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ);
	VHT_CAP_CHECK(VHT_CAP_RXLDPC);
	VHT_CAP_CHECK(VHT_CAP_SHORT_GI_80);
	VHT_CAP_CHECK(VHT_CAP_SHORT_GI_160);
	VHT_CAP_CHECK(VHT_CAP_TXSTBC);
	VHT_CAP_CHECK_MAX(VHT_CAP_RXSTBC_MASK);
	VHT_CAP_CHECK(VHT_CAP_SU_BEAMFORMER_CAPABLE);
	VHT_CAP_CHECK(VHT_CAP_SU_BEAMFORMEE_CAPABLE);
	VHT_CAP_CHECK_MAX(VHT_CAP_SOUNDING_DIMENSION_MAX);
	VHT_CAP_CHECK(VHT_CAP_MU_BEAMFORMER_CAPABLE);
	VHT_CAP_CHECK(VHT_CAP_MU_BEAMFORMEE_CAPABLE);
	VHT_CAP_CHECK(VHT_CAP_VHT_TXOP_PS);
	VHT_CAP_CHECK(VHT_CAP_HTC_VHT);
	VHT_CAP_CHECK_MAX(VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MAX);
	VHT_CAP_CHECK(VHT_CAP_VHT_LINK_ADAPTATION_VHT_UNSOL_MFB);
	VHT_CAP_CHECK(VHT_CAP_VHT_LINK_ADAPTATION_VHT_MRQ_MFB);
	VHT_CAP_CHECK(VHT_CAP_RX_ANTENNA_PATTERN);
	VHT_CAP_CHECK(VHT_CAP_TX_ANTENNA_PATTERN);

#undef VHT_CAP_CHECK
#undef VHT_CAP_CHECK_MAX

	return 1;
}
#endif /* CONFIG_IEEE80211AC */

#endif /* CONFIG_IEEE80211N */


int hostapd_check_ht_capab(struct hostapd_iface *iface)
{
#ifdef CONFIG_IEEE80211N
	int ret;
	if (!iface->conf->ieee80211n)
		return 0;

	if (iface->current_mode->mode != HOSTAPD_MODE_IEEE80211B &&
	    iface->current_mode->mode != HOSTAPD_MODE_IEEE80211G &&
	    (iface->conf->ht_capab & HT_CAP_INFO_DSSS_CCK40MHZ)) {
		wpa_printf(MSG_DEBUG,
			   "Disable HT capability [DSSS_CCK-40] on 5 GHz band");
		iface->conf->ht_capab &= ~HT_CAP_INFO_DSSS_CCK40MHZ;
	}

	if (!ieee80211n_supported_ht_capab(iface))
		return -1;
	if (!ieee80211n_supported_ht_tx_bf_capab(iface))
		return -1;
#ifdef CONFIG_IEEE80211AC
	if (!ieee80211ac_supported_vht_capab(iface))
		return -1;
#endif /* CONFIG_IEEE80211AC */
	ret = ieee80211n_check_40mhz(iface);
	if (ret)
		return ret;
	if (!ieee80211n_allowed_ht40_channel_pair(iface))
		return -1;
#endif /* CONFIG_IEEE80211N */

	return 0;
}


static int hostapd_is_usable_chan(struct hostapd_iface *iface,
				  int channel, int primary)
{
	int i;
	struct hostapd_channel_data *chan;

	if (!iface->current_mode)
		return 0;

	for (i = 0; i < iface->current_mode->num_channels; i++) {
		chan = &iface->current_mode->channels[i];

		if (chan->chan != channel)
			continue;

		if (!(chan->flag & HOSTAPD_CHAN_DISABLED))
			return 1;

		wpa_printf(MSG_DEBUG,
			   "%schannel [%i] (%i) is disabled for use in AP mode, flags: 0x%x%s%s",
			   primary ? "" : "Configured HT40 secondary ",
			   i, chan->chan, chan->flag,
			   chan->flag & HOSTAPD_CHAN_NO_IR ? " NO-IR" : "",
			   chan->flag & HOSTAPD_CHAN_RADAR ? " RADAR" : "");
	}

	return 0;
}


static int hostapd_is_usable_chans(struct hostapd_iface *iface)
{
	if (!hostapd_is_usable_chan(iface, iface->conf->channel, 1))
		return 0;

	if (!iface->conf->secondary_channel)
		return 1;

	return hostapd_is_usable_chan(iface, iface->conf->channel +
				      iface->conf->secondary_channel * 4, 0);
}


static enum hostapd_chan_status
hostapd_check_chans(struct hostapd_iface *iface)
{
	if (iface->conf->channel) {
		if (hostapd_is_usable_chans(iface))
			return HOSTAPD_CHAN_VALID;
		else
			return HOSTAPD_CHAN_INVALID;
	}

	/*
	 * The user set channel=0 or channel=acs_survey
	 * which is used to trigger ACS.
	 */

	switch (acs_init(iface)) {
	case HOSTAPD_CHAN_ACS:
		return HOSTAPD_CHAN_ACS;
	case HOSTAPD_CHAN_VALID:
	case HOSTAPD_CHAN_INVALID:
	default:
		return HOSTAPD_CHAN_INVALID;
	}
}


static void hostapd_notify_bad_chans(struct hostapd_iface *iface)
{
	if (!iface->current_mode) {
		hostapd_logger(iface->bss[0], NULL, HOSTAPD_MODULE_IEEE80211,
			       HOSTAPD_LEVEL_WARNING,
			       "Hardware does not support configured mode");
		return;
	}
	hostapd_logger(iface->bss[0], NULL,
		       HOSTAPD_MODULE_IEEE80211,
		       HOSTAPD_LEVEL_WARNING,
		       "Configured channel (%d) not found from the "
		       "channel list of current mode (%d) %s",
		       iface->conf->channel,
		       iface->current_mode->mode,
		       hostapd_hw_mode_txt(iface->current_mode->mode));
	hostapd_logger(iface->bss[0], NULL, HOSTAPD_MODULE_IEEE80211,
		       HOSTAPD_LEVEL_WARNING,
		       "Hardware does not support configured channel");
}


int hostapd_acs_completed(struct hostapd_iface *iface, int err)
{
	int ret = -1;
	int dfs_channel = 0;
	struct hostapd_channel_data* chan;
	int freq;

	if (err)
		goto out;

	switch (hostapd_check_chans(iface)) {
	case HOSTAPD_CHAN_VALID:
		freq = hostapd_hw_get_freq(iface->bss[0], iface->conf->channel);
		chan = hostapd_hw_get_channel_data(iface, freq);
		if (chan && (chan->flag & HOSTAPD_CHAN_RADAR))
			dfs_channel = 1;

#ifdef CONFIG_ACS
	if (!iface->conf->acs_scan_mode) {
			wpa_msg(iface->bss[0]->msg_ctx, MSG_INFO,
					ACS_EVENT_COMPLETED "freq=%d channel=%d"
					" OperatingChannelBandwidt=%d ExtensionChannel=%d cf1=%d cf2=%d"
					" reason=%s dfs_chan=%d",
					freq, iface->conf->channel,
					get_num_width(iface->conf->vht_oper_chwidth, iface->conf->secondary_channel),
					iface->conf->secondary_channel,
					acs_chan_to_freq(iface->conf->vht_oper_centr_freq_seg0_idx),
					acs_chan_to_freq(iface->conf->vht_oper_centr_freq_seg1_idx),
					hostapd_channel_switch_text(HAPD_CHAN_SWITCH_OTHER),
					dfs_channel);
	}
	else {
			hostapd_set_state(iface, HAPD_IFACE_ACS_DONE);
			wpa_msg(iface->bss[0]->msg_ctx, MSG_INFO, ACS_EVENT_COMPLETED "SCAN");
	}
#endif /* CONFIG_ACS */
		break;
	case HOSTAPD_CHAN_ACS:
		wpa_printf(MSG_ERROR, "ACS error - reported complete, but no result available");
		wpa_msg(iface->bss[0]->msg_ctx, MSG_INFO, ACS_EVENT_FAILED);
		hostapd_notify_bad_chans(iface);
		goto out;
	case HOSTAPD_CHAN_INVALID:
	default:
		wpa_printf(MSG_ERROR, "ACS picked unusable channels");
		wpa_msg(iface->bss[0]->msg_ctx, MSG_INFO, ACS_EVENT_FAILED);
		hostapd_notify_bad_chans(iface);
		goto out;
	}

	/* After scan and ACS don't set the channel */
	if (iface->conf->acs_scan_mode) {
		iface->conf->acs_scan_mode = 0;
		return 0;
	}

	ret = hostapd_check_ht_capab(iface);
	if (ret < 0)
		goto out;

	if (ret == 1) {
		wpa_printf(MSG_DEBUG, "Interface initialization will be completed in a callback");
		return 0;
	}

	ret = 0;
out:
	return hostapd_setup_interface_complete(iface, ret);
}


/**
 * hostapd_select_hw_mode - Select the hardware mode
 * @iface: Pointer to interface data.
 * Returns: 0 on success, < 0 on failure
 *
 * Sets up the hardware mode, channel, rates, and passive scanning
 * based on the configuration.
 */
int hostapd_select_hw_mode(struct hostapd_iface *iface)
{
	int i;

	if (iface->num_hw_features < 1)
		return -1;

	if ((iface->conf->hw_mode == HOSTAPD_MODE_IEEE80211G ||
	     iface->conf->ieee80211n || iface->conf->ieee80211ac) &&
	    iface->conf->channel == 14) {
		wpa_printf(MSG_INFO, "Disable OFDM/HT/VHT on channel 14");
		iface->conf->hw_mode = HOSTAPD_MODE_IEEE80211B;
		iface->conf->ieee80211n = 0;
		iface->conf->ieee80211ac = 0;
	}

	iface->current_mode = NULL;
	for (i = 0; i < iface->num_hw_features; i++) {
		struct hostapd_hw_modes *mode = &iface->hw_features[i];
		if (mode->mode == iface->conf->hw_mode) {
			iface->current_mode = mode;
			break;
		}
	}

	if (iface->current_mode == NULL) {
		if (!(iface->drv_flags & WPA_DRIVER_FLAGS_ACS_OFFLOAD) ||
		    !(iface->drv_flags & WPA_DRIVER_FLAGS_SUPPORT_HW_MODE_ANY))
		{
			wpa_printf(MSG_ERROR,
				   "Hardware does not support configured mode");
			hostapd_logger(iface->bss[0], NULL,
				       HOSTAPD_MODULE_IEEE80211,
				       HOSTAPD_LEVEL_WARNING,
				       "Hardware does not support configured mode (%d) (hw_mode in hostapd.conf)",
				       (int) iface->conf->hw_mode);
			return -2;
		}
	}

	switch (hostapd_check_chans(iface)) {
	case HOSTAPD_CHAN_VALID:
		return 0;
	case HOSTAPD_CHAN_ACS: /* ACS will run and later complete */
		return 1;
	case HOSTAPD_CHAN_INVALID:
	default:
		hostapd_notify_bad_chans(iface);
		return -3;
	}
}


const char * hostapd_hw_mode_txt(int mode)
{
	switch (mode) {
	case HOSTAPD_MODE_IEEE80211A:
		return "IEEE 802.11a";
	case HOSTAPD_MODE_IEEE80211B:
		return "IEEE 802.11b";
	case HOSTAPD_MODE_IEEE80211G:
		return "IEEE 802.11g";
	case HOSTAPD_MODE_IEEE80211AD:
		return "IEEE 802.11ad";
	default:
		return "UNKNOWN";
	}
}


int hostapd_hw_get_freq(struct hostapd_data *hapd, int chan)
{
	return hw_get_freq(hapd->iface->current_mode, chan);
}


int hostapd_hw_get_channel(struct hostapd_data *hapd, int freq)
{
	return hw_get_chan(hapd->iface->current_mode, freq);
}

struct hostapd_channel_data* hostapd_hw_get_channel_data(struct hostapd_iface *iface, int freq)
{
  int i;
  struct hostapd_channel_data *ch;

  if (!iface->current_mode)
    return NULL;

  for (i = 0; i < iface->current_mode->num_channels; i++) {
    ch = &iface->current_mode->channels[i];
    if (ch->freq == freq)
      return ch;
  }

  return NULL;
}

struct hostapd_channel_data* hostapd_hw_get_channel_data_from_ch(struct hostapd_iface *iface, int chan)
{
  int i;
  struct hostapd_channel_data *ch;

  if (!iface->current_mode)
    return NULL;

  for (i = 0; i < iface->current_mode->num_channels; i++) {
    ch = &iface->current_mode->channels[i];
    if (ch->chan == chan)
      return ch;
  }

  return NULL;
}

/* Returns mask with lowest num_antennas bits of full_mask set */
static u32 _hostapd_hw_get_antenna_mask (u32 full_mask, u32 num_antennas)
{
  u32 cur_bit, cur_mask, result = 0;

  for (cur_bit = 0, cur_mask = 1; num_antennas && (cur_bit < (sizeof(result) << 3));
    cur_bit++, cur_mask <<= 1) {
    result |= full_mask & cur_mask;
    if (full_mask & cur_mask) num_antennas--;
  }
  return result;
}


int hostapd_hw_get_antenna_mask(struct hostapd_data *hapd, int tx_ant,
  int rx_ant, u32 *tx_ant_mask, u32 *rx_ant_mask)
{
  int ret;
  struct wpa_driver_capa capa;

  ret = hostapd_drv_get_capa(hapd, &capa);
  if (ret != 0)
    return ret;
  *tx_ant_mask = _hostapd_hw_get_antenna_mask(capa.available_antennas_tx,
    tx_ant);
  *rx_ant_mask = _hostapd_hw_get_antenna_mask(capa.available_antennas_rx,
    rx_ant);
  return 0;
}


