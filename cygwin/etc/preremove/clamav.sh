if [ -f /etc/clamd.conf ] && cmp -s /etc/defaults/etc/clamd.conf /etc/clamd.conf
then
    rm /etc/clamd.conf
fi

if [ -f /etc/freshclam.conf ] && cmp -s /etc/defaults/etc/freshclam.conf /etc/freshclam.conf
then
    rm /etc/freshclam.conf
fi

