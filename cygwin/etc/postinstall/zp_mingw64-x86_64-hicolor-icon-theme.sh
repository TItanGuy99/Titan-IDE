if [ ! -f /usr/x86_64-w64-mingw32/sys-root/mingw/share/icons/hicolor/icon-theme.cache ]
then
    /usr/bin/gtk-update-icon-cache --force /usr/x86_64-w64-mingw32/sys-root/mingw/share/icons/hicolor || :
fi
