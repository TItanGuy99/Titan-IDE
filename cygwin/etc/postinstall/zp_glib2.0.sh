if [ ! -f /usr/lib/gio/modules/giomodule.cache ]
then
    /usr/bin/gio-querymodules /usr/lib/gio/modules
fi
find /usr/lib/gio/modules -name '*.dll' -cnewer /usr/lib/gio/modules/giomodule.cache -exec /usr/bin/gio-querymodules /usr/lib/gio/modules \;

if [ ! -f /usr/share/glib-2.0/schemas/gschemas.compiled ]
then
    /usr/bin/glib-compile-schemas /usr/share/glib-2.0/schemas
fi
find /usr/share/glib-2.0/schemas -name '*.xml' -cnewer /usr/share/glib-2.0/schemas/gschemas.compiled -exec /usr/bin/glib-compile-schemas /usr/share/glib-2.0/schemas \;
