if [ -f /etc/php.ini ] && cmp -s /etc/defaults/etc/php.ini /etc/php.ini
then
    rm /etc/php.ini
fi

if [ -f /etc/php-fpm.conf ] && cmp -s /etc/defaults/etc/php-fpm.conf /etc/php-fpm.conf
then
    rm /etc/php-fpm.conf
fi

if [ -f /etc/php-fpm.d/www.conf ] && cmp -s /etc/defaults/etc/php-fpm.d/www.conf /etc/php-fpm.d/www.conf
then
    rm /etc/php-fpm.d/www.conf
fi

if [ -f /etc/httpd/conf.d/php7.conf ] && cmp -s /etc/defaults/etc/httpd/conf.d/php7.conf /etc/httpd/conf.d/php7.conf
then
    rm /etc/httpd/conf.d/php7.conf
fi

