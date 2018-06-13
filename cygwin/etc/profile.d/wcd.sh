#   Copyright
#
#       Copyright (C) 2011-2014 Erwin Waterlander
#       Copyright (C) 2009-2011 Jari Aalto
#
#   License
#
#       This program is free software; you can redistribute it and/or modify
#       it under the terms of the GNU General Public License as published by
#       the Free Software Foundation; either version 2 of the License, or
#       (at your option) any later version.
#
#       This program is distributed in the hope that it will be useful,
#       but WITHOUT ANY WARRANTY; without even the implied warranty of
#       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#       GNU General Public License for more details.
#
#       You should have received a copy of the GNU General Public License
#       along with this program. If not, see <http://www.gnu.org/licenses/>.
#
#   Description
#
#       Define a shell alias for wcd(1), which itself change
#       directories, so it must be done in a shell alias.
#
#       This file is in /etc/profile.d/ and it should be sourced from
#       a shell startup file: ~/.<shell>rc


if [ -z "$WCDHOME" ]
then
    export WCDHOME="$HOME/.wcd"
fi

wcd ()
{
    typeset go="${WCDHOME:-${HOME}}/bin/wcd.go"

    rm -f "$go" 2> /dev/null

    /usr/lib/wcd/wcd.exe "$@"

    [ -f "$go" ] && . "$go"
}

# End of file
