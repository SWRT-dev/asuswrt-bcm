#!/bin/sh

#
# USAGE:
#  - Use <FTP/HTTP> protocol to download the MFG NVRAM file <bcm94908bifr.nvm>
#    from FTP/HTTP server on the HOST PC with IP address <192.168.1.100>
#
#      CFE> kernp mfg_nvram_mode=1 mfg_nvram_url=ftp://192.168.1.100/bcm94908bifr.nvm
#      CFE> kernp mfg_nvram_mode=1 mfg_nvram_url=http://192.168.1.100/bcm94908bifr.nvm
#
#  - Use <TFTP> protocol to download the MFG NVRAM file <bcm94908bifr.nvm>
#    from TFTP server on the HOST PC with IP address <192.168.1.100>
#
#      CFE> kernp mfg_nvram_mode=1 mfg_nvram_url=tftp://192.168.1.100/bcm94908bifr.nvm
#


#
# Variables
#
MFG_NVRAM_MTD_PARTITION=misc1
MFG_NVRAM_DIR=/mnt/nvram
MFG_NVRAM_TMP_DIR=/var/tmp/nvram
MFG_NVRAM_FILE=nvram.nvm
MFG_NVRAM_FILEPATH=$MFG_NVRAM_DIR/$MFG_NVRAM_FILE
#
# Indicates nvram mfg mode.
# Created as a result of CFE> kernp mfg_nvram_mode=1
MFG_NVRAM_MODE_FILEPATH=/proc/brcm/blxparms/mfg_nvram_mode
#
# Indicates nvram mfg mode debug.
# Created as a result of CFE> kernp mfg_nvram_mode_debug=1
MFG_NVRAM_MODE_DEBUG_FILEPATH=/proc/brcm/blxparms/mfg_nvram_mode_debug
is_mfg_nvram_mode_dbg=0
#
# Indicates nvram file URL.
# Created as a result of CFE> kernp mfg_nvram_url=ftp://<hostip>/<nvram_file>
MFG_NVRAM_URL_FILEPATH=/proc/brcm/blxparms/mfg_nvram_url
MFG_NVRAM_TMP_URL_FILEPATH=/var/tmp/mfg_nvram_url

# Protocol to download the nvram file (ftp or tftp)
MFG_NVRAM_URL_PROTO=""
# IP address of mfg host PC
MFG_NVRAM_URL_IP=""
# mfg nvram file hame on host PC
MFG_NVRAM_URL_FILE=""

#
# Board default IP address and mask
TARGET_IP=192.168.1.1
TARGET_NETMASK=255.255.255.0
#
# max number of pings for network verification.
MFG_PING_RETRY_LIMIT=7

#
# Fatal error message strings
#
MSG_FATAL_NVRAMURL=$(cat <<-END
    *** Cannot find URL ***.

    Make sure mfg_nvram_url=<URL> tuple is specified as one the
    kernp arguments.
    URL format is: <proto>://<host IP address>/<nvram file name>
    where <proto> is 'ftp' or 'tftp'.

    Example:
      kernp mfg_nvram_mode=1 mfg_nvram_url=ftp://192.168.1.100/bcm94908bifr.nvm
    or
      kernp mfg_nvram_mode=1 mfg_nvram_url=tftp://192.168.1.100/bcm94908bifr.nvm
END
 )

MSG_FATAL_MISCPARTITION=$(cat <<-END
    ***  Cannot find $MFG_NVRAM_MTD_PARTITION partitiont ***.

    Make sure that '$MFG_NVRAM_MTD_PARTITION' partition size in CFEROM image embedded NVRAM
    has been configured.
    Tf so, then make sure that '$MFG_NVRAM_MTD_PARTITION' partition size is specifed in CFEROM
    NVRAM on the NANAD flash.
    Use CFERAM 'c' command to specify $MFG_NVRAM_MTD_PARTITION partition size in CFEROM
    NVRAM on the NANAD flash.
END
)

MSG_FATAL_WGET=$(cat <<-END
    ***  WGET failed. ***.

    Make sure that FTP/HTTP server is up and running on the HOST PC.
    If so, then make sure IP address and mfg file name in URL
    in correct and mfg file exists in  FTP/HTTP server directory
    on the HOST PC.
END
)

