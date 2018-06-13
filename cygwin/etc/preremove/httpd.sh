if [ -f /etc/httpd/conf/extra/httpd-autoindex.conf ] && cmp -s /etc/defaults/etc/httpd/conf/extra/httpd-autoindex.conf /etc/httpd/conf/extra/httpd-autoindex.conf
then
    rm /etc/httpd/conf/extra/httpd-autoindex.conf
fi

if [ -f /etc/httpd/conf/extra/httpd-dav.conf ] && cmp -s /etc/defaults/etc/httpd/conf/extra/httpd-dav.conf /etc/httpd/conf/extra/httpd-dav.conf
then
    rm /etc/httpd/conf/extra/httpd-dav.conf
fi

if [ -f /etc/httpd/conf/extra/httpd-default.conf ] && cmp -s /etc/defaults/etc/httpd/conf/extra/httpd-default.conf /etc/httpd/conf/extra/httpd-default.conf
then
    rm /etc/httpd/conf/extra/httpd-default.conf
fi

if [ -f /etc/httpd/conf/extra/httpd-info.conf ] && cmp -s /etc/defaults/etc/httpd/conf/extra/httpd-info.conf /etc/httpd/conf/extra/httpd-info.conf
then
    rm /etc/httpd/conf/extra/httpd-info.conf
fi

if [ -f /etc/httpd/conf/extra/httpd-languages.conf ] && cmp -s /etc/defaults/etc/httpd/conf/extra/httpd-languages.conf /etc/httpd/conf/extra/httpd-languages.conf
then
    rm /etc/httpd/conf/extra/httpd-languages.conf
fi

if [ -f /etc/httpd/conf/extra/httpd-manual.conf ] && cmp -s /etc/defaults/etc/httpd/conf/extra/httpd-manual.conf /etc/httpd/conf/extra/httpd-manual.conf
then
    rm /etc/httpd/conf/extra/httpd-manual.conf
fi

if [ -f /etc/httpd/conf/extra/httpd-mpm.conf ] && cmp -s /etc/defaults/etc/httpd/conf/extra/httpd-mpm.conf /etc/httpd/conf/extra/httpd-mpm.conf
then
    rm /etc/httpd/conf/extra/httpd-mpm.conf
fi

if [ -f /etc/httpd/conf/extra/httpd-multilang-errordoc.conf ] && cmp -s /etc/defaults/etc/httpd/conf/extra/httpd-multilang-errordoc.conf /etc/httpd/conf/extra/httpd-multilang-errordoc.conf
then
    rm /etc/httpd/conf/extra/httpd-multilang-errordoc.conf
fi

if [ -f /etc/httpd/conf/extra/httpd-ssl.conf ] && cmp -s /etc/defaults/etc/httpd/conf/extra/httpd-ssl.conf /etc/httpd/conf/extra/httpd-ssl.conf
then
    rm /etc/httpd/conf/extra/httpd-ssl.conf
fi

if [ -f /etc/httpd/conf/extra/httpd-userdir.conf ] && cmp -s /etc/defaults/etc/httpd/conf/extra/httpd-userdir.conf /etc/httpd/conf/extra/httpd-userdir.conf
then
    rm /etc/httpd/conf/extra/httpd-userdir.conf
fi

if [ -f /etc/httpd/conf/extra/httpd-vhosts.conf ] && cmp -s /etc/defaults/etc/httpd/conf/extra/httpd-vhosts.conf /etc/httpd/conf/extra/httpd-vhosts.conf
then
    rm /etc/httpd/conf/extra/httpd-vhosts.conf
fi

if [ -f /etc/httpd/conf/extra/proxy-html.conf ] && cmp -s /etc/defaults/etc/httpd/conf/extra/proxy-html.conf /etc/httpd/conf/extra/proxy-html.conf
then
    rm /etc/httpd/conf/extra/proxy-html.conf
fi

if [ -f /etc/httpd/conf/httpd.conf ] && cmp -s /etc/defaults/etc/httpd/conf/httpd.conf /etc/httpd/conf/httpd.conf
then
    rm /etc/httpd/conf/httpd.conf
fi

if [ -f /etc/httpd/conf/magic ] && cmp -s /etc/defaults/etc/httpd/conf/magic /etc/httpd/conf/magic
then
    rm /etc/httpd/conf/magic
fi

if [ -f /etc/httpd/conf/mime.types ] && cmp -s /etc/defaults/etc/httpd/conf/mime.types /etc/httpd/conf/mime.types
then
    rm /etc/httpd/conf/mime.types
fi

if [ -f /etc/httpd/conf/original/extra/httpd-autoindex.conf ] && cmp -s /etc/defaults/etc/httpd/conf/original/extra/httpd-autoindex.conf /etc/httpd/conf/original/extra/httpd-autoindex.conf
then
    rm /etc/httpd/conf/original/extra/httpd-autoindex.conf
fi

