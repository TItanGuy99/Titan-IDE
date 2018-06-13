if [ -f /etc/multitail.conf ] && cmp -s /etc/defaults/etc/multitail.conf /etc/multitail.conf
then
    rm /etc/multitail.conf
fi