MSG_FATAL_TFTP=$(cat <<-END
    ***  TFTP client failed. ***.

    Make sure that TFTP server is up and running on the HOST PC.
    If so, then make sure IP address and mfg file name in URL
    in correct and mfg file exists in TFTP server directory
    on the HOST PC.
END
)


MSG_FATAL_DNLD=$(cat <<-END
    ***  Failed to download mfg nvram file. ***.

    Make sure nvram directory is mounted properly.
    From emergency CLI use command "ls -al /mnt/nvram" to verify
    if directory exists and empty.
END
)

MSG_FATAL_NETTEST=$(cat <<-END
    ***  Network test failed ***.

    Make sure Ethernet network cable is plugged in properly between HOST PC and
    the board. Verify that HOST PC Ethernet IP addredd is setted up same as specified
    in the URL.   
END
)

MSG_FATAL_BASEMACADDR=$(cat <<-END
    ***  Cannot get Base MAC Address from NVRAM ***

    Make sure the Manufacturing NVRAM template contains the variable
    'et0macaddr' and it has proper MAC address value.
    If so, make sure that 'envrams' daemon is running:
      from emergency CLI type: 'ps | grep nvrams'
END
)

MSG_FATAL_NVRAMURL_PROTO=$(cat <<-END
    *** Bad protocol is specified in URL ***.

    Make sure mfg_nvram_url=<URL> tuple is specified as one the
    kernp arguments.
    URL format is: <proto>://<host IP address>/<nvram file name>
    where <proto> is 'ftp', 'http' or 'tftp'.

    Example:
      kernp mfg_nvram_mode=1 mfg_nvram_url=ftp://192.168.1.100/bcm94908bifr.nvm
      kernp mfg_nvram_mode=1 mfg_nvram_url=http://192.168.1.100/bcm94908bifr.nvm
    or
      kernp mfg_nvram_mode=1 mfg_nvram_url=tftp://192.168.1.100/bcm94908bifr.nvm
END
 )

MSG_FATAL_NVRAMURL_IPADDR=$(cat <<-END
    *** Bad IP address is specified in URL ***.

    Make sure mfg_nvram_url=<URL> tuple is specified as one the
    kernp arguments.
    URL format is: <proto>://<host IP address>/<nvram file name>
    where <proto> is 'ftp', 'http' or 'tftp'.

    Example:
      kernp mfg_nvram_mode=1 mfg_nvram_url=ftp://192.168.1.100/bcm94908bifr.nvm
      kernp mfg_nvram_mode=1 mfg_nvram_url=http://192.168.1.100/bcm94908bifr.nvm
    or
      kernp mfg_nvram_mode=1 mfg_nvram_url=tftp://192.168.1.100/bcm94908bifr.nvm
END
 )

MSG_FATAL_NVRAMURL_HOSTFILE=$(cat <<-END
    *** Bad host nvram file name is specified in URL ***.

    Make sure mfg_nvram_url=<URL> tuple is specified as one the
    kernp arguments.
    URL format is: <proto>://<host IP address>/<nvram file name>
    where <proto> is 'ftp', 'http' or 'tftp'.

    Example:
      kernp mfg_nvram_mode=1 mfg_nvram_url=ftp://192.168.1.100/bcm94908bifr.nvm
      kernp mfg_nvram_mode=1 mfg_nvram_url=http://192.168.1.100/bcm94908bifr.nvm
    or
      kernp mfg_nvram_mode=1 mfg_nvram_url=tftp://192.168.1.100/bcm94908bifr.nvm
END
 )

#
# Functions
#

