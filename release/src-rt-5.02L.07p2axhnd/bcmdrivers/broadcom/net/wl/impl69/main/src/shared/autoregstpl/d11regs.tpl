#
# d11regs.tpl  makefile - Generates d11 regs files
#
# $Copyright (C) 2002-2004 Broadcom Corporation$
# <<Broadcom-WL-IPTag/Proprietary:>>
# $Id: d11regs.tpl $

FEATURE_BEGIN[regs_common_lt40]
	uint32 biststatus #,0x000c,biststatus missing
	uint32 biststatus2 #,0x0010,biststatus2 missing
	uint32 gptimer #,0x0018,gptimer
	uint32 usectimer #,0x001c,usectimer
	uint16 intstat0 #,0x0020,intctrlregs
	uint32 alt_intmask0 #,0x0060,altintmask
	uint16 inddma #,0x0080,inddma missing
	uint16 indaqm #,0x00a0,indaqm  missing
	uint32 indqsel #,0x00c0,indqsel  missing
	uint32 suspreq #,0x00c4,suspreq   missing
	uint32 flushreq #,0x00c8,flushreq  missing
	uint32 chnflushstatus #,0x00cc,chnflushstatus    missing
	uint32 intrcvlzy0 #,0x0100,intrcvlazy
	uint32 MACCONTROL #,0x0120,maccontrol
	uint32 MACCOMMAND #,0x0124,maccommand
	uint32 MACINTSTATUS #,0x0128,macintstatus
	uint32 MACINTMASK #,0x012c,macintmask
	uint32 XMT_TEMPLATE_RW_PTR #,0x0130,tplatewrptr
	uint32 XMT_TEMPLATE_RW_DATA #,0x0134,tplatewrdata
	uint16 PMQHOSTDATA #,0x0140,pmqreg
	uint32 PMQPATL #,0x0144,pmqpatl
	uint32 PMQPATH #,0x0148,pmqpath
	uint32 CHNSTATUS #,0x0150,chnstatus
	uint32 PSM_DEBUG #,0x0154,psmdebug
	uint32 PHY_DEBUG #,0x0158,phydebug
	uint32 MacCapability #,0x015c,machwcap
	uint32 objaddr #,0x0160,objaddr, missing
	uint32 objdata #,0x0164,objdata     missing
	uint32 ALT_MACINTSTATUS #,0x0168,altmacintstatus
	uint32 ALT_MACINTMASK #,0x016c,altmacintmask
	uint32 FrmTxStatus #,0x0170,frmtxstatus
	uint32 FrmTxStatus2 #,0x0174,frmtxstatus2
	uint32 FrmTxStatus3 #,0x0178,frmtxstatus3
	uint32 FrmTxStatus4 #,0x017c,frmtxstatus4
	uint32 TSFTimerLow #,0x0180,tsf_timerlow
	uint32 TSFTimerHigh #,0x0184,tsf_timerhigh
	uint32 CFPRep #,0x0188,tsf_cfprep
	uint32 CFPStart #,0x018c,tsf_cfpstart
	uint32 CFPMaxDur #,0x0190,tsf_cfpmaxdur32
	uint32 AvbRxTimeStamp #,0x0194,avbrx_timestamp
	uint32 AvbTxTimeStamp #,0x0198,avbtx_timestamp
	uint32 MacControl1 #,0x01a0,maccontrol1
	uint32 MacHWCap1 #,0x01a4,machwcap1
	uint32 MacPatchCtrl #,0x01ac,psm_patchcopy_ctrl
	uint32 gptimer_x #,0x01b0,gptimer_x     missing
	uint32 maccontrol_x #,0x01b4,maccontrol_x    missing
	uint32 maccontrol1_x #,0x01b8,maccontrol1_x    missing
	uint32 maccommand_x #,0x01bc,maccommand_x      missing
	uint32 macintstatus_x #,0x01c0,macintstatus_x     missing
	uint32 macintmask_x #,0x01c4,macintmask_x          missing
	uint32 altmacintstatus_x #,0x01c8,altmacintstatus_x  missing
	uint32 altmacintmask_x #,0x01cc,altmacintmask_x    missing
	uint32 psmdebug_x #,0x01d0,psmdebug_x     missing
	uint32 phydebug_x #,0x01d4,phydebug_x    missing
	uint32 statctr2 #,0x01d8,statctr2    missing
	uint32 statctr3 #,0x01dc,statctr3     missing
	uint32 ClockCtlStatus #,0x01e0,clk_ctl_st
	uint32 Workaround #,0x01e4,hw_war
	uint32 POWERCTL #,0x01e8,powerctl
	uint16 xmt0ctl #,0x0200,f64regs
	uint16 fifobase #,0x0380,dmafifo
	uint32 aggfifocnt #,0x0390,aggfifocnt    missing
	uint32 aggfifodata #,0x0394,aggfifodata    missing
	uint32 DebugStoreMask #,0x0398,dbgstrmask
	uint32 DebugTriggerMask #,0x039c,dbgstrtrigmask
	uint32 DebugTriggerValue #,0x03a0,dbgstrtrig
	uint16 radioregaddr_cross #,0x03c8,altradioregaddr
	uint16 radioregdata_cross #,0x03ca,altradioregdata
	uint16 radioregaddr #,0x03d8,radioregaddr
	uint16 radioregdata #,0x03da,radioregdata
	uint32 rfdisabledly #,0x03dc,rfdisabledly
	uint16 PHY_REG_0 #,0x03e0,phyversion
	uint16 PHY_REG_1 #,0x03e2,phybbconfig
	uint16 PHY_REG_2 #,0x03e4,phyadcbias
	uint16 PHY_REG_3 #,0x03e6,phyanacore
	uint16 PHY_REG_4 #,0x03e8,phyrxstatus0
	uint16 PHY_REG_5 #,0x03ea,phyrxstatus1
	uint16 PHY_REG_7 #,0x03ec,phycrsth
	uint16 PHY_REG_6 #,0x03ee,phytxerror
	uint16 PHY_REG_8 #,0x03f0,phychannel
	uint16 PHY_REG_A #,0x03f4,phytest
	uint16 PHY_REG_B #,0x03f6,phy4waddr
	uint16 PHY_REG_C #,0x03f8,phy4wdatahi
	uint16 PHY_REG_D #,0x03fa,phy4wdatalo
	uint16 PHY_REG_ADDR #,0x03fc,phyregaddr
	uint16 PHY_REG_DATA #,0x03fe,phyregdata
	uint16 RCV_FIFO_CTL #,0x0406,rcv_fifo_ctl
	uint16 RCV_CTL #,0x0408,rcv_ctl
	uint16 RCV_FRM_CNT #,0x040a,rcv_frm_cnt
	uint16 RCV_STATUS_LEN #,0x040c,rcv_status_len
	uint16 RXE_PHYRS_1 #,0x0414,rssi
	uint16 RXE_RXCNT #,0x0418,rxe_rxcnt
	uint16 RXE_STATUS1 #,0x041a,rxe_status1
	uint16 RXE_STATUS2 #,0x041c,rxe_status2
	uint16 RXE_PLCP_LEN #,0x041e,rxe_plcp_len
	uint16 rcm_ctl #,0x0420,rcm_ctl
	uint16 rcm_mat_data #,0x0422,rcm_mat_data
	uint16 rcm_mat_mask #,0x0424,rcm_mat_mask
	uint16 rcm_mat_dly #,0x0426,rcm_mat_dly
	uint16 rcm_cond_mask_l #,0x0428,rcm_cond_mask_l
	uint16 rcm_cond_mask_h #,0x042a,rcm_cond_mask_h
	uint16 rcm_cond_dly #,0x042c,rcm_cond_dly
	uint16 EXT_IHR_ADDR #,0x0430,ext_ihr_addr
	uint16 EXT_IHR_DATA #,0x0432,ext_ihr_data
	uint16 RXE_PHYRS_2 #,0x0434,rxe_phyrs_2
	uint16 RXE_PHYRS_3 #,0x0436,rxe_phyrs_3
	uint16 PHY_MODE #,0x0438,phy_mode
	uint16 rcmta_ctl #,0x043a,rcmta_ctl
	uint16 rcmta_size #,0x043c,rcmta_size
	uint16 rcmta_addr0 #,0x043e,rcmta_addr0
	uint16 rcmta_addr1 #,0x0440,rcmta_addr1
	uint16 rcmta_addr2 #,0x0442,rcmta_addr2
	uint16 ext_ihr_status #,0x045e,ext_ihr_status
	uint16 radio_ihr_addr #,0x0460,radio_ihr_addr
	uint16 radio_ihr_data #,0x0462,radio_ihr_data
	uint16 radio_ihr_status #,0x0468,radio_ihr_status
	uint16 PSM_MAC_CTLH #,0x0482,psm_maccontrol_h
	uint16 PSM_MAC_INTSTAT_L #,0x0484,psm_macintstatus_l
	uint16 PSM_MAC_INTSTAT_H #,0x0486,psm_macintstatus_h
	uint16 PSM_MAC_INTMASK_L #,0x0488,psm_macintmask_l
	uint16 PSM_MAC_INTMASK_H #,0x048a,psm_macintmask_h
	uint16 PSM_MACCOMMAND #,0x048e,psm_maccommand
	uint16 PSM_BRC_0 #,0x0490,psm_brc
	uint16 PSM_PHY_CTL #,0x0492,psm_phy_hdr_param
	uint16 PSM_IHR_ERR #,0x0494,psm_int_sel_0
	uint16 DMP_OOB_AIN_MASK #,0x0496,psm_int_sel_1
	uint16 psm_int_sel_2 #,0x0498,psm_int_sel_2     missing
	uint16 PSM_GPIOIN #,0x049a,psm_gpio_in
	uint16 PSM_GPIOOUT #,0x049c,psm_gpio_out
	uint16 PSM_GPIOEN #,0x049e,psm_gpio_oe
	uint16 PSM_BRED_0 #,0x04a0,psm_bred_0
	uint16 PSM_BRED_1 #,0x04a2,psm_bred_1
	uint16 PSM_BRED_2 #,0x04a4,psm_bred_2
	uint16 PSM_BRED_3 #,0x04a6,psm_bred_3
	uint16 PSM_BRCL_0 #,0x04a8,psm_brcl_0
	uint16 PSM_BRCL_1 #,0x04aa,psm_brcl_1
	uint16 PSM_BRCL_2 #,0x04ac,psm_brcl_2
	uint16 PSM_BRCL_3 #,0x04ae,psm_brcl_3
	uint16 PSM_BRPO_0 #,0x04b0,psm_brpo_0
	uint16 PSM_BRPO_1 #,0x04b2,psm_brpo_1
	uint16 PSM_BRPO_2 #,0x04b4,psm_brpo_2
	uint16 PSM_BRPO_3 #,0x04b6,psm_brpo_3
	uint16 PSM_BRWK_0 #,0x04b8,psm_brwk_0
	uint16 PSM_BRWK_1 #,0x04ba,psm_brwk_1
	uint16 PSM_BRWK_2 #,0x04bc,psm_brwk_2
	uint16 PSM_BRWK_3 #,0x04be,psm_brwk_3
	uint16 PSM_INTSEL_0 #,0x04c0,psm_base_lt64
	uint16 PSMPowerReqStatus #,0x04c8,psm_power_req_sts
	uint16 psm_ihr_err #,0x04ce,psm_ihr_err
	uint16 SubrStkStatus #,0x04d0,psm_pc_reg_0
	uint16 SubrStkRdPtr #,0x04d2,psm_pc_reg_1
	uint16 SubrStkRdData #,0x04d4,psm_pc_reg_2
	uint16 psm_pc_reg_3 #,0x04d6,psm_pc_reg_3     missing
	uint16 PSM_BRC_1 #,0x04d8,psm_brc_1
	uint16 SBRegAddr #,0x04ea,psm_sbreg_addr
	uint16 SBRegDataL #,0x04ec,psm_sbreg_dataL
	uint16 SBRegDataH #,0x04ee,psm_sbreg_dataH
	uint16 PSMCoreCtlStat #,0x04f0,psm_corectlsts
	uint16 SbAddrLL #,0x04f4,psm_sbbar0
	uint16 SbAddrL #,0x04f6,psm_sbbar1
	uint16 SbAddrH #,0x04f8,psm_sbbar2
	uint16 SbAddrHH #,0x04fa,psm_sbbar3
	uint16 TXE_CTL #,0x0500,txe_ctl
	uint16 TXE_AUX #,0x0502,txe_aux
	uint16 TXE_TS_LOC #,0x0504,txe_ts_loc
	uint16 TXE_TIME_OUT #,0x0506,txe_time_out
	uint16 TXE_WM_0 #,0x0508,txe_wm_0
	uint16 TXE_WM_1 #,0x050a,txe_wm_1
	uint16 TXE_PHYCTL #,0x050c,txe_phyctl
	uint16 TXE_STATUS #,0x050e,txe_status
	uint16 TXE_MMPLCP0 #,0x0510,txe_mmplcp0
	uint16 TXE_MMPLCP1 #,0x0512,txe_mmplcp1
	uint16 TXE_PHYCTL1 #,0x0514,txe_phyctl1
	uint16 TXE_PHYCTL2 #,0x0516,txe_phyctl2
	uint16 xmtfifodef #,0x0520,xmtfifodef
	uint16 XmtFifoFrameCnt #,0x0522,xmtfifo_frame_cnt
	uint16 xmtfifo_byte_cnt #,0x0524,xmtfifo_byte_cnt
	uint16 xmtfifo_head #,0x0526,xmtfifo_head
	uint16 xmtfifo_rd_ptr #,0x0528,xmtfifo_rd_ptr
	uint16 xmtfifo_wr_ptr #,0x052a,xmtfifo_wr_ptr
	uint16 xmtfifodef1 #,0x052c,xmtfifodef1
	uint16 aggfifo_cmd #,0x052e,aggfifo_cmd
	uint16 aggfifo_stat #,0x0530,aggfifo_stat
	uint16 aggfifo_cfgctl #,0x0532,aggfifo_cfgctl
	uint16 aggfifo_cfgdata #,0x0534,aggfifo_cfgdata
	uint16 aggfifo_mpdunum #,0x0536,aggfifo_mpdunum
	uint16 aggfifo_len #,0x0538,aggfifo_len
	uint16 aggfifo_bmp #,0x053a,aggfifo_bmp
	uint16 aggfifo_ackedcnt #,0x053c,aggfifo_ackedcnt
	uint16 aggfifo_sel #,0x053e,aggfifo_sel
	uint16 xmtfifocmd #,0x0540,xmtfifocmd
	uint16 xmtfifoflush #,0x0542,xmtfifoflush
	uint16 xmtfifothresh #,0x0544,xmtfifothresh
	uint16 xmtfifordy #,0x0546,xmtfifordy
	uint16 xmtfifoprirdy #,0x0548,xmtfifoprirdy
	uint16 xmtfiforqpri #,0x054a,xmtfiforqpri
	uint16 xmttplatetxptr #,0x054c,xmttplatetxptr
	uint16 xmttplateptr #,0x0550,xmttplateptr
	uint16 SampleCollectStartPtr #,0x0552,smpl_clct_strptr
	uint16 SampleCollectStopPtr #,0x0554,smpl_clct_stpptr
	uint16 SampleCollectCurPtr #,0x0556,smpl_clct_curptr
	uint16 aggfifo_data #,0x0558,aggfifo_data
	uint16 XmtTemplateDataLo #,0x0560,xmttplatedatalo
	uint16 XmtTemplateDataHi #,0x0562,xmttplatedatahi
	uint16 xmtsel #,0x0568,xmtsel
	uint16 xmttxcnt #,0x056a,xmttxcnt
	uint16 xmttxshmaddr #,0x056c,xmttxshmaddr
	uint16 xmt_ampdu_ctl #,0x0570,xmt_ampdu_ctl
	uint16 TSF_CFP_STRT_L #,0x0604,tsf_cfpstrt_l
	uint16 TSF_CFP_STRT_H #,0x0606,tsf_cfpstrt_h
	uint16 TSF_CFP_PRE_TBTT #,0x0612,tsf_cfppretbtt
	uint16 TSF_CLK_FRAC_L #,0x062e,tsf_clk_frac_l
	uint16 TSF_CLK_FRAC_H #,0x0630,tsf_clk_frac_h
	uint16 TSF_RANDOM #,0x065a,tsf_random
	uint16 TSF_GPT_2_STAT #,0x0666,tsf_gpt2_stat
	uint16 TSF_GPT_2_CTR_L #,0x0668,tsf_gpt2_ctr_l
	uint16 TSF_GPT_2_CTR_H #,0x066a,tsf_gpt2_ctr_h
	uint16 TSF_GPT_2_VAL_L #,0x066c,tsf_gpt2_val_l
	uint16 TSF_GPT_2_VAL_H #,0x066e,tsf_gpt2_val_h
	uint16 TSF_GPT_ALL_STAT #,0x0670,tsf_gptall_stat
	uint16 IFS_SIFS_RX_TX_TX #,0x0680,ifs_sifs_rx_tx_tx
	uint16 IFS_SIFS_NAV_TX #,0x0682,ifs_sifs_nav_tx
	uint16 IFS_SLOT #,0x0684,ifs_slot
	uint16 IFS_CTL #,0x0688,ifs_ctl
	uint16 IFS_BOFF_CTR #,0x068a,ifs_boff
	uint16 IFS_STAT #,0x0690,ifsstat
	uint16 IFS_MEDBUSY_CTR #,0x0692,ifsmedbusyctl
	uint16 IFS_TX_DUR #,0x0694,iftxdur
	uint16 IFS_STAT1 #,0x0698,ifsstat1
	uint16 IFS_EDCAPRI #,0x069a,ifs_edcapri
	uint16 IFS_AIFSN #,0x069c,ifs_aifsn
	uint16 IFS_CTL1 #,0x069e,ifs_ctl1
	uint16 SLOW_CTL #,0x06a0,scc_ctl
	uint16 SLOW_TIMER_L #,0x06a2,scc_timer_l
	uint16 SLOW_TIMER_H #,0x06a4,scc_timer_h
	uint16 SLOW_FRAC #,0x06a6,scc_frac
	uint16 FAST_PWRUP_DLY #,0x06a8,scc_fastpwrup_dly
	uint16 SLOW_PER #,0x06aa,scc_per
	uint16 SLOW_PER_FRAC #,0x06ac,scc_per_frac
	uint16 SLOW_CALTIMER_L #,0x06ae,scc_cal_timer_l
	uint16 SLOW_CALTIMER_H #,0x06b0,scc_cal_timer_h
	uint16 BTCX_CTL #,0x06b4,btcx_ctrl
	uint16 BTCX_STAT #,0x06b6,btcx_stat
	uint16 BTCX_TRANSCTL #,0x06b8,btcx_trans_ctrl
	uint16 BTCXPriorityWin #,0x06ba,btcx_pri_win
	uint16 BTCXConfTimer #,0x06bc,btcx_tx_conf_timer
	uint16 BTCXPriSelTimer #,0x06be,btcx_ant_sw_timer
	uint16 BTCXPrvRfActTimer #,0x06c0,btcx_prv_rfact_timer
	uint16 BTCXCurRfActTimer #,0x06c2,btcx_cur_rfact_timer
	uint16 BTCXActDurTimer #,0x06c4,btcx_rfact_dur_timer
	uint16 IFS_CTL_SEL_PRICRS #,0x06c6,ifs_ctl_sel_pricrs
	uint16 IfsCtlSelSecCrs #,0x06c8,ifs_ctl_sel_seccrs
	uint16 BTCXEciAddr #,0x06f0,btcx_eci_addr
	uint16 BTCXEciData #,0x06f2,btcx_eci_data
	uint16 BTCXEciMaskAddr #,0x06f4,btcx_eci_mask_addr
	uint16 BTCXEciMaskData #,0x06f6,btcx_eci_mask_data
	uint16 CoexIOMask #,0x06f8,coex_io_mask
	uint16 btcx_eci_event_addr #,0x06fa,btcx_eci_event_addr
	uint16 btcx_eci_event_data #,0x06fc,btcx_eci_event_data
	uint16 NAV_CTL #,0x0700,nav_ctl
	uint16 NAV_STAT #,0x0702,navstat
	uint16 WEP_CTL #,0x07c0,wepctl
	uint16 WEP_STAT #,0x07c2,wepivloc
	uint16 WEP_HDRLOC #,0x07c4,wepivkey
	uint16 WEP_PSDULEN #,0x07c6,wepwkey
	uint16 pcmctl #,0x07d0,pcmctl
	uint16 pcmstat #,0x07d2,pcmstat
	uint16 PMQ_CTL #,0x07e0,pmqctl
	uint16 PMQ_STATUS #,0x07e2,pmqstatus
	uint16 PMQ_PAT_0 #,0x07e4,pmqpat0
	uint16 PMQ_PAT_1 #,0x07e6,pmqpat1
	uint16 PMQ_PAT_2 #,0x07e8,pmqpat2
	uint16 PMQ_DAT #,0x07ea,pmqdat
	uint16 PMQ_DAT_OR_MAT #,0x07ec,pmqdataor_mat
	uint16 PMQ_DAT_OR_ALL #,0x07ee,pmqdataor_all
	uint16 CLK_GATE_REQ0 #,0x0ae0,ClkGateReqCtrl0
	uint16 CLK_GATE_REQ1 #,0x0ae2,ClkGateReqCtrl1
	uint16 CLK_GATE_REQ2 #,0x0ae4,ClkGateReqCtrl2
	uint16 CLK_GATE_UCODE_REQ0 #,0x0ae6,ClkGateUcodeReq0
	uint16 CLK_GATE_UCODE_REQ1 #,0x0ae8,ClkGateUcodeReq1
	uint16 CLK_GATE_UCODE_REQ2 #,0x0aea,ClkGateUcodeReq2
	uint16 CLK_GATE_STRETCH0 #,0x0aec,ClkGateStretch0
	uint16 CLK_GATE_STRETCH1 #,0x0aee,ClkGateStretch1
	uint16 CLK_GATE_MISC #,0x0af0,ClkGateMisc
	uint16 CLK_GATE_DIV_CTRL #,0x0af2,ClkGateDivCtrl
	uint16 CLK_GATE_PHY_CLK_CTRL #,0x0af4,ClkGatePhyClkCtrl
	uint16 CLK_GATE_STS #,0x0af6,ClkGateSts
	uint16 CLK_GATE_EXT_REQ0 #,0x0af8,ClkGateExtReq0
	uint16 CLK_GATE_EXT_REQ1 #,0x0afa,ClkGateExtReq1
	uint16 CLK_GATE_EXT_REQ2 #,0x0afc,ClkGateExtReq2
	uint16 CLK_GATE_UCODE_PHY_CLK_CTRL #,0x0afe,ClkGateUcodePhyClkCtrl
