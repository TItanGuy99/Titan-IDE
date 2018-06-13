#!/bin/sh
sbindir=/usr/sbin
e=2
rbindir=/opt/gcc-tools/epoch${e}/bin
lbindir=/opt/gcc-tools/bin

${sbindir}/update-alternatives --remove gcc-tools-autoconf ${rbindir}/autoconf-2.64