if [ -f /etc/httpd/conf/original/extra/httpd-dav.conf ] && cmp -s /etc/defaults/etc/httpd/conf/original/extra/httpd-dav.conf /etc/httpd/conf/original/extra/httpd-dav.conf
then
    rm /etc/httpd/conf/original/extra/httpd-dav.conf
fi

if [ -f /etc/httpd/conf/original/extra/httpd-default.conf ] && cmp -s /etc/defaults/etc/httpd/conf/original/extra/httpd-default.conf /etc/httpd/conf/original/extra/httpd-default.conf
then
    rm /etc/httpd/conf/original/extra/httpd-default.conf
fi

if [ -f /etc/httpd/conf/original/extra/httpd-info.conf ] && cmp -s /etc/defaults/etc/httpd/conf/original/extra/httpd-info.conf /etc/httpd/conf/original/extra/httpd-info.conf
then
    rm /etc/httpd/conf/original/extra/httpd-info.conf
fi

if [ -f /etc/httpd/conf/original/extra/httpd-languages.conf ] && cmp -s /etc/defaults/etc/httpd/conf/original/extra/httpd-languages.conf /etc/httpd/conf/original/extra/httpd-languages.conf
then
    rm /etc/httpd/conf/original/extra/httpd-languages.conf
fi

if [ -f /etc/httpd/conf/original/extra/httpd-manual.conf ] && cmp -s /etc/defaults/etc/httpd/conf/original/extra/httpd-manual.conf /etc/httpd/conf/original/extra/httpd-manual.conf
then
    rm /etc/httpd/conf/original/extra/httpd-manual.conf
fi

if [ -f /etc/httpd/conf/original/extra/httpd-mpm.conf ] && cmp -s /etc/defaults/etc/httpd/conf/original/extra/httpd-mpm.conf /etc/httpd/conf/original/extra/httpd-mpm.conf
then
    rm /etc/httpd/conf/original/extra/httpd-mpm.conf
fi

if [ -f /etc/httpd/conf/original/extra/httpd-multilang-errordoc.conf ] && cmp -s /etc/defaults/etc/httpd/conf/original/extra/httpd-multilang-errordoc.conf /etc/httpd/conf/original/extra/httpd-multilang-errordoc.conf
then
    rm /etc/httpd/conf/original/extra/httpd-multilang-errordoc.conf
fi

if [ -f /etc/httpd/conf/original/extra/httpd-ssl.conf ] && cmp -s /etc/defaults/etc/httpd/conf/original/extra/httpd-ssl.conf /etc/httpd/conf/original/extra/httpd-ssl.conf
then
    rm /etc/httpd/conf/original/extra/httpd-ssl.conf
fi

if [ -f /etc/httpd/conf/original/extra/httpd-userdir.conf ] && cmp -s /etc/defaults/etc/httpd/conf/original/extra/httpd-userdir.conf /etc/httpd/conf/original/extra/httpd-userdir.conf
then
    rm /etc/httpd/conf/original/extra/httpd-userdir.conf
fi

if [ -f /etc/httpd/conf/original/extra/httpd-vhosts.conf ] && cmp -s /etc/defaults/etc/httpd/conf/original/extra/httpd-vhosts.conf /etc/httpd/conf/original/extra/httpd-vhosts.conf
then
    rm /etc/httpd/conf/original/extra/httpd-vhosts.conf
fi

if [ -f /etc/httpd/conf/original/extra/proxy-html.conf ] && cmp -s /etc/defaults/etc/httpd/conf/original/extra/proxy-html.conf /etc/httpd/conf/original/extra/proxy-html.conf
then
    rm /etc/httpd/conf/original/extra/proxy-html.conf
fi

if [ -f /etc/httpd/conf/original/httpd.conf ] && cmp -s /etc/defaults/etc/httpd/conf/original/httpd.conf /etc/httpd/conf/original/httpd.conf
then
    rm /etc/httpd/conf/original/httpd.conf
fi

if [ -f /srv/www/cgi-bin/printenv ] && cmp -s /etc/defaults/srv/www/cgi-bin/printenv /srv/www/cgi-bin/printenv
then
    rm /srv/www/cgi-bin/printenv
fi

if [ -f /srv/www/cgi-bin/printenv.vbs ] && cmp -s /etc/defaults/srv/www/cgi-bin/printenv.vbs /srv/www/cgi-bin/printenv.vbs
then
    rm /srv/www/cgi-bin/printenv.vbs
fi

if [ -f /srv/www/cgi-bin/printenv.wsf ] && cmp -s /etc/defaults/srv/www/cgi-bin/printenv.wsf /srv/www/cgi-bin/printenv.wsf
then
    rm /srv/www/cgi-bin/printenv.wsf
fi

if [ -f /srv/www/cgi-bin/test-cgi ] && cmp -s /etc/defaults/srv/www/cgi-bin/test-cgi /srv/www/cgi-bin/test-cgi
then
    rm /srv/www/cgi-bin/test-cgi
fi

if [ -f /srv/www/htdocs/index.html ] && cmp -s /etc/defaults/srv/www/htdocs/index.html /srv/www/htdocs/index.html
then
    rm /srv/www/htdocs/index.html
fi

