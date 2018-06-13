if [ -f /etc/xdg/colors/40.colors ] && cmp -s /etc/defaults/etc/xdg/colors/40.colors /etc/xdg/colors/40.colors
then
    rm /etc/xdg/colors/40.colors
fi

if [ -f /etc/xdg/colors/Oxygen.colors ] && cmp -s /etc/defaults/etc/xdg/colors/Oxygen.colors /etc/xdg/colors/Oxygen.colors
then
    rm /etc/xdg/colors/Oxygen.colors
fi

if [ -f /etc/xdg/colors/Rainbow.colors ] && cmp -s /etc/defaults/etc/xdg/colors/Rainbow.colors /etc/xdg/colors/Rainbow.colors
then
    rm /etc/xdg/colors/Rainbow.colors
fi

if [ -f /etc/xdg/colors/Royal.colors ] && cmp -s /etc/defaults/etc/xdg/colors/Royal.colors /etc/xdg/colors/Royal.colors
then
    rm /etc/xdg/colors/Royal.colors
fi

if [ -f /etc/xdg/colors/Web.colors ] && cmp -s /etc/defaults/etc/xdg/colors/Web.colors /etc/xdg/colors/Web.colors
then
    rm /etc/xdg/colors/Web.colors
fi

if [ -f /etc/xdg/kdebug.areas ] && cmp -s /etc/defaults/etc/xdg/kdebug.areas /etc/xdg/kdebug.areas
then
    rm /etc/xdg/kdebug.areas
fi

if [ -f /etc/xdg/kdebugrc ] && cmp -s /etc/defaults/etc/xdg/kdebugrc /etc/xdg/kdebugrc
then
    rm /etc/xdg/kdebugrc
fi

if [ -f /etc/xdg/ksslcalist ] && cmp -s /etc/defaults/etc/xdg/ksslcalist /etc/xdg/ksslcalist
then
    rm /etc/xdg/ksslcalist
fi

