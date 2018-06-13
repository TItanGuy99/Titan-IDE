if [ -f /etc/smartd.conf ] && cmp -s /etc/defaults/etc/smartd.conf /etc/smartd.conf
then
    rm /etc/smartd.conf
fi

if [ -f /etc/smartd_warning.sh ] && cmp -s /etc/defaults/etc/smartd_warning.sh /etc/smartd_warning.sh
then
    rm /etc/smartd_warning.sh
fi

rm -f /usr/share/smartmontools/drivedb.h.error \
      /usr/share/smartmontools/drivedb.h.lastcheck \
      /usr/share/smartmontools/drivedb.h.old

