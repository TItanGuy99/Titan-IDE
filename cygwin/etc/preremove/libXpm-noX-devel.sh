#!/bin/sh
prefix=/usr
incdir=${prefix}/include/noX
libdir=${prefix}/lib/noX

(cd ${incdir}; 
  rm -f simx.h xpm.h || /bin/true
)

(cd ${libdir};
  rm -f libXpm.dll.a libXpm.a || /bin/true
)

