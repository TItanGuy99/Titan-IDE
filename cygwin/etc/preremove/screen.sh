if [ -f /etc/screenrc ] && cmp -s /etc/defaults/etc/screenrc /etc/screenrc
then
    rm /etc/screenrc
fi

