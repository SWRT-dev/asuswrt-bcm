/*
 * DFS - Dynamic Frequency Selection
 * Copyright (c) 2002-2013, Jouni Malinen <j@w1.fi>
 * Copyright (c) 2013-2015, Qualcomm Atheros, Inc.
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#include "utils/includes.h"

#include "utils/common.h"
#include "common/ieee802_11_defs.h"
#include "common/hw_features_common.h"
#include "common/wpa_ctrl.h"
#include "common/ltq-vendor.h"
#include "hostapd.h"
#include "ap_drv_ops.h"
#include "drivers/driver.h"
#include "dfs.h"
#include "acs.h"
#include "hw_features.h"
#include "../hostapd/ctrl_iface.h"

/* Must be aligned with driver structure */
struct vendor_cac_data
{
	int chan_width;
	int cf1;
	int cf2;
};

static int dfs_get_used_n_chans(struct hostapd_iface *iface, int *seg1)
{
	int n_chans = 1;

	*seg1 = 0;

	if (iface->conf->ieee80211n && iface->conf->secondary_channel)
		n_chans = 2;

	if (iface->conf->ieee80211ac) {
		switch (iface->conf->vht_oper_chwidth) {
		case VHT_CHANWIDTH_USE_HT:
			break;
		case VHT_CHANWIDTH_80MHZ:
			n_chans = 4;
			break;
		case VHT_CHANWIDTH_160MHZ:
			n_chans = 8;
			break;
		case VHT_CHANWIDTH_80P80MHZ:
			n_chans = 4;
			*seg1 = 4;
			break;
		default:
			break;
		}
	}

	return n_chans;
}


static int dfs_channel_available(struct hostapd_channel_data *chan,
				 int skip_radar)
{
	/*
	 * When radar detection happens, CSA is performed. However, there's no
	 * time for CAC, so radar channels must be skipped when finding a new
	 * channel for CSA, unless they are available for immediate use.
	 */
	if (skip_radar && (chan->flag & HOSTAPD_CHAN_RADAR) &&
	    ((chan->flag & HOSTAPD_CHAN_DFS_MASK) !=
	     HOSTAPD_CHAN_DFS_AVAILABLE))
		return 0;

	if (chan->flag & HOSTAPD_CHAN_DISABLED)
		return 0;
	if ((chan->flag & HOSTAPD_CHAN_RADAR) &&
	    ((chan->flag & HOSTAPD_CHAN_DFS_MASK) ==
	     HOSTAPD_CHAN_DFS_UNAVAILABLE))
		return 0;
	return 1;
}


static int dfs_is_chan_allowed(struct hostapd_channel_data *chan, int n_chans)
{
	/*
	 * The tables contain first valid channel number based on channel width.
	 * We will also choose this first channel as the control one.
	 */
	int allowed_40[] = { 36, 44, 52, 60, 100, 108, 116, 124, 132, 149, 157,
			     184, 192 };
	/*
	 * VHT80, valid channels based on center frequency:
	 * 42, 58, 106, 122, 138, 155
	 */
	int allowed_80[] = { 36, 52, 100, 116, 132, 149 };
	/*
	 * VHT160 valid channels based on center frequency:
	 * 50, 114
	 */
	int allowed_160[] = { 36, 100 };
	int *allowed = allowed_40;
	unsigned int i, allowed_no = 0;

	switch (n_chans) {
	case 2:
		allowed = allowed_40;
		allowed_no = ARRAY_SIZE(allowed_40);
		break;
	case 4:
		allowed = allowed_80;
		allowed_no = ARRAY_SIZE(allowed_80);
		break;
	case 8:
		allowed = allowed_160;
		allowed_no = ARRAY_SIZE(allowed_160);
		break;
	default:
		wpa_printf(MSG_DEBUG, "Unknown width for %d channels", n_chans);
		break;
	}

	for (i = 0; i < allowed_no; i++) {
		if (chan->chan == allowed[i])
			return 1;
	}

	return 0;
}


static struct hostapd_channel_data *
dfs_get_chan_data(struct hostapd_hw_modes *mode, int freq, int first_chan_idx)
{
	int i;

	for (i = first_chan_idx; i < mode->num_channels; i++) {
		if (mode->channels[i].freq == freq)
			return &mode->channels[i];
	}

	return NULL;
}


static int dfs_chan_range_available(struct hostapd_hw_modes *mode,
				    int first_chan_idx, int num_chans,
				    int skip_radar)
{
	struct hostapd_channel_data *first_chan, *chan;
	int i;

	if (first_chan_idx + num_chans > mode->num_channels)
		return 0;

	first_chan = &mode->channels[first_chan_idx];

	for (i = 0; i < num_chans; i++) {
		chan = dfs_get_chan_data(mode, first_chan->freq + i * 20,
					 first_chan_idx);
		if (!chan)
			return 0;

		if (!dfs_channel_available(chan, skip_radar))
			return 0;
	}

	return 1;
}


static int is_in_chanlist(struct hostapd_iface *iface,
			  struct hostapd_channel_data *chan)
{
	if (!iface->conf->acs_ch_list.num)
		return 1;

	return freq_range_list_includes(&iface->conf->acs_ch_list, chan->chan);
}


/*
 * The function assumes HT40+ operation.
 * Make sure to adjust the following variables after calling this:
 *  - hapd->secondary_channel
 *  - hapd->vht_oper_centr_freq_seg0_idx
 *  - hapd->vht_oper_centr_freq_seg1_idx
 */
