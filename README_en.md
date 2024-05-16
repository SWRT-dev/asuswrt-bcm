[ENGLISH](README_en.md) [中文](README.md)


## Code compilation test

**MODEL**:GT-AX6000 GT-AX11000 RT-AX82U TUF-AX3000_V2

**status** [![CircleCI](https://dl.circleci.com/status-badge/img/gh/SWRT-dev/asuswrt-bcm/tree/master.svg?style=svg)](https://dl.circleci.com/status-badge/redirect/gh/SWRT-dev/asuswrt-bcm/tree/master)

=======

AC series:[https://github.com/SWRT-dev/asuswrt-bcm-ac](https://github.com/SWRT-dev/asuswrt-bcm-ac)

AX series:[https://github.com/SWRT-dev/asuswrt-bcm](https://github.com/SWRT-dev/asuswrt-bcm)

NOTE：
=
1. **DO NOT USE** **root** user for git or compilation!!!
2. if you are in china, you need a network proxy

## Compilation

1. Install Ubuntu 64bit，Ubuntu 18 LTS x64 and Mint 19.1 are recommended

2. Run `sudo apt-get update` in terminal, and then run
`
sudo apt-get -y install build-essential asciidoc binutils bzip2 gawk gettext git libncurses5-dev libz-dev patch python3.5 python2.7 unzip zlib1g-dev lib32gcc1 libc6-dev-i386 subversion flex uglifyjs git-core gcc-multilib p7zip p7zip-full msmtp libssl-dev texinfo libglib2.0-dev xmlto qemu-utils upx libelf-dev autoconf automake libtool autopoint device-tree-compiler g++-multilib antlr3 gperf wget libncurses5:i386 libelf1:i386 lib32z1 lib32stdc++6 gtk-doc-tools intltool binutils-dev cmake lzma liblzma-dev lzma-dev uuid-dev liblzo2-dev xsltproc dos2unix libstdc++5 docbook-xsl-* sharutils autogen shtool gengetopt libltdl-dev libtool-bin
`

3. Run `git clone https://github.com/SWRT-dev/asuswrt-bcm` to clone the source code 

4. Run `git clone https://github.com/SWRT-dev/bcmhnd-toolchains` to clone the toolchains

5. Run `cd bcmhnd-toolchains` to enter the directory, and follow commands step by step 

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

6. Build firmware

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

	`git checkout 388_21224 && make xt12`

	`make rt-ax82u_v2`

	`make tuf-ax3000_v2`

	`make tuf-ax5400_v2`

	`make rt-ax88u_pro`

	`make gt10`

	`git checkout rtax3000n && make rt-ax3000n`

	Build result will be produced to `asuswrt-bcm/release/src-rt-xxxxx/image` directory

	`asuswrt-bcm/release/src-rt-5.02axhnd.675x/image`

	`asuswrt-bcm/release/src-rt-5.02L.07p2axhnd/image`

	`asuswrt-bcm/release/src-rt-5.02axhnd/image`

	`asuswrt-bcm/release/src-rt-5.04axhnd.675x/image`

This source code is promised to be compiled successfully.

You can use this source code freely, but please link this GitHub repository when redistributing. Thank you for your cooperation!

## Donate

If this project does help you, please consider donating to support the development of this project.

### PayPal

[![Support via PayPal](https://cdn.rawgit.com/twolfson/paypal-github-button/1.0.0/dist/button.svg)](https://paypal.me/paldier9/)

### Alipay 支付宝

![alipay](doc/alipay_donate.jpg)

### Wechat 微信
  
![wechat](doc/wechat_donate.jpg)


