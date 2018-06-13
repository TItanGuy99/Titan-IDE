#!/bin/sh
sbindir=/usr/sbin
e=1
rbindir=/opt/gcc-tools/epoch${e}/bin
lbindir=/opt/gcc-tools/bin

${sbindir}/update-alternatives --remove gcc-tools-automake ${rbindir}/automake-1.9