static int dfs_find_channel(struct hostapd_iface *iface,
			    struct hostapd_channel_data **ret_chan,
			    int idx, int skip_radar)
{
	struct hostapd_hw_modes *mode;
	struct hostapd_channel_data *chan;
	int i, channel_idx = 0, n_chans, n_chans1;

	mode = iface->current_mode;
	n_chans = dfs_get_used_n_chans(iface, &n_chans1);

	wpa_printf(MSG_DEBUG, "DFS new chan checking %d channels", n_chans);
	for (i = 0; i < mode->num_channels; i++) {
		chan = &mode->channels[i];

		/* Skip HT40/VHT incompatible channels */
		if (iface->conf->ieee80211n &&
		    iface->conf->secondary_channel &&
		    !dfs_is_chan_allowed(chan, n_chans))
			continue;

		/* Skip incompatible chandefs */
		if (!dfs_chan_range_available(mode, i, n_chans, skip_radar))
			continue;

		if (!is_in_chanlist(iface, chan))
			continue;

		if (ret_chan && idx == channel_idx) {
			wpa_printf(MSG_DEBUG, "Selected ch. #%d", chan->chan);
			*ret_chan = chan;
			return idx;
		}
		wpa_printf(MSG_DEBUG, "Adding channel: %d", chan->chan);
		channel_idx++;
	}
	return channel_idx;
}


static void dfs_adjust_vht_center_freq(struct hostapd_iface *iface,
				       struct hostapd_channel_data *chan,
				       int secondary_channel,
				       u8 *vht_oper_centr_freq_seg0_idx,
				       u8 *vht_oper_centr_freq_seg1_idx)
{
	if (!iface->conf->ieee80211ac)
		return;

	if (!chan)
		return;

	*vht_oper_centr_freq_seg1_idx = 0;

	switch (iface->conf->vht_oper_chwidth) {
	case VHT_CHANWIDTH_USE_HT:
		if (secondary_channel == 1)
			*vht_oper_centr_freq_seg0_idx = chan->chan + 2;
		else if (secondary_channel == -1)
			*vht_oper_centr_freq_seg0_idx = chan->chan - 2;
		else
			*vht_oper_centr_freq_seg0_idx = chan->chan;
		break;
	case VHT_CHANWIDTH_80MHZ:
		*vht_oper_centr_freq_seg0_idx = chan->chan + 6;
		break;
	case VHT_CHANWIDTH_160MHZ:
		*vht_oper_centr_freq_seg0_idx = chan->chan + 14;
		break;
	default:
		wpa_printf(MSG_INFO, "DFS only VHT20/40/80/160 is supported now");
		*vht_oper_centr_freq_seg0_idx = 0;
		break;
	}

	wpa_printf(MSG_DEBUG, "DFS adjusting VHT center frequency: %d, %d",
		   *vht_oper_centr_freq_seg0_idx,
		   *vht_oper_centr_freq_seg1_idx);
}


/* Return start channel idx we will use for mode->channels[idx] */
static int dfs_get_start_chan_idx(struct hostapd_iface *iface, int *seg1_start)
{
	struct hostapd_hw_modes *mode;
	struct hostapd_channel_data *chan;
	int channel_no = iface->conf->channel;
	int res = -1, i;
	int chan_seg1 = -1;

	*seg1_start = -1;

	/* HT40- */
	if (iface->conf->ieee80211n && iface->conf->secondary_channel == -1)
		channel_no -= 4;

	/* VHT */
	if (iface->conf->ieee80211ac) {
		switch (iface->conf->vht_oper_chwidth) {
		case VHT_CHANWIDTH_USE_HT:
			break;
		case VHT_CHANWIDTH_80MHZ:
			channel_no =
				iface->conf->vht_oper_centr_freq_seg0_idx - 6;
			break;
		case VHT_CHANWIDTH_160MHZ:
			channel_no =
				iface->conf->vht_oper_centr_freq_seg0_idx - 14;
			break;
		case VHT_CHANWIDTH_80P80MHZ:
			channel_no =
				iface->conf->vht_oper_centr_freq_seg0_idx - 6;
			chan_seg1 =
				iface->conf->vht_oper_centr_freq_seg1_idx - 6;
			break;
		default:
			wpa_printf(MSG_INFO,
				   "DFS only VHT20/40/80/160/80+80 is supported now");
			channel_no = -1;
			break;
		}
	}

	/* Get idx */
	mode = iface->current_mode;
	for (i = 0; i < mode->num_channels; i++) {
		chan = &mode->channels[i];
		if (chan->chan == channel_no) {
			res = i;
			break;
		}
	}

	if (res != -1 && chan_seg1 > -1) {
		int found = 0;

		/* Get idx for seg1 */
		mode = iface->current_mode;
		for (i = 0; i < mode->num_channels; i++) {
			chan = &mode->channels[i];
			if (chan->chan == chan_seg1) {
				*seg1_start = i;
				found = 1;
				break;
			}
		}
		if (!found)
			res = -1;
	}

	if (res == -1) {
		wpa_printf(MSG_DEBUG,
			   "DFS chan_idx seems wrong; num-ch: %d ch-no: %d conf-ch-no: %d 11n: %d sec-ch: %d vht-oper-width: %d",
			   mode->num_channels, channel_no, iface->conf->channel,
			   iface->conf->ieee80211n,
			   iface->conf->secondary_channel,
			   iface->conf->vht_oper_chwidth);

		for (i = 0; i < mode->num_channels; i++) {
			wpa_printf(MSG_DEBUG, "Available channel: %d",
				   mode->channels[i].chan);
		}
	}

	return res;
}


/* At least one channel have radar flag */
static int dfs_check_chans_radar(struct hostapd_iface *iface,
				 int start_chan_idx, int n_chans)
{
	struct hostapd_channel_data *channel;
	struct hostapd_hw_modes *mode;
	int i, res = 0;

	mode = iface->current_mode;

	for (i = 0; i < n_chans; i++) {
		channel = &mode->channels[start_chan_idx + i];
		if (channel->flag & HOSTAPD_CHAN_RADAR)
			res++;
	}

	return res;
}


