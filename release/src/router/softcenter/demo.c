//$(CC) $(CFLAGS) -D$(MODEL) -I$(TOP)/shared -I$(SRCBASE)/include -I$(SRCBASE)/shared/bcmwifi/include -L$(TOP_PLATFORM)/nvram$(BCMEX)${EX7} ${EXTRA_NV_LDFLAGS} -lnvram -I$(SRCBASE)/common/include -L$(TOP)/shared -L$(INSTALLDIR)/shared/usr/lib -lshared demo.c -o demo
//hnd//$(CC) $(CFLAGS) -D$(MODEL) -I$(TOP)/shared -I$(SRCBASE)/include -L$(TOP_PLATFORM)/nvram$(BCMEX)${EX7} ${EXTRA_NV_LDFLAGS} -lnvram -I$(SRCBASE)/common/include -L$(TOP)/shared -L$(INSTALLDIR)/shared/usr/lib -lshared demo.c -o demo
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <shared.h>

struct tcode_list_s {
	int modelid;
	char *model;
	char *tcode;
	char *key;
	char *value;
#if defined(RTAC68U)
	int  hwflag;
#endif
};

struct odmpid_rc_list_s {
	int modelid;
	char *odmpid;
	char *tcode;
	char *value;
};

struct tcode_location_s {
	int modelid;
	char *tcode;
	char *formot;
	int idx_base;
	char *ccode1;
	char *regrev1;
	char *ccode2;
	char *regrev2;
	char *ccode3;
	char *regrev3;
#if defined(RTAC68U)
	int hw_flag;
#endif
};
struct tcode_lang_s {
	int modelid;
	char *odmpid;
	char *tcode;
	char *support_lang;
	int auto_change;
};

struct tcode_langcode_s {
	int modelid;
	char *tcode;
	char *lang_list;
	char *location;
};

struct location_init_s {
	int modelid;
	char *model;
	char *tcode;
	char *key;
	char *value;
};

struct tcode_rc_s {
	int modelid;
	char *tcode;
	char *value;
#if defined(RTAC68U)
	int hw_flag;
#endif
};

struct ctrl_s {
	int modelid;
};

extern const struct tcode_list_s tcode_init_nvram_list[];
extern const struct tcode_location_s tcode_location_list[];
#if defined(RTCONFIG_BCM_7114) || defined(GTAC5300)
#if !defined(GTAC5300)
extern const struct tcode_location_s legacy_tcode_location_list[];
#endif
extern const struct tcode_location_s asusctrl_tcode_location_list[];
#endif
extern const struct tcode_lang_s tcode_lang_list[];
extern const struct tcode_langcode_s tcode_langcode_list[];
extern const struct location_init_s location_init_nvram_list[];
extern const struct tcode_rc_s tcode_rc_support_list[];
extern const struct tcode_rc_s tcode_del_rc_support_list[];
#if defined(RTCONFIG_BCM_7114) || defined(GTAC5300)
extern int asus_ctrl_models();
extern int asus_ctrl_ignore();
extern int asus_ctrl_nv(char *asusctrl);
extern int asus_ctrl_en(int cid);
#endif

struct model_s {
	char *pid;
	int model;
};

