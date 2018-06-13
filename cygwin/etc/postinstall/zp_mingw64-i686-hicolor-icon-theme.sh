if [ ! -f /usr/i686-w64-mingw32/sys-root/mingw/share/icons/hicolor/icon-theme.cache ]
then
    /usr/bin/gtk-update-icon-cache --force /usr/i686-w64-mingw32/sys-root/mingw/share/icons/hicolor || :
fi
