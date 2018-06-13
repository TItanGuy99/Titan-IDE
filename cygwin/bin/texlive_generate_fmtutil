#! /bin/bash

# This script recreates /etc/texmf/web2c/fmtutil.cnf based on the
# installed packages as reflected in /usr/share/tlpkg/texlive.tlpdb.

confdir=/etc/texmf/web2c
conffile=${confdir}/fmtutil.cnf
if [ -f ${conffile} ]
then
    mv -fv ${conffile} ${conffile}.bak
fi
/usr/bin/tlmgr generate --dest ${conffile} _fmtutil