FEATURE_END

FEATURE_BEGIN[regs_common_ge40_lt64]
	uint16 RCV_FRM_CNT_Q0 #,0x0420,rcv_frm_cnt_q0
	uint16 RCV_FRM_CNT_Q1 #,0x0422,rcv_frm_cnt_q1
	uint16 RCV_WRD_CNT_Q0 #,0x0424,rcv_wrd_cnt_q0
	uint16 RCV_WRD_CNT_Q1 #,0x0426,rcv_wrd_cnt_q1
	uint16 RCV_BM_STARTPTR_Q0 #,0x042c,rcv_bm_sp_q0
	uint16 RCV_BM_ENDPTR_Q0 #,0x042e,rcv_bm_ep_q0
	uint16 RCV_BM_STARTPTR_Q1 #,0x043a,rcv_bm_sp_q1
	uint16 RCV_BM_ENDPTR_Q1 #,0x043c,rcv_bm_ep_q1
	uint16 RCV_COPYCNT_Q1 #,0x043e,rcv_copcnt_q1
	uint16 rxe_errval #,0x0448,rxe_errval       missing
	uint16 rxe_status3 #,0x044c,rxe_status3         missing
	uint16 XmtFIFOFullThreshold #,0x0520,XmtFIFOFullThreshold
	uint16 BMCReadReq #,0x0526,BMCReadReq
	uint16 BMCReadOffset #,0x0528,BMCReadOffset
	uint16 BMCReadLength #,0x052a,BMCReadLength
	uint16 BMCReadStatus #,0x052c,BMCReadStatus
	uint16 XmtShmAddr #,0x052e,XmtShmAddr
	uint16 PsmMSDUAccess #,0x0530,PsmMSDUAccess
	uint16 MSDUEntryBufCnt #,0x0532,MSDUEntryBufCnt
	uint16 MSDUEntryStartIdx #,0x0534,MSDUEntryStartIdx
	uint16 MSDUEntryEndIdx #,0x0536,MSDUEntryEndIdx
	uint16 SampleCollectPlayPtrHigh #,0x0538,SampleCollectPlayPtrHigh
	uint16 SampleCollectCurPtrHigh #,0x053a,SampleCollectCurPtrHigh
	uint16 BMCCmd1 #,0x053c,BMCCmd1
	uint16 BMCDynAllocStatus #,0x053e,BMCDynAllocStatus
	uint16 BMCCTL #,0x0540,BMCCTL
	uint16 BMCConfig #,0x0542,BMCConfig
	uint16 BMCStartAddr #,0x0544,BMCStartAddr
	uint16 BMCSize #,0x0546,BMCSize         missing
	uint16 BMCCmd #,0x0548,BMCCmd
	uint16 BMCMaxBuffers #,0x054a,BMCMaxBuffers
	uint16 BMCMinBuffers #,0x054c,BMCMinBuffers
	uint16 BMCAllocCtl #,0x054e,BMCAllocCtl
	uint16 BMCDescrLen #,0x0550,BMCDescrLen
	uint16 SaveRestoreStartPtr #,0x0558,SaveRestoreStartPtr    missing
	uint16 SamplePlayStartPtr #,0x055a,SamplePlayStartPtr
	uint16 SamplePlayStopPtr #,0x055c,SamplePlayStopPtr
	uint16 XmtDMABusy #,0x055e,XmtDMABusy
	uint16 XmtTemplatePtr #,0x0564,XmtTemplatePtr
	uint16 XmtSuspFlush #,0x0566,XmtSuspFlush
	uint16 XmtFifoRqPrio #,0x0568,XmtFifoRqPrio
	uint16 BMCStatCtl #,0x056a,BMCStatCtl
	uint16 BMCStatData #,0x056c,BMCStatData
	uint16 BMCMSDUFifoStat #,0x056e,BMCMSDUFifoStat
	uint16 TXE_STATUS1 #,0x0578,txe_status1
	uint16 pmqdataor_mat1 #,0x07f0,pmqdataor_mat1    missing
	uint16 pmqdataor_mat2 #,0x07f2,pmqdataor_mat2    missing
	uint16 pmqdataor_mat3 #,0x07f4,pmqdataor_mat3     missing
	uint16 pmq_auxsts  #,0x07f6,pmq_auxsts       missing
	uint16 pmq_ctl1    #,0x07f8,pmq_ctl1      missing
	uint16 pmq_status1 #,0x07fa,pmq_status1     missing
	uint16 pmq_addthr  #,0x07fc,pmq_addthr     missing
	uint16 AQMConfig #,0x0800,AQMConfig
	uint16 AQMFifoDef #,0x0802,AQMFifoDef
	uint16 AQMMaxIdx #,0x0804,AQMMaxIdx
	uint16 AQMRcvdBA0 #,0x0806,AQMRcvdBA0
	uint16 AQMRcvdBA1 #,0x0808,AQMRcvdBA1
	uint16 AQMRcvdBA2 #,0x080a,AQMRcvdBA2
	uint16 AQMRcvdBA3 #,0x080c,AQMRcvdBA3
	uint16 AQMBaSSN #,0x080e,AQMBaSSN
	uint16 AQMRefSN #,0x0810,AQMRefSN
	uint16 AQMMaxAggLenLow #,0x0812,AQMMaxAggLenLow
	uint16 AQMMaxAggLenHi #,0x0814,AQMMaxAggLenHi
	uint16 AQMAggParams #,0x0816,AQMAggParams
	uint16 AQMMinMpduLen #,0x0818,AQMMinMpduLen
	uint16 AQMMacAdjLen #,0x081a,AQMMacAdjLen
	uint16 DebugBusCtrl #,0x081c,DebugBusCtrl
	uint16 AQMAggStats #,0x0820,AQMAggStats
	uint16 AQMAggLenLow #,0x0822,AQMAggLenLow
	uint16 AQMAggLenHi #,0x0824,AQMAggLenHi
	uint16 AQMIdx #,0x0826,AQMIdxFifo
	uint16 AQMMpduLen #,0x0828,AQMMpduLenFifo
	uint16 AQMTxCnt #,0x082a,AQMTxCntFifo
	uint16 AQMUpdBA0 #,0x082c,AQMUpdBA0
	uint16 AQMUpdBA1 #,0x082e,AQMUpdBA1
	uint16 AQMUpdBA2 #,0x0830,AQMUpdBA2
	uint16 AQMUpdBA3 #,0x0832,AQMUpdBA3
	uint16 AQMAckCnt #,0x0834,AQMAckCnt
	uint16 AQMConsCnt #,0x0836,AQMConsCnt
	uint16 AQMFifoReady #,0x0838,AQMFifoReady
	uint16 AQMStartLoc #,0x083a,AQMStartLoc
	uint16 AQMAggRptr #,0x083c,AQMRptr
	uint16 AQMTxcntRptr #,0x083e,AQMTxcntRptr
	uint16 TDCCTL #,0x0840,TDCCTL
	uint16 TDC_Plcp0 #,0x0842,TDC_Plcp0
	uint16 TDC_Plcp1 #,0x0844,TDC_Plcp1
	uint16 TDC_FrmLen0 #,0x0846,TDC_FrmLen0
	uint16 TDC_FrmLen1 #,0x0848,TDC_FrmLen1
	uint16 TDC_Txtime #,0x084a,TDC_Txtime
	uint16 TDC_VhtSigB0 #,0x084c,TDC_VhtSigB0
	uint16 TDC_VhtSigB1 #,0x084e,TDC_VhtSigB1
	uint16 TDC_LSigLen #,0x0850,TDC_LSigLen
	uint16 TDC_NSym0 #,0x0852,TDC_NSym0
	uint16 TDC_NSym1 #,0x0854,TDC_NSym1
	uint16 TDC_VhtPsduLen0 #,0x0856,TDC_VhtPsduLen0
	uint16 TDC_VhtPsduLen1 #,0x0858,TDC_VhtPsduLen1
	uint16 TDC_VhtMacPad #,0x085a,TDC_VhtMacPad
	uint16 AQMCurTxcnt #,0x085e,AQMCurTxcnt
	uint16 ShmDma_Ctl #,0x0860,ShmDma_Ctl
	uint16 ShmDma_TxdcAddr #,0x0862,ShmDma_TxdcAddr
	uint16 ShmDma_ShmAddr #,0x0864,ShmDma_ShmAddr
	uint16 ShmDma_XferCnt #,0x0866,ShmDma_XferCnt
	uint16 Txdc_Addr #,0x0868,Txdc_Addr
	uint16 Txdc_Data #,0x086a,Txdc_Data
	uint16 MHP_Status #,0x0880,MHP_Status
	uint16 MHP_FC #,0x0882,MHP_FC
	uint16 MHP_DUR #,0x0884,MHP_DUR
	uint16 MHP_SC #,0x0886,MHP_SC
	uint16 MHP_QOS #,0x0888,MHP_QOS
	uint16 MHP_HTC_H #,0x088a,MHP_HTC_H
	uint16 MHP_HTC_L #,0x088c,MHP_HTC_L
	uint16 MHP_Addr1_H #,0x088e,MHP_Addr1_H
	uint16 MHP_Addr1_M #,0x0890,MHP_Addr1_M
	uint16 MHP_Addr1_L #,0x0892,MHP_Addr1_L
	uint16 MHP_Addr2_H #,0x08a0,MHP_Addr2_H
	uint16 MHP_Addr2_M #,0x08a2,MHP_Addr2_M
	uint16 MHP_Addr2_L #,0x08a4,MHP_Addr2_L
	uint16 MHP_Addr3_H #,0x08a6,MHP_Addr3_H
	uint16 MHP_Addr3_M #,0x08a8,MHP_Addr3_M
	uint16 MHP_Addr3_L #,0x08aa,MHP_Addr3_L
	uint16 MHP_Addr4_H #,0x08ac,MHP_Addr4_H
	uint16 MHP_Addr4_M #,0x08ae,MHP_Addr4_M
	uint16 MHP_Addr4_L #,0x08b0,MHP_Addr4_L
	uint16 MHP_CFC #,0x08b2,MHP_CFC
	uint16 DAGG_CTL2 #,0x08c0,DAGG_CTL2
	uint16 DAGG_BYTESLEFT #,0x08c2,DAGG_BYTESLEFT
	uint16 DAGG_SH_OFFSET #,0x08c4,DAGG_SH_OFFSET
	uint16 DAGG_STAT #,0x08c6,DAGG_STAT
	uint16 DAGG_LEN #,0x08c8,DAGG_LEN
	uint16 TXBA_CTL #,0x08ca,TXBA_CTL
	uint16 TXBA_DataSel #,0x08cc,TXBA_DataSel
	uint16 TXBA_Data #,0x08ce,TXBA_Data
	uint16 DAGG_LEN_THR #,0x08d0,DAGG_LEN_THR
	uint16 AMT_CTL #,0x08e0,AMT_CTL
	uint16 AMT_Status #,0x08e2,AMT_Status
	uint16 AMT_Limit #,0x08e4,AMT_Limit
	uint16 AMT_Attr #,0x08e6,AMT_Attr
	uint16 AMT_Match1 #,0x08e8,AMT_Match1
	uint16 AMT_Match2 #,0x08ea,AMT_Match2
	uint16 AMT_Table_Addr #,0x08ec,AMT_Table_Addr
	uint16 AMT_Table_Data #,0x08ee,AMT_Table_Data
	uint16 AMT_Table_Val #,0x08f0,AMT_Table_Val
	uint16 AMT_DBG_SEL #,0x08f2,AMT_DBG_SEL
	uint16 RoeCtrl #,0x0900,RoeCtrl
	uint16 RoeStatus #,0x0902,RoeStatus
	uint16 RoeIPChkSum #,0x0904,RoeIPChkSum
	uint16 RoeTCPUDPChkSum #,0x0906,RoeTCPUDPChkSum
	uint16 PSOCtl #,0x0920,PSOCtl
	uint16 PSORxWordsWatermark #,0x0922,PSORxWordsWatermark
	uint16 PSORxCntWatermark #,0x0924,PSORxCntWatermark
	uint16 OBFFCtl #,0x0930,OBFFCtl
	uint16 OBFFRxWordsWatermark #,0x0932,OBFFRxWordsWatermark
	uint16 OBFFRxCntWatermark #,0x0934,OBFFRxCntWatermark
	uint16 RcvHdrConvCtrlSts #,0x093e,RCVHdrConvCtrlStats
	uint16 RcvHdrConvSts #,0x0940,RCVHdrConvStats
	uint16 RcvHdrConvSts1 #,0x0942,RCVHdrConvStats1
	uint16 RCVLB_DAGG_CTL #,0x0944,RcvLB_DAGG_CTL
	uint16 RcvFifo0Len #,0x0946,RcvFifo0Len
	uint16 RcvFifo1Len #,0x0948,RcvFifo1Len
	uint16 ToECTL #,0x0a00,ToECTL
	uint16 ToERst #,0x0a02,ToERst
	uint16 ToECSumNZ #,0x0a04,ToECSumNZ
	uint16 TxSerialCtl #,0x0a40,TxSerialCtl
	uint16 TxPlcpLSig0 #,0x0a42,TxPlcpLSig0
	uint16 TxPlcpLSig1 #,0x0a44,TxPlcpLSig1
	uint16 TxPlcpHtSig0 #,0x0a46,TxPlcpHtSig0
	uint16 TxPlcpHtSig1 #,0x0a48,TxPlcpHtSig1
	uint16 TxPlcpHtSig2 #,0x0a4a,TxPlcpHtSig2
	uint16 TxPlcpVhtSigB0 #,0x0a4c,TxPlcpVhtSigB0
	uint16 TxPlcpVhtSigB1 #,0x0a4e,TxPlcpVhtSigB1
	uint16 MacHdrFromShmLen #,0x0a52,MacHdrFromShmLen
	uint16 TxPlcpLen #,0x0a54,TxPlcpLen
	uint16 TxBFRptLen #,0x0a58,TxBFRptLen
	uint16 BytCntInTxFrmLo #,0x0a5a, BytCntInTxFrmLo
	uint16 BytCntInTxFrmHi #,0x0a5c, BytCntInTxFrmHi
	uint16 TXBFCtl #,0x0a60,TXBFCtl
	uint16 BfmRptOffset #,0x0a62,BfmRptOffset
	uint16 BfmRptLen #,0x0a64,BfmRptLen
	uint16 TXBFBfeRptRdCnt #,0x0a66,TXBFBfeRptRdCnt
	uint16 PsmMboxOutSts #,0x0a90,psm_reg_mux
	uint16 PSM_BASE_0 #,0x0aa0,psm_base
	uint16 psm_base_x #,0x0abc,psm_base_x   missing
	uint16 RXMapFifoSize #,0x0b00,RXMapFifoSize
	uint16 RXMapStatus #,0x0b02,RXMapStatus
	uint16 MsduThreshold #,0x0b04,MsduThreshold
	uint16 BMCCore0TXAllMaxBuffers #,0x0b0e,BMCCore0TXAllMaxBuffers
	uint16 BMCCore1TXAllMaxBuffers #,0x0b10,BMCCore1TXAllMaxBuffers
	uint16 BMCDynAllocStatus1 #,0x0b12,BMCDynAllocStatus1
	uint16 DMAMaxOutStBuffers #,0x0b14,TXE_DMAMaxOutStBuffers
	uint16 SampleCollectStoreMaskLo #,0x0b16,TXE_SCS_MASK_L
	uint16 SampleCollectStoreMaskHi #,0x0b18,TXE_SCS_MASK_H
	uint16 SampleCollectMatchMaskLo #,0x0b1a,TXE_SCM_MASK_L
	uint16 SampleCollectMatchMaskHi #,0x0b1c,TXE_SCM_MASK_H
	uint16 SampleCollectMatchValueLo #,0x0b1e,TXE_SCM_VAL_L
	uint16 SampleCollectMatchValueHi #,0x0b20,TXE_SCM_VAL_H
	uint16 SampleCollectTriggerMaskLo #,0x0b22,TXE_SCT_MASK_L
	uint16 SampleCollectTriggerMaskHi #,0x0b24,TXE_SCT_MASK_H
	uint16 SampleCollectTriggerValueLo #,0x0b26,TXE_SCT_VAL_L
	uint16 SampleCollectTriggerValueHi #,0x0b28,TXE_SCT_VAL_H
	uint16 SampleCollectTransMaskLo #,0x0b2a,TXE_SCX_MASK_L
	uint16 SampleCollectTransMaskHi #,0x0b2c,TXE_SCX_MASK_H
	uint16 SampleCollectPlayCtrl #,0x0b2e,SampleCollectPlayCtrl
	uint16 Core0BMCAllocStatusTID7 #,0x0b30,Core0BMCAllocStatusTID7
	uint16 Core1BMCAllocStatusTID7 #,0x0b32,Core1BMCAllocStatusTID7
	uint16 XmtTemplatePtrOffset #, 0xb3a,XmtTemplatePtrOffset
	uint16 BMVpConfig #,0x0b36
