set LA_PREFIX=/usr
set LA_LIBDIR=${LA_PREFIX}/lib
set LA_BINDIR=${LA_LIBDIR}/lapack

set newpath=($path:q $LA_BINDIR:q)
foreach f ($path:q)
    if ( "$f" == "$LA_BINDIR" ) then
        set newpath=($path:q)
        break
    endif
end
set path=($newpath:q)

