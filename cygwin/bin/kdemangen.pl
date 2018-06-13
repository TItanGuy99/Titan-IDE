#! /usr/bin/env perl

# kdemangen.pl
# Copyright (C)  2003  Dominique Devriese <devriese@kde.org>

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.



# Here's a little explanation about this script:
# In order to fix long-standing Debian bug #116485, I've written a
# script that takes a KDE app, and generates a nice man page..  It uses
# the app's "--author" and "--help-all" output, along with a description
# from Debian's control file to get the data.  I think the script works
# great, the man pages look almost hand-written ;) I encourage you all
# to try this out, and very much welcome any feedback, especially as to
# how to integrate this into either the Debian KDE packaging system or
# the KDE build system..

# The idea to do this with a script allows us to easily keep the man
# pages up to date, and is generally very low-trouble for the
# developer...

# The script is attached at the bottom..

# USAGE:
# Suppose you wanted to generate a man page for the KDE-Edu program
# kalzium..  Then you would
# 1 cd to /path/to/kde/srcs/kdeedu/debian  ( necessary so the script
#   finds the Debian control file.. )
# 2 run "/path/to/kdemangen.pl $(which kstars) > kstars.1"
# 3 run "man ./kstars.1" to check out the generated page..

# PROBLEMS:
# Only works for full KDE applications that use KCmdLineArgs (
# inherent to my approach, but most KDE apps fulfill this requirement
# )

use warnings;
use strict;

sub optionstonroff
  {
    my $options = shift;
    my $ret = "";
    foreach( split /\n/, $options )
      {
	if( /^  (--?[[:alpha:]]+, )?(--[[:alpha:]-]*|-[[:alpha:]])( <[[:alpha:] ]*>| [[:alpha:]]*)? *(.*)$/ )
	  {
	    my $short;
	    my $long;
	    my $arg;
	    my $desc;
	    if( $1 ) { $short = $1; } else { $short = ""; };
	    if( $2 ) { $long = $2; } else { $long = ""; };
	    if( $3 ) { $arg = $3; } else { $arg = ""; };
	    if( $4 ) { $desc = $4; } else { $desc = ""; };
	    $short =~ s/-/\\-/g;
	    $long =~ s/-/\\-/g;
	    $arg =~ s/-/\\-/g;
	    $ret .= ".TP\n";
	    $ret .= ".B $short $long $arg\n";
	    $ret .= "$desc\n";
	  }
	elsif( /^  ([[:alpha:]]+) +(.*)$/ )
	  {
	    $ret .= ".TP\n";
	    $ret .= ".B $1\n";
	    $ret .= "$2\n";
	  }
	elsif( /^ +(.*)$/ )
	  {
	    $ret .= "$1\n";
	  }
	elsif( /^(.*)$/ )
	  {
	    $ret .= ".SS $1\n";
	    # this means a header like "Qt Options:" I'm wondering
	    # what to do with this, I don't know enough nroff to
	    # format it nicely, I'm affraid..
	  }
      }
    return $ret;
  };

