/usr/bin/install-catalog --remove /etc/sgml/xml-docbook-4.5.cat /etc/sgml/sgml-docbook.cat
/usr/bin/install-catalog --remove /etc/sgml/xml-docbook-4.5.cat /usr/share/sgml/docbook/xml-dtd-4.5/docbook.cat

/usr/bin/rm -f /etc/xml/docbook
/usr/bin/rm -f /usr/share/sgml/docbook/xml-dtd-4.5/*docbook*.dtd
/usr/bin/build-docbook-catalog