#
# Inster module into kernel with verification of
# file existence before loading. If kernel module
# doesn't exist then do nothing.
# Throwing fatal error (ending up with reboot) if
# insmod fails.
#
# Parameters:
#   First parameter: is the kernel module file name_path
#   Second parameter: (optional) is a kernel module
#                     ALL parameters composed in single string.
# Example:
#   mfg_insmod "/dir/module.ko" "param1=val1 param2=val2 ... paramN=valN"
#                     
mfg_insmod()
{
    ins_mod=1
    echo ""
    echo "loading [$1 $2] ... "
    #if [ $is_mfg_nvram_mode_dbg == 1 ]; then
	#yes_no_confirmation
	#ins_mod=$?
    #fi
    
    if [ -e $1 ]; then
	
	if [ $ins_mod == 1 ]; then
	    insmod $1 $2 > /dev/null 2>/dev/null || error_exit "$0: insmod $1 failed"
	    echo "[$1] loaded"
	else
	    echo "[$1] skipped"
	fi
	
    else
	
	echo "[$1] dosn't exist."
	
    fi
    return 0
}

#
# Handling a fatal error by printing optional error
# message specified as a first argument.
# Entering shell for diagnostic purpose.
# After exiting the shell with 'exit' command do the
# system reboot.
#
mfg_fatal()
{
    echo $'\n\n'"$1"$'\n\n'
    
    # offering bash CLI for diagnostic
    echo $'\n\nEntering emergency mode. Exit the shell to reboot the system.\n\n'
    /bin/bash -i
    
    # System rebooting. Do not allow farther execution.
    reboot -f
}

#
# Verifying return value of previously executed command
# and throw fatal error if the command is not succeeded.
# In case of error this funciton will never return and
# will endup with system reboot.
#
error_exit()
{
    if [ "$?" != "0" ]; then
	mfg_fatal "*** ERROR $1"
    fi
}

#
# Return values:
#  1 - [Yy]
#  0 - [Nn]
#
yes_no_confirmation() {
    while true; do
	echo ""
	echo ""
	read -p ">> Do you want to continue ... ? " yn
	case $yn in
            [Yy]* ) return 1;;
            [Nn]* ) return 0;;
            * ) echo "Please answer yes or no.";;
	esac
    done
}

