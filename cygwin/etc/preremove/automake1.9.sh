#!/bin/sh
prefix=/usr
bindir=${prefix}/bin
sbindir=${prefix}/sbin
infodir=${prefix}/share/info
man1dir=${prefix}/share/man/man1

${sbindir}/update-alternatives --remove automake-doc ${infodir}/automake1.9.info.gz

