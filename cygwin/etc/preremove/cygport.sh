if [ -f /etc/cygport.conf ] && cmp -s /etc/defaults/etc/cygport.conf /etc/cygport.conf
then
    rm /etc/cygport.conf
fi

if [ -f /etc/X11/cygport-xvfb.conf ] && cmp -s /etc/defaults/etc/X11/cygport-xvfb.conf /etc/X11/cygport-xvfb.conf
then
    rm /etc/X11/cygport-xvfb.conf
fi