FEATURE_END

FEATURE_BEGIN[regs_common_ge64_lt80]
	uint32 syncSlowTimeStamp #,0x0010,biststatus2
	uint16 IndXmtCtl #,0x0080,inddma
	uint16 IndAQMctl #,0x00a0,indaqm
	uint32 IndAQMQSel #,0x00c0,indqsel
	uint32 SUSPREQ #,0x00c4,suspreq
	uint32 FLUSHREQ #,0x00c8,flushreq
	uint32 CHNFLUSH_STATUS #,0x00cc,chnflushstatus
	uint32 gptimer_psmx #,0x01b0,gptimer_x
	uint32 MACCONTROL_psmx #,0x01b4,maccontrol_x
	uint32 MacControl1_psmx #,0x01b8,maccontrol1_x
	uint32 MACCOMMAND_psmx #,0x01bc,maccommand_x
	uint32 MACINTSTATUS_psmx #,0x01c0,macintstatus_x
	uint32 MACINTMASK_psmx #,0x01c4,macintmask_x
	uint32 ALT_MACINTSTATUS_psmx #,0x01c8,altmacintstatus_x
	uint32 ALT_MACINTMASK_psmx #,0x01cc,altmacintmask_x
	uint32 PSM_DEBUG_psmx #,0x01d0,psmdebug_x
	uint32 PHY_DEBUG_psmx #,0x01d4,phydebug_x
	uint16 RXE_ERRVAL #,0x0448,rxe_errval
	uint16 RXE_ERRMASK #,0x044a,rxe_errmask
	uint16 RXE_STATUS3 #,0x044c,rxe_status3
	uint16 PSM_STAT_CTR0_L #,0x04c8,psm_power_req_sts
	uint16 PSM_STAT_CTR1_H #,0x04ce,psm_ihr_err
	uint16 PSM_STAT_SEL #,0x04d0,psm_pc_reg_0
	uint16 TXE_MMPLCP_0 #,0x0510,txe_mmplcp0
	uint16 TXE_MMPLCP_1 #,0x0512,txe_mmplcp1
	uint16 TXE_PHYCTL_1 #,0x0514,txe_phyctl1
	uint16 TXE_PHYCTL_2 #,0x0516,txe_phyctl2
	uint16 SMP_PTR_H #,0x0538,SampleCollectPlayPtrHigh
	uint16 SCP_CURPTR_H #,0x053a,SampleCollectCurPtrHigh
	uint16 SCP_STRTPTR #,0x0552,SampleCollectStartPtr
	uint16 SCP_STOPPTR #,0x0554,SampleCollectStopPtr
	uint16 SCP_CURPTR #,0x0556,SampleCollectCurPtr
	uint16 SPP_STRTPTR #,0x055a,SamplePlayStartPtr
	uint16 SPP_STOPPTR #,0x055c,SamplePlayStopPtr
	uint16 WEP_HWKEY_ADDR #,0x07d0,pcmctl
	uint16 WEP_HWKEY_LEN #,0x07d2,pcmstat
	uint16 PMQ_DAT_OR_MAT_MU1 #,0x07f0,pmqdataor_mat1
	uint16 PMQ_DAT_OR_MAT_MU2 #,0x07f2,pmqdataor_mat2
	uint16 PMQ_DAT_OR_MAT_MU3 #,0x07f4,pmqdataor_mat3
	uint16 PMQ_AUXPMQ_STATUS #,0x07f6,pmq_auxsts
	uint16 PMQ_CTL1 #,0x07f8,pmq_ctl1
	uint16 PMQ_STATUS1 #,0x07fa,pmq_status1
	uint16 PMQ_ADDTHR #,0x07fc,pmq_addthr
	uint16 CTMode #,0x0800,TXE_ctmode
	uint16 SCM_HVAL_L #,0x080a,TXE_SCM_HVAL_L
	uint16 SCM_HVAL_H #,0x080c,TXE_SCM_HVAL_H
	uint16 SCT_HMASK_L #,0x080e,TXE_SCT_HMASK_L
	uint16 SCT_HMASK_H #,0x0810,TXE_SCT_HMASK_H
	uint16 SCT_HVAL_L #,0x0812,TXE_SCT_HVAL_L
	uint16 SCT_HVAL_H #,0x0814,TXE_SCT_HVAL_H
	uint16 SCX_HMASK_L #,0x0816,TXE_SCX_HMASK_L
	uint16 SCX_HMASK_H #,0x0818,TXE_SCX_HMASK_H
	uint16 BMC_ReadQID #,0x081e,BMC_ReadQID
	uint16 BMC_BQFrmCnt #,0x0820,BMC_BQFrmCnt
	uint16 BMC_BQByteCnt_L #,0x0822,BMC_BQByteCnt_L
	uint16 BMC_BQByteCnt_H #,0x0824,BMC_BQByteCnt_H
	uint16 AQM_BQFrmCnt #,0x0826,AQM_BQFrmCnt
	uint16 AQM_BQByteCnt_L #,0x0828,AQM_BQByteCnt_L
	uint16 AQM_BQByteCnt_H #,0x082a,AQM_BQByteCnt_H
	uint16 AQM_BQPrelWM #,0x082c,AQM_BQPrelWM
	uint16 AQM_BQPrelStatus #,0x082e,AQM_BQPrelStatus
	uint16 AQM_BQStatus #,0x0830,AQM_BQStatus
	uint16 BMC_MUDebugConfig #,0x0832,BMC_MUDebugConfig
	uint16 BMC_MUDebugStatus #,0x0834,BMC_MUDebugStatus
	uint16 BMCBQCutThruSt0 #,0x0836,BMCBQCutThruSt0
	uint16 BMCBQCutThruSt1 #,0x0838,BMCBQCutThruSt1
	uint16 BMCBQCutThruSt2 #,0x083a,BMCBQCutThruSt2
	uint16 TDC_VhtMacPad0 #,0x085a,TDC_VhtMacPad0
	uint16 TDC_VhtMacPad1 #,0x085c,TDC_VhtMacPad1
	uint16 TDC_MuVhtMCS #,0x085e,TDC_MuVhtMCS
	uint16 ShmDma_XferWCnt #,0x0866,ShmDma_XferCnt
	uint16 AMT_MATCH1 #,0x08e8,AMT_Match1
	uint16 AMT_MATCH2 #,0x08ea,AMT_Match2
	uint16 PSM_REG_MUX #,0x0a90,psm_reg_mux
	uint16 PSM_BASE_PSMX #,0x0abc,psm_base_x
	uint16 SCS_MASK_L #,0x0b16,TXE_SCS_MASK_L
	uint16 SCS_MASK_H #,0x0b18,TXE_SCS_MASK_H
	uint16 SCM_MASK_L #,0x0b1a,TXE_SCM_MASK_L
	uint16 SCM_MASK_H #,0x0b1c,TXE_SCM_MASK_H
	uint16 SCM_VAL_L #,0x0b1e,TXE_SCM_VAL_L
	uint16 SCM_VAL_H #,0x0b20,TXE_SCM_VAL_H
	uint16 SCT_MASK_L #,0x0b22,TXE_SCT_MASK_L
	uint16 SCT_MASK_H #,0x0b24,TXE_SCT_MASK_H
	uint16 SCT_VAL_L #,0x0b26,TXE_SCT_VAL_L
	uint16 SCT_VAL_H #,0x0b28,TXE_SCT_VAL_H
	uint16 SCX_MASK_L #,0x0b2a,TXE_SCX_MASK_L
	uint16 SCX_MASK_H #,0x0b2c,TXE_SCX_MASK_H
	uint16 SMP_CTRL #,0x0b2e,SampleCollectPlayCtrl
	uint16 SysMStartAddrHi #,0x0b48,SysMStartAddrHi
	uint16 SysMStartAddrLo #,0x0b4a,SysMStartAddrLo
	uint16 AQM_REG_SEL #,0x0b64,AQM_REG_SEL
	uint16 AQMQMAP #,0x0b66,AQMQMAP
	uint16 AQMCmd #,0x0b68,AQMCmd
	uint16 AQMConsMsdu #,0x0b6a,AQMConsMsdu
	uint16 AQMDMACTL #,0x0b6c,AQMDMACTL
	uint16 AQMMinCons #,0x0b86,AQMMinCons
	uint16 MsduMinCons #,0x0b88,MsduMinCons
	uint16 AQMAggNum #,0x0b8c,AQMAggNum
	uint16 AQMAggEntry #,0x0b96,AQMAggEntry
	uint16 AQMAggIdx #,0x0b98,AQMAggIdx
	uint16 AQMFiFoRptr #,0x0ba2,AQMFiFoRptr
	uint16 AQMFIFO_SOFDPtr #,0x0ba4,AQMFIFO_SOFDPtr
	uint16 AQMFIFO_SWDCnt #,0x0ba6,AQMFIFO_SWDCnt
	uint16 AQMFIFO_TXDPtr_L #,0x0ba8,AQMFIFO_TXDPtr_L
	uint16 AQMFIFO_TXDPtr_ML #,0x0baa,AQMFIFO_TXDPtr_ML
	uint16 AQMFIFO_TXDPtr_MU #,0x0bac,AQMFIFO_TXDPtr_MU
	uint16 AQMFIFO_TXDPtr_H #,0x0bae,AQMFIFO_TXDPtr_H
	uint16 AQMFifoRdy_L #,0x0bbc,AQMFifoRdy_L
	uint16 AQMFifoRdy_H #,0x0bbe,AQMFifoRdy_H
	uint16 AQMFifo_Status #,0x0bc0,AQMFifo_Status
	uint16 AQMFifoFull_L #,0x0bc2,AQMFifoFull_L
	uint16 AQMFifoFull_H #,0x0bc4,AQMFifoFull_H
	uint16 AQMTBCP_Busy_L #,0x0bc6,AQMTBCP_Busy_L
	uint16 AQMTBCP_Busy_H #,0x0bc8,AQMTBCP_Busy_H
	uint16 AQMDMA_SuspFlush #,0x0bca,AQMDMA_SuspFlush
	uint16 AQMFIFOSusp_L #,0x0bcc,AQMFIFOSusp_L
	uint16 AQMFIFOSusp_H #,0x0bce,AQMFIFOSusp_H
	uint16 AQMFIFO_SuspPend_L #,0x0bd0,AQMFIFO_SuspPend_L
	uint16 AQMFIFO_SuspPend_H #,0x0bd2,AQMFIFO_SuspPend_H
	uint16 AQMFIFOFlush_L #,0x0bd4,AQMFIFOFlush_L
	uint16 AQMFIFOFlush_H #,0x0bd6,AQMFIFOFlush_H
	uint16 AQMTXD_CTL #,0x0bd8,AQMTXD_CTL
	uint16 AQMTXD_RdOffset #,0x0bda,AQMTXD_RdOffset
	uint16 AQMTXD_RdLen #,0x0bdc,AQMTXD_RdLen
	uint16 AQMTXD_DestAddr #,0x0bde,AQMTXD_DestAddr
	uint16 AQMTBCP_QSEL #,0x0be0,AQMTBCP_QSEL
	uint16 AQMTBCP_Prio #,0x0be2,AQMTBCP_Prio
	uint16 AQMTBCP_PrioFifo #,0x0be4,AQMTBCP_PrioFifo
	uint16 AQMFIFO_MPDULen #,0x0be6,AQMFIFO_MPDULen
	uint16 AQMTBCP_Max_ReqEntry #,0x0be8,AQMTBCP_Max_ReqEntry
	uint16 AQMTBCP_FCNT #,0x0bea,AQMTBCP_FCNT
	uint16 AQMSTATUS #,0x0bf8,AQMSTATUS
	uint16 AQMDBG_CTL #,0x0bfa,AQMDBG_CTL
	uint16 AQMDBG_DATA #,0x0bfc,AQMDBG_DATA
	uint32 CHNSUSP_STATUS #,0x00d0