/* All channels available */
static int dfs_check_chans_available(struct hostapd_iface *iface,
				     int start_chan_idx, int n_chans)
{
	struct hostapd_channel_data *channel;
	struct hostapd_hw_modes *mode;
	int i;

	mode = iface->current_mode;

	for (i = 0; i < n_chans; i++) {
		channel = &mode->channels[start_chan_idx + i];

		if (channel->flag & HOSTAPD_CHAN_DISABLED)
			break;

		if (!(channel->flag & HOSTAPD_CHAN_RADAR))
			continue;

		if ((channel->flag & HOSTAPD_CHAN_DFS_MASK) !=
		    HOSTAPD_CHAN_DFS_AVAILABLE)
			break;
	}

	return i == n_chans;
}


/* At least one channel unavailable */
static int dfs_check_chans_unavailable(struct hostapd_iface *iface,
				       int start_chan_idx,
				       int n_chans)
{
	struct hostapd_channel_data *channel;
	struct hostapd_hw_modes *mode;
	int i, res = 0;

	mode = iface->current_mode;

	for (i = 0; i < n_chans; i++) {
		channel = &mode->channels[start_chan_idx + i];
		if (channel->flag & HOSTAPD_CHAN_DISABLED)
			res++;
		if ((channel->flag & HOSTAPD_CHAN_DFS_MASK) ==
		    HOSTAPD_CHAN_DFS_UNAVAILABLE)
			res++;
	}

	return res;
}


static struct hostapd_channel_data *
dfs_get_valid_channel(struct hostapd_iface *iface,
		      int *secondary_channel,
		      u8 *vht_oper_centr_freq_seg0_idx,
		      u8 *vht_oper_centr_freq_seg1_idx,
		      int skip_radar)
{
	struct hostapd_hw_modes *mode;
	struct hostapd_channel_data *chan = NULL;
	int num_available_chandefs;
	int chan_idx;
	u32 _rand;

	wpa_printf(MSG_DEBUG, "DFS: Selecting random channel");
	*secondary_channel = 0;
	*vht_oper_centr_freq_seg0_idx = 0;
	*vht_oper_centr_freq_seg1_idx = 0;

	if (iface->current_mode == NULL)
		return NULL;

	mode = iface->current_mode;
	if (mode->mode != HOSTAPD_MODE_IEEE80211A)
		return NULL;

	/* Get the count first */
	num_available_chandefs = dfs_find_channel(iface, NULL, 0, skip_radar);
	if (num_available_chandefs == 0)
		return NULL;

	if (os_get_random((u8 *) &_rand, sizeof(_rand)) < 0)
		return NULL;
	chan_idx = _rand % num_available_chandefs;
	dfs_find_channel(iface, &chan, chan_idx, skip_radar);

	/* dfs_find_channel() calculations assume HT40+ */
	if (iface->conf->secondary_channel)
		*secondary_channel = 1;
	else
		*secondary_channel = 0;

	dfs_adjust_vht_center_freq(iface, chan,
				   *secondary_channel,
				   vht_oper_centr_freq_seg0_idx,
				   vht_oper_centr_freq_seg1_idx);

	return chan;
}

static struct hostapd_channel_data *
dfs_get_valid_channel_failsafe(struct hostapd_iface *iface,
          struct hostapd_freq_params* freq_params,
          int *secondary_channel,
          u8 *vht_oper_centr_freq_seg0_idx,
          u8 *vht_oper_centr_freq_seg1_idx)
{
  struct hostapd_channel_data *channel;

  channel = hostapd_hw_get_channel_data(iface, iface->failsafe.freq);
  if (!channel)
    return channel;

  memset(freq_params, 0, sizeof(*freq_params));
  freq_params->channel = channel->chan;
  freq_params->freq = iface->failsafe.freq;
  freq_params->center_freq1 = iface->failsafe.center_freq1;
  freq_params->center_freq2 = iface->failsafe.center_freq2;
  freq_params->bandwidth = iface->failsafe.bandwidth;
  freq_params->vht_enabled = 1;
  set_iface_conf(iface, freq_params);
  *secondary_channel = iface->conf->secondary_channel;
  *vht_oper_centr_freq_seg0_idx = iface->conf->vht_oper_centr_freq_seg0_idx;
  *vht_oper_centr_freq_seg1_idx = iface->conf->vht_oper_centr_freq_seg1_idx;

  return channel;
}


static int set_dfs_state_freq(struct hostapd_iface *iface, int freq, u32 state)
{
	struct hostapd_hw_modes *mode;
	struct hostapd_channel_data *chan = NULL;
	int i;

	mode = iface->current_mode;
	if (mode == NULL)
		return 0;

	wpa_printf(MSG_DEBUG, "set_dfs_state 0x%X for %d MHz", state, freq);
	for (i = 0; i < iface->current_mode->num_channels; i++) {
		chan = &iface->current_mode->channels[i];
		if (chan->freq == freq) {
			if (chan->flag & HOSTAPD_CHAN_RADAR) {
				chan->flag &= ~HOSTAPD_CHAN_DFS_MASK;
				chan->flag |= state;
				return 1; /* Channel found */
			}
		}
	}
	wpa_printf(MSG_WARNING, "Can't set DFS state for freq %d MHz", freq);
	return 0;
}


static int set_dfs_state(struct hostapd_iface *iface, int freq, int ht_enabled,
			 int chan_offset, int chan_width, int cf1,
			 int cf2, u32 state)
{
	int n_chans = 1, i;
	struct hostapd_hw_modes *mode;
	int frequency = freq;
	int ret = 0;

	mode = iface->current_mode;
	if (mode == NULL)
		return 0;

	if (mode->mode != HOSTAPD_MODE_IEEE80211A) {
		wpa_printf(MSG_WARNING, "current_mode != IEEE80211A");
		return 0;
	}

	/* Seems cf1 and chan_width is enough here */
	switch (chan_width) {
	case CHAN_WIDTH_20_NOHT:
	case CHAN_WIDTH_20:
		n_chans = 1;
		if (frequency == 0)
			frequency = cf1;
		break;
	case CHAN_WIDTH_40:
		n_chans = 2;
		frequency = cf1 - 10;
		break;
	case CHAN_WIDTH_80:
		n_chans = 4;
		frequency = cf1 - 30;
		break;
	case CHAN_WIDTH_160:
		n_chans = 8;
		frequency = cf1 - 70;
		break;
	default:
		wpa_printf(MSG_INFO, "DFS chan_width %d not supported",
			   chan_width);
		break;
	}

	wpa_printf(MSG_DEBUG, "DFS freq: %dMHz, n_chans: %d", frequency,
		   n_chans);
	for (i = 0; i < n_chans; i++) {
		ret += set_dfs_state_freq(iface, frequency, state);
		frequency = frequency + 20;
	}

	return ret;
}


