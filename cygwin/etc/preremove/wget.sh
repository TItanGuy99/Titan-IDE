if [ -f /etc/wgetrc ] && cmp -s /etc/defaults/etc/wgetrc /etc/wgetrc
then
    rm /etc/wgetrc
fi