FEATURE_END

FEATURE_BEGIN[regs_common_ge80_lt128]
	uint32 RxFilterEn #,0x03b4,RxFilterEn
	uint32 RxHwaCtrl #,0x03b8,RxHwaCtrl
	uint32 FlowAgeTimer #,0x03bc,FlowAgeTimer
	uint16 RcvAMPDUCtl1 #,0x0430,rcvampductl1
	uint16 RXE_PHYRS_ADDR #,0x0478,rcmta_addr1
	uint16 RXE_PHYRS_DATA #,0x047a,rcmta_addr2
	uint16 AMT_MATCH #,0x04f4,AMT_Match
	uint16 AMT_ATTR_A1 #,0x04f6,AMT_Attr_A1
	uint16 AMT_ATTR_A2 #,0x04f8,AMT_Attr_A2
	uint16 AMT_ATTR_A3 #,0x04fa,AMT_Attr_A3
	uint16 AMT_ATTR_BSSID #,0x04fc,AMT_Attr_Bssid
	uint16 RXE_TXBA_CTL2 #,0x0506,TXBA_CTL2
	uint16 MULTITID_STATUS #,0x0508,MULTITID_STATUS
	uint16 FRAG_INFO #,0x050a,FRAG_Info
	uint16 FP_SHM_OFFSET #,0x050c,FP_SHM_OFFSET
	uint16 FP_CTL #,0x050e,FP_CTL
	uint16 BA_INFO_ACCESS #,0x0510,BA_INFO_ACCESS
	uint16 BA_INFO_DATA #,0x0512,BA_INFO_DATA
	uint16 FP_CONFIG #,0x0514,FP_CONFIG
	uint16 FP_PATTERN1 #,0x0516,FP_PATTERN1
	uint16 FP_MASK #,0x0518,FP_MASK
	uint16 FP_STATUS #,0x051a,FP_STATUS
	uint16 FP_PATTERN2 #,0x051c,FP_PATTERN2
	uint16 FP_PATTERN3 #,0x051e,FP_PATTERN3
	uint16 RoeStatus1 #,0x055c,RoeStatus1
	uint16 PSOCurRxFramePtrs #,0x0566,PSOCurRxFramePtrs
	uint16 PSOOBFFStatus #,0x0568,PSOOBFFStatus
	uint16 AVB_RXTIMESTAMP_L #,0x057c,AVB_RXTIMESTAMP_L
	uint16 AVB_RXTIMESTAMP_H #,0x057e,AVB_RXTIMESTAMP_H
	uint16 IFS_STAT2 #,0x06a0,ifsstat2
	uint16 IFS_CTL_SEL_SECCRS #,0x06a4,ifs_ctl_sel_seccrs
	uint16 WEP_KEY_DATA #,0x070c,wepivkey
	uint16 WEP_DATA #,0x0710,wepwkey
	uint16 BTCX_PRIORITYWIN #,0x0746,btcx_pri_win
	uint16 BTCX_TXCONFTIMER #,0x0748,btcx_tx_conf_timer
	uint16 BTCX_PRISELTIMER #,0x074a,btcx_ant_sw_timer
	uint16 BTCX_PRV_RFACT_TIMER #,0x074c,btcx_prv_rfact_timer
	uint16 BTCX_CUR_RFACT_TIMER #,0x074e,btcx_cur_rfact_timer
	uint16 BTCX_RFACT_DUR_TIMER #,0x0750,btcx_rfact_dur_timer
	uint16 BTCX_ECI_ADDR #,0x0764,btcx_eci_addr
	uint16 BTCX_ECI_DATA #,0x0766,btcx_eci_data
	uint16 BTCX_ECI_MASK_ADDR #,0x0768,btcx_eci_mask_addr
	uint16 BTCX_ECI_MASK_DATA #,0x076a,btcx_eci_mask_data
	uint16 COEX_IO_MASK #,0x076c,coex_io_mask
	uint16 BTCX_ECI_EVENT_ADDR #,0x076e,btcx_eci_event_addr
	uint16 BTCX_ECI_EVENT_DATA #,0x0770,btcx_eci_event_data
	uint16 PSM_INTSEL_1 #,0x0822,psm_int_sel_1
	uint16 PSM_INTSEL_2 #,0x0824,psm_int_sel_2
	uint16 PSM_INTSEL_3 #,0x0826,psm_int_sel_3
	uint16 TXE_BV_31 #,0x08fe,txe_ctl
	uint16 TXE_STATUS2 #,0x0988,txe_status2
	uint16 XmtSusp #,0x09EE,XmtSusp
	uint16 TXE_PHYCTL8 #,0x0a1c,txe_phyctl8
	uint16 TXE_PHYCTL9 #,0x0a1e,txe_phyctl9
	uint16 TXE_PHYCTL_3 #,0x0a38,txe_phyctl3
	uint16 TXE_PHYCTL_4 #,0x0a3a,txe_phyctl4
	uint16 TXE_PHYCTL_5 #,0x0a3c,txe_phyctl5
	uint16 TXE_PHYCTL_6 #,0x0a3e,txe_phyctl6
	uint16 TXE_PHYCTL_7 #,0x0a40,txe_phyctl7
	uint16 DebugTxFlowCtl #,0x0a5e,DebugTxFlowCtl
	uint16 TDC_PLCP0 #,0x0a62,TDC_Plcp0
	uint16 TDC_PLCP1 #,0x0a64,TDC_Plcp1
	uint16 TDC_FRMLEN0 #,0x0a66,TDC_FrmLen0
	uint16 TDC_FRMLEN1 #,0x0a68,TDC_FrmLen1
	uint16 TDC_TXTIME #,0x0a6a,TDC_Txtime
	uint16 TDC_PLCP2 #,0x0a6c,TDC_Plcp3
	uint16 TDC_PLCP3 #,0x0a6e,TDC_Plcp4
	uint16 TDC_LSIGLEN #,0x0a70,TDC_LSigLen
	uint16 TDC_NSYM0 #,0x0a72,TDC_NSym0
	uint16 TDC_NSYM1 #,0x0a74,TDC_NSym1
	uint16 SampleCollectPlayCtrl2 #,0x0ac4,SampleCollectPlayCtrl2
	uint16 XmtFlush #,0x0AF0,XmtFlush
	uint16 AQMAGGR #,0x0b2a,AQMAggr
	uint16 AQMMultBAFL #,0x0b2c,AQMMultBAFL
	uint16 AQM_DFAdjB #,0x0b4a,AQM_DFAdjB
	uint16 AQM_MFAdjB #,0x0b4c,AQM_MFAdjB
	uint16 AQM_CFAdjB #,0x0b4e,AQM_CFAdjB
	uint16 AQMminfragB #,0x0b50,AQMminfragB
	uint16 AQMcagburst #,0x0b52,AQMcagburst
	uint16 MQAQMMaxAggLenLow #,0x0b60,MQAQMMaxAggLenLow
	uint16 MQAQMMaxAggLenHi #,0x0b62,MQAQMMaxAggLenHi
	uint16 MQMAXMPDU #,0x0b64,MQMAXMPDU
	uint16 AMPDUXMT #,0x0b66,AMPDUXMT
	uint16 AQMCaggNum #,0x0b74,AQMCaggNum
	uint16 AQMCaggLenLow #,0x0b76,AQMCaggLenLow
	uint16 AQMCAggLenHi #,0x0b78,AQMCaggLenHi
	uint16 XMT_AMPDU_DLIM_H #,0x0b7e,AQMFragOS
	uint16 AQMFIFO_FLAG #,0x0b94,AQMFIFO_FLAG
	uint16 AQMFSIE_OP #,0x0ba0,AQMFSIE_OP
	uint16 AQMFSIE_RWD0 #,0x0ba2,AQMFSIE_RWD0
	uint16 AQMFSIE_RWD1 #,0x0ba4,AQMFSIE_RWD1
	uint16 AQMFSIE_RWD2 #,0x0ba6,AQMFSIE_RWD2
	uint16 BMCHdrOffset #,0x0bbc,AQMFifoFull_H
	uint16 BMCHdrLength #,0x0bbe,BMCHdrLength
	uint16 Core0BMCAllocStatusTplate #,0x0bf2,Core0BMCAllocStatusTplate
	uint16 Core1BMCAllocStatusTplate #,0x0bf4,Core1BMCAllocStatusTplate
FEATURE_END

