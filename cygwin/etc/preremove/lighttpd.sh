if [ -f /etc/lighttpd/conf.d/access_log.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/access_log.conf /etc/lighttpd/conf.d/access_log.conf
then
    rm /etc/lighttpd/conf.d/access_log.conf
fi

if [ -f /etc/lighttpd/conf.d/auth.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/auth.conf /etc/lighttpd/conf.d/auth.conf
then
    rm /etc/lighttpd/conf.d/auth.conf
fi

if [ -f /etc/lighttpd/conf.d/cgi.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/cgi.conf /etc/lighttpd/conf.d/cgi.conf
then
    rm /etc/lighttpd/conf.d/cgi.conf
fi

if [ -f /etc/lighttpd/conf.d/cml.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/cml.conf /etc/lighttpd/conf.d/cml.conf
then
    rm /etc/lighttpd/conf.d/cml.conf
fi

if [ -f /etc/lighttpd/conf.d/compress.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/compress.conf /etc/lighttpd/conf.d/compress.conf
then
    rm /etc/lighttpd/conf.d/compress.conf
fi

if [ -f /etc/lighttpd/conf.d/debug.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/debug.conf /etc/lighttpd/conf.d/debug.conf
then
    rm /etc/lighttpd/conf.d/debug.conf
fi

if [ -f /etc/lighttpd/conf.d/dirlisting.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/dirlisting.conf /etc/lighttpd/conf.d/dirlisting.conf
then
    rm /etc/lighttpd/conf.d/dirlisting.conf
fi

if [ -f /etc/lighttpd/conf.d/evhost.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/evhost.conf /etc/lighttpd/conf.d/evhost.conf
then
    rm /etc/lighttpd/conf.d/evhost.conf
fi

if [ -f /etc/lighttpd/conf.d/expire.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/expire.conf /etc/lighttpd/conf.d/expire.conf
then
    rm /etc/lighttpd/conf.d/expire.conf
fi

if [ -f /etc/lighttpd/conf.d/fastcgi.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/fastcgi.conf /etc/lighttpd/conf.d/fastcgi.conf
then
    rm /etc/lighttpd/conf.d/fastcgi.conf
fi

if [ -f /etc/lighttpd/conf.d/geoip.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/geoip.conf /etc/lighttpd/conf.d/geoip.conf
then
    rm /etc/lighttpd/conf.d/geoip.conf
fi

if [ -f /etc/lighttpd/conf.d/magnet.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/magnet.conf /etc/lighttpd/conf.d/magnet.conf
then
    rm /etc/lighttpd/conf.d/magnet.conf
fi

if [ -f /etc/lighttpd/conf.d/mime.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/mime.conf /etc/lighttpd/conf.d/mime.conf
then
    rm /etc/lighttpd/conf.d/mime.conf
fi

if [ -f /etc/lighttpd/conf.d/mysql_vhost.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/mysql_vhost.conf /etc/lighttpd/conf.d/mysql_vhost.conf
then
    rm /etc/lighttpd/conf.d/mysql_vhost.conf
fi

if [ -f /etc/lighttpd/conf.d/proxy.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/proxy.conf /etc/lighttpd/conf.d/proxy.conf
then
    rm /etc/lighttpd/conf.d/proxy.conf
fi

if [ -f /etc/lighttpd/conf.d/rrdtool.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/rrdtool.conf /etc/lighttpd/conf.d/rrdtool.conf
then
    rm /etc/lighttpd/conf.d/rrdtool.conf
fi

if [ -f /etc/lighttpd/conf.d/scgi.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/scgi.conf /etc/lighttpd/conf.d/scgi.conf
then
    rm /etc/lighttpd/conf.d/scgi.conf
fi

if [ -f /etc/lighttpd/conf.d/secdownload.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/secdownload.conf /etc/lighttpd/conf.d/secdownload.conf
then
    rm /etc/lighttpd/conf.d/secdownload.conf
fi

if [ -f /etc/lighttpd/conf.d/simple_vhost.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/simple_vhost.conf /etc/lighttpd/conf.d/simple_vhost.conf
then
    rm /etc/lighttpd/conf.d/simple_vhost.conf
fi

if [ -f /etc/lighttpd/conf.d/ssi.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/ssi.conf /etc/lighttpd/conf.d/ssi.conf
then
    rm /etc/lighttpd/conf.d/ssi.conf
fi

if [ -f /etc/lighttpd/conf.d/status.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/status.conf /etc/lighttpd/conf.d/status.conf
then
    rm /etc/lighttpd/conf.d/status.conf
fi

if [ -f /etc/lighttpd/conf.d/trigger_b4_dl.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/trigger_b4_dl.conf /etc/lighttpd/conf.d/trigger_b4_dl.conf
then
    rm /etc/lighttpd/conf.d/trigger_b4_dl.conf
fi

if [ -f /etc/lighttpd/conf.d/userdir.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/userdir.conf /etc/lighttpd/conf.d/userdir.conf
then
    rm /etc/lighttpd/conf.d/userdir.conf
fi

if [ -f /etc/lighttpd/conf.d/webdav.conf ] && cmp -s /etc/defaults/etc/lighttpd/conf.d/webdav.conf /etc/lighttpd/conf.d/webdav.conf
then
    rm /etc/lighttpd/conf.d/webdav.conf
fi

if [ -f /etc/lighttpd/lighttpd.conf ] && cmp -s /etc/defaults/etc/lighttpd/lighttpd.conf /etc/lighttpd/lighttpd.conf
then
    rm /etc/lighttpd/lighttpd.conf
fi

if [ -f /etc/lighttpd/modules.conf ] && cmp -s /etc/defaults/etc/lighttpd/modules.conf /etc/lighttpd/modules.conf
then
    rm /etc/lighttpd/modules.conf
fi

if [ -f /etc/lighttpd/vhosts.d/vhosts.template ] && cmp -s /etc/defaults/etc/lighttpd/vhosts.d/vhosts.template /etc/lighttpd/vhosts.d/vhosts.template
then
    rm /etc/lighttpd/vhosts.d/vhosts.template
fi

