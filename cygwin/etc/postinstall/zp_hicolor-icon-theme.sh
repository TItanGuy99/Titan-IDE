if [ ! -f /usr/share/icons/hicolor/icon-theme.cache ]
then
    /usr/bin/gtk-update-icon-cache --force /usr/share/icons/hicolor || :
fi
