if [ -f /etc/papersize ] && cmp -s /etc/defaults/etc/papersize /etc/papersize
then
    rm /etc/papersize
fi