FEATURE_BEGIN[regs_common_ge128_lt129]
	uint32 xmt_dma_chsel #,0x0050,xmt_dma_chsel
	uint32 xmt_dma_intmap0 #,0x0054,xmt_dma_intmap0
	uint32 xmt_dma_intmap1 #,0x0058,xmt_dma_intmap1
	uint32 indintstat #,0x0078,indintstat
	uint32 indintmask #,0x007c,indintmask
	uint32 SUSPREQ1 #,0x00D4,SUSPREQ1
	uint32 FLUSHREQ1 #,0x00D8,FLUSHREQ1
	uint32 CHNFLUSH_STATUS1 #,0x00DC,CHNFLUSH_STATUS1
	uint32 CHNSUSP_STATUS1 #,0x00E0,CHNSUSP_STATUS1
	uint32 SUSPREQ2 #,0x00E4,SUSPREQ2
	uint32 FLUSHREQ2 #,0x00E8,FLUSHREQ2
	uint32 CHNFLUSH_STATUS2 #,0x00EC,CHNFLUSH_STATUS2
	uint32 CHNSUSP_STATUS2 #,0x00F0,CHNSUSP_STATUS2
	uint32 TxDMAIndXmtStat0 #,0x00F8,TxDMAIndXmtStat0
	uint32 TxDMAIndXmtStat1 #,0x00Fc,TxDMAIndXmtStat1
	uint16 PHYPLUS1CTL #,0x01AC,PHYPLUS1CTL
	uint16 PSM_CHK0_ERR #,0x0247,PSM_CHK0_ERR
	uint16 PSM_CHK1_ERR #,0x024B,PSM_CHK1_ERR
	uint32 gptimer_R1 #,0x0320,gptimer_R1
	uint32 MACCONTROL_r1 #,0x0324,MACCONTROL_r1
	uint32 MacControl1_R1 #,0x0328,MacControl1_R1
	uint32 MACCOMMAND_R1 #,0x032C,MACCOMMAND_R1
	uint32 MACINTSTATUS_R1 #,0x0330,MACINTSTATUS_R1
	uint32 MACINTMASK_R1 #,0x0334,MACINTMASK_R1
	uint32 ALT_MACINTSTATUS_R1 #,0x0338,ALT_MACINTSTATUS_R1
	uint32 ALT_MACINTMASK_R1 #,0x033C,ALT_MACINTMASK_R1
	uint16 PSM_DEBUG_R1 #,0x0360,PSM_DEBUG_R1
	uint32 TSFTimerLow_R1 #,0x0364,TSFTimerLow_R1
	uint32 TSFTimerHigh_R1 #,0x0368,TSFTimerHigh_R1
	uint16 HostFCBSCmdPtr #,0x03B4,HostFCBSCmdPtr
	uint16 HostFCBSDataPtr #,0x03B8,HostFCBSDataPtr
	uint16 HostCtrlStsReg #,0x03BC,HostCtrlStsReg
	uint16 RXE_CBR_CTL #,0x0406,RXE_CBR_CTL
	uint16 RXE_CBR_STAT #,0x0408,RXE_CBR_STAT
	uint16 RXE_DMA_STCNT #,0x0436,RXE_DMA_STCNT
	uint16 OMAC_HWSTS_L #,0x0458,OMAC_HWSTS_L
	uint16 OMAC_HWSTS_H #,0x045A,OMAC_HWSTS_H
	uint16 RXBM_DBG_SEL #,0x045C,RXBM_DBG_SEL
	uint16 RXBM_DBG_DATA #,0x045E,RXBM_DBG_DATA
	uint16 RCV_BM_OVFL_DBGSEL #,0x0478,RCV_BM_OVFL_DBGSEL
	uint16 MHP_FCTP #,0x04A8,MHP_FCTP
	uint16 MHP_FCTST #,0x04AA,MHP_FCTST
	uint16 MHP_DFCTST #,0x04AC,MHP_DFCTST
	uint16 MHP_EXT0 #,0x04AE,MHP_EXT0
	uint16 MHP_EXT1 #,0x04B0,MHP_EXT1
	uint16 MHP_EXT2 #,0x04B2,MHP_EXT2
	uint16 MHP_EXT3 #,0x04B4,MHP_EXT3
	uint16 MHP_PLCP0 #,0x04B6,MHP_PLCP0
	uint16 MHP_PLCP1 #,0x04B8,MHP_PLCP1
	uint16 MHP_PLCP2 #,0x04BA,MHP_PLCP2
	uint16 MHP_PLCP3 #,0x04BC,MHP_PLCP3
	uint16 MHP_PLCP4 #,0x04BE,MHP_PLCP4
	uint16 MHP_PLCP5 #,0x04C0,MHP_PLCP5
	uint16 MHP_PLCP6 #,0x04C2,MHP_PLCP6
	uint16 MHP_SEL #,0x04C4,MHP_SEL
	uint16 MHP_DATA #,0x04C6,MHP_DATA
	uint16 MHP_CFG #,0x04C8,MHP_CFG
	uint16 RXE_RCF_CTL #,0x04D0,RXE_RCF_CTL
	uint16 RXE_RCF_ADDR #,0x04D2,RXE_RCF_ADDR
	uint16 RXE_RCF_WDATA #,0x04D4,RXE_RCF_WDATA
	uint16 RXE_RCF_RDATA #,0x04D6,RXE_RCF_RDATA
	uint16 RXE_RCF_NP_STATS #,0x04D8,RXE_RCF_NP_STATS
	uint16 RXE_RCF_HP_STATS #,0x04DA,RXE_RCF_HP_STATS
	uint16 RXE_HDRC_CTL #,0x0500,RXE_HDRC_CTL
	uint16 RXE_HDRC_STATUS #,0x0502,RXE_HDRC_STATUS
	uint16 RXE_WM_0 #,0x0504,RXE_WM_0
	uint16 RXE_WM_1 #,0x0506,RXE_WM_1
	uint16 RXE_BM_ADDR #,0x0508,RXE_BM_ADDR
	uint16 RXE_BM_DATA #,0x050A,RXE_BM_DATA
	uint16 RXE_BV_ADDR #,0x050C,RXE_BV_ADDR
	uint16 RXE_BV_DATA #,0x050E,RXE_BV_DATA
	uint16 PERUSER_DBG_SEL #,0x0510,PERUSER_DBG_SEL
	uint16 RXQ_DBG_CTL #,0x0518,RXQ_DBG_CTL
	uint16 RXQ_DBG_STS #,0x051A,RXQ_DBG_STS
	uint16 FP_PAT0 #,0x0528,FP_PAT0
	uint16 FP_PAT1 #,0x052A,FP_PAT1
	uint16 FP_PAT2 #,0x052C,FP_PAT2
	uint16 FP_SUPAT #,0x052E,FP_SUPAT
	uint16 RXE_FP_SHMADDR #,0x0530,RXE_FP_SHMADDR
	uint16 RXE_TXBA_CTL1 #,0x0542,RXE_TXBA_CTL1
	uint16 MTID_STATUS #,0x0548,MTID_STATUS
	uint16 BA_LEN #,0x054A,BA_LEN
	uint16 BA_LEN_ENC #,0x054C,BA_LEN_ENC
	uint16 MULTITID_STATUS2 #,0x054E,MULTITID_STATUS2
	uint16 BAINFO_SEL #,0x0550,BAINFO_SEL
	uint16 BAINFO_DATA #,0x0552,BAINFO_DATA
	uint16 TXBA_UBMP #,0x0554,TXBA_UBMP
	uint16 TXBA_UCNT #,0x0556,TXBA_UCNT
	uint16 TXBA_XFRBMP #,0x0558,TXBA_XFRBMP
	uint16 TXBA_XFRCTL #,0x055A,TXBA_XFRCTL
	uint16 TXBA_XFRCNT #,0x055C,TXBA_XFRCNT
	uint16 TXBA_XFROFFS #,0x055E,TXBA_XFROFFS
	uint16 RDFBD_CTL0 #,0x0560,RDFBD_CTL0
	uint16 RDF_CTL0 #,0x0562,RDF_CTL0
	uint16 RDF_CTL1 #,0x0564,RDF_CTL1
	uint16 RDF_CTL2 #,0x0566,RDF_CTL2
	uint16 RDF_CTL3 #,0x0568,RDF_CTL3
	uint16 RDF_CTL4 #,0x056A,RDF_CTL4
	uint16 RDF_CTL5 #,0x056C,RDF_CTL5
	uint16 RDF_STAT1 #,0x056E,RDF_STAT1
	uint16 RDF_STAT2 #,0x0570,RDF_STAT2
	uint16 RDF_STAT3 #,0x0572,RDF_STAT3
	uint16 RDF_STAT4 #,0x0574,RDF_STAT4
	uint16 RDF_STAT5 #,0x0576,RDF_STAT5
	uint16 RDF_STAT6 #,0x0578,RDF_STAT6
	uint16 RDF_STAT7 #,0x057A,RDF_STAT7
	uint16 RDF_STAT8 #,0x057C,RDF_STAT8
	uint16 RXE_PHYSTS_SHMADDR #,0x0592,RXE_PHYSTS_SHMADDR
	uint16 RXE_PHYSTS_BMP_SEL #,0x0594,RXE_PHYSTS_BMP_SEL
	uint16 RXE_PHYSTS_BMP_DATA #,0x0596,RXE_PHYSTS_BMP_DATA
	uint16 RXE_PHYSTS_TIMEOUT #,0x0598,RXE_PHYSTS_TIMEOUT
	uint16 RXE_OOB_CFG #,0x05B0,RXE_OOB_CFG
	uint16 RXE_OOB_BMP0 #,0x05B2,RXE_OOB_BMP0
	uint16 RXE_OOB_BMP1 #,0x05B4,RXE_OOB_BMP1
	uint16 RXE_OOB_BMP2 #,0x05B6,RXE_OOB_BMP2
	uint16 RXE_OOB_BMP3 #,0x05B8,RXE_OOB_BMP3
	uint16 RXE_OOB_DSCR_ADDR #,0x05BA,RXE_OOB_DSCR_ADDR
	uint16 RXE_OOB_DSCR_SIZE #,0x05BC,RXE_OOB_DSCR_SIZE
	uint16 RXE_OOB_BUFA_ADDR #,0x05BE,RXE_OOB_BUFA_ADDR
	uint16 RXE_OOB_BUFA_SIZE #,0x05C0,RXE_OOB_BUFA_SIZE
	uint16 RXE_OOB_BUFB_ADDR #,0x05C2,RXE_OOB_BUFB_ADDR
	uint16 RXE_OOB_BUFB_SIZE #,0x05C4,RXE_OOB_BUFB_SIZE
	uint16 RXE_OOB_STATUS #,0x05C6,RXE_OOB_STATUS
	uint16 RXE_OOB_DESC_PTR #,0x05C8,RXE_OOB_DESC_PTR
	uint16 RXE_OOB_BUFA_PTR #,0x05CA,RXE_OOB_BUFA_PTR
	uint16 RXE_OOB_BUFB_PTR #,0x05CC,RXE_OOB_BUFB_PTR
	uint16 RXE_BFDRPT_CTL #,0x05CE,RXE_BFDRPT_CTL
	uint16 RXE_BFDRPT_RST #,0x05D0,RXE_BFDRPT_RST
	uint16 RXE_BFDRPT_LEN #,0x05D2,RXE_BFDRPT_LEN
	uint16 RXE_BFDRPT_OFFSET #,0x05D4,RXE_BFDRPT_OFFSET
	uint16 RXE_BFDRPT_MEND #,0x05D6,RXE_BFDRPT_MEND
	uint16 RXE_BFDRPT_XFER #,0x05D8,RXE_BFDRPT_XFER
	uint16 RXE_BFDRPT_SUCC #,0x05DA,RXE_BFDRPT_SUCC
	uint16 RXE_BFDRPT_DONE #,0x05DC,RXE_BFDRPT_DONE
	uint16 RXE_BFM_HDRSEL #,0x05DE,RXE_BFM_HDRSEL
	uint16 RXE_BFM_HDRDATA #,0x05E0,RXE_BFM_HDRDATA
	uint16 CMDPTR_L #,0x06E0,CMDPTR_L
	uint16 CMDPTR_H #,0x06E2,CMDPTR_H
	uint16 DATA_PTR_L #,0x06E4,DATA_PTR_L
	uint16 DATA_PTR_H #,0x06E6,DATA_PTR_H
	uint16 CTRL_STS #,0x06E8,CTRL_STS
	uint16 PHY_ADDR #,0x06EA,PHY_ADDR
	uint16 PHY_DATA #,0x06EC,PHY_DATA
	uint16 RADIO_ADDR #,0x06EE,RADIO_ADDR
	uint16 RADIO_DATA #,0x06F0,RADIO_DATA
	uint16 RUNTIME_CNT #,0x06F2,RUNTIME_CNT
	uint16 TSF_GPT_0_CTR_L #,0x0762,TSF_GPT_0_CTR_L
	uint16 TSF_GPT_0_CTR_H #,0x0764,TSF_GPT_0_CTR_H
	uint16 TSF_GPT_0_VAL_L #,0x0766,TSF_GPT_0_VAL_L
	uint16 TSF_GPT_0_VAL_H #,0x0768,TSF_GPT_0_VAL_H
	uint16 TSF_GPT_1_STAT #,0x076A,TSF_GPT_1_STAT
	uint16 TSF_GPT_1_CTL_L #,0x076C,TSF_GPT_1_CTL_L
	uint16 TSF_GPT_1_CTL_H #,0x076E,TSF_GPT_1_CTL_H
	uint16 TSF_GPT_1_VAL_L #,0x0770,TSF_GPT_1_VAL_L
	uint16 HWA_MACIF_CTL #,0x07B2,HWA_MACIF_CTL
	uint16 PSM_DIV_REM_L #,0x07BC,PSM_DIV_REM_L
	uint16 PSM_DIV_REM_H #,0x07BE,PSM_DIV_REM_H
	uint16 PSM_MACCTL #,0x07C2,PSM_MACCTL
	uint16 PSM_SBADDR #,0x07E2,PSM_SBADDR
	uint16 PSM_BRC_SEL_1 #,0x082A,PSM_BRC_SEL_1
	uint16 PSM_BASE_14 #,0x085C,PSM_BASE_14
	uint16 PSM_BASE_15 #,0x085E,PSM_BASE_15
	uint16 PSM_BASE_16 #,0x0860,PSM_BASE_16
	uint16 PSM_BASE_17 #,0x0862,PSM_BASE_17
	uint16 PSM_BASE_18 #,0x0864,PSM_BASE_18
	uint16 PSM_BASE_19 #,0x0866,PSM_BASE_19
	uint16 PSM_BASE_20 #,0x0868,PSM_BASE_20
	uint16 PSM_BASE_21 #,0x086A,PSM_BASE_21
	uint16 PSM_BASE_22 #,0x086C,PSM_BASE_22
	uint16 PSM_BASE_23 #,0x086E,PSM_BASE_23
	uint16 PSM_RATEMEM_DBG #,0x0872,PSM_RATEMEM_DBG
	uint16 PSM_RATEMEM_CTL #,0x0874,PSM_RATEMEM_CTL
	uint16 PSM_RATEBLK_SIZE #,0x0876,PSM_RATEBLK_SIZE
	uint16 PSM_RATEXFER_SIZE #,0x0878,PSM_RATEXFER_SIZE
	uint16 PSM_LINKMEM_CTL #,0x087A,PSM_LINKMEM_CTL
	uint16 PSM_LINKBLK_SIZE #,0x087C,PSM_LINKBLK_SIZE
	uint16 PSM_LINKXFER_SIZE #,0x087E,PSM_LINKXFER_SIZE
	uint16 MAC_GPIOOUT_L #,0x0886,MAC_GPIOOUT_L
	uint16 MAC_GPIOOUT_H #,0x0888,MAC_GPIOOUT_H
	uint16 PMQ_CNT #,0x08C2,PMQ_CNT
	uint16 PMQ_SRCH_USREN #,0x08C4,PMQ_SRCH_USREN
	uint16 PMQ_USR_SEL #,0x08C6,PMQ_USR_SEL
	uint16 PMQ_DAT_OR_MAT_SEL #,0x08D0,PMQ_DAT_OR_MAT_SEL
	uint16 PMQ_DAT_OR_MAT_DATA #,0x08D2,PMQ_DAT_OR_MAT_DATA
	uint16 PMQ_MATCH #,0x08D4,PMQ_MATCH
	uint16 APMQ_MATCH #,0x08D6,APMQ_MATCH
	uint16 PMQ_USER_BMP #,0x08E0,PMQ_USER_BMP
	uint16 TXE_FCS_CTL #,0x0910,TXE_FCS_CTL
	uint16 AMPDU_CTL #,0x0914,AMPDU_CTL
	uint16 AMPDU_CRC #,0x0916,AMPDU_CRC
	uint16 TXE_WM_LEG0 #,0x0918,TXE_WM_LEG0
	uint16 TXE_WM_LEG1 #,0x091a,TXE_WM_LEG1
	uint16 TXE_CTL3 #,0x091C,TXE_CTL3
	uint16 TXE_TXE_EARLYTXMEND_CNT #,0x091E,TXE_TXE_EARLYTXMEND_CNT
	uint16 TXE_TXE_EARLYTXMEND_BSUB_CNT #,0x0920,TXE_TXE_EARLYTXMEND_BSUB_CNT
	uint16 TXE_TXE_TXMEND_CNT #,0x0922,TXE_TXE_TXMEND_CNT
	uint16 TXE_TXE_TXMEND_NCONS #,0x0924,TXE_TXE_TXMEND_NCONS
	uint16 TXE_TXE_TXMEND_PEND #,0x0926,TXE_TXE_TXMEND_PEND
	uint16 TXE_TXE_TXMEND_USR2GO #,0x0928,TXE_TXE_TXMEND_USR2GO
	uint16 TXE_TXE_TXMEND_CONSCNT #,0x092A,TXE_TXE_TXMEND_CONSCNT
	uint16 TXE_BVBM_INIT #,0x093E,TXE_BVBM_INIT
	uint16 ToEChannelState #,0x0948,ToEChannelState
	uint16 TXE_BV_REG0 #,0x0952,TXE_BV_REG0
	uint16 TXE_BM_REG0 #,0x0954,TXE_BM_REG0
	uint16 TXE_BV_REG1 #,0x0956,TXE_BV_REG1
	uint16 TXE_BM_REG1 #,0x0958,TXE_BM_REG1
	uint16 TXE_SHMDMA_MPMADDR #,0x0970,TXE_SHMDMA_MPMADDR
	uint16 TXE_BITSUB_IDX #,0x0976,TXE_BITSUB_IDX
	uint16 TXE_BM_ADDR #,0x0978,TXE_BM_ADDR
	uint16 TXE_BM_DATA #,0x097A,TXE_BM_DATA
	uint16 TXE_BV_ADDR #,0x097C,TXE_BV_ADDR
	uint16 TXE_BV_DATA #,0x097E,TXE_BV_DATA
	uint16 TXE_BV_10 #,0x09B4,TXE_BV_10
	uint16 TXE_BV_11 #,0x09B6,TXE_BV_11
	uint16 TXE_BV_12 #,0x09B8,TXE_BV_12
	uint16 TXE_BV_13 #,0x09BA,TXE_BV_13
	uint16 TXE_BV_14 #,0x09BC,TXE_BV_14
	uint16 TXE_BV_15 #,0x09BE,TXE_BV_15
	uint16 TXE_BMC_CONFIG#,0x09CE,TXE_BMC_CONFIG
	uint16 TXE_BMC_RXMAPFIFOSIZE #,0x09DC,TXE_BMC_RXMAPFIFOSIZE
	uint16 TXE_BMC_RXMAPSTATUS #,0x09DE,TXE_BMC_RXMAPSTATUS
	uint16 TXE_BMC_DYNSTATUS1 #,0x09EA,TXE_BMC_DYNSTATUS1
	uint16 TXE_BMC_MAXOUTSTBUFS #,0x09EC,TXE_BMC_MAXOUTSTBUFS
	uint16 TXE_BMC_CONFIG1 #,0x09EE,TXE_BMC_CONFIG1
	uint16 TXE_LLM_CONFIG #,0x09F6,TXE_LLM_CONFIG
	uint16 TXE_LOCALM_SADDR_L #,0x0A0A,TXE_LOCALM_SADDR_L
	uint16 TXE_LOCALM_SADDR_H #,0x0A0C,TXE_LOCALM_SADDR_H
	uint16 TXE_LOCALM_EADDR_L #,0x0A0E,TXE_LOCALM_EADDR_L
	uint16 TXE_LOCALM_EADDR_H #,0x0A10,TXE_LOCALM_EADDR_H
	uint16 TXE_BMC_ALLOCCTL1 #,0x0A12,TXE_BMC_ALLOCCTL1
	uint16 TXE_BMC_MALLOCREQ_QB0 #,0x0A20,TXE_BMC_MALLOCREQ_QB0
	uint16 TXE_BMC_MALLOCREQ_QB1 #,0x0A22,TXE_BMC_MALLOCREQ_QB1
	uint16 TXE_BMC_MALLOCREQ_QB2 #,0x0A24,TXE_BMC_MALLOCREQ_QB2
	uint16 TXE_BMC_MALLOCREQ_QB3 #,0x0A26,TXE_BMC_MALLOCREQ_QB3
	uint16 TXE_BMC_MALLOCREQ_QB4 #,0x0A28,TXE_BMC_MALLOCREQ_QB4
	uint16 PHYCTL_LEN #,0x0A40,PHYCTL_LEN
	uint16 TXE_PHYCTL_10 #,0x0A56,TXE_PHYCTL_10
	uint16 PLCP_LSIG0 #,0x0A58,PLCP_LSIG0
	uint16 PLCP_LSIG1 #,0x0A5A,PLCP_LSIG1
	uint16 PLCP_HTSIG0 #,0x0A5C,PLCP_HTSIG0
	uint16 PLCP_HTSIG1 #,0x0A5E,PLCP_HTSIG1
	uint16 PLCP_HTSIG2 #,0x0A60,PLCP_HTSIG2
	uint16 TXE_PLCP_VHTSIGB0 #,0x0A62,TXE_PLCP_VHTSIGB0
	uint16 TXE_PLCP_VHTSIGB1 #,0x0A64,TXE_PLCP_VHTSIGB1
	uint16 PLCP_EXT2 #,0x0A66,PLCP_EXT2
	uint16 PLCP_CC1_LEN #,0x0A68,PLCP_CC1_LEN
	uint16 PLCP_CC2_LEN #,0x0A6A,PLCP_CC2_LEN
	uint16 TXE_MPMSIZE_SEL #,0x0A6C,TXE_MPMSIZE_SEL
	uint16 TXE_MPMSIZE_VAL #,0x0A6E,TXE_MPMSIZE_VAL
	uint16 TXE_PLCPEXT_ADDR #,0x0A70,TXE_PLCPEXT_ADDR
	uint16 TXE_PLCPEXT_DATA #,0x0A72,TXE_PLCPEXT_DATA
	uint16 TXE_PHYCTLEXT_BASE #,0x0A74,TXE_PHYCTLEXT_BASE
	uint16 TXE_PLCPEXT_BASE #,0x0A76,TXE_PLCPEXT_BASE
	uint16 TXE_SIGB_BASE #,0x0A78,TXE_SIGB_BASE
	uint16 TXE_PLCP_LEN #,0x0A7A,TXE_PLCP_LEN
	uint16 TXE_TXDBG_SEL #,0x0A86,TXE_TXDBG_SEL
	uint16 TXE_TXDBG_DATA #,0x0A88,TXE_TXDBG_DATA
	uint16 TXE_BFMRPT_MEMSEL #,0x0A8A,TXE_BFMRPT_MEMSEL
	uint16 TXE_BFMRPT_ADDR #,0x0A8C,TXE_BFMRPT_ADDR
	uint16 TXE_BFMRPT_DATA #,0x0A8E,TXE_BFMRPT_DATA
	uint16 TXE_MEND_STATUS #,0x0A90,TXE_MEND_STATUS
	uint16 TXE_UNFLOW_STATUS #,0x0A92,TXE_UNFLOW_STATUS
	uint16 TXE_TXERROR_STATUS #,0x0A94,TXE_TXERROR_STATUS
	uint16 TXE_SNDFRM_STATUS #,0x0A96,TXE_SNDFRM_STATUS
	uint16 TXE_TXERROR_USR #,0x0A98,TXE_TXERROR_USR
	uint16 TXE_MACPAD_PAT_L #,0x0A9A,TXE_MACPAD_PAT_L
	uint16 TXE_MACPAD_PAT_H #,0x0A9C,TXE_MACPAD_PAT_H
	uint16 TXE_PHYTXREQ_TMOUT#,0x0A9E, TXE_PHYTXREQ_TMOUT
	uint16 TXE_XMTSUSP_QB0 #,0x0AE8,TXE_XMTSUSP_QB0
	uint16 TXE_XMTSUSP_QB1 #,0x0AEA,TXE_XMTSUSP_QB1
	uint16 TXE_XMTSUSP_QB2 #,0x0AEC,TXE_XMTSUSP_QB2
	uint16 TXE_XMTSUSP_QB3 #,0x0AEE,TXE_XMTSUSP_QB3
	uint16 TXE_XMTSUSP_QB4 #,0x0AF0,TXE_XMTSUSP_QB4
	uint16 TXE_XMTFLUSH_QB0 #,0x0AF2,TXE_XMTFLUSH_QB0
	uint16 TXE_XMTFLUSH_QB1 #,0x0AF4,TXE_XMTFLUSH_QB1
	uint16 TXE_XMTFLUSH_QB2 #,0x0AF6,TXE_XMTFLUSH_QB2
	uint16 TXE_XMTFLUSH_QB3 #,0x0AF8,TXE_XMTFLUSH_QB3
	uint16 TXE_XMTFLUSH_QB4 #,0x0AFA,TXE_XMTFLUSH_QB4
	uint16 TXE_XMT_SHMADDR #,0x0AFC,TXE_XMT_SHMADDR
	uint16 TXE_BMC_READQID #,0x0AFE,TXE_BMC_READQID
	uint16 TXE_BMC_READIDX #,0x0B02,TXE_BMC_READIDX
	uint16 BMC_AQMBQID #,0x0B0A,BMC_AQMBQID
	uint16 BMC_PSMCMD_THRESH #,0x0B0C,BMC_PSMCMD_THRESH
	uint16 BMC_PSMCMD_LOWVEC #,0x0B0E,BMC_PSMCMD_LOWVEC
	uint16 BMC_PSMCMD_EMPTYVEC #,0x0B10,BMC_PSMCMD_EMPTYVEC
	uint16 BMC_PSMCMD_OFLOW #,0x0B12,BMC_PSMCMD_OFLOW
	uint16 BMC_CMD2SCHED_PEND #,0x0B14,BMC_CMD2SCHED_PEND
	uint16 BMC_AQM_TXDRD_PEND #,0x0B16,BMC_AQM_TXDRD_PEND
	uint16 BMC_UC_TXDRD_PEND #,0x0B18,BMC_UC_TXDRD_PEND
	uint16 BMC_CMDQ_FREECNT #,0x0B1A,BMC_CMDQ_FREECNT
	uint16 BMC_CMDQ_FREESTS #,0x0B1C,BMC_CMDQ_FREESTS
	uint16 BMC_CMDQ_FRMCNT #,0x0B1E,BMC_CMDQ_FRMCNT
	uint16 BMC_FRM2SER_PEND #,0x0B20,BMC_FRM2SER_PEND
	uint16 BMC_FRM2SER_PRGR #,0x0B22,BMC_FRM2SER_PRGR
	uint16 BMC_FRM2MPM_PEND #,0x0B24,BMC_FRM2MPM_PEND
	uint16 BMC_FRM2MPM_PENDSTS #,0x0B26,BMC_FRM2MPM_PENDSTS
	uint16 BMC_FRM2MPM_PRGR #,0x0B28,BMC_FRM2MPM_PRGR
	uint16 BMC_BITSUB_FREECNT #,0x0B2A,BMC_BITSUB_FREECNT
	uint16 BMC_BITSUB_FREESTS #,0x0B2C,BMC_BITSUB_FREESTS
	uint16 BMC_CMDQ_USR2GO #,0x0B2E,BMC_CMDQ_USR2GO
	uint16 BMC_BITSUB_USR2GO #,0x0B30,BMC_BITSUB_USR2GO
	uint16 TXE_BRC_CMDQ_FREEUP #,0x0B32,TXE_BRC_CMDQ_FREEUP
	uint16 TXE_BRC_FRM2MPM_PEND #,0x0B34,TXE_BRC_FRM2MPM_PEND
	uint16 BMC_PSMCMD0 #,0x0B36,BMC_PSMCMD0
	uint16 BMC_PSMCMD1 #,0x0B38,BMC_PSMCMD1
	uint16 BMC_PSMCMD2 #,0x0B3A,BMC_PSMCMD2
	uint16 BMC_PSMCMD3 #,0x0B3C,BMC_PSMCMD3
	uint16 BMC_PSMCMD4 #,0x0B3E,BMC_PSMCMD4
	uint16 BMC_PSMCMD5 #,0x0B40,BMC_PSMCMD5
	uint16 BMC_PSMCMD6 #,0x0B42,BMC_PSMCMD6
	uint16 BMC_PSMCMD7 #,0x0B44,BMC_PSMCMD7
	uint16 BMC_RDCLIENT_CTL #,0x0B46,BMC_RDCLIENT_CTL
	uint16 BMC_RDMGR_USR_RST #,0x0B48,BMC_RDMGR_USR_RST
	uint16 BMC_BMRD_INFLIGHT_THRESH #,0x0B4A,BMC_BMRD_INFLIGHT_THRESH
	uint16 BMC_BITSUB_CAP #,0x0B4C,BMC_BITSUB_CAP
	uint16 BMC_ERR #,0x0B4E,BMC_ERR
	uint16 TXE_SCHED_USR_RST #,0x0B50,TXE_SCHED_USR_RST
	uint16 TXE_SCHED_SET_UFL #,0x0B52,TXE_SCHED_SET_UFL
	uint16 TXE_SCHED_UFL_WAIT #,0x0B54,TXE_SCHED_UFL_WAIT
	uint16 BMC_SCHED_UFL_NOCMD #,0x0B56,TXE_SCHED_UFL_NOCMD
	uint16 BMC_CMD2SCHED_PENDSTS #,0x0B58,BMC_CMD2SCHED_PENDSTS
	uint16 BMC_PSMCMD_RST #,0x0B5A,BMC_PSMCMD_RST
	uint16 TXE_SCHED_SENT_L #,0x0B5C,TXE_SCHED_SENT_L
	uint16 TXE_SCHED_SENT_H #,0x0B5E,TXE_SCHED_SENT_H
	uint16 TXE_SCHED_CTL #,0x0B60,TXE_SCHED_CTL
	uint16 TXE_MSCHED_USR_EN #,0x0B62,TXE_MSCHED_USR_EN
	uint16 TXE_MSCHED_SYMB_CYCS #,0x0B64,TXE_MSCHED_SYMB_CYCS
	uint16 TXE_SCHED_UFL_STS #,0x0B66,TXE_SCHED_UFL_STS
	uint16 TXE_MSCHED_BURSTPH_TOTSZ #,0x0B68,TXE_MSCHED_BURSTPH_TOTSZ
	uint16 TXE_MSCHED_BURSTPH_BURSTSZ #,0x0B6A,TXE_MSCHED_BURSTPH_BURSTSZ
	uint16 TXE_MSCHED_NDPBS_L #,0x0B6C,TXE_MSCHED_NDPBS_L
	uint16 TXE_MSCHED_NDPBS_H #,0x0B6E,TXE_MSCHED_NDPBS_H
	uint16 TXE_MSCHED_STATE #,0x0B70,TXE_MSCHED_STATE
	uint16 TXE_FRMINPROG_QB0 #,0x0B74,TXE_FRMINPROG_QB0
	uint16 TXE_FRMINPROG_QB1 #,0x0B76,TXE_FRMINPROG_QB1
	uint16 TXE_FRMINPROG_QB2 #,0x0B78,TXE_FRMINPROG_QB2
	uint16 TXE_FRMINPROG_QB3 #,0x0B7A,TXE_FRMINPROG_QB3
	uint16 TXE_FRMINPROG_QB4 #,0x0B7C,TXE_FRMINPROG_QB4
	uint16 TXE_XMT_DMABUSY_QB0 #,0x0B7E,TXE_XMT_DMABUSY_QB0
	uint16 TXE_XMT_DMABUSY_QB1 #,0x0B80,TXE_XMT_DMABUSY_QB1
	uint16 TXE_XMT_DMABUSY_QB2 #,0x0B82,TXE_XMT_DMABUSY_QB2
	uint16 TXE_XMT_DMABUSY_QB3 #,0x0B84,TXE_XMT_DMABUSY_QB3
	uint16 TXE_XMT_DMABUSY_QB4 #,0x0B86,TXE_XMT_DMABUSY_QB4
	uint16 TXE_BMC_FIFOFULL_QB0 #,0x0B88,TXE_BMC_FIFOFULL_QB0
	uint16 TXE_BMC_FIFOFULL_QB1 #,0x0B8A,TXE_BMC_FIFOFULL_QB1
	uint16 TXE_BMC_FIFOFULL_QB2 #,0x0B8C,TXE_BMC_FIFOFULL_QB2
	uint16 TXE_BMC_FIFOFULL_QB3 #,0x0B8E,TXE_BMC_FIFOFULL_QB3
	uint16 TXE_BMC_FIFOFULL_QB4 #,0x0B90,TXE_BMC_FIFOFULL_QB4
	uint16 TXE_XMT_DPQSL_QB0 #,0x0B92,TXE_XMT_DPQSL_QB0
	uint16 TXE_XMT_DPQSL_QB1 #,0x0B94,TXE_XMT_DPQSL_QB1
	uint16 TXE_XMT_DPQSL_QB2 #,0x0B96,TXE_XMT_DPQSL_QB2
	uint16 TXE_XMT_DPQSL_QB3 #,0x0B98,TXE_XMT_DPQSL_QB3
	uint16 TXE_XMT_DPQSL_QB4 #,0x0B9A,TXE_XMT_DPQSL_QB4
	uint16 TXE_AQM_BQSTATUS #,0x0B9C,TXE_AQM_BQSTATUS
	uint16 TXE_DBG_BMC_STATUS #,0x0BAC,TXE_DBG_BMC_STATUS
	uint16 TXE_HDR_PDLIM #,0x0BB6,TXE_HDR_PDLIM
	uint16 TXE_MAC_PADBYTES #,0x0BB8,TXE_MAC_PADBYTES
	uint16 TXE_MPDU_MINLEN #,0x0BBA,TXE_MPDU_MINLEN
	uint16 TXE_AMP_EOFPD_L #,0x0BBC,TXE_AMP_EOFPD_L
	uint16 TXE_AMP_EOFPD_H #,0x0BBE,TXE_AMP_EOFPD_H
	uint16 TXE_AMP_EOFPADBYTES #,0x0BC0,TXE_AMP_EOFPADBYTES
	uint16 TXE_PSDULEN_L #,0x0BC2,TXE_PSDULEN_L
	uint16 TXE_PSDULEN_H #,0x0BC4,TXE_PSDULEN_H
	uint16 XMTDMA_CTL #,0x0BC8,XMTDMA_CTL
	uint16 TXE_XMTDMA_PRELD_RANGE #,0x0BCA,TXE_XMTDMA_PRELD_RANGE
	uint16 TXE_XMTDMA_ACT_RANGE #,0x0BCC,TXE_XMTDMA_ACT_RANGE
	uint16 TXE_XMTDMA_RUWT_QSEL #,0x0BCE,TXE_XMTDMA_RUWT_QSEL
	uint16 TXE_XMTDMA_RUWT_DATA #,0x0BD0,TXE_XMTDMA_RUWT_DATA
	uint16 TXE_CTDMA_CTL #,0x0BD2,TXE_CTDMA_CTL
	uint16 TXE_XMTDMA_DBG_CTL #,0x0BD4,TXE_XMTDMA_DBG_CTL
	uint16 XMTDMA_AQMIF_STS #,0x0BD6,XMTDMA_AQMIF_STS
	uint16 XMTDMA_PRELD_STS #,0x0BD8,XMTDMA_PRELD_STS
	uint16 XMTDMA_ACT_STS #,0x0BDA,XMTDMA_PRELD_STS
	uint16 XMTDMA_QUEUE_STS #,0x0BDC,XMTDMA_QUEUE_STS
	uint16 XMTDMA_ENGINE_STS #,0x0BDE,XMTDMA_ENGINE_STS
	uint16 XMTDMA_DMATX_STS #,0x0BE0,XMTDMA_DMATX_STS
	uint16 XMTDMA_THRUPUTCTL_STS #,0x0BE2,XMTDMA_THRUPUTCTL_STS
	uint16 TXE_SCHED_MPMFC_STS #,0x0BE4,TXE_SCHED_MPMFC_STS
	uint16 TXE_SCHED_FORCE_BAD #,0x0BE6,TXE_SCHED_FORCE_BAD
	uint16 TXE_BMC_RDMGR_STATE #,0x0BE8,TXE_BMC_RDMGR_STATE
	uint16 TXE_SCHED_ERR #,0x0BEA,TXE_SCHED_ERR
	uint16 TXE_BMC_PFF_CFG #,0x0BEC,TXE_BMC_PFF_CFG
	uint16 TXE_BMC_PFFSTART_DEF #,0x0BEE,TXE_BMC_PFFSTART_DEF
	uint16 TXE_BMC_PFFSZ_DEF #,0x0BF0,TXE_BMC_PFFSZ_DEF
	uint16 XmtDMABusyOtherQ0to15 #,0x0BF4,XmtDMABusyOtherQ0to15
	uint16 XmtDMABusyOtherQ16to31 #,0x0BF6,XmtDMABusyOtherQ16to31
	uint16 XmtDMABusyOtherQ32to47 #,0x0BF8,XmtDMABusyOtherQ32to47
	uint16 XmtDMABusyOtherQ48to63 #,0x0BFA,XmtDMABusyOtherQ48to63
	uint16 XmtDMABusyOtherQ64to69 #,0x0BFC,XmtDMABusyOtherQ64to69
	uint16 AQM_CFG #,0x0C00,AQM_CFG
	uint16 AQM_FIFODEF0 #,0x0C02,AQM_FIFODEF0
	uint16 AQM_FIFODEF1 #,0x0C04,AQM_FIFODEF1
	uint16 AQM_TXCNTDEF0 #,0x0C06,AQM_TXCNTDEF0
	uint16 AQM_TXCNTDEF1 #,0x0C08,AQM_TXCNTDEF1
	uint16 AQM_INITREQ#,0x0C0A,AQM_INITREQ
	uint16 AQM_REGSEL #,0x0C10,AQM_REGSEL
	uint16 AQM_QMAP #,0x0C12,AQM_QMAP
	uint16 AQM_MAXAGGRLEN_H #,0x0C14,AQM_MAXAGGRLEN_L
	uint16 AQM_MAXAGGRLEN_L #,0x0C16,AQM_MAXAGGRLEN_H
	uint16 AQM_MAXAGGRNUM #,0x0C18,AQM_MAXAGGRNUM
	uint16 AQM_MINMLEN #,0x0C1A,AQM_MINMLEN
	uint16 AQM_MAXOSFRAG #,0x0C1C,AQM_MAXOSFRAG
	uint16 AQM_AGGPARM #,0x0C1E,AQM_AGGPARM
	uint16 AQM_FRPRAM #,0x0C20,AQM_FRPRAM
	uint16 AQM_MINFRLEN #,0x0C22,AQM_MINFRLEN
	uint16 AQM_MQBURST #,0x0C24,AQM_MQBURST
	uint16 AQM_DMLEN #,0x0C26,AQM_DMLEN
	uint16 AQM_MMLEN #,0x0C28,AQM_MMLEN
	uint16 AQM_CMLEN #,0x0C2A,AQM_CMLEN
	uint16 AQM_VQENTRY0 #,0x0C2C,AQM_VQENTRY0
	uint16 AQM_VQENTRY1 #,0x0C2E,AQM_VQENTRY1
	uint16 AQM_VQADJ #,0x0C30,AQM_VQADJ
	uint16 AQM_VQPADADJ #,0x0C32,AQM_VQPADADJ
	uint16 AQM_AGGREN #,0x0C34,AQM_AGGREN
	uint16 AQM_AGGREQ #,0x0C36,AQM_AGGREQ
	uint16 AQM_CAGGLEN_L #,0x0C38,AQM_CAGGLEN_L
	uint16 AQM_CAGGLEN_H #,0x0C3A,AQM_CAGGLEN_H
	uint16 AQM_CAGGNUM #,0x0C3C,AQM_CAGGNUM
	uint16 AQM_QAGGSTATS #,0x0C3E,AQM_QAGGSTATS
	uint16 AQM_QAGGNUM #,0x0C40,AQM_QAGGNUM
	uint16 AQM_QAGGINFO #,0x0C42,AQM_QAGGINFO
	uint16 AQM_AGGRPTR #,0x0C44,AQM_AGGRPTR
	uint16 AQM_QAGGLEN_L #,0x0C46,AQM_QAGGLEN_L
	uint16 AQM_QAGGLEN_H #,0x0C48,AQM_QAGGLEN_H
	uint16 AQM_QMPDULEN #,0x0C4A,AQM_QMPDULEN
	uint16 AQM_QFRAGOS #,0x0C4C,AQM_QFRAGOS
	uint16 AQM_QTXCNT #,0x0C4E,AQM_QTXCNT
	uint16 AQM_QMPDUINFO0 #,0x0C50,AQM_QMPDUINFO0
	uint16 AQM_QMPDUINFO1 #,0x0C52,AQM_QMPDUINFO1
	uint16 AQM_TXCNTEN #,0x0C54,AQM_TXCNTEN
	uint16 AQM_TXCNTUPD #,0x0C56,AQM_TXCNTUPD
	uint16 AQM_QTXCNTRPTR #,0x0C58,AQM_QTXCNTRPTR
	uint16 AQM_QCURTXCNT #,0x0C5A,AQM_QCURTXCNT
	uint16 AQM_BASEL #,0x0C60,AQM_BASEL
	uint16 AQM_RCVDBA0 #,0x0C62,AQM_RCVDBA0
	uint16 AQM_RCVDBA1 #,0x0C64,AQM_RCVDBA1
	uint16 AQM_RCVDBA2 #,0x0C66,AQM_RCVDBA2
	uint16 AQM_RCVDBA3 #,0x0C68,AQM_RCVDBA3
	uint16 AQM_BASSN #,0x0C6A,AQM_BASSN
	uint16 AQM_REFSN #,0x0C6C,AQM_REFSN
	uint16 AQM_QMAXBAIDX #,0x0C6E,AQM_QMAXBAIDX
	uint16 AQM_BAEN #,0x0C70,AQM_BAEN
	uint16 AQM_BAREQ #,0x0C72,AQM_BAREQ
	uint16 AQM_UPDBARD #,0x0C74,AQM_UPDBARD
	uint16 AQM_UPDBA0 #,0x0C76,AQM_UPDBA0
	uint16 AQM_UPDBA1 #,0x0C78,AQM_UPDBA1
	uint16 AQM_UPDBA2 #,0x0C7A,AQM_UPDBA2
	uint16 AQM_UPDBA3 #,0x0C7C,AQM_UPDBA3
	uint16 AQM_ACKCNT #,0x0C7E,AQM_ACKCNT
	uint16 AQM_CONSTYPE #,0x0C80,AQM_CONSTYPE
	uint16 AQM_CONSEN #,0x0C82,AQM_CONSEN
	uint16 AQM_CONSREQ #,0x0C84,AQM_CONSREQ
	uint16 AQM_CONSCNT #,0x0C88,AQM_CONSCNT
	uint16 AQM_XUPDEN #,0x0C90,AQM_XUPDEN
	uint16 AQM_XUPDREQ #,0x0C92,AQM_XUPDREQ
	uint16 AQM_TXDMAEN #,0x0C98,AQM_TXDMAEN
	uint16 AQM_TXDMAREQ #,0x0C9A,AQM_TXDMAREQ
	uint16 AQMF_READY0 #,0x0CA0,AQMF_READY0
	uint16 AQMF_READY1 #,0x0CA2,AQMF_READY1
	uint16 AQMF_READY2 #,0x0CA4,AQMF_READY2
	uint16 AQMF_READY3 #,0x0CA6,AQMF_READY3
	uint16 AQMF_READY4 #,0x0CA8,AQMF_READY4
	uint16 AQMF_MTE0 #,0x0CAA,AQMF_MTE0
	uint16 AQMF_MTE1 #,0x0CAC,AQMF_MTE1
	uint16 AQMF_MTE2 #,0x0CAE,AQMF_MTE2
	uint16 AQMF_MTE3 #,0x0CB0,AQMF_MTE3
	uint16 AQMF_MTE4 #,0x0CB2,AQMF_MTE4
	uint16 AQMF_PLREADY0 #,0x0CB4,AQMF_PLREADY0
	uint16 AQMF_PLREADY1 #,0x0CB6,AQMF_PLREADY1
	uint16 AQMF_PLREADY2 #,0x0CB8,AQMF_PLREADY2
	uint16 AQMF_PLREADY3 #,0x0CBA,AQMF_PLREADY3
	uint16 AQMF_PLREADY4 #,0x0CBC,AQMF_PLREADY4
	uint16 AQMF_FULL0 #,0x0CBE,AQMF_FULL0
	uint16 AQMF_FULL1 #,0x0CC0,AQMF_FULL1
	uint16 AQMF_FULL2 #,0x0CC2,AQMF_FULL2
	uint16 AQMF_FULL3 #,0x0CC4,AQMF_FULL3
	uint16 AQMF_FULL4 #,0x0CC6,AQMF_FULL4
	uint16 AQMF_STATUS #,0x0CC8,AQMF_STATUS
	uint16 MQF_EMPTY0 #,0x0CCA,MQF_EMPTY0
	uint16 MQF_EMPTY1 #,0x0CCC,MQF_EMPTY1
	uint16 MQF_EMPTY2 #,0x0CCE,MQF_EMPTY2
	uint16 MQF_EMPTY3 #,0x0CD0,MQF_EMPTY3
	uint16 MQF_EMPTY4 #,0x0CD2,MQF_EMPTY4
	uint16 MQF_STATUS #,0x0CD4,MQF_STATUS
	uint16 TXQ_STATUS #,0x0CD8,TXQ_STATUS
	uint16 AQM_BQEN #,0x0CE0,AQM_BQEN
	uint16 AQM_BQSUSP #,0x0CE2,AQM_BQSUSP
	uint16 AQM_BQFLUSH #,0x0CE4,AQM_BQFLUSH
	uint16 AQMF_HSUSP0 #,0x0CE8,AQMF_HSUSP0
	uint16 AQMF_HSUSP1 #,0x0CEA,AQMF_HSUSP1
	uint16 AQMF_HSUSP2 #,0x0CEC,AQMF_HSUSP2
	uint16 AQMF_HSUSP3 #,0x0CEE,AQMF_HSUSP3
	uint16 AQMF_HSUSP4 #,0x0CF0,AQMF_HSUSP4
	uint16 AQMF_HSUSP_PRGR0 #,0x0CF2,AQMF_HSUSP_PRGR0
	uint16 AQMF_HSUSP_PRGR1 #,0x0CF4,AQMF_HSUSP_PRGR1
	uint16 AQMF_HSUSP_PRGR2 #,0x0CF6,AQMF_HSUSP_PRGR2
	uint16 AQMF_HSUSP_PRGR3 #,0x0CF8,AQMF_HSUSP_PRGR3
	uint16 AQMF_HSUSP_PRGR4 #,0x0CFA,AQMF_HSUSP_PRGR4
	uint16 AQMF_HFLUSH0 #,0x0CFC,AQMF_HFLUSH0
	uint16 AQMF_HFLUSH1 #,0x0CFE,AQMF_HFLUSH1
	uint16 AQMF_HFLUSH2 #,0x0D00,AQMF_HFLUSH2
	uint16 AQMF_HFLUSH3 #,0x0D02,AQMF_HFLUSH3
	uint16 AQMF_HFLUSH4 #,0x0D04,AQMF_HFLUSH4
	uint16 AQMTXD_READ #,0x0D10,AQMTXD_READ
	uint16 AQMTXD_RDOFFSET #,0x0D12,AQMTXD_RDOFFSET
	uint16 AQMTXD_RDLEN #,0x0D14,AQMTXD_RDLEN
	uint16 AQMTXD_DSTADDR #,0x0D16,AQMTXD_DSTADDR
	uint16 AQMTXD_AUTOPF #,0x0D18,AQMTXD_AUTOPF
	uint16 AQMTXD_APFOFFSET #,0x0D1A,AQMTXD_APFOFFSET
	uint16 AQMTXD_APFDSTADDR #,0x0D1C,AQMTXD_APFDSTADDR
	uint16 AQMTXD_PFREADY0 #,0x0D1E,AQMTXD_PFREADY0
	uint16 AQMTXD_PFREADY1 #,0x0D20,AQMTXD_PFREADY1
	uint16 AQMTXD_PFREADY2 #,0x0D22,AQMTXD_PFREADY2
	uint16 AQMTXD_PFREADY3 #,0x0D24,AQMTXD_PFREADY3
	uint16 AQMTXD_PFREADY4 #,0x0D26,AQMTXD_PFREADY4
	uint16 AQMCT_BUSY0 #,0x0D28,AQMCT_BUSY0
	uint16 AQMCT_BUSY1 #,0x0D2A,AQMCT_BUSY1
	uint16 AQMCT_BUSY2 #,0x0D2C,AQMCT_BUSY2
	uint16 AQMCT_BUSY3 #,0x0D2E,AQMCT_BUSY3
	uint16 AQMCT_BUSY4 #,0x0D30,AQMCT_BUSY4
	uint16 AQMCT_QSEL #,0x0D32,AQMCT_QSEL
	uint16 AQMCT_PRI #,0x0D34,AQMCT_PRI
	uint16 AQMCT_PRIFIFO #,0x0D36,AQMCT_PRIFIFO
	uint16 AQMCT_MAXREQNUM #,0x0D38,AQMCT_MAXREQNUM
	uint16 AQMCT_FREECNT #,0x0D3A,AQMCT_FREECNT
	uint16 AQMCT_CHDIS #,0x0D3C,AQMCT_CHDIS
	uint16 AQMPL_CFG #,0x0D40,AQMPL_CFG
	uint16 AQMPL_QSEL #,0x0D42,AQMPL_QSEL
	uint16 AQMPL_THRESHOLD #,0x0D44,AQMPL_THRESHOLD
	uint16 AQMPL_EPOCHMASK#,0x0D46,AQMPL_EPOCHMASK
	uint16 AQMPL_MAXMPDU#,0x0D48,AQMPL_MAXMPDU
	uint16 AQMPL_DIS #,0x0D4A,AQMPL_DIS
	uint16 AQMPL_FORCE #,0x0D4C,AQMPL_FORCE
	uint16 AQMTXPL_THRESH #,0x0D4E,AQMTXPL_THRESH
	uint16 AQMTXPL_MASK #,0x0D50,AQMTXPL_MASK
	uint16 AQMTXPL_RDY #,0x0D52,AQMTXPL_RDY
	uint16 AQMCSB_REQ #,0x0D60,AQMCSB_REQ
	uint16 AQMF_RPTR #,0x0D62,AQMF_RPTR
	uint16 AQMF_MPDULEN #,0x0D64,AQMF_MPDULEN
	uint16 AQMF_SOFDPTR #,0x0D66,AQMF_SOFDPTR
	uint16 AQMF_SWDCNT #,0x0D68,AQMF_SWDCNT
	uint16 AQMF_FLAG #,0x0D6A,AQMF_FLAG
	uint16 AQMF_TXDPTR_L #,0x0D6C,AQMF_TXDPTR_L
	uint16 AQMF_TXDPTR_ML #,0x0D6E,AQMF_TXDPTR_ML
	uint16 AQMF_TXDPTR_MU #,0x0D70,AQMF_TXDPTR_MU
	uint16 AQMF_TXDPTR_H #,0x0D72,AQMF_TXDPTR_H
	uint16 AQMF_SRTIDX #,0x0D74,AQMF_SRTIDX
	uint16 AQMF_ENDIDX #,0x0D76,AQMF_ENDIDX
	uint16 AQMF_NUMBUF #,0x0D78,AQMF_NUMBUF
	uint16 AQMF_BUFLEN #,0x0D7A,AQMF_BUFLEN
	uint16 AQMFR_RWD0 #,0x0D7C,AQMFR_RWD0
	uint16 AQMFR_RWD1 #,0x0D7E,AQMFR_RWD1
	uint16 AQMFR_RWD2 #,0x0D80,AQMFR_RWD2
	uint16 AQMFR_RWD3 #,0x0D82,AQMFR_RWD3
	uint16 AQMCSB_RPTR #,0x0D84,AQMCSB_RPTR
	uint16 AQMCSB_WPTR #,0x0D86,AQMCSB_WPTR
	uint16 AQMCSB_BASEL #,0x0D88,AQMCSB_BASEL
	uint16 AQMCSB_BA0 #,0x0D8A,AQMCSB_BA0
	uint16 AQMCSB_BA1 #,0x0D8C,AQMCSB_BA1
	uint16 AQMCSB_BA2 #,0x0D8E,AQMCSB_BA2
	uint16 AQMCSB_BA3 #,0x0D90,AQMCSB_BA3
	uint16 AQMCSB_QAGGLEN_L #,0x0D92,AQMCSB_QAGGLEN_L
	uint16 AQMCSB_QAGGLEN_H #,0x0D94,AQMCSB_QAGGLEN_H
	uint16 AQMCSB_QAGGNUM #,0x0D96,AQMCSB_QAGGNUM
	uint16 AQMCSB_QAGGSTATS #,0x0D98,AQMCSB_QAGGSTATS
	uint16 AQMCSB_QAGGINFO #,0x0D9A,AQMCSB_QAGGINFO
	uint16 AQMCSB_CONSCNT #,0x0D9C,AQMCSB_CONSCNT
	uint16 AQMCSB_TOTCONSCNT #,0x0D9E,AQMCSB_TOTCONSCNT
	uint16 AQMCSB_CFGSTRADDR #,0x0DA0,AQMCSB_CFGSTRADDR
	uint16 AQMCSB_CFGENDADDR #,0x0DA2,AQMCSB_CFGENDADDR
	uint16 AQM_AGGERR #,0x0DA8,AQM_AGGERR
	uint16 AQM_QAGGERR #,0x0DAA,AQM_QAGGERR
	uint16 AQM_BRSTATUS #,0x0DAC,AQM_BRSTATUS
	uint16 AQM_QBRSTATUS #,0x0DAE,AQM_QBRSTATUS
	uint16 AQM_DBGCTL #,0x0DB0,AQM_DBGCTL
	uint16 AQM_DBGDATA0 #,0x0DB2,AQM_DBGDATA0
	uint16 AQM_DBGDATA1 #,0x0DB4,AQM_DBGDATA1
	uint16 AQM_DBGDATA2 #,0x0DB6,AQM_DBGDATA2
	uint16 AQM_DBGDATA3 #,0x0DB8,AQM_DBGDATA3
	uint16 AQM_ERRSEL #,0x0DBA,AQM_ERRSEL
	uint16 AQM_ERRSTS #,0x0DBC,AQM_ERRSTS
	uint16 AQM_SWRESET #,0x0DBE,AQM_SWRESET
	uint16 TDC_CTL #,0x0E00,TDC_CTL
	uint16 TDC_USRCFG #,0x0E02,TDC_USRCFG
	uint16 TDC_RUNCMD #,0x0E04,TDC_RUNCMD
	uint16 TDC_RUNSTS #,0x0E06,TDC_RUNSTS
	uint16 TDC_STATUS #,0x0E08,TDC_STATUS
	uint16 TDC_NUSR #,0x0E0A,TDC_NUSR
	uint16 TDC_ORIGBW #,0x0E14,TDC_ORIGBW
	uint16 TDC_FRMLEN_L #,0x0E16,TDC_FRMLEN_L
	uint16 TDC_FRMLEN_H #,0x0E18,TDC_FRMLEN_H
	uint16 TDC_USRINFO_0 #,0x0E1A,TDC_USRINFO_0
	uint16 TDC_USRINFO_1 #,0x0E1C,TDC_USRINFO_1
	uint16 TDC_USRAID #,0x0E1E,TDC_USRAID
	uint16 TDC_PPET0 #,0x0E20,TDC_PPET0
	uint16 TDC_PPET1 #,0x0E22,TDC_PPET1
	uint16 TDC_MAX_LENEXP #,0x0E24,TDC_MAX_LENEXP
	uint16 TDC_MAXDUR #,0x0E26,TDC_MAXDUR
	uint16 TDC_MINMDUR #,0x0E28,TDC_MINMDUR
	uint16 TDC_HDRDUR #,0x0E2A,TDC_HDRDUR
	uint16 TDC_TRIG_PADDUR #,0x0E2C,TDC_TRIG_PADDUR
	uint16 TDC_PSDULEN_L #,0x0E36,TDC_PSDULEN_L
	uint16 TDC_PSDULEN_H #,0x0E38,TDC_PSDULEN_H
	uint16 TDC_HDR_PDLIM #,0x0E3A,TDC_HDR_PDLIM
	uint16 TDC_MAC_PADLEN #,0x0E3C,TDC_MAC_PADLEN
	uint16 TDC_EOFPDLIM_L #,0x0E3E,TDC_EOFPDLIM_L
	uint16 TDC_EOFPDLIM_H #,0x0E40,TDC_EOFPDLIM_H
	uint16 TDC_MAXPSDULEN_L #,0x0E42,TDC_MAXPSDULEN_L
	uint16 TDC_MAXPSDULEN_H #,0x0E44,TDC_MAXPSDULEN_H
	uint16 TDC_MPDU_MINLEN #,0x0E46,TDC_MPDU_MINLEN
	uint16 TDC_CCLEN #,0x0E48,TDC_CCLEN
	uint16 TDC_RATE_L #,0x0E4A,TDC_RATE_L
	uint16 TDC_RATE_H #,0x0E4C,TDC_RATE_H
	uint16 TDC_NSYMINIT_L #,0x0E4E,TDC_NSYMINIT_L
	uint16 TDC_NSYMINIT_H #,0x0E50,TDC_NSYMINIT_H
	uint16 TDC_NDBPS_L #,0x0E52,TDC_NDBPS_L
	uint16 TDC_NDBPS_H #,0x0E54,TDC_NDBPS_H
	uint16 TDC_NDBPS_S #,0x0E56,TDC_NDBPS_S
	uint16 TDC_T_PRE #,0x0E58,TDC_T_PRE
	uint16 TDC_TDATA #,0x0E5A,TDC_TDATA
	uint16 TDC_TDATA_MIN #,0x0E5C,TDC_TDATA_MIN
	uint16 TDC_TDATA_MAX #,0x0E5E,TDC_TDATA_MAX
	uint16 TDC_TDATA_AVG #,0x0E60,TDC_TDATA_AVG
	uint16 TDC_TDATA_TOT #,0x0E62,TDC_TDATA_TOT
	uint16 TDC_HESIGB_NSYM #,0x0E64,TDC_HESIGB_NSYM
	uint16 TDC_AGGLEN_L #,0x0E66,TDC_AGGLEN_L
	uint16 TDC_AGGLEN_H #,0x0E68,TDC_AGGLEN_H
	uint16 TDC_TIME_IN #,0x0E6A,TDC_TIME_IN
	uint16 TDC_INITREQ #,0x0E6C,TDC_INITREQ
	uint16 TDC_AGG0STS #,0x0E6E,TDC_AGG0STS
	uint16 TDC_TRIGENDLOG #,0x0E70,TDC_TRIGENDLOG
	uint16 TDC_RUSTS #,0x0E72,TDC_RUSTS
	uint16 TDC_DAID
	uint16 TDC_FBWCTL
	uint16 TDC_PPCTL
	uint16 TDC_FBWSTS
	uint16 TDC_PPSTS
	uint16 TDC_CTL1
	uint16 TDC_PDBG
	uint16 TDC_PSDU_ACKSTS
	uint16 TDC_AGG_RDYSTS
	uint16 TDC_AGGLEN_OVR_L
	uint16 TDC_AGGLEN_OVR_H
	uint16 TDC_DROPUSR
	uint16 TDC_DURMARGIN
	uint16 TDC_DURTHRESH
	uint16 TDC_MAXTXOP
	uint16 TDC_RXPPET
	uint16 TDC_AGG0TXOP
