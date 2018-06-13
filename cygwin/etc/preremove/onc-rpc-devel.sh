if [ -f /etc/rpc ] && cmp -s /etc/defaults/etc/rpc /etc/rpc
then
    rm /etc/rpc
fi

