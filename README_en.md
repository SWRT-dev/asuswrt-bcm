
NOTE：
=
1. **DO NOT USE** **root** user for git or compilation!!!
2. if you are in china, you need a network proxy

## Compilation

1. Install Ubuntu 64bit，recommend Ubuntu 18 LTS x64 / Mint 19.1

2. Enter `sudo apt-get update` in terminal, then enter
`
sudo apt-get -y install build-essential asciidoc binutils bzip2 gawk gettext git libncurses5-dev libz-dev patch python3.5 python2.7 unzip zlib1g-dev lib32gcc1 libc6-dev-i386 subversion flex uglifyjs git-core gcc-multilib p7zip p7zip-full msmtp libssl-dev texinfo libglib2.0-dev xmlto qemu-utils upx libelf-dev autoconf automake libtool autopoint device-tree-compiler g++-multilib antlr3 gperf wget libncurses5:i386 libelf1:i386 lib32z1 lib32stdc++6 gtk-doc-tools intltool binutils-dev cmake lzma liblzma-dev lzma-dev uuid-dev liblzo2-dev xsltproc dos2unix libstdc++5 docbook-xsl-* sharutils autogen shtool gengetopt libltdl-dev libtool-bin
`

3. Enter `git clone https://github.com/SWRT-dev/asuswrt-bcm` to download source code 

4. Enter `git clone https://github.com/SWRT-dev/bcmhnd-toolchains` to download toolchains

5. Enter the following commands step by step `cd bcmhnd-toolchains`

    `sudo mkdir -p /opt/toolchains/`

    `sudo ln -sf $(pwd)/crosstools-aarch64-gcc-5.3-linux-4.1-glibc-2.22-binutils-2.25 /opt/toolchains/`

    `sudo ln -sf $(pwd)/crosstools-arm-gcc-5.3-linux-4.1-glibc-2.22-binutils-2.25 /opt/toolchains/`

    `sudo ln -sf $(pwd)/crosstools-aarch64-gcc-5.3-linux-4.1-glibc-2.24-binutils-2.25 /opt/toolchains/`
    
    `sudo ln -sf $(pwd)/crosstools-aarch64-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1 /opt/toolchains/`
    
    `sudo ln -sf $(pwd)/crosstools-arm-gcc-5.3-linux-4.1-glibc-2.24-binutils-2.25 /opt/toolchains/`
    
    `sudo ln -sf $(pwd)crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1 /opt/toolchains/`
    
    `sudo ln -sf $(pwd)/crosstools-gcc-5.3-linux-4.1-uclibc-1.0.12-glibc-2.24-binutils-2.25 /opt/toolchains/`
    
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
	`cd asuswrt-bcm/release/src-rt-6.x.4708`

	`make rt-ac68u`

	`cd asuswrt-bcm/release/src-rt-7.14.114.x/src` 

	`make rt-ac88u`

	`make rt-ac3100`

	`make rt-ac5300`

	The firmware is in 
	asuswrt-bcm/release/src-rt-6.x.4708/image 
	asuswrt-bcm/release/src-rt-7.14.114.x/src/image

## Donate

If you think this project is helpful to you, please donate to us so that the project can continue to develop and become more complete. 

### PayPal

[![Support via PayPal](https://cdn.rawgit.com/twolfson/paypal-github-button/1.0.0/dist/button.svg)](https://paypal.me/paldier9/)

### Alipay 支付宝

![alipay](doc/alipay_donate.jpg)

### Wechat 微信
  
![wechat](doc/wechat_donate.jpg)