static int dfs_are_channels_overlapped(struct hostapd_iface *iface, int freq,
				       int chan_width, int cf1, int cf2)
{
	int start_chan_idx, start_chan_idx1;
	struct hostapd_hw_modes *mode;
	struct hostapd_channel_data *chan;
	int n_chans, n_chans1, i, j, frequency = freq, radar_n_chans = 1;
	u8 radar_chan;
	int res = 0;

	/* Our configuration */
	mode = iface->current_mode;
	start_chan_idx = dfs_get_start_chan_idx(iface, &start_chan_idx1);
	n_chans = dfs_get_used_n_chans(iface, &n_chans1);

	/* Check we are on DFS channel(s) */
	if (!dfs_check_chans_radar(iface, start_chan_idx, n_chans))
		return 0;

	/* Reported via radar event */
	switch (chan_width) {
	case CHAN_WIDTH_20_NOHT:
	case CHAN_WIDTH_20:
		radar_n_chans = 1;
		if (frequency == 0)
			frequency = cf1;
		break;
	case CHAN_WIDTH_40:
		radar_n_chans = 2;
		frequency = cf1 - 10;
		break;
	case CHAN_WIDTH_80:
		radar_n_chans = 4;
		frequency = cf1 - 30;
		break;
	case CHAN_WIDTH_160:
		radar_n_chans = 8;
		frequency = cf1 - 70;
		break;
	default:
		wpa_printf(MSG_INFO, "DFS chan_width %d not supported",
			   chan_width);
		break;
	}

	ieee80211_freq_to_chan(frequency, &radar_chan);

	for (i = 0; i < n_chans; i++) {
		chan = &mode->channels[start_chan_idx + i];
		if (!(chan->flag & HOSTAPD_CHAN_RADAR))
			continue;
		for (j = 0; j < radar_n_chans; j++) {
			wpa_printf(MSG_DEBUG, "checking our: %d, radar: %d",
				   chan->chan, radar_chan + j * 4);
			if (chan->chan == radar_chan + j * 4)
				res++;
		}
	}

	wpa_printf(MSG_DEBUG, "overlapped: %d", res);

	return res;
}


static unsigned int dfs_get_cac_time(struct hostapd_iface *iface,
				     int start_chan_idx, int n_chans)
{
	struct hostapd_channel_data *channel;
	struct hostapd_hw_modes *mode;
	int i;
	unsigned int cac_time_ms = 0;

	mode = iface->current_mode;

	for (i = 0; i < n_chans; i++) {
		channel = &mode->channels[start_chan_idx + i];
		if (!(channel->flag & HOSTAPD_CHAN_RADAR))
			continue;
		if (channel->dfs_cac_ms > cac_time_ms)
			cac_time_ms = channel->dfs_cac_ms;
	}

	return cac_time_ms;
}


/*
 * Main DFS handler
 * 1 - continue channel/ap setup
 * 0 - channel/ap setup will be continued after CAC
 * -1 - hit critical error
 */
