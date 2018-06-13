if [ -x /usr/bin/xmlcatalog ] ; then
    /usr/bin/xmlcatalog --noout --del /usr/share/xml/fontconfig/fonts.dtd /etc/xml/catalog
fi
