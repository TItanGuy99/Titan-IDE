#   Copyright
#
#       Copyright (C) 2011 Erwin Waterlander
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

if ( ! ${?WCDHOME} ) then
    setenv WCDHOME "$HOME/.wcd"
endif

if ( ${?WCDHOME} ) then
    alias wcd "rm -f $WCDHOME/bin/wcd.go ; /usr/lib/wcd/wcd.exe \!* ; source $WCDHOME/bin/wcd.go"
else
    alias wcd "rm -f $HOME/bin/wcd.go ; /usr/lib/wcd/wcd.exe \!* ; source $HOME/bin/wcd.go"
endif

# End of file
