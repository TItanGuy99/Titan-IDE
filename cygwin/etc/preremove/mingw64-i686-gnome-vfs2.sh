export GCONF_CONFIG_SOURCE="xml:merged:/usr/i686-w64-mingw32/sys-root/mingw/etc/gconf/gconf.xml.defaults"
/usr/bin/gconftool-2 --makefile-uninstall-rule /usr/i686-w64-mingw32/sys-root/mingw/etc/gconf/schemas/desktop_default_applications.schemas > /dev/null 2>&1
/usr/bin/gconftool-2 --makefile-uninstall-rule /usr/i686-w64-mingw32/sys-root/mingw/etc/gconf/schemas/desktop_gnome_url_handlers.schemas > /dev/null 2>&1
/usr/bin/gconftool-2 --makefile-uninstall-rule /usr/i686-w64-mingw32/sys-root/mingw/etc/gconf/schemas/system_dns_sd.schemas > /dev/null 2>&1
/usr/bin/gconftool-2 --makefile-uninstall-rule /usr/i686-w64-mingw32/sys-root/mingw/etc/gconf/schemas/system_http_proxy.schemas > /dev/null 2>&1
/usr/bin/gconftool-2 --makefile-uninstall-rule /usr/i686-w64-mingw32/sys-root/mingw/etc/gconf/schemas/system_smb.schemas > /dev/null 2>&1

