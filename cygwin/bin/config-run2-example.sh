#!/bin/bash
CYGUTILS_VER_REQD=1.4.2
CYGUTILS_VER_INST=$(cygcheck -cd cygutils | grep cygutils | awk '{print $2}')
XMLFILE=/usr/local/bin/cygshell.xml

_version_parse_pkg_major=
_version_parse_pkg_minor=
_version_parse_pkg_micro=
# ======================================================================
# Routine: version_parse
#   safely parses a version string of the form x.y.z into three 
#   separate values.
# ======================================================================
version_parse () {
  local pkg_version="$1"
  # remove any non-digit characters from the version numbers to permit numeric
  _version_parse_pkg_major=`echo $pkg_version | cut -d. -f1 | sed s/[a-zA-Z\-].*//g`
  _version_parse_pkg_minor=`echo $pkg_version | cut -d. -f2 | sed s/[a-zA-Z\-].*//g`
  _version_parse_pkg_micro=`echo $pkg_version | cut -d. -f3 | sed s/[a-zA-Z\-].*//g`
  test -z "$_version_parse_pkg_major" && _version_parse_pkg_major=0
  test -z "$_version_parse_pkg_minor" && _version_parse_pkg_minor=0
  test -z "$_version_parse_pkg_micro" && _version_parse_pkg_micro=0
}
readonly -f version_parse

# ======================================================================
# Routine: version_ge
#   Compares two version strings: $1 ad $2 should both be version
#   strings of the form x.y.z
#   returns true if $1 >= $2, when compared as normal version strings
#   returns false otherwise
# ======================================================================
version_ge() {
  local lh_pkg_version="$1"
  local rh_pkg_version="$2"
  local lh_pkg_major
  local lh_pkg_minor
  local lh_pkg_micro
  local rh_pkg_major
  local rh_pkg_minor
  local rh_pkg_micro

  version_parse "$lh_pkg_version"
  lh_pkg_major=$_version_parse_pkg_major
  lh_pkg_minor=$_version_parse_pkg_minor
  lh_pkg_micro=$_version_parse_pkg_micro

  version_parse "$rh_pkg_version"
  rh_pkg_major=$_version_parse_pkg_major
  rh_pkg_minor=$_version_parse_pkg_minor
  rh_pkg_micro=$_version_parse_pkg_micro

  if [ $lh_pkg_major -gt $rh_pkg_major ]
  then
    return 0
  elif [ $lh_pkg_major -eq $rh_pkg_major ]
  then
    if [ $lh_pkg_minor -gt $rh_pkg_minor ]
    then
      return 0
    elif [ $lh_pkg_minor -eq $rh_pkg_minor ]
    then
      if [ $lh_pkg_micro -ge $rh_pkg_micro ]
      then
        return 0
      fi
    fi
  fi
  return 1
} # === End of version_ge() === #
readonly -f version_ge

errorMsg ()
{
  local errorcode=$?
  if ((errorcode == 0))
  then
    errorcode=1
  fi
  echo -e "\e[1;31m*** ERROR:\e[0;0m ${1:-no error message provided}"
  exit ${errorcode};
}
warnMsg()
{
  echo -e "\e[1;33m*** Warning:\e[0;0m ${1}"
}
infoMsg()
{
  echo -e "\e[1;32m*** Info:\e[0;0m ${1}"
}
readonly -f errorMsg warnMsg infoMsg


if version_ge "$CYGUTILS_VER_INST" "$CYGUTILS_VER_REQD"
then
  :
else
  msg="This script requires cygutils-$CYGUTILS_VER_REQD or better."
  if cygcheck -cd cygutils | grep cygutils >/dev/null
  then
    msg="$msg You have $CYGUTILS_VER_INST.\n"
  else
    msg="$msg You don't have cygutils installed.\n"
  fi
  errorMsg "$msg"
fi

if [ -e $XMLFILE ]
then
  mv $XMLFILE $XMLFILE.bak
  bn=${XMLFILE##*/}
  infoMsg "Moved existing file $XMLFILE to ${bn}.bak"
fi

cat >${XMLFILE} <<"EOF"
<?xml version="1.0" encoding="us-ascii"?>
<Run2Config
  xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:noNamespaceSchemaLocation="run2.xsd">
  <SelfOptions />
  <Global>
    <Environment />
  </Global>
  <GDI>
    <Environment>
      <Set var="TERM" value="xterm-256color"/>
    </Environment>
    <Target filename="/usr/bin/mintty.exe" startin="~">
      <Arg>-e /bin/bash -!-login</Arg>
    </Target>
  </GDI>
  <X11>
    <Environment>
      <Set var="TERM" value="rxvt-unicode"/>
    </Environment>
    <Target filename="/usr/bin/urxvt-X.exe" startin="~">
      <Arg>-display 127.0.0.1:0.0</Arg>
      <Arg>-ls</Arg>
      <Arg>-e /bin/bash -!-login</Arg>
    </Target>
  </X11>
</Run2Config>
EOF
infoMsg "Created ${XMLFILE}."

mkshortcut --desc="Cygwin Terminal" \
  --icon="/usr/bin/cygicons-0.dll" \
  --iconoffset=10 \
  --arguments="--display 127.0.0.1:0.0 ${XMLFILE}" \
  --name="CygShell" \
  /usr/bin/run2.exe

infoMsg "Created CygShell.lnk in $PWD."
infoMsg "You should move it to the desired location. Feel free"
infoMsg "to edit its properties, or the contents of ${XMLFILE}."