static const struct model_s model_list[] = {
	{ "MODEL_GENERIC", MODEL_GENERIC },
	{ "MODEL_UNKNOWN", MODEL_UNKNOWN },
	{ "MODEL_DSLN55U", MODEL_DSLN55U },
	{ "MODEL_DSLAC68U", MODEL_DSLAC68U },
	{ "MODEL_EAN66", MODEL_EAN66 },
	{ "MODEL_RTN11P", MODEL_RTN11P },
	{ "MODEL_RTN300", MODEL_RTN300 },
	{ "MODEL_RTN13U", MODEL_RTN13U },
	{ "MODEL_RTN14U", MODEL_RTN14U },
	{ "MODEL_RTAC52U", MODEL_RTAC52U },
	{ "MODEL_RTAC51U", MODEL_RTAC51U },
	{ "MODEL_RTN54U", MODEL_RTN54U },
	{ "MODEL_RTAC54U", MODEL_RTAC54U },
	{ "MODEL_RTN56UB1", MODEL_RTN56UB1 },
	{ "MODEL_RTN56UB2", MODEL_RTN56UB2 },
	{ "MODEL_RTAC1200HP", MODEL_RTAC1200HP },
	{ "MODEL_RTAC55U", MODEL_RTAC55U },
	{ "MODEL_RTAC55UHP", MODEL_RTAC55UHP },
	{ "MODEL_RT4GAC55U", MODEL_RT4GAC55U },
	{ "MODEL_RTAC59U", MODEL_RTAC59U },
	{ "MODEL_PLN12", MODEL_PLN12 },
	{ "MODEL_PLAC56", MODEL_PLAC56 },
	{ "MODEL_PLAC66U", MODEL_PLAC66U },
	{ "MODEL_RTAC58U", MODEL_RTAC58U },
	{ "MODEL_RT4GAC53U", MODEL_RT4GAC53U },
	{ "MODEL_RTAC82U", MODEL_RTAC82U },
	{ "MODEL_MAPAC1300", MODEL_MAPAC1300 },
	{ "MODEL_MAPAC2200", MODEL_MAPAC2200 },
	{ "MODEL_MAPAC2200", MODEL_MAPAC2200 },
	{ "MODEL_MAPAC1750", MODEL_MAPAC1750 },
	{ "MODEL_RTAC95U", MODEL_RTAC95U },
	{ "MODEL_MAPAC2200V", MODEL_MAPAC2200V },
	{ "MODEL_RTN36U3", MODEL_RTN36U3 },
	{ "MODEL_RTN56U", MODEL_RTN56U },
	{ "MODEL_RTN65U", MODEL_RTN65U },
	{ "MODEL_RTN67U", MODEL_RTN67U },
	{ "MODEL_RTN12", MODEL_RTN12 },
	{ "MODEL_RTN12B1", MODEL_RTN12B1 },
	{ "MODEL_RTN12C1", MODEL_RTN12C1 },
	{ "MODEL_RTN12D1", MODEL_RTN12D1 },
	{ "MODEL_RTN12VP", MODEL_RTN12VP },
	{ "MODEL_RTN12HP", MODEL_RTN12HP },
	{ "MODEL_RTN12HP_B1", MODEL_RTN12HP_B1 },
	{ "MODEL_APN12", MODEL_APN12 },
	{ "MODEL_APN12HP", MODEL_APN12HP },
	{ "MODEL_RTN16", MODEL_RTN16 },
	{ "MODEL_RTN18U", MODEL_RTN18U },
	{ "MODEL_RTN15U", MODEL_RTN15U },
	{ "MODEL_RTN53", MODEL_RTN53 },
	{ "MODEL_RTN66U", MODEL_RTN66U },
	{ "MODEL_RTAC66U", MODEL_RTAC66U },
	{ "MODEL_RTAC68U", MODEL_RTAC68U },
	{ "MODEL_UNUSED", MODEL_UNUSED(62) },
	{ "MODEL_RTAC87U", MODEL_RTAC87U },
	{ "MODEL_RTAC56S", MODEL_RTAC56S },
	{ "MODEL_RTAC56U", MODEL_RTAC56U },
	{ "MODEL_RTAC53U", MODEL_RTAC53U },
	{ "MODEL_RTAC3200", MODEL_RTAC3200 },
	{ "MODEL_RTAC88U", MODEL_RTAC88U },
	{ "MODEL_RTAC3100", MODEL_RTAC3100 },
	{ "MODEL_RTAC5300", MODEL_RTAC5300 },
	{ "MODEL_GTAC5300", MODEL_GTAC5300 },
	{ "MODEL_RTN14UHP", MODEL_RTN14UHP },
	{ "MODEL_RTN10U", MODEL_RTN10U },
	{ "MODEL_RTN10P", MODEL_RTN10P },
	{ "MODEL_RTN10D1", MODEL_RTN10D1 },
	{ "MODEL_RTN10PV2", MODEL_RTN10PV2 },
	{ "MODEL_RTAC1200", MODEL_RTAC1200 },
	{ "MODEL_RTAC1200G", MODEL_RTAC1200G },
	{ "MODEL_RTAC1200GP", MODEL_RTAC1200GP },
	{ "MODEL_RTAC1200GA1", MODEL_RTAC1200GA1 },
	{ "MODEL_RTAC1200GU", MODEL_RTAC1200GU },
	{ "MODEL_RPAC66", MODEL_RPAC66 },
	{ "MODEL_RPAC51", MODEL_RPAC51 },
	{ "MODEL_RTAC51UP", MODEL_RTAC51UP },
	{ "MODEL_RTAC53", MODEL_RTAC53 },
	{ "MODEL_RTN11P_B1", MODEL_RTN11P_B1 },
	{ "MODEL_RPAC87", MODEL_RPAC87 },
	{ "MODEL_RTAC85U", MODEL_RTAC85U },
	{ "MODEL_RTAC85P", MODEL_RTAC85P },
	{ "MODEL_RTACRH26", MODEL_RTACRH26 },
	{ "MODEL_RTN800HP", MODEL_RTN800HP },
	{ "MODEL_RTAC88N", MODEL_RTAC88N },
	{ "MODEL_BRTAC828", MODEL_BRTAC828 },
	{ "MODEL_RTAC88S", MODEL_RTAC88S },
	{ "MODEL_RPAC53", MODEL_RPAC53 },
	{ "MODEL_RPAC68U", MODEL_RPAC68U },
	{ "MODEL_RPAC55", MODEL_RPAC55 },
	{ "MODEL_RTAC86U", MODEL_RTAC86U },
	{ "MODEL_GTAC9600", MODEL_GTAC9600 },
	{ "MODEL_BLUECAVE", MODEL_BLUECAVE },
	{ "MODEL_RTAD7200", MODEL_RTAD7200 },
	{ "MODEL_GTAXY16000", MODEL_GTAXY16000 },
	{ "MODEL_GTAX6000N", MODEL_GTAX6000N },
	{ "MODEL_RTAX89U", MODEL_RTAX89U },
	{ "MODEL_RTAC1200V2", MODEL_RTAC1200V2 },
	{ "MODEL_RTN19", MODEL_RTN19 },
	{ "MODEL_TUFAC1750", MODEL_TUFAC1750 },
	{ "MODEL_RTAX88U", MODEL_RTAX88U },
	{ "MODEL_GTAX11000", MODEL_GTAX11000 },
	{ "MODEL_RTAX92U", MODEL_RTAX92U },
	{ "MODEL_RTAX95Q", MODEL_RTAX95Q },
	{ "MODEL_RTAXE95Q", MODEL_RTAXE95Q },
	{ "MODEL_RTAX56_XD4", MODEL_RTAX56_XD4 },
	{ "MODEL_RTAX58U", MODEL_RTAX58U },
	{ "MODEL_RTAX56U", MODEL_RTAX56U },
	{ "MODEL_RPAX56", MODEL_RPAX56 },
	{ "MODEL_SHAC1300", MODEL_SHAC1300 },
	{ "MODEL_RPAC92", MODEL_RPAC92 },
	{ "MODEL_RTAC59CD6R", MODEL_RTAC59CD6R },
	{ "MODEL_RTAC59CD6N", MODEL_RTAC59CD6N },
	{ "MODEL_RTAX86U", MODEL_RTAX86U },
	{ "MODEL_RTAX68U", MODEL_RTAX68U },
	{ "MODEL_RT4GAC56", MODEL_RT4GAC56 },
	{ "MODEL_DSLAX82U", MODEL_DSLAX82U },
	{ "MODEL_RTAX55", MODEL_RTAX55 },
	{ "MODEL_GTAXE11000", MODEL_GTAXE11000 },
	{ "MODEL_RTACRH18", MODEL_RTACRH18 },
	{ "MODEL_PLAX56XP4", MODEL_PLAX56XP4 },
	{ "MODEL_CTAX56_XD4", MODEL_CTAX56_XD4 },
	{ "MODEL_RTAC68U_V4", MODEL_RTAC68U_V4 },
	{ "MODEL_MAX", MODEL_MAX },
};