FEATURE_END

FEATURE_BEGIN[regs_common_ge129_lt132]
	uint16 SCTSTP_MASK_L
	uint16 SCTSTP_MASK_H
	uint16 SCTSTP_VAL_L
	uint16 SCTSTP_VAL_H
	uint16 SCTSTP_HMASK_L
	uint16 SCTSTP_HMASK_H
	uint16 SCTSTP_HVAL_L
	uint16 SCTSTP_HVAL_H
	uint16 SMP_CTRL2
	uint32 PSM_GpioMonMemPtr
	uint32 PSM_GpioMonMemData
	uint16 PSM_XMT_TPLDATA_L
	uint16 PSM_XMT_TPLDATA_H
	uint16 PSM_XMT_TPLPTR
	uint16 PSM_SMP_CTRL
	uint16 PSM_SCT_MASK_L
	uint16 PSM_SCT_MASK_H
	uint16 PSM_SCT_VAL_L
	uint16 PSM_SCT_VAL_H
	uint16 PSM_SCTSTP_MASK_L
	uint16 PSM_SCTSTP_MASK_H
	uint16 PSM_SCTSTP_VAL_L
	uint16 PSM_SCTSTP_VAL_H
	uint16 PSM_SCX_MASK_L
	uint16 PSM_SCX_MASK_H
	uint16 PSM_SCM_MASK_L
	uint16 PSM_SCM_MASK_H
	uint16 PSM_SCM_VAL_L
	uint16 PSM_SCM_VAL_H
	uint16 PSM_SCS_MASK_L
	uint16 PSM_SCS_MASK_H
	uint16 PSM_SCP_CURPTR
	uint16 PSM_SCP_STRTPTR
	uint16 PSM_SCP_STOPPTR
	uint16 PSM_SMP_CTRL2
	uint16 PSM_BRWK_4
