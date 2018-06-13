#!/bin/bash
PATH=/bin:/sbin:/usr/bin:/usr/sbin
LC_ALL=C
dest=$1

set -e
bindir=/usr/bin

cd ${bindir}
for prog in autoconf autoheader autom4te autoreconf autoscan autoupdate ifnames
do
	rm -f ${prog}
done
