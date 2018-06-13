if [ -f /usr/lib/gcc/i686-pc-cygwin/5.4.0/logging.properties ] && cmp -s /etc/defaults/usr/lib/gcc/i686-pc-cygwin/5.4.0/logging.properties /usr/lib/gcc/i686-pc-cygwin/5.4.0/logging.properties
then
    rm /usr/lib/gcc/i686-pc-cygwin/5.4.0/logging.properties
fi

if [ -f /usr/lib/gcc/i686-pc-cygwin/5.4.0/security/classpath.security ] && cmp -s /etc/defaults/usr/lib/gcc/i686-pc-cygwin/5.4.0/security/classpath.security /usr/lib/gcc/i686-pc-cygwin/5.4.0/security/classpath.security
then
    rm /usr/lib/gcc/i686-pc-cygwin/5.4.0/security/classpath.security
fi

