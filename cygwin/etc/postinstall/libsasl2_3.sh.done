# Move any existing *.conf files from /usr/lib/sasl2 to /etc/sasl2,
# but only if there are no *.conf files in /etc/sasl2.

etc_files=/etc/sasl2/*.conf
if [ "$(/usr/bin/echo /etc/sasl2/*.conf)" = '/etc/sasl2/*.conf' \
     -a "$(/usr/bin/echo /usr/lib/sasl2/*.conf)" != '/usr/lib/sasl2/*.conf' ]
then
  /usr/bin/mv /usr/lib/sasl2/*.conf /etc/sasl2
fi
