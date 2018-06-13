if [ ! -f /usr/share/applications/mimeinfo.cache ]
then
    /usr/bin/update-desktop-database /usr/share/applications
fi
find /usr/share/applications -name '*.desktop' -cnewer /usr/share/applications/mimeinfo.cache -exec /usr/bin/update-desktop-database /usr/share/applications \;
