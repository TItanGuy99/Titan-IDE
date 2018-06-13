#!/bin/sh

if cmp -s /etc/defaults/etc/netscsid.conf /etc/netscsid.conf; then
  rm -f /etc/netscsid.conf
fi
if cmp -s /etc/defaults/etc/wodim.conf /etc/wodim.conf; then
  rm -f /etc/wodim.conf
fi