int hostapd_handle_dfs(struct hostapd_iface *iface, Boolean *dfs_dbg_set_beacon)
{
	struct hostapd_channel_data *channel;
	int res, n_chans, n_chans1, start_chan_idx, start_chan_idx1;
	int skip_radar = 0;

	if (!iface->current_mode) {
		/*
		 * This can happen with drivers that do not provide mode
		 * information and as such, cannot really use hostapd for DFS.
		 */
		wpa_printf(MSG_DEBUG,
			   "DFS: No current_mode information - assume no need to perform DFS operations by hostapd");
		return 1;
	}

	iface->cac_started = 0;

	do {
		/* Get start (first) channel for current configuration */
		start_chan_idx = dfs_get_start_chan_idx(iface,
							&start_chan_idx1);
		if (start_chan_idx == -1)
			return -1;

		/* Get number of used channels, depend on width */
		n_chans = dfs_get_used_n_chans(iface, &n_chans1);

		/* Setup CAC time */
		iface->dfs_cac_ms = dfs_get_cac_time(iface, start_chan_idx,
						     n_chans);

		/* Check if any of configured channels require DFS */
		res = dfs_check_chans_radar(iface, start_chan_idx, n_chans);
		wpa_printf(MSG_DEBUG,
			   "DFS %d channels required radar detection",
			   res);
		if (!res)
			return 1;

		/* Check if all channels are DFS available */
		res = dfs_check_chans_available(iface, start_chan_idx, n_chans);
		wpa_printf(MSG_DEBUG,
			   "DFS all channels available, (SKIP CAC): %s",
			   res ? "yes" : "no");
		if (res) {
			if (iface->conf->dfs_debug_chan && iface->bss[0]->started) {
				wpa_printf(MSG_INFO, "DFS_DEBUG: Will set beacons and skip CAC");
				*dfs_dbg_set_beacon = TRUE;
			}
			return 1;
		}

		/* Check if any of configured channels is unavailable */
		res = dfs_check_chans_unavailable(iface, start_chan_idx,
						  n_chans);

		/* For radar simulation */
		/* Allow to switch to the unavailable channel for dfs debug */
		if (res && iface->conf->dfs_debug_chan) {
			wpa_printf(MSG_INFO, "DFS_DEBUG: Forcing to stay on the channel %u", iface->conf->channel);
			res = 0;
		}

		wpa_printf(MSG_DEBUG, "DFS %d chans unavailable - choose other channel: %s",
			   res, res ? "yes": "no");
		if (res) {
			int sec = 0;
			u8 cf1 = 0, cf2 = 0;

			channel = dfs_get_valid_channel(iface, &sec, &cf1, &cf2,
							skip_radar);
			if (!channel) {
				wpa_printf(MSG_ERROR, "could not get valid channel");
				hostapd_set_state(iface, HAPD_IFACE_DFS);
				return 0;
			}

			iface->freq = channel->freq;
			iface->conf->channel = channel->chan;
			iface->conf->secondary_channel = sec;
			iface->conf->vht_oper_centr_freq_seg0_idx = cf1;
			iface->conf->vht_oper_centr_freq_seg1_idx = cf2;
		}
	} while (res);

	/* Finally start CAC */
	hostapd_set_state(iface, HAPD_IFACE_DFS);
	wpa_printf(MSG_DEBUG, "DFS start CAC on %d MHz", iface->freq);
	wpa_msg(iface->bss[0]->msg_ctx, MSG_INFO, DFS_EVENT_CAC_START
		"freq=%d chan=%d sec_chan=%d, width=%d, seg0=%d, seg1=%d, cac_time=%ds",
		iface->freq,
		iface->conf->channel, iface->conf->secondary_channel,
		iface->conf->vht_oper_chwidth,
		iface->conf->vht_oper_centr_freq_seg0_idx,
		iface->conf->vht_oper_centr_freq_seg1_idx,
		iface->dfs_cac_ms / 1000);

	res = hostapd_start_dfs_cac(iface, iface->conf->hw_mode,
				    iface->freq,
				    iface->conf->channel,
				    iface->conf->ieee80211n,
				    iface->conf->ieee80211ac,
				    iface->conf->secondary_channel,
				    iface->conf->vht_oper_chwidth,
				    iface->conf->vht_oper_centr_freq_seg0_idx,
				    iface->conf->vht_oper_centr_freq_seg1_idx);

	if (res) {
		wpa_printf(MSG_ERROR, "DFS start_dfs_cac() failed, %d", res);
		return -1;
	}

	return 0;
}

int chan_width_enum_to_freq(enum chan_width width)
{
	switch (width) {
	case CHAN_WIDTH_20_NOHT:
	case CHAN_WIDTH_20:
		return 20;
	case CHAN_WIDTH_40:
		return 40;
	case CHAN_WIDTH_80:
	case CHAN_WIDTH_80P80:
		return 80;
	case CHAN_WIDTH_160:
		return 160;
	default:
		return 0;
	}
}

int hostapd_dfs_complete_cac(struct hostapd_iface *iface, int success, int freq,
			     int ht_enabled, int chan_offset, int chan_width,
			     int cf1, int cf2)
{
  int err;
  struct hostapd_freq_params freq_params;

	wpa_msg(iface->bss[0]->msg_ctx, MSG_INFO, DFS_EVENT_CAC_COMPLETED
		"success=%d freq=%d ht_enabled=%d chan_offset=%d chan_width=%d cf1=%d cf2=%d"
	  " timeout=%d",
		success, freq, ht_enabled, chan_offset, chan_width, cf1, cf2,
		iface->dfs_cac_ms / 1000);

	if (success) {
		/* Complete iface/ap configuration */
		if (iface->drv_flags & WPA_DRIVER_FLAGS_DFS_OFFLOAD) {
			/* Complete AP configuration for the first bring up. */
			if (iface->state != HAPD_IFACE_ENABLED)
				hostapd_setup_interface_complete(iface, 0);
			else
				iface->cac_started = 0;
		} else {
			set_dfs_state(iface, freq, ht_enabled, chan_offset,
				      chan_width, cf1, cf2,
				      HOSTAPD_CHAN_DFS_AVAILABLE);
#ifdef CONFIG_ACS
      if (iface->conf->acs_init_done)
        acs_update_radar(iface);
#endif
      err = hostapd_set_freq_params(&freq_params,
        iface->conf->hw_mode,
        iface->freq,
        iface->conf->channel,
        iface->conf->ieee80211n,
        iface->conf->ieee80211ac,
        iface->conf->secondary_channel,
        iface->conf->vht_oper_chwidth,
        iface->conf->vht_oper_centr_freq_seg0_idx,
        iface->conf->vht_oper_centr_freq_seg1_idx,
        iface->current_mode->vht_capab);
      if (err) {
        wpa_printf(MSG_ERROR, "failed to calculate freq params");
        return 0;
      }
      /* check if CAC was on our channel */
#if 0
      printf("Interface cac started %d freq %d ht_enabled %d secondary_channel %d "
        "width %d freq1 %d freq2 %d\n",
        iface->cac_started,
        iface->freq,
        iface->conf->ieee80211n,
        iface->conf->secondary_channel,
        get_num_width(iface->conf->vht_oper_chwidth, chan_offset),
        acs_chan_to_freq(iface->conf->vht_oper_centr_freq_seg0_idx),
        acs_chan_to_freq(iface->conf->vht_oper_centr_freq_seg1_idx));
      printf("Interface cac started %d freq %d "
        "width %d freq1 %d freq2 %d\n",
        iface->cac_started,
        freq_params.freq,
        freq_params.bandwidth,
        freq_params.center_freq1,
        freq_params.center_freq2);
      printf("CAC complete cac started %d freq %d ht_enabled %d secondary_channel %d "
        "width %d freq1 %d freq2 %d\n",
        iface->cac_started,
        freq,
        ht_enabled,
        chan_offset,
        chan_width_enum_to_freq(chan_width),
        cf1,
        cf2);
#endif
			if (iface->cac_started &&
			  freq_params.freq == freq &&
			  freq_params.bandwidth == chan_width_enum_to_freq(chan_width) &&
			  freq_params.center_freq1 == cf1 &&
			  freq_params.center_freq2 == cf2) {
			    iface->cac_started = 0;
			    if (!iface->block_tx) {
			      printf("CAC hostapd_setup_interface_complete\n");
			      hostapd_setup_interface_complete(iface, 0);
			    }
			}
		}
	}

	return 0;
}