#
# Parse URL.
# Store protocol, host IP address and host nvram file name
# in dedicated variables.
#
mfg_parse_url()
{
    MFG_NVRAM_URL=""

    if [ ! -e $MFG_NVRAM_URL_FILEPATH ]; then
	mfg_fatal "[$0]: $MSG_FATAL_NVRAMURL"
   else
	MFG_NVRAM_URL=$(cat $MFG_NVRAM_URL_FILEPATH)
   fi
    
    # The typical mfg nvram URL string looks like this:
    # For example: 
    #           "ftp://192.168.1.100/bcm94908bifr.nvm"
    #           "http://192.168.1.100/bcm94908bifr.nvm"
    #           "tftp://192.168.1.100/bcm94908bifr.nvm"

    # Get protocol.
    # strip everything start with the first ':' till the end of the string.
    MFG_NVRAM_URL_PROTO=$MFG_NVRAM_URL
    MFG_NVRAM_URL_PROTO=${MFG_NVRAM_URL_PROTO/:*/}
    # Validate protocol
    if [ "${MFG_NVRAM_URL_PROTO}" != "ftp" ] && [ "${MFG_NVRAM_URL_PROTO}" != "tftp" ] && [ "${MFG_NVRAM_URL_PROTO}" != "http" ]
    then
	mfg_fatal "[$0]: $MSG_FATAL_NVRAMURL_PROTO"
    else
	echo "[$0]: Host protocol: <$MFG_NVRAM_URL_PROTO>"
    fi

    # strip everything before IP address(192.168.1.100)
    # will get "192.168.1.100/bcm94908bifr.nvm"
    MFG_NVRAM_URL=${MFG_NVRAM_URL#*\/\/}
    
    # Get ip address.
    # strip everything start with the first '/' till the end of the string.
    MFG_NVRAM_URL_IP=$MFG_NVRAM_URL
    MFG_NVRAM_URL_IP=${MFG_NVRAM_URL_IP/\/*/}
    # Validate IP
    [[ -z "${MFG_NVRAM_URL_IP// }" ]] && mfg_fatal "$0: $MSG_FATAL_NVRAMURL_IPADDR"
    echo "[$0]: Host IP address: <$MFG_NVRAM_URL_IP>"

    # strip IP addr and following '/' from the URL: <192.168.1.100/>
    MFG_NVRAM_URL=${MFG_NVRAM_URL/${MFG_NVRAM_URL_IP}/}
    MFG_NVRAM_URL=${MFG_NVRAM_URL#*\/}

    # Get file name. (this is the last substring in the URL)
    MFG_NVRAM_URL_FILE=$MFG_NVRAM_URL
    # Validate host file name
    [[ -z "${MFG_NVRAM_URL_FILE// }" ]] && mfg_fatal "$0: $MSG_FATAL_NVRAMURL_HOSTFILE"
    echo "[$0]: Host file name: <$MFG_NVRAM_URL_FILE>"
}

#
# Download mfg nvram file from FTP or TFTP server.
#
mfg_download_nvram_file()
{
    URL=$(cat $MFG_NVRAM_URL_FILEPATH)
    echo "[$0]: Downloading MFG NVRAM file <URL=$URL>"

    if [ "${MFG_NVRAM_URL_PROTO}" == "ftp" ] || [ "${MFG_NVRAM_URL_PROTO}" == "http" ]
    then
	wget $URL -P $MFG_NVRAM_TMP_DIR -O $MFG_NVRAM_TMP_DIR/$MFG_NVRAM_FILE || mfg_fatal "$0: $MSG_FATAL_WGET"
    fi

    if [ "${MFG_NVRAM_URL_PROTO}" == "tftp" ]
    then
	tftp -g -l $MFG_NVRAM_TMP_DIR/$MFG_NVRAM_FILE -r $MFG_NVRAM_URL_FILE $MFG_NVRAM_URL_IP || mfg_fatal "$0: $MSG_FATAL_TFTP"
    fi

    if [ ! -f $MFG_NVRAM_TMP_DIR/$MFG_NVRAM_FILE ]
    then
	mfg_fatal "$0: $MSG_FATAL_DNLD"
    else
	echo "[$0]: '$MFG_NVRAM_TMP_DIR'/'$MFG_NVRAM_FILE' file downloaded successfully."
    fi
}

mfg_init()
{
    echo "$0: Initializing. [is_mfg_nvram_mode_dbg=$is_mfg_nvram_mode_dbg]"

    #
    # MDEV and hotplug:
    #
    # Configure hotplug handler
    echo /sbin/mdev > /proc/sys/kernel/hotplug
    # Initialize and run mdev to crete dynamic device nodes
    echo "$0: Starting mdev."
    /sbin/mdev -s
    
    mkdir /var/tmp || error_exit "$0: mkdir failed"
    mkdir $MFG_NVRAM_DIR || error_exit "$0: mkdir failed"
    mkdir $MFG_NVRAM_TMP_DIR || error_exit "$0: mkdir failed"

    # Parse URL.
    mfg_parse_url

    echo "$0: Done"
}

#
# Do system reboot
# Options:
#  --iteractive - Entering iteractive mode.
#                 Will wait for reboot confirmation.
#                 If confirmed with "y", then rebooting
#                 If not confirmed with "n", then entering bash CLI.
#
mfg_reboot()
{
    reboot=1

    echo "System is goint to reboot ..."
    # iteractive mode. for debugging purpose
    if [ "$1" == "--iteractive" ]; then
	yes_no_confirmation
	reboot=$?
	if [ $reboot == 1 ]; then
	    reboot -f # System reboot
	else
	    /bin/bash -i
	fi
    fi

    [ $reboot == 1 ] && reboot -f # System reboot
}

mfg_program_nvram()
{
    echo "[$0]: Programming manufacturing NVRAM file to NAND flash ..."
    if MTD=`grep $MFG_NVRAM_MTD_PARTITION /proc/mtd`;
    then

	#
	# Downloading mfg NVRAM file from HOST PC.
	#
	mfg_download_nvram_file

	#
	# Creating UBI volume
	#
	MTD=${MTD/mtd/}; # replace "mtd" with nothing
	MTD=${MTD/:*/}; # replace ":*" (trailing) with nothing
	echo "[$0]: $MFG_NVRAM_MTD_PARTITION partition is on MTD devide $MTD"

	echo "[$0]: Erasing the MTD $MTD partition"
	ubiformat /dev/mtd$MTD || error_exit "$0: ubiformat failed"
	
	echo "[$0]: Attaching MTD device $MTD to UBI device"
	ubiattach -m $MTD || error_exit "$0: ubiattach failed"

	echo "[$0]: Createing new UBI device node"
	UBI=`grep -l $MTD /sys/class/ubi/*/mtd_num`
	UBI=${UBI/\/mtd_num/}; # remove "/mtd_num" from the path
	UBI=${UBI/\/sys\/class\/ubi\//}; # remove "/sys/class/ubi/" from the path
	DEV=/dev/$UBI # mdev should already populate the new device node for ubi in /dev.
	echo "[$0]: DEV=$DEV UBI=$UBI"
	[ -e $DEV ] || error_exit "$0: device node '$DEV' does not exist."

	echo "[$0]: Createing new UBI volume"
	ubimkvol $DEV --name=nvram --type=dynamic --maxavsize || error_exit "$0: ubimkvol failed"
	
	echo "[$0]: Mounting nvram UBI volume"
	mount -t ubifs $UBI:nvram $MFG_NVRAM_DIR || error_exit "$0: mount failed"

	#
	# copy mfg NVRAM file from MFG_NVRAM_TMP_DIR to misc1
	#
	echo "[$0]: copying nvram file to misc1"
	cp $MFG_NVRAM_TMP_DIR/$MFG_NVRAM_FILE $MFG_NVRAM_FILEPATH
	rm $MFG_NVRAM_TMP_DIR/$MFG_NVRAM_FILE
	
	#
	# Unmounting and detaching UBI volume.
	#
	echo "[$0]: Un-mounting NVRAM UBI volume"
	umount $MFG_NVRAM_DIR || error_exit "$0: umount failed"
	
	rm -rf $MFG_NVRAM_DIR || error_exit "$0: rm failed"

	echo "[$0]: Detaching MTD device $MTD from UBI"
	ubidetach -m $MTD || error_exit "$0: ubidetach failed"

	echo "$0: Done"
	return 0
    else
	mfg_fatal "$0: $MSG_FATAL_MISCPARTITION"
    fi
}

mfg_load_drivers()
{
    echo "$0: Loading basic drivers"
    
    mfg_insmod "/lib/modules/*/extra/rdp_fpm.ko"
    mfg_insmod "/lib/modules/*/extra/bdmf.ko" "bdmf_chrdev_major=215"
    mfg_insmod "/lib/modules/*/extra/rdpa_gpl.ko"
    mfg_insmod "/lib/modules/*/extra/rdpa_gpl_ext.ko"
    mfg_insmod "/lib/modules/*/extra/rdpa.ko"
    mfg_insmod "/lib/modules/*/extra/rdpa_mw.ko"
    
    # General
    mfg_insmod "/lib/modules/*/extra/chipinfo.ko"
    mfg_insmod "/lib/modules/*/extra/pktflow.ko"
    
    # enet
    mfg_insmod "/lib/modules/*/extra/bcm_enet.ko"
    
    # moving
    mfg_insmod "/lib/modules/*/extra/pktrunner.ko"
    mfg_insmod "/lib/modules/*/extra/nciTMSkmod.ko"

    # other
    mfg_insmod "/lib/modules/*/extra/bcmvlan.ko"
    mfg_insmod "/lib/modules/*/extra/pwrmngtd.ko"

    mfg_insmod "/lib/modules/*/extra/rdpa_cmd.ko"

    test -e /rom/etc/rdpa_init.sh && /rom/etc/rdpa_init.sh

    echo "$0: Loading basic drivers - done"

    return 0
}

mfg_setup_network()
{
    ip=$1
    mask=$2
    echo "$0: Bringing up the network ($ip/$mask)"

    /rom/etc/init.d/swmdk.sh start

    brctl addbr br0
    brctl stp br0 off
    brctl setfd br0 0
    #sendarp -s br0 -d br0
    ifconfig br0 up

    ifconfig br0 $ip netmask $mask up

    for intf in `(cd /sys/class/net ; echo eth*)`
    do
	if ifconfig $intf up >/dev/null 2>/dev/null
	then
	    brctl addif br0 $intf
	    if type tmctl 2> /dev/null > /dev/null
	    then
		tmctl porttminit --devtype 0 --if $intf --flag 1
	    fi
	fi
    done

    # bring up the loopback interface
    ifconfig lo 127.0.0.1 netmask 255.0.0.0 broadcast 127.255.255.255 up
    
    # need this rule to be able run wget
    iptables -A INPUT -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT

    return 0
}

# This function performs some basic network test
mfg_test_network()
{
    ip=$MFG_NVRAM_URL_IP
    count=0
    fail=no
    
    echo "$0: testing network connection with host $ip"

    while [ "$count" -le "$MFG_PING_RETRY_LIMIT" ]
    do
	ping -c 1 -W 1 $ip  > /dev/null
	if [ $? != 0 ]; then
	    fail=yes
	else
	    fail=no
	    break
	fi
	let "count += 1"
	echo "not ready ($count) ..."
    done

    if [ "${fail}" = "yes" ]; then
	mfg_fatal "$0: $MSG_FATAL_NETTEST"
    fi

    return 0
}

# Get base MAC address from mfg NVRAM file
# and set it to the CFEROM NVRAM space.
mfg_set_base_macaddr()
{
    # launching envram server in order to read mfg NVRAM variables.
    # envram server will mount manufacturing NVRAM UBI FS.
    /usr/sbin/envrams

    MACADDR=`envram get et0macaddr`

    [[ -z "${MACADDR// }" ]] && mfg_fatal "$0: $MSG_FATAL_BASEMACADDR"

    echo "[$0]: Setting Base MAC addredd $MACADDR to CFEROM NVRAM."
    
    # replace all colons in MAC address with space.
    MACADDR=${MACADDR//:/ }

    # Set MAC address into CFEROM NVRAM
    echo $MACADDR > /proc/nvram/BaseMacAddr

    echo "[$0]: Done."
    
    return 0
}

case "$1" in
    start)
	/bin/mount -a

	if  [ -e $MFG_NVRAM_MODE_FILEPATH ]; then
	    mfg_nvram_mode=$(cat $MFG_NVRAM_MODE_FILEPATH)
	else
	    mfg_nvram_mode=0
	fi

	if  [ -e $MFG_NVRAM_MODE_DEBUG_FILEPATH ]; then
	    mfg_nvram_mode_dbg=$(cat $MFG_NVRAM_MODE_DEBUG_FILEPATH)
	else
	    mfg_nvram_mode_dbg=0
	fi
	
	is_mfg_nvram_mode=$(($mfg_nvram_mode & 1))
	is_mfg_nvram_mode_dbg=$(($mfg_nvram_mode_dbg & 1))
	
	if [ $is_mfg_nvram_mode -eq 1 ]; then
	    mfg_init
	    mfg_load_drivers
	    mfg_setup_network "$TARGET_IP" "$TARGET_NETMASK"
	    mfg_test_network
	    mfg_program_nvram
	    mfg_set_base_macaddr
	    if [ $is_mfg_nvram_mode_dbg -eq 1 ]; then
		mfg_reboot --iteractive
	    else
		mfg_reboot
	    fi
	    
	fi
	exit 0
	;;
    stop)
	exit 0
	;;
    dlnvram)
	# parsing input url
	echo "$2" > $MFG_NVRAM_TMP_URL_FILEPATH
	MFG_NVRAM_URL_FILEPATH=$MFG_NVRAM_TMP_URL_FILEPATH
	mfg_parse_url

	# mkdir for downloading nvram file and mounting misc1
	mkdir $MFG_NVRAM_DIR || error_exit "$0: mkdir failed"
	mkdir $MFG_NVRAM_TMP_DIR || error_exit "$0: mkdir failed"

	# start to download nvram and write it to flash
	mfg_program_nvram
	mfg_set_base_macaddr

	# remove the temp files
	rm $MFG_NVRAM_TMP_URL_FILEPATH
	rm -rf $MFG_NVRAM_DIR
	rm -rf $MFG_NVRAM_TMP_DIR

	exit 0
	;;
    *)
	echo "$0: unrecognized option $1"
	;;
esac
