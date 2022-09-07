#!/bin/sh
REPO=/home/paldier/release/asuswrt-bcm

build_link(){
	[ ! -d RT-AC68U ] && ln -sf BCM470X RT-AC68U
	[ ! -d RT-AC88U ] && ln -sf BCM470X RT-AC88U
	[ ! -d RT-AC3100 ] && ln -sf BCM470X RT-AC3100
	[ ! -d RT-AC5300 ] && ln -sf BCM470X RT-AC5300
	[ ! -d RT-AC86U ] && ln -sf BCM490X_AC RT-AC86U
	[ ! -d GT-AC2900 ] && ln -sf BCM490X_AC GT-AC2900
	[ ! -d GT-AC5300 ] && ln -sf BCM490X_AC GT-AC5300
	[ ! -d RT-AX55 ] && ln -sf BCM675X RT-AX55
	[ ! -d RT-AX56U ] && ln -sf BCM675X RT-AX56U
	[ ! -d RT-AX58U ] && ln -sf BCM675X RT-AX58U
	[ ! -d RT-AX82U ] && ln -sf BCM675X RT-AX82U
	[ ! -d RT-AX95Q ] && ln -sf BCM675X RT-AX95Q
	[ ! -d RT-AXE95Q ] && ln -sf BCM675X RT-AXE95Q
	[ ! -d TUF-AX3000 ] && ln -sf BCM675X TUF-AX3000
	[ ! -d TUF-AX5400 ] && ln -sf BCM675X TUF-AX5400
	[ ! -d RT-AX88U ] && ln -sf BCM490X_AX RT-AX88U
	[ ! -d RT-AX92U ] && ln -sf BCM490X_AX RT-AX92U
	[ ! -d GT-AX11000 ] && ln -sf BCM490X_AX GT-AX11000
	[ ! -d RT-AX68U ] && ln -sf BCM490X_AX RT-AX68U
	[ ! -d RT-AX86U ] && ln -sf BCM490X_AX RT-AX86U
	[ ! -d GT-AXE11000 ] && ln -sf BCM490X_AX GT-AXE11000
	[ ! -d GT-AX6000 ] && ln -sf BCM491X GT-AX6000
	[ ! -d GT-AXE16000 ] && ln -sf BCM490X_AX GT-AXE16000
	[ ! -d GT-AX11000_PRO ] && ln -sf BCM490X_AX GT-AX11000_PRO
	[ ! -d XT12 ] && ln -sf BCM490X_AX XT12
}

cd $REPO/release/src/router/aaews/prebuild/ && build_link
cd $REPO/release/src/router/asusnatnl/natnl/prebuild/ && build_link
cd $REPO/release/src/router/asuswebstorage/prebuild/ && build_link
cd $REPO/release/src/router/bsd/prebuilt/ && build_link
cd $REPO/release/src/router/dhd/prebuilt/ && build_link
cd $REPO/release/src/router/dropbox_client/prebuild/ && build_link
cd $REPO/release/src/router/eventd/prebuilt/ && build_link
cd $REPO/release/src/router/ftpclient/prebuild/ && build_link
cd $REPO/release/src/router/infosvr/prebuild/ && build_link
cd $REPO/release/src/router/inotify/prebuild/ && build_link
cd $REPO/release/src/router/libbcm/prebuilt/ && build_link
cd $REPO/release/src/router/libletsencrypt/prebuild/ && build_link
cd $REPO/release/src/router/lighttpd-1.4.39/prebuild/ && build_link
cd $REPO/release/src/router/networkmap/prebuild/ && build_link
cd $REPO/release/src/router/nt_center/actMail/prebuild/ && build_link
cd $REPO/release/src/router/nt_center/lib/prebuild/ && build_link
cd $REPO/release/src/router/nt_center/prebuild/ && build_link
cd $REPO/release/src/router/protect_srv/lib/prebuild/ && build_link
cd $REPO/release/src/router/protect_srv/prebuild/ && build_link
cd $REPO/release/src/router/sambaclient/prebuild/ && build_link
cd $REPO/release/src/router/sysstate/commands/prebuild/ && build_link
cd $REPO/release/src/router/sysstate/log_daemon/prebuild/ && build_link
cd $REPO/release/src/router/u2ec/prebuild/ && build_link
cd $REPO/release/src/router/usbclient/prebuild/ && build_link
cd $REPO/release/src/router/wb/prebuild/ && build_link
cd $REPO/release/src/router/webdav_client/prebuild/ && build_link
cd $REPO/release/src/router/wlc_nt/prebuild/ && build_link
cd $REPO/release/src/router/dblog/commands/prebuild/ && build_link
cd $REPO/release/src/router/dblog/daemon/prebuild/ && build_link
cd $REPO/release/src/router/libasuslog/prebuild/ && build_link



