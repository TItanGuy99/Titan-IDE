#!/bin/sh
# Arrange initial setup from defaults directory
# This is automatically generated file

PATH=/bin:/sbin:/usr/bin:/usr/sbin
LC_ALL=C

fromdir=/etc/defaults

for i in   etc etc/sgreprc
do
    src=$fromdir/$i
    dest=/$i

    [ -e $dest ] && continue

    if [ -d $src ] ; then
	install -d -m 755 /etc/$i
	continue
    fi

    install -m 644 $src $dest
done