sub sortoptionsfromnroff {
    # Zack Cerza

    # Rather than redo Dominique's optionstonroff(), I decided
    # to make this function to sort the options sections created
    # by his function.

    # What it does is read line-by-line and first determine which
    # section it's looking at via the ".SS <SECTION>" lines. Once
    # it knows, it sets a "$in_<SECTION>" variable to "1" and
    # begins to write the section data into $<SECTION>. When it
    # gets to a line that contains only ".SS ", it sets
    # $in_<SECTION> to "0" and continues.

    # It's a little messy, but it's the only way I could 
    # get it to work with what little knowledge I had.

    # This is the first time I've used Perl. Be kind.

    my $options = shift;
    my $ret="";

    my $in_gen_opts = "0";
    my $gen_opts = "";
    my $in_qt_opts = "0";
    my $qt_opts = "";
    my $in_kde_opts = "0";
    my $kde_opts = "";
    my $in_opts = "0";
    my $opts = "";
    my $in_args = "0";
    my $args = "";

    foreach ( split /\n/, $options ) {
        if( $in_gen_opts == "1" ) {
	    if( /^(\.SS )$/ ) { $in_gen_opts = "0"; }
	    $gen_opts .= $_;
	    $gen_opts .= "\n";
	}
	if( /^(\.SS.+Generic options:)$/ ) 
	  { $in_gen_opts = "1"; $gen_opts .= $1; $gen_opts .= "\n"; }
      
        if( $in_qt_opts == "1" ) {
	    if( /^(\.SS )$/ ) { $in_qt_opts = "0"; }
	    $qt_opts .= $_;
	    $qt_opts .= "\n";
	}
        if( /^(\.SS.+Qt options:)$/ ) 
	  { $in_qt_opts = "1"; $qt_opts .= $1; $qt_opts .= "\n"; }

        if( $in_kde_opts == "1" ) {
	    if( /^(\.SS )$/ ) { $in_kde_opts = "0"; }
	    $kde_opts .= $_;
	    $kde_opts .= "\n";
	}
        if( /^(\.SS.+KDE options:)$/ ) 
	  { $in_kde_opts = "1"; $kde_opts .= $1; $kde_opts .= "\n"; }
        
	if( $in_opts == "1" ) {
	    if( /^(\.SS )$/ ) { $in_opts = "0"; }
	    $opts .= $_;
	    $opts .= "\n";
	}
        if( /^(\.SS.+Options:)$/ ) 
	  { $in_opts = "1"; $opts .= $1; $opts .= "\n"; }

        if( $in_args == "1" ) {
	    if( /^(\.SS )$/ ) { $in_args = "0"; }
	    $args .= $_;
	    $args .= "\n";
	}
        if( /^(\.SS.+Arguments:)$/ ) 
	  { $in_args = "1"; $args .= ".SS\n"; $args .= $1; $args .= "\n"; }
      }
    $ret .= $args;
    $ret .= $opts;
    $ret .= $gen_opts;
    $ret .= $kde_opts;
    $ret .= $qt_opts;
    return $ret;
  };

sub usage
  {
    print "This script generates a nice manual page for a KDE app which uses KCmdLineArgs..\n";
    print "USAGE: $0 app\n";
    print "There's more information about how to use this script in the comments at the front of the source..\n"
  };

if( $#ARGV < 0 ){
  usage();
  exit 1;
}

my $runapp = "$ARGV[0]";
if ( ! -x $runapp )
  {
    print "Error: $runapp is not executable.\n";
    exit 1;
  }
else { $runapp = "KDE_LANG=en_US $runapp"; };

my $shortdescription = `$runapp --help | sed -ne '3p'`;
chomp $shortdescription;

my $synopsis = `$runapp --help | sed -n '1p' | sed -e 's/[^:]*: //'`;
chomp $synopsis;
$synopsis =~ s/-/\\-/g;
my $appname = $synopsis;
$appname =~ s/ .*$//;
my $ucappname = uc $appname;

my $options = `$runapp --help-all | sed -e '1,4d'`;
$options = optionstonroff( $options );
$options = sortoptionsfromnroff( $options );

my $timespec = ucfirst `date '+%b %G'`;
chomp $timespec;

my $description = $shortdescription;
if( -r "control" )
  {
    $description = `cat control | sed -ne '/^Description:/,/^\$/p' | egrep -v '^\\w*:.*\$' | sed -e 's/^ //' | sed -e 's/^\\.//'`;
# leads to problems in some cases :(
#    $description =~ s/KDE ?/\n.SM KDE\n/g;
  }

my $authors = `$runapp --author | sed -ne '2,\$p' | sed -e '\$d' | sed -e 's/^ *//'`;
$authors =~ s/\n/\n.br\n/g;

print <<EOF;
.\\\" This file was generated by kdemangen.pl
.TH $ucappname 1 \"$timespec\" \"KDE\" \"$shortdescription\"
.SH NAME
$appname
\\- $shortdescription
.SH SYNOPSIS
$synopsis
.SH DESCRIPTION
$description
.SH OPTIONS
$options
.SH SEE ALSO
Full user documentation is available through the KDE Help Center.  You can also enter the URL
.BR help:/$appname/
directly into konqueror or you can run 
.BR "`khelpcenter help:/$appname/'"
from the command-line.
.br
.SH AUTHORS
.nf
$authors
EOF
