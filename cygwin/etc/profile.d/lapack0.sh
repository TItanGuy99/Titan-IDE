LA_PREFIX=/usr
LA_LIBDIR=${LA_PREFIX}/lib
LA_BINDIR=${LA_LIBDIR}/lapack

# Check if the PATH variable is empty or not


if test -n "${PATH}"; then
  # PATH is not empty

  # Check if path is already in PATH
  if ! /bin/echo ${PATH} | /bin/grep -q "${LA_BINDIR}" ; then
    # Path is not already in PATH, append it to PATH
    export PATH="${PATH}:${LA_BINDIR}"
  fi
else
  # PATH is empty
  export PATH="${LA_BINDIR}"
fi

unset LA_PREFIX
unset LA_LIBDIR
unset LA_BINDIR
