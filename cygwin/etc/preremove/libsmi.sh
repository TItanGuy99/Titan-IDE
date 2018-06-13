if [ -f /etc/smi.conf ] && cmp -s /etc/defaults/etc/smi.conf /etc/smi.conf
then
    rm /etc/smi.conf
fi

