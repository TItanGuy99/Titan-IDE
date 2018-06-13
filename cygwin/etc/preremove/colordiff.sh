if [ -f /etc/colordiffrc ] && cmp -s /etc/defaults/etc/colordiffrc /etc/colordiffrc
then
    rm /etc/colordiffrc
fi

