if [ -f /etc/lftp.conf ] && cmp -s /etc/defaults/etc/lftp.conf /etc/lftp.conf
then
    rm /etc/lftp.conf
fi

