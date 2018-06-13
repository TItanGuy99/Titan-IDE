#!/bin/sh
prefix=/usr
incdir=${prefix}/include/noX
libdir=${prefix}/lib/noX

(cd ${incdir}; 
  rm -f simx.h xpm.h || /bin/true
  ln -fs X11/xpm.h xpm.h
  ln -fs X11/simx.h simx.h
)

(cd ${libdir}; 
  rm -f libXpm.dll.a libXpm.a || /bin/true
  ln -fs libXpm-noX.dll.a libXpm.dll.a
  ln -fs libXpm-noX.a     libXpm.a
)