int dfs_adjust_debug_dfs_chan (struct hostapd_iface *iface, struct hostapd_channel_data *channel,
							    int *secondary_chan_offset, u8 *vht_oper_centr_freq_seg0_idx)
{
	/* 20 MHz channel configured */
	if (!iface->conf->secondary_channel) {
		*vht_oper_centr_freq_seg0_idx = channel->chan;
		*secondary_chan_offset = 0;
		return 0;
	}
	
	return acs_get_chan_data_from_candidates_5g(channel->chan, iface->conf->vht_oper_chwidth,
											    secondary_chan_offset, vht_oper_centr_freq_seg0_idx);
}

struct hostapd_channel_data *
dfs_get_debug_dfs_chan(struct hostapd_iface *iface,
											 int *secondary_channel,
											 u8 *vht_oper_centr_freq_seg0_idx,
											 u8 *vht_oper_centr_freq_seg1_idx)
{
	int i, found = 0;
	struct hostapd_channel_data *channel;
	struct hostapd_hw_modes *mode = iface->current_mode;

	for (i = 0; i < mode->num_channels; i++) {
		channel = &mode->channels[i];

		if (channel->chan == iface->conf->dfs_debug_chan) {
			wpa_printf(MSG_INFO, "DFS_DEBUG: Selected ch. #%d", channel->chan);
			found = 1;
			break;
		}
	}

	if (!found) {
		wpa_printf(MSG_INFO, "DFS_DEBUG: Did not find ch. #%d", iface->conf->dfs_debug_chan);
		return NULL;
	}

	/* Set the same channel bandwidth as configured in conf file */
	if (dfs_adjust_debug_dfs_chan(iface, channel, secondary_channel, vht_oper_centr_freq_seg0_idx)) {
		wpa_printf(MSG_ERROR, "DFS_DEBUG: Failed to adjust channel %d parameters", channel->chan);
		return NULL;
	}

	/* Not supported */
	*vht_oper_centr_freq_seg1_idx = 0;

	if (channel->flag & HOSTAPD_CHAN_RADAR)
		iface->conf->dfs_dbg_need_cac = TRUE;

	return channel;
}

int hostapd_dfs_start_channel_switch_cac(struct hostapd_iface *iface)
{
	struct hostapd_channel_data *channel = NULL;
	int secondary_channel;
	u8 vht_oper_centr_freq_seg0_idx = 0;
	u8 vht_oper_centr_freq_seg1_idx = 0;
	int skip_radar = 0;
	int err = 1;
	struct csa_settings settings;

    memset(&settings, 0, sizeof(settings));
	/* Radar detected during active CAC */
	iface->cac_started = 0;
	if (iface->conf->dfs_debug_chan)
		channel = dfs_get_debug_dfs_chan(iface, &secondary_channel,
						&vht_oper_centr_freq_seg0_idx,
						&vht_oper_centr_freq_seg1_idx);
	else if (iface->failsafe.freq != 0) {
	  /* switch to failsafe channel */
	  channel = dfs_get_valid_channel_failsafe(iface,
	    &settings.freq_params,
	    &secondary_channel,
	    &vht_oper_centr_freq_seg0_idx,
	    &vht_oper_centr_freq_seg1_idx);
	  if (!channel) {
	    wpa_printf(MSG_ERROR, "Invalid/no failsafe frequency specified %d\n",
	      iface->failsafe.freq);
	  }
	}

  if (!channel)
    channel = dfs_get_valid_channel(iface, &secondary_channel,
            &vht_oper_centr_freq_seg0_idx,
            &vht_oper_centr_freq_seg1_idx,
            skip_radar);

	if (!channel) {
		wpa_printf(MSG_ERROR, "No valid channel available");
		return err;
	}

	wpa_printf(MSG_DEBUG, "DFS will switch to a new channel %d",
		   channel->chan);
	wpa_msg(iface->bss[0]->msg_ctx, MSG_INFO, DFS_EVENT_NEW_CHANNEL
		"freq=%d chan=%d sec_chan=%d", channel->freq,
		channel->chan, secondary_channel);

	iface->freq = channel->freq;
	iface->conf->channel = channel->chan;
	iface->conf->secondary_channel = secondary_channel;
	iface->conf->vht_oper_centr_freq_seg0_idx =
		vht_oper_centr_freq_seg0_idx;
	iface->conf->vht_oper_centr_freq_seg1_idx =
		vht_oper_centr_freq_seg1_idx;

	err = 0;
	iface->chan_switch_reason = HAPD_CHAN_SWITCH_RADAR_DETECTED;
	hostapd_setup_interface_complete(iface, err);

	return err;
}


