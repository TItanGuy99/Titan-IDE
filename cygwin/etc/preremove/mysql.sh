if [ -f /etc/my.cnf ] && cmp -s /etc/defaults/etc/my.cnf /etc/my.cnf
then
    rm /etc/my.cnf
fi

if [ -f /etc/my.cnf.d/client.cnf ] && cmp -s /etc/defaults/etc/my.cnf.d/client.cnf /etc/my.cnf.d/client.cnf
then
    rm /etc/my.cnf.d/client.cnf
fi

if [ -f /etc/my.cnf.d/enable_encryption.preset ] && cmp -s /etc/defaults/etc/my.cnf.d/enable_encryption.preset /etc/my.cnf.d/enable_encryption.preset
then
    rm /etc/my.cnf.d/enable_encryption.preset
fi

if [ -f /etc/my.cnf.d/mysql-clients.cnf ] && cmp -s /etc/defaults/etc/my.cnf.d/mysql-clients.cnf /etc/my.cnf.d/mysql-clients.cnf
then
    rm /etc/my.cnf.d/mysql-clients.cnf
fi

if [ -f /etc/my.cnf.d/server.cnf ] && cmp -s /etc/defaults/etc/my.cnf.d/server.cnf /etc/my.cnf.d/server.cnf
then
    rm /etc/my.cnf.d/server.cnf
fi

