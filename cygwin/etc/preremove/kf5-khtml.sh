if [ -f /etc/xdg/khtmlrc ] && cmp -s /etc/defaults/etc/xdg/khtmlrc /etc/xdg/khtmlrc
then
    rm /etc/xdg/khtmlrc
fi