static int hostapd_dfs_start_channel_switch(struct hostapd_iface *iface)
{
	struct hostapd_channel_data *channel = NULL;
	int secondary_channel;
	u8 vht_oper_centr_freq_seg0_idx;
	u8 vht_oper_centr_freq_seg1_idx;
	int skip_radar = 1;
	struct csa_settings csa_settings;
	unsigned int i;
	int err = 1;
	int failsafe = 0;

	wpa_printf(MSG_DEBUG, "%s called (CAC active: %s, CSA active: %s)",
		   __func__, iface->cac_started ? "yes" : "no",
		   hostapd_csa_in_progress(iface) ? "yes" : "no");

	/* Check if CSA in progress */
	if (hostapd_csa_in_progress(iface))
		return 0;

	/* Check if active CAC */
	if (iface->cac_started)
		return hostapd_dfs_start_channel_switch_cac(iface);

	/* For radar simulation */
	if(iface->conf->dfs_debug_chan) {
		channel = dfs_get_debug_dfs_chan(iface, &secondary_channel,
																		 &vht_oper_centr_freq_seg0_idx,
																		 &vht_oper_centr_freq_seg1_idx);
		if (channel)
			goto switch_chan;
	}

  os_memset(&csa_settings, 0, sizeof(csa_settings));
  if (iface->failsafe.freq != 0) {
    /* switch to failsafe channel */
    channel = dfs_get_valid_channel_failsafe(iface,
      &csa_settings.freq_params,
      &secondary_channel,
      &vht_oper_centr_freq_seg0_idx,
      &vht_oper_centr_freq_seg1_idx);
    failsafe = 1;
  } else
  /* Perform channel switch/CSA */
  channel = dfs_get_valid_channel(iface, &secondary_channel,
          &vht_oper_centr_freq_seg0_idx,
          &vht_oper_centr_freq_seg1_idx,
          skip_radar);
	if (!channel) {
		if (failsafe) {
    		wpa_printf(MSG_ERROR, "Invalid/no failsafe frequency specified %d\n",
      		iface->failsafe.freq);
	  		failsafe = 0;
	  }
		/*
		 * If there is no channel to switch immediately to, check if
		 * there is another channel where we can switch even if it
		 * requires to perform a CAC first.
		 */
		skip_radar = 0;
		channel = dfs_get_valid_channel(iface, &secondary_channel,
						&vht_oper_centr_freq_seg0_idx,
						&vht_oper_centr_freq_seg1_idx,
						skip_radar);
		if (!channel) {
			wpa_printf(MSG_INFO,
				   "%s: no DFS channels left, waiting for NOP to finish",
				   __func__);
			return err;
		}

		iface->freq = channel->freq;
		iface->conf->channel = channel->chan;
		iface->conf->secondary_channel = secondary_channel;
		iface->conf->vht_oper_centr_freq_seg0_idx =
			vht_oper_centr_freq_seg0_idx;
		iface->conf->vht_oper_centr_freq_seg1_idx =
			vht_oper_centr_freq_seg1_idx;

		hostapd_disable_iface(iface);
		hostapd_enable_iface(iface);
		return 0;
	}

switch_chan:
	wpa_printf(MSG_DEBUG, "DFS will switch to a new channel %d",
		   channel->chan);
	wpa_msg(iface->bss[0]->msg_ctx, MSG_INFO, DFS_EVENT_NEW_CHANNEL
		"freq=%d chan=%d sec_chan=%d", channel->freq,
		channel->chan, secondary_channel);

	/* Setup CSA request */
	csa_settings.cs_count = 5;
	csa_settings.block_tx = 1;
	if (!failsafe) {
    err = hostapd_set_freq_params(&csa_settings.freq_params,
                iface->conf->hw_mode,
                channel->freq,
                channel->chan,
                iface->conf->ieee80211n,
                iface->conf->ieee80211ac,
                secondary_channel,
                iface->conf->vht_oper_chwidth,
                vht_oper_centr_freq_seg0_idx,
                vht_oper_centr_freq_seg1_idx,
                iface->current_mode->vht_capab);

    if (err) {
      wpa_printf(MSG_ERROR, "DFS failed to calculate CSA freq params");
      hostapd_disable_iface(iface);
      return err;
    }
	}

  if (failsafe && iface->failsafe.tx_ant > 0) {
    err = hostapd_drv_set_antenna(iface->bss[0],
      iface->failsafe.tx_ant,
      iface->failsafe.rx_ant);
    if (err < 0) {
      wpa_printf(MSG_ERROR, "hostapd_dfs_start_channel_switch: setting antenna "
        "failed: %s", strerror(errno));
    }
  }
	iface->chan_switch_reason = HAPD_CHAN_SWITCH_RADAR_DETECTED;
	for (i = 0; i < iface->num_bss; i++) {
		err = hostapd_switch_channel(iface->bss[i], &csa_settings);
		if (err)
			break;
	}

	if (err) {
		wpa_printf(MSG_WARNING, "DFS failed to schedule CSA (%d) - trying fallback",
			   err);
		iface->freq = channel->freq;
		iface->conf->channel = channel->chan;
		iface->conf->secondary_channel = secondary_channel;
		iface->conf->vht_oper_centr_freq_seg0_idx =
			vht_oper_centr_freq_seg0_idx;
		iface->conf->vht_oper_centr_freq_seg1_idx =
			vht_oper_centr_freq_seg1_idx;

		hostapd_disable_iface(iface);
		hostapd_enable_iface(iface);
		return 0;
	}

	/* Channel configuration will be updated once CSA completes and
	 * ch_switch_notify event is received */

	wpa_printf(MSG_DEBUG, "DFS waiting channel switch event");
	return 0;
}

void hostapd_send_dfs_debug_channel_flag(struct hostapd_iface *iface)
{
	int i;
	u8 dfs_required = 0;
	u8 debug_chan = iface->conf->dfs_debug_chan;
	struct hostapd_channel_data *channel;
	struct hostapd_data *hapd = iface->bss[0];
	struct hostapd_hw_modes *mode = iface->current_mode;

	if (!mode || !hapd) {
		wpa_printf(MSG_ERROR, "HW mode or hostapd data not initialized, dfs debug channel flag won't be sent");
		return;
	}
	
	if (iface->conf->dfs_debug_chan) {
		for (i = 0; i < mode->num_channels; i++) {
			channel = &mode->channels[i];

			if (channel->chan == debug_chan) {
				if (channel->flag & HOSTAPD_CHAN_RADAR)
					dfs_required = 1;
				break;
			}
		}
	}
	
	if (hostapd_drv_vendor_cmd(hapd, OUI_LTQ, LTQ_NL80211_VENDOR_SUBCMD_DFS_DEBUG,
							   &dfs_required, sizeof(dfs_required), NULL))
		wpa_printf(MSG_INFO, "Failed to send driver vendor command LTQ_NL80211_VENDOR_SUBCMD_DFS_DEBUG");
}

