obj-$(CONFIG_BCM_BDMF) = bdmf.o

bdmf-objs += bdmf_dep.o

$(obj)/bdmf_dep.o:
ifeq ($(CONFIG_BCM96855),y)
	cp $(obj)/bdmf_6855.o $(obj)/bdmf_dep.o
else
	cp $(obj)/bdmf_4912.o $(obj)/bdmf_dep.o
endif

applinks:

