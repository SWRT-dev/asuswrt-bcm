[ENGLISH](README_en.md) [中文](README.md)

## 编译测试

测试目标:GT-AX6000 GT-AX11000 RT-AX82U TUF-AX3000_V2

**状态** [![CircleCI](https://dl.circleci.com/status-badge/img/gh/SWRT-dev/asuswrt-bcm/tree/master.svg?style=svg)](https://dl.circleci.com/status-badge/redirect/gh/SWRT-dev/asuswrt-bcm/tree/master)


=======

AC系列:[https://github.com/SWRT-dev/asuswrt-bcm-ac](https://github.com/SWRT-dev/asuswrt-bcm-ac)

AX系列:[https://github.com/SWRT-dev/asuswrt-bcm](https://github.com/SWRT-dev/asuswrt-bcm)


注意：
=
1. **不**要用 **root** 用户 git 和编译！！！
2. 国内用户编译前最好准备好梯子

## 编译

1. 首先装好 Ubuntu 64bit，推荐  Ubuntu  18 LTS x64 /  Mint 19.1

2. 命令行输入 `sudo apt-get update` ，然后输入
`
sudo apt-get -y install build-essential asciidoc binutils bzip2 gawk gettext git libncurses5-dev libz-dev patch python3.5 python2.7 unzip zlib1g-dev lib32gcc1 libc6-dev-i386 subversion flex uglifyjs git-core gcc-multilib p7zip p7zip-full msmtp libssl-dev texinfo libglib2.0-dev xmlto qemu-utils upx libelf-dev autoconf automake libtool autopoint device-tree-compiler g++-multilib antlr3 gperf wget libncurses5:i386 libelf1:i386 lib32z1 lib32stdc++6 gtk-doc-tools intltool binutils-dev cmake lzma liblzma-dev lzma-dev uuid-dev liblzo2-dev xsltproc dos2unix libstdc++5 docbook-xsl-* sharutils autogen shtool gengetopt libltdl-dev libtool-bin pkg-config
`

3. 使用 `git clone https://github.com/SWRT-dev/asuswrt-bcm` 命令下载好源代码

4. 使用 `git clone https://github.com/SWRT-dev/bcmhnd-toolchains` 命令下载toolchains

5. 分别执行 `cd bcmhnd-toolchains`

    `sudo mkdir -p /opt/toolchains/`

    `sudo ln -sf $(pwd)/crosstools-aarch64-gcc-5.3-linux-4.1-glibc-2.22-binutils-2.25 /opt/toolchains/`

    `sudo ln -sf $(pwd)/crosstools-arm-gcc-5.3-linux-4.1-glibc-2.22-binutils-2.25 /opt/toolchains/`

    `sudo ln -sf $(pwd)/crosstools-aarch64-gcc-5.3-linux-4.1-glibc-2.24-binutils-2.25 /opt/toolchains/`
    
    `sudo ln -sf $(pwd)/crosstools-aarch64-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1 /opt/toolchains/`
    
    `sudo ln -sf $(pwd)/crosstools-arm-gcc-5.3-linux-4.1-glibc-2.24-binutils-2.25 /opt/toolchains/`
    
    `sudo ln -sf $(pwd)crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1 /opt/toolchains/`
    
    `sudo ln -sf $(pwd)/crosstools-gcc-5.3-linux-4.1-uclibc-1.0.12-glibc-2.24-binutils-2.25 /opt/toolchains/`

    `sudo ln -sf $(pwd)/crosstools-aarch64-gcc-9.2-linux-4.19-glibc-2.30-binutils-2.32 /opt/toolchains/`

    `sudo ln -sf $(pwd)/crosstools-arm-gcc-9.2-linux-4.19-glibc-2.30-binutils-2.32 /opt/toolchains/`
    
    `sudo mkdir -p /projects/`
    
    `sudo mkdir -p /projects/bca/`
    
    `sudo mkdir -p /projects/bca/tools/`
    
    `sudo mkdir -p /projects/bca/tools/linux/`
    
    `sudo mkdir -p /projects/bca/tools/linux/bin/`
    
    `sudo ln -sf $(pwd)/hndtools-armeabi-2013.11 /projects/bca/tools/linux/`
    
    `sudo ln -sf $(pwd)/fwtag.ini /projects/bca/tools/linux/bin/`
    
    `sudo ln -sf /projects/bca/ /projects/hnd/`

    `chsh -s /bin/bash`

    `sudo ln -sf /bin/bash /bin/sh`

6. 编译固件

	`cd asuswrt-bcm/release/src-rt-5.02axhnd.675x` 

	`make rt-ax95q`

	`make rt-axe95q`

	`git checkout 386 && make rt-ax55`

	`make rt-ax56u`

	`make rt-ax58u`

	`make rt-ax82u`

	`make tuf-ax3000`

	`make tuf-ax5400`

	`cd asuswrt-bcm/release/src-rt-5.02L.07p2axhnd` 

	`make rt-ax68u`

	`make rt-ax86u`

	`make gt-axe11000`

	`cd asuswrt-bcm/release/src-rt-5.02axhnd` 

	`make rt-ax88u`

	`make rt-ax92u`

	`make gt-ax11000`

	`cd asuswrt-bcm/release/src-rt-5.04axhnd.675x` 

	`make rt-ax86u_pro`

	`make gt-ax11000_pro`

	`make gt-ax6000`

	`make gt-axe16000`

	`make xt12`

	`make rt-ax82u_v2`

	`make tuf-ax3000_v2`

	`git checkout 22525 && make tuf-ax5400_v2`

	`make rt-ax88u_pro`

	`git checkout 22525 && make gt10`

	`git checkout rtax3000n && make rt-ax3000n`

	编译完成后输出固件路径：

	asuswrt-bcm/release/src-rt-5.02axhnd.675x/image

	asuswrt-bcm/release/src-rt-5.02L.07p2axhnd/image

	asuswrt-bcm/release/src-rt-5.02axhnd/image

	asuswrt-bcm/release/src-rt-5.04axhnd.675x/image

## Donate

如果你觉得此项目对你有帮助，请捐助我们，以使项目能持续发展，更加完善。

### PayPal

[![Support via PayPal](https://cdn.rawgit.com/twolfson/paypal-github-button/1.0.0/dist/button.svg)](https://paypal.me/paldier9/)

### Alipay 支付宝

![alipay](doc/alipay_donate.jpg)

### Wechat 微信
  
![wechat](doc/wechat_donate.jpg)


