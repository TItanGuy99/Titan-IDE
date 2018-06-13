if [ -f /usr/share/t1lib/t1lib.config ] && cmp -s /etc/defaults/usr/share/t1lib/t1lib.config /usr/share/t1lib/t1lib.config
then
    rm /usr/share/t1lib/t1lib.config
fi

