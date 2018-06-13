if [ -f /etc/discusrc ] && cmp -s /etc/defaults/etc/discusrc /etc/discusrc
then
    rm /etc/discusrc
fi