char *show_modelid(int model)
{
	char *pid = "UNKNOWN ID";
	const struct model_s *p;

	for (p = &model_list[0]; p->pid; ++p) {
		if (model == p->model) {
			pid = p->pid;
			break;
		}
	}
	return pid;
}

int main()
{
	const struct tcode_list_s *list;
	const struct tcode_location_s *list1;
	const struct tcode_lang_s *list2;
	const struct tcode_langcode_s *list3;
	const struct location_init_s *list4;
	const struct tcode_rc_s *list5;
	printf("tcode_init_nvram_list\n");
	for ( list = &tcode_init_nvram_list[0]; list->key; list++)
	{
#if defined(RTAC68U)
		printf("modelid=%s,model=%s,tcode=%s,key=%s,value=%s,hwflag=%d\n",show_modelid(list->modelid),list->model,list->tcode,list->key,list->value,list->hwflag);
#else
		printf("modelid=%s,model=%s,tcode=%s,key=%s,value=%s\n",show_modelid(list->modelid),list->model,list->tcode,list->key,list->value);
#endif
	}
	printf("tcode_location_list\n");
	for ( list1 = &tcode_location_list[0]; list1->tcode; list1++)
	{
#if defined(RTAC68U)
		printf("modelid=%s,tcode=%s,formot=%s,idx_base=%d,ccode1=%s,regrev1=%s,ccode2=%s,regrev2=%s,ccode3=%s,regrev3=%s,hw_flag=%d\n",show_modelid(list1->modelid),list1->tcode,list1->formot,list1->idx_base,list1->ccode1,list1->regrev1,list1->ccode2,list1->regrev2,list1->ccode3?:"NULL",list1->regrev3?:"NULL",list1->hw_flag);
#else
		printf("modelid=%s,tcode=%s,formot=%s,idx_base=%d,ccode1=%s,regrev1=%s,ccode2=%s,regrev2=%s,ccode3=%s,regrev3=%s\n",show_modelid(list1->modelid),list1->tcode,list1->formot,list1->idx_base,list1->ccode1,list1->regrev1,list1->ccode2,list1->regrev2,list1->ccode3?:"NULL",list1->regrev3?:"NULL");
#endif
	}
#if defined(RTCONFIG_BCM_7114) || defined(GTAC5300)
#if !defined(GTAC5300)
	printf("legacy_tcode_location_list\n");
	for ( list1 = &legacy_tcode_location_list[0]; list1->tcode; list1++)
	{
		printf("modelid=%s,tcode=%s,formot=%s,idx_base=%d,ccode1=%s,regrev1=%s,ccode2=%s,regrev2=%s,ccode3=%s,regrev3=%s\n",show_modelid(list1->modelid),list1->tcode,list1->formot,list1->idx_base,list1->ccode1,list1->regrev1,list1->ccode2,list1->regrev2,list1->ccode3?:"NULL",list1->regrev3?:"NULL");
	}
#endif
	printf("asusctrl_tcode_location_list\n");
	for ( list1 = &asusctrl_tcode_location_list[0]; list1->tcode; list1++)
	{
		printf("modelid=%s,tcode=%s,formot=%s,idx_base=%d,ccode1=%s,regrev1=%s,ccode2=%s,regrev2=%s,ccode3=%s,regrev3=%s\n",show_modelid(list1->modelid),list1->tcode,list1->formot,list1->idx_base,list1->ccode1,list1->regrev1,list1->ccode2,list1->regrev2,list1->ccode3?:"NULL",list1->regrev3?:"NULL");

	}
#endif
#if 1
	printf("tcode_lang_list\n");
	for ( list2 = &tcode_lang_list[0]; list2->tcode; list2++)
	{
		printf("modelid=%s,odmpid=%s,tcode=%s,support_lang=%s,auto_change=%d\n",show_modelid(list2->modelid),list2->odmpid?:"NULL",list2->tcode,list2->support_lang,list2->auto_change);
	}
	printf("tcode_langcode_list\n");
	for ( list3 = &tcode_langcode_list[0]; list3->tcode; list3++)
	{
		printf("modelid=%s,tcode=%s,lang_list=%s,location=%s\n",show_modelid(list3->modelid),list3->tcode,list3->lang_list,list3->location);
	}
	printf("location_init_nvram_list\n");
	for ( list4 = &location_init_nvram_list[0]; list4->tcode; list4++)
	{
		printf("modelid=%s,model=%s,tcode=%s,key=%s,value=%s\n",show_modelid(list4->modelid),list4->model,list4->tcode,list4->key,list4->value);
	}
	printf("tcode_rc_support_list\n");
	for ( list5 = &tcode_rc_support_list[0]; list5->tcode; list5++)
	{
#if defined(RTAC68U)
		printf("modelid=%s,tcode=%s,value=%s,hw_flag=%d\n",show_modelid(list5->modelid),list5->tcode,list5->value,list5->hw_flag);
#else
		printf("modelid=%s,tcode=%s,value=%s\n",show_modelid(list5->modelid),list5->tcode,list5->value);
#endif
	}
	printf("tcode_del_rc_support_list\n");
	for ( list5 = &tcode_del_rc_support_list[0]; list5->tcode; list5++)
	{
#if defined(RTAC68U)
		printf("modelid=%s,tcode=%s,value=%s,hw_flag=%d\n",show_modelid(list5->modelid),list5->tcode,list5->value,list5->hw_flag);
#else
		printf("modelid=%s,tcode=%s,value=%s\n",show_modelid(list5->modelid),list5->tcode,list5->value);
#endif
	}
#endif
#if defined(RTCONFIG_BCM_7114) || defined(GTAC5300)
	printf("asus_ctrl_models()=%d\n",asus_ctrl_models());
	printf("asus_ctrl_ignore()=%d\n",asus_ctrl_ignore());
	char *nv="0x2s";
	printf("asus_ctrl_nv()=%d,%s\n",asus_ctrl_nv(nv),nv);
	printf("asus_ctrl_en()=%d\n",asus_ctrl_en(1));
#endif
	return 0;
}