FEATURE_END

FEATURE_BEGIN[regs_common_ge132]
	uint32 ctdma_ctl
	uint32 MAC_BOOT_CTRL
	uint32 MacCapability2
	uint32 RxDmaXferCnt
	uint32 RxDmaXferCntMax
	uint32 RxFIFOCnt
	uint16 AMT_START
	uint16 AMT_END
	uint16 AMT_MATCH_A1
	uint16 AMT_MATCH_A2
	uint16 AMT_MATCH_A3
	uint16 AMT_MATCH_BSSID
	uint16 FP_PAT1A
	uint16 PSM_USR_SEL
	uint16 PSM_FATAL_STS
	uint16 PSM_FATAL_MASK
	uint16 HWA_MACIF_CTL1
	uint16 PSM_BASE_24
	uint16 PSM_BASE_25
	uint16 PSM_BASE_26
	uint16 PSM_BASE_27
	uint16 PSM_M2DMA_ADDR
	uint16 PSM_M2DMA_DATA
	uint16 PSM_M2DMA_FREE
	uint16 PSM_M2DMA_CFG
	uint16 PSM_M2DMA_DATA_L
	uint16 PSM_M2DMA_DATA_H
	uint16 TXE_HTC_LOC
	uint16 TXE_HTC_L
	uint16 TXE_HTC_H
	uint16 BMCHWC_CNT_SEL
	uint16 BMCHWC_CNT
	uint16 BMCHWC_CTL
	uint16 BMC_FRM2MPM_PRGRSTS
	uint16 BMC_PSMCMD8
	uint16 TXE_SHMDMA_PHYSTSADDR
	uint16 TXE_SHMDMA_MACFIFOADDR
	uint16 TXE_BMC_PSMCMDQ_CTL
	uint16 TXE_BMC_ERRSTSEN
	uint16 TX_PREBM_FATAL_ERRVAL
	uint16 TX_PREBM_FATAL_ERRMASK
	uint16 SCS_TAIL_CNT
	uint16 PLCP_CC34_LEN
	uint16 TXE_BMC_ERRSTS
	uint16 XMTDMA_FATAL_ERR_RPTEN
	uint16 TXE_XMTDMA_SW_RSTCTL
	uint16 XMTDMA_ACTUSR_DBGCTL
	uint16 XMTDMA_ACTUSR_VLDSTS
	uint16 XMTDMA_ACTUSR_QID
	uint16 XMTDMA_PROGERR
	uint16 TXE_MENDLAST_STATUS
	uint16 XMTDMA_AQM_ACT_CNT
	uint16 XMTDMA_FATAL_ERR
	uint16 AQM_MSDUDEF0
	uint16 AQM_MSDUDEF1
	uint16 AQM_PSMTXDSZ
	uint16 AQM_NDLIM
	uint16 AQM_MAXNDLIMLEN
	uint16 AQM_FRLENLIMIT
	uint16 AQM_FRFIXLEN
	uint16 AQM_2TDCCTL
	uint16 AQM_QFRTXCNT
	uint16 AQM_TOTACKCNT
	uint16 AQM_AGGR_PLDRDY
	uint16 AQM_AUTOBQC_EN
	uint16 AQM_AUTOBQC
	uint16 AQM_AUTOBQC_TO
	uint16 AQM_AUTOBQC_TOSTS
	uint16 AQM_AUTOBQC_TSCALE
	uint16 AQM_AUTOBQC_MAXTCNT
	uint16 AQMHWC_INPROG
	uint16 AQMHWC_STATUS
	uint16 AQM_DBGCTL1
	uint16 AQM_ERRSTSEN
	uint16 AQMFTM_CTL
	uint16 AQMFTM_MPDULEN
	uint16 AQMFTM_FLAG
	uint16 AQM_AUTOBQC_CONSDLY
	uint16 AQM_MUENGCTL
	uint16 TDC_NDLIM
	uint16 TDC_MAXNDLIMLEN
	uint16 TDC_CC34LEN
	uint16 TDC_NMURU
	uint16 TDC_MIMOSTS
	uint16 PSM_SCS_TAIL_CNT
	uint16 TXE_BMC_CMDPUSH_CNT
	uint16 TXE_BMC_CMDPOP_CNT
	uint16 TXE_MEND_SIG
	uint16 TXE_RST_TXMEND
	uint16 TXE_BMC_BQSEL
	uint16 TXE_BMC_WBCNT0
	uint16 TXE_BMC_WBCNT1
	uint16 TXE_XMTDMA_CNTSTS_CTL
	uint16 XMTDMA_QREQBYTE_CNT0
	uint16 XMTDMA_QREQBYTE_CNT1
	uint16 XMTDMA_QREQ_MPDU_CNT
	uint16 XMTDMA_UREQBYTE_CNT0
	uint16 XMTDMA_UREQBYTE_CNT1
	uint16 XMTDMA_QRESPBYTE_CNT0
	uint16 XMTDMA_QRESPBYTE_CNT1
	uint16 XMTDMA_QRESP_MPDU_CNT
	uint16 XMTDMA_DATAPRI_STS0
	uint16 XMTDMA_DATAPRI_STS1
	uint16 TXE_MEND_CTL
	uint16 TXE_MENDLAST_SIG
	uint16 TXE_BMC_WFCNT
	uint16 TXE_SIGBCC3_BASE
	uint16 TXE_SIGBCC4_BASE
	uint16 TXE_BMC_EOFCNT
	uint16 TXE_PPR_CFG0
	uint16 TXE_PPR_CFG1
	uint16 TXE_PPR_CFG2
	uint16 TXE_PPR_CFG3
	uint16 TXE_PPR_CFG4
	uint16 TXE_PPR_CFG5
	uint16 TXE_PPR_CFG6
	uint16 TXE_PPR_CFG7
	uint16 TXE_PPR_CFG8
	uint16 TXE_PPR_CFG9
	uint16 TXE_PPR_CFG10
	uint16 TXE_PPR_CFG11
	uint16 TXE_PPR_CFG12
	uint16 TXE_PPR_CFG13
	uint16 TXE_PPR_CFG14
	uint16 TXE_PPR_CFG15
	uint16 TXE_PPR_CFG16
	uint16 TXE_PPR_CTL0
	uint16 TXE_PPR_CTL1
	uint16 TXE_PPR_CTL2
	uint16 TXE_PPR_STAT0
	uint16 TXE_PPR_STAT1
	uint16 TXE_PPR_STAT2
	uint16 TXE_PPR_STAT3
	uint16 RXE_IFEVENTDBG_CTL
	uint16 RXE_IFEVENTDBG_STAT
	uint16 RXE_MEND_FLAT
	uint16 RXE_XFERACT_FLAT
	uint16 RXE_PHYFIFO_NOT_EMPTY_FLAT
	uint16 RXE_PFPLCP_WRDCNT
	uint16 RXE_RXDATA_NOT_EMPTY_FLAT
	uint16 RXE_PHYSTS_SHM_CTL
	uint16 RXE_RXBM_FATAL_ERRVAL
	uint16 RXE_RXBM_FATAL_ERRMASK
	uint16 RXE_PREBM_FATAL_ERRVAL
	uint16 RXE_PREBM_FATAL_ERRMASK
	uint16 RXE_CTXSTSFIFO_FATAL_ERRVAL
	uint16 RXE_CTXSTSFIFO_FATAL_ERRMASK
	uint16 RXE_POSTBM_FATAL_ERRVAL
	uint16 RXE_POSTBM_FATAL_ERRMASK
	uint16 RXQ_FATAL_ERR_RPTEN
	uint16 RXQ_FATAL_ERR
	uint16 RXE_RXFRMUP_TSF_L
	uint16 RXE_RXFRMUP_TSF_H
	uint16 RXE_RXFRMDN_TSF_L
	uint16 RXE_RXFRMDN_TSF_H
	uint16 RXE_RSF_NP_STATS
	uint16 RXE_RSF_HP_STATS
	uint16 RXE_POSTBM_TIMEOUT
	uint16 RDF_CTL8
	uint16 FP_DEBUG
	uint16 RXE_RXE2WEP_BYTES
	uint16 RXE_WEP2FP_BYTES
	uint16 RXE_RXE2BM_BYTES
	uint16 RXE_WCS_HDR_THRESHOLD
	uint16 RXE_WCS_MIN_THRESHOLD
	uint16 RXE_WCS_MAX_THRESHOLD
	uint16 RXE_DAGG_DEBUG
	uint16 RXE_BFDRPT_XFERPEND
	uint16 RXE_BFDRPT_XFERRD
	uint16 RXE_BFDRPT_XFERSTS
	uint16 RXE_BFDRPT_CAPSTS
	uint16 RXE_WCS_TOUT_THRESHOLD
	uint16 RXE_WCS_TOUT_STATUS
	uint16 RXE_WCS_CTL
	uint16 RXE_BMCLOOPBACK_DISCARD
	uint16 RXE_STRMRD_THRESHOLD
	uint16 RXE_RCM_XFERBMP
	uint16 RXE_WCS_COUNTERS
	uint16 RXE_WCS_DEBUG
	uint16 FP_STATUS6
	uint16 FP_ACKTYPETID_BITMAP
	uint16 RXE_PHYSTS_DEBUG1
	uint16 RXE_PHYSTS_DEBUG2
	uint16 RXE_PHYSTS_ADDR
	uint16 RXE_PHYSTS_DATA
	uint16 RXE_PHYSTS_FREE
	uint16 RXE_PHYSTS_CFG
	uint16 RXE_PHYSTS_DATA_L
	uint16 RXE_PHYSTS_DATA_H
	uint16 CBR_DBG_DATA
	uint16 PHYFIFO_SIZE_CFG
	uint16 PHYFIFO_SIZE_CFG1
	uint16 FP_MUBAR_CONFIG
	uint16 FP_MUBAR_TYPE_0
	uint16 FP_MUBAR_TYPE_1
	uint16 FP_MUBAR_TYPE_2
	uint16 FP_MUBAR_TYPE_3
	uint16 RXE_EOFPD_CNT
	uint16 RXE_EOFPD_THRSH
	uint16 RXE_AGGLEN_EST
	uint16 RXE_PFWRDCNT_CTL
	uint16 RXE_OPMODE_CFG
	uint16 RXE_DBG_CTL
	uint16 POSTBM_DBG_STS
	uint16 PREBM_DBG_STS
	uint16 RXE_RCVCTL2
	uint16 PSM_CHK0_EADDR
	uint16 PSM_CHK1_EADDR
FEATURE_END