int hostapd_dfs_radar_detected(struct hostapd_iface *iface, int freq,
			       int ht_enabled, int chan_offset, int chan_width,
			       int cf1, int cf2)
{
	int res;

	wpa_msg(iface->bss[0]->msg_ctx, MSG_INFO, DFS_EVENT_RADAR_DETECTED
		"freq=%d ht_enabled=%d chan_offset=%d chan_width=%d cf1=%d cf2=%d",
		freq, ht_enabled, chan_offset, chan_width, cf1, cf2);

	/* Proceed only if DFS is not offloaded to the driver */
	if (iface->drv_flags & WPA_DRIVER_FLAGS_DFS_OFFLOAD)
		return 0;

	if (!iface->conf->ieee80211h)
		return 0;

	/* mark radar frequency as invalid */
	set_dfs_state(iface, freq, ht_enabled, chan_offset, chan_width,
		      cf1, cf2, HOSTAPD_CHAN_DFS_UNAVAILABLE);

#ifdef CONFIG_ACS
  if (iface->conf->acs_init_done)
    acs_set_radar(iface, freq, chan_width_enum_to_freq(chan_width), cf1);
#endif

	/* Skip if reported radar event not overlapped our channels */
	res = dfs_are_channels_overlapped(iface, freq, chan_width, cf1, cf2);
	if (!res)
		return 0;

#ifdef CONFIG_ACS
  if (iface->failsafe.freq == 0 && iface->conf->acs_init_done)
    acs_radar_switch(iface);
  else
#endif
    /* radar detected while operating, switch the channel. */
    res = hostapd_dfs_start_channel_switch(iface);

	return res;
}


int hostapd_dfs_nop_finished(struct hostapd_iface *iface, int freq,
			     int ht_enabled, int chan_offset, int chan_width,
			     int cf1, int cf2)
{
	wpa_msg(iface->bss[0]->msg_ctx, MSG_INFO, DFS_EVENT_NOP_FINISHED
		"freq=%d ht_enabled=%d chan_offset=%d chan_width=%d cf1=%d cf2=%d",
		freq, ht_enabled, chan_offset, chan_width, cf1, cf2);

	/* Proceed only if DFS is not offloaded to the driver */
	if (iface->drv_flags & WPA_DRIVER_FLAGS_DFS_OFFLOAD)
		return 0;

	/* TODO add correct implementation here */
	set_dfs_state(iface, freq, ht_enabled, chan_offset, chan_width,
		      cf1, cf2, HOSTAPD_CHAN_DFS_USABLE);

#ifdef CONFIG_ACS
  if (iface->conf->acs_init_done)
    acs_update_radar(iface);
#endif

	/* Handle cases where all channels were initially unavailable */
	if (iface->state == HAPD_IFACE_DFS && !iface->cac_started) {
		Boolean dfs_dbg_set_beacon = FALSE;
		hostapd_handle_dfs(iface, &dfs_dbg_set_beacon);
	}

	return 0;
}


int hostapd_is_dfs_required(struct hostapd_iface *iface)
{
	int n_chans, n_chans1, start_chan_idx, start_chan_idx1, res;

	if (!iface->conf->ieee80211h || !iface->current_mode ||
	    iface->current_mode->mode != HOSTAPD_MODE_IEEE80211A)
		return 0;

	/* Get start (first) channel for current configuration */
	start_chan_idx = dfs_get_start_chan_idx(iface, &start_chan_idx1);
	if (start_chan_idx == -1)
		return -1;

	/* Get number of used channels, depend on width */
	n_chans = dfs_get_used_n_chans(iface, &n_chans1);

	/* Check if any of configured channels require DFS */
	res = dfs_check_chans_radar(iface, start_chan_idx, n_chans);
	if (res)
		return res;
	if (start_chan_idx1 >= 0 && n_chans1 > 0)
		res = dfs_check_chans_radar(iface, start_chan_idx1, n_chans1);
	return res;
}


int hostapd_dfs_start_cac(struct hostapd_iface *iface, int freq,
			  int ht_enabled, int chan_offset, int chan_width,
			  int cf1, int cf2)
{
	wpa_msg(iface->bss[0]->msg_ctx, MSG_INFO, DFS_EVENT_CAC_START
		"freq=%d chan=%d chan_offset=%d width=%d seg0=%d "
		"seg1=%d cac_time=%ds",
		freq, (freq - 5000) / 5, chan_offset, chan_width, cf1, cf2, 60);
	iface->cac_started = 1;
	return 0;
}


/*
 * Main DFS handler for offloaded case.
 * 2 - continue channel/AP setup for non-DFS channel
 * 1 - continue channel/AP setup for DFS channel
 * 0 - channel/AP setup will be continued after CAC
 * -1 - hit critical error
 */
int hostapd_handle_dfs_offload(struct hostapd_iface *iface)
{
	wpa_printf(MSG_DEBUG, "%s: iface->cac_started: %d",
		   __func__, iface->cac_started);

	/*
	 * If DFS has already been started, then we are being called from a
	 * callback to continue AP/channel setup. Reset the CAC start flag and
	 * return.
	 */
	if (iface->cac_started) {
		wpa_printf(MSG_DEBUG, "%s: iface->cac_started: %d",
			   __func__, iface->cac_started);
		iface->cac_started = 0;
		return 1;
	}

	if (ieee80211_is_dfs(iface->freq)) {
		wpa_printf(MSG_DEBUG, "%s: freq %d MHz requires DFS",
			   __func__, iface->freq);
		return 0;
	}

	wpa_printf(MSG_DEBUG,
		   "%s: freq %d MHz does not require DFS. Continue channel/AP setup",
		   __func__, iface->freq);
	return 2;
}
