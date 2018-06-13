if [ ! -f /usr/share/icons/oxygen/icon-theme.cache ]
then
    /usr/bin/gtk-update-icon-cache --force /usr/share/icons/oxygen || :
fi
