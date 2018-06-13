if [ -f /etc/X11/app-defaults/Gnuplot ] && cmp -s /etc/defaults/etc/X11/app-defaults/Gnuplot /etc/X11/app-defaults/Gnuplot
then
    rm /etc/X11/app-defaults/Gnuplot
fi

