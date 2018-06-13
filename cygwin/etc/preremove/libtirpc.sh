if [ -f /etc/netconfig ] && cmp -s /etc/defaults/etc/netconfig /etc/netconfig
then
    rm /etc/netconfig
fi

