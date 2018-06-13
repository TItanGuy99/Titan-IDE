#!/usr/bin/perl
#
#   copyright-update -- Utility to update copyright information in files
#
#   Copyright
#
#       Copyright (C) 2000-2013 Jari Aalto
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
#   Documentation
#
#       To read manual, start this program with option: --help

# ****************************************************************************
#
#   Standard perl modules
#
# ****************************************************************************

use strict;

use autouse 'Pod::Text'     => qw( pod2text );
use autouse 'Pod::Html'     => qw( pod2html );

use English qw( -no_match_vars );
use Getopt::Long;
use File::Basename;
use File::Find;
use charnames q(:full);

IMPORT: # This is just a syntactic sugar: actually no-op
{
    #   Import following environment variables

    use Env;
    use vars qw
    (
	$NAME
	$EMAIL
    );
}

# ****************************************************************************
#
#   GLOBALS
#
# ****************************************************************************

use vars qw ( $VERSION );

#   This is for use of Makefile.PL and ExtUtils::MakeMaker
#
#   The following variable is updated by custom Emacs setup whenever
#   this file is saved.

my $VERSION = '2015.0928.0638';

my $DEFAULT_PATH_EXCLUDE =              # Matches *only path component
    '(CVS|RCS|\.(bzr|svn|git|darcs|arch|mtn|hg))$'
    ;

my $DEFAULT_FILE_EXCLUDE =              # Matches *only* file component
    '[#~]$'
    . '|\.[#]'
    . '|\.(s?o|l?a|bin|com|exe|class|elc)$'
    . '|\.(ods|odt|pdf|ppt|xls|rtf)$'
    . '|\.(xpm|jpg|png|gif|tiff|bmp)$'
    . '|(config.guess|config.sub|ltconfig|depcomp|missing|COPYING)$'
    ;

# ****************************************************************************
#
#   DESCRIPTION
#
#       Set global variables for the program
#
#   INPUT PARAMETERS
#
#       none
#
#   RETURN VALUES
#
#       none
#
# ****************************************************************************

sub Initialize ()
{
    use vars qw
    (
	$LICENSE
	$CONTACT
	$URL

	$LIB
	$PROGNAME
    );

    $LICENSE    = "GPL-2+";
    $CONTACT    = "Jari Aalto";
    $URL        = "http://freecode.com/projects/copyright-update";

    $LIB        = basename $PROGRAM_NAME;
    $PROGNAME   = $LIB;

    $OUTPUT_AUTOFLUSH = 1;
}

# ****************************************************************************
#
#   DESCRIPTION
#
#       Help function and embedded POD documentation
#
#   INPUT PARAMETERS
#
#       none
#
#   RETURN VALUES
#
#       none
#
# ****************************************************************************

=pod

=head1 NAME

copyright-update - Update Copyright information in files

=head1 SYNOPSIS

  copyright-update [options] FILE [FILE ...]
  copyright-update [options] --recursive PATH [PATH ...]

=head1 DESCRIPTION

Update the copyright information in set of files, possibly
recursively, matching content criteria. The updating affects copyright
year, GPL address information etc.

The line must have word "Copyright", a space, three characters '(C)'
(or a U+00A9 UTF copyright sign), a space, and the range of
years. Varying amount of spaces and tabs are permitted, but there must
be no spaces around the dash-character in YEAR-YEAR. Examples:

	    A whitespace, or multiple, required
	    |   |           No space between years
	    |   |           |
   Copyright (C)        YYYY-YYYY
   Copyright: (C)       YYYY-YYYY
	    |
	    A colon is optional

By default certain files and paths are always ignored; like version
control directories, backups files, object files and binary files
according to Perl's C<-T> file test. Run program with option
B<--help-exclude> to see exclude path list.

=head1 OPTIONS

=head2 Run options

=over 4

=item B<-a, --auto>

In automatic mode, the author's name is read from environment variable
NAME and only lines matching 'Copyright.*$NAME' are affected. If NAME
is not set, read information from EMAIL.

If neither NAME nor EMAIL exists in evenvironemt, or if their values
are not in a recognizable formats (see section ENVIRONMENT), this
options does nothing.

This option effectively tries to preset value for the B<--line> option.

=item B<-c, --code>

Preset B<--include> to match common code files: .c, .h, .cc, .hh, .cpp,
.c++, .hpp, .C, .pl, .py, .sh and .rb

=item B<-d, --debug LEVEL>

Turn on debug. Level can be in range 0-10.

=item B<-f, --fsf-address>

Change License paragraphs that refer to FSF address. The FSF's current
recommendation is to redirect inquiries about licences to their URL.

Effectively replace paragraphs:

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

  You should have received a copy of the GNU General Public License
  along with this package; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301USA

With this:

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.

=item B<-i, --include REGEXP>

Include files matching regexp. The match is done against whole path.

If this option is not supplied, every file is automatically included.
The matches can be further filtered by using option B<--exclude>.

This option can be used multiple times. See also option B<--code>.

=item B<-l, --line REGEXP>

Change only lines which match REGEXP. The match is case-insensitive.

=item B<-r, --recursive>

Recursively search all directories given in command line.

=item B<-R, --regexp REGEXP>

Change only files whose content matches REGEXP. The file is read in as
a one big string so that it's possible to match using Perl regular
expressions across the whole file. An example:
'(?smi)This.*multi.*line.*match'. See perlre(1) for more information
about 'smi' and other modifiers.

This option can be used as a preliminary I<Content criteria>, to
select files before B<--line> option finds the correct Copyright
lines.

=item B<-t, --test, --dry-run>

Run in test mode. Show what would happen. No files are changed.

=item B<-v, --verbose LEVEL>

Print informational messages. Increase numeric LEVEL for more
verbosity.

=item B<-x, --exclude REGEXP>

Ignore files matching regexp. The match is done against whole path.
The option can be used multiple times.

This option is applied after possible B<--include> matches.

=item B<-y, --year YEAR>

Update files using YEAR. Value must be four digits.

The default operation is to use currect year, so this option is not
necessary in normal use. Use case: you plan to take a long holiday
before year's end and want to update the next year's value beforehand.

=item B<-Y, --no-year>

Disable updating year.

=back

=head2 Miscellaneus options

=over 4

=item B<-h, --help>

Display help.

=item B<--help-exclude>

Display default values used to exclude paths and files.

=item B<--help-html>

Display help in HTML format.

=item B<--help-man>

Display help in manual page C<man(1)> format.

=item B<-V, --version>

Display contact and version information.

=back

=head1 EXAMPLES

The primary use is to update files to reflect current year; option
B<--year> is implicit:

   copyright-update *

To test what would happen:

   copyright-update --verbose 1 --test *

Update only C-code file:

   copyright-update --verbose 1 --include '\.[ch]$' --recursive .

It is possible to restrict updating files recursively to only those
files whose content match regexp. Here, the lines affected are those
that match B<--line> regular expression.

   copyright-update \
	--regexp  '(?i)Author:.*John.*Doe' \
	--line    '\bFoo\b' \
	--ignore  '\.(bak|bup|[~#]])$' \
	--verbose 1 \
	--year    2013 \
	--test \
	--recursive \
	.

=head1 TROUBLESHOOTING

See option B<--debug>.

=head1 ENVIRONMENT

=over 4

=item EMAIL

In the form "firstname.lastname@example.com"; that is, without the
angles <>. If set, the value is used in option B<--auto> only if
environment variable NAME is not set.

In order to find first and lastname, the localpart in email address
must match case insensitive regexp C<'^[a-z-]+\.[a-z-]+@'>:

    address@example.com            Not used, not in form First.Last
    +------ +----------

    mr.first.lastname@example.com  Not used, likewise
    +---------------- +----------
    |                 |
    Localpart         Domain part

=item NAME

In the form "Firstname Lastname". If set, the value is used in option
B<--auto>.

=back

=head1 FILES

None.

=head1 EXIT STATUS

Not defined.

=head1 SEE ALSO

licensecheck(1)

=head1 DEPENDENCIES

Uses only standard Perl modules.

=head1 BUGS AND LIMITATIONS

The Copyright stanzas searched with option B<--fsf-address> must be
exactly like in the FSF recommendation in order for them to be
noticed. See STANDARDS.

=head1 STANDARDS

C<How to use GNU licenses for your own software>
http://www.gnu.org/copyleft/gpl-howto.html

C<Information for maintainers of GNU software (6.5 Copyright Notices)>
http://www.gnu.org/prep/maintain/html_node/Copyright-Notices.html

C<Information for maintainers of GNU software (6.6 License Notices)>
http://www.gnu.org/prep/maintain/html_node/License-Notices.html#License-Notices

=head1 AVAILABILITY

Homepage is at http://freecode.com/projects/copyright-update

=head1 AUTHOR

Jari Aalto

=head1 LICENSE AND COPYRIGHT

Copyright (C) 2000-2013 Jari Aalto

This program is free software; you can redistribute and/or modify
program under the terms of GNU General Public license either version 2
of the License, or (at your option) any later version.
For more information, see see <http://www.gnu.org/licenses/>.

=cut

sub Help (;$$)
{
    my $id   = "$LIB.Help";
    my $type = shift;  # optional arg, type
    my $msg  = shift;  # optional arg, why are we here...

    if ( $type eq -html )
    {
	pod2html $PROGRAM_NAME;
    }
    elsif ( $type eq -man )
    {
	eval { require Pod::Man; 1 }
	    or die "$id: Cannot generate Man: $EVAL_ERROR";

	my %options;
	$options{center} = "User commands";

	my $parser = Pod::Man->new(%options);
	$parser->parse_from_file ($PROGRAM_NAME);
    }
    else
    {
	system "perl -S pod2text $PROGRAM_NAME"
    }

    defined $msg  and  print $msg;
    exit 0;
}

# ****************************************************************************
#
#   DESCRIPTION
#
#       Display default excludes.
#
#   INPUT PARAMETERS
#
#       None
#
#   RETURN VALUES
#
#       None
#
# ****************************************************************************

sub HelpExclude ()
{
    my $id = "$LIB.HelpExclude";

    print "Default path exclude regexp: '$DEFAULT_PATH_EXCLUDE'\n";
    print "Default file exclude regexp: '$DEFAULT_FILE_EXCLUDE'\n";
}

# ****************************************************************************
#
#   DESCRIPTION
#
#       Return current year YYYY.
#
#   INPUT PARAMETERS
#
#       None
#
#   RETURN VALUES
#
#       number      YYYY
#
# ****************************************************************************

sub Year ()
{
    my $id = "$LIB.Year";
    1900 + (localtime time() )[5];
}

# ****************************************************************************
#
#   DESCRIPTION
#
#       Read command line arguments and their parameters.
#
#   INPUT PARAMETERS
#
#       None
#
#   RETURN VALUES
#
#       Globally set options.
#
# ****************************************************************************

sub HandleCommandLineArgs ()
{
    my $id = "$LIB.HandleCommandLineArgs";

    use vars qw
    (
	$test
	$verb
	$debug

	$YEAR
	$OPT_AUTOMATIC
	@OPT_FILE_REGEXP_EXCLUDE
	@OPT_FILE_REGEXP_INCLUDE
	$OPT_FSF_ADDRESS
	$OPT_LINE_REGEXP
	$OPT_NO_YEAR
	$OPT_RECURSIVE
	$OPT_REGEXP
    );

    Getopt::Long::config( qw
    (
	no_ignore_case
	no_ignore_case_always
    ));

    my ( $help, $helpMan, $helpHtml, $version ); # local variables to function
    my ( $helpExclude, $code );

    $debug = -1;

    GetOptions      # Getopt::Long
    (
	  "a|auto"          => \$OPT_AUTOMATIC
	, "fsf-address"     => \$OPT_FSF_ADDRESS
	, "c|code"          => \$code
	, "d|debug:i"       => \$debug
	, "dry-run"         => \$test
	, "help-exclude"    => \$helpExclude
	, "help-html"       => \$helpHtml
	, "help-man"        => \$helpMan
	, "h|help"          => \$help
	, "include=s"       => \@OPT_FILE_REGEXP_INCLUDE
	, "line=s"          => \$OPT_LINE_REGEXP
	, "r|recursive"     => \$OPT_RECURSIVE
	, "R|regexp=s"      => \$OPT_REGEXP
	, "test"            => \$test
	, "v|verbose:i"     => \$verb
	, "V|version"       => \$version
	, "year=i"          => \$YEAR
	, "Y|no-year"       => \$OPT_NO_YEAR
	, "x|exclude=s"     => \@OPT_FILE_REGEXP_EXCLUDE
    );

    $version            and  die "$VERSION $CONTACT $LICENSE $URL\n";
    $helpExclude        and  HelpExclude();
    $help               and  Help();
    $helpMan            and  Help(-man);
    $helpHtml           and  Help(-html);
    $version            and  Version();

    $debug = 1          if $debug == 0;
    $debug = 0          if $debug < 0;

    $YEAR = Year()  unless defined $YEAR;

    unless ( $YEAR =~ m,^\d{4}$, )
    {
	die "$id: Option --year must be given with four digits [$YEAR]";
    }

    if ( defined $verb  and  $verb == 0 )
    {
	$verb = 1;
    }

    if ( $code )
    {
	push @OPT_FILE_REGEXP_INCLUDE,
	    '\.([Cch]|cc|hh|cpp|c\+\+|hpp|p[y]l|sh|rb)';
    }

    $verb = 1  if  $test and $verb == 0;
    $verb = 5  if  $debug;

    if ( $OPT_LINE_REGEXP  and  $OPT_AUTOMATIC )
    {
	die "$id: option --auto cannot be used togethet with --line";
    }

    if ( $OPT_AUTOMATIC )
    {
	if ( $NAME )
	{
	    local $ARG = $NAME;

	    if ( /^([a-z-]+) +([a-z-]+)/i )
	    {
		$verb > 1 and  print "$id: Using NAME: $NAME\n";
		$OPT_LINE_REGEXP = "${1}[ \\t]+$2";
	    }
	    else
	    {
		$verb  and  print "$id: WARN: NAME not recognized: '$NAME'\n";
	    }
	}

	if ( not $OPT_LINE_REGEXP  and  $EMAIL )
	{
	    local $ARG = $EMAIL;

	    if ( /^([a-z-]+)\.([a-z-]+)@/i )
	    {
		$verb > 1  and  print "$id: Using EMAIL: $EMAIL\n";
		$OPT_LINE_REGEXP = "${1}[ \\t]+$2";
	    }
	    else
	    {
		$verb  and  print "$id: WARN: EMAIL not recognized: '$EMAIL'\n";
	    }

	    unless ( $OPT_LINE_REGEXP )
	    {
		die "$id: information for option --auto missing";
	    }
	}

	$verb > 1  and  print "$id: automatic preset of --line '$OPT_LINE_REGEXP'\n";
    }
}

# ****************************************************************************
#
#   DESCRIPTION
#
#       Change FSF Address
#
#   INPUT PARAMETERS
#
#       $content        File content.
#
#   RETURN VALUES
#
#       $string         File content or empty if no chnages.
#
# ****************************************************************************

sub FsfAddress ( $ ; $ )
{
    my $id     = "$LIB.FsfAddress";
    local $ARG = shift;
    my $file   = shift;

    my $X = $debug ? "$id: " : "";
    my $done;

    s
    {^([^\r\n]*)You \s+ should \s+ have \s+ received
	 .*? (write \s+ to | contact .*? Foundation)
	 .*? USA[ \t.]*
    }
    {$1You should have received a copy of the GNU General Public License\n$1along with this program. If not, see <http://www.gnu.org/licenses/>.}smix
    and $done++;

    $ARG if $done;
}

# ****************************************************************************
#
#   DESCRIPTION
#
#       Handle Single file
#
#   INPUT PARAMETERS
#
#       %hash       -file   => [filename list]
#                   -regexp => Regexp to match file content.
#                              If regexp is not found in file, file is not
#                              handled.
#
#   RETURN VALUES
#
#       none
#
# ****************************************************************************

sub HandleFile ( % )
{
    my $id  = "$LIB.HandleFile";
    my %arg = @ARG;

    my $X       = $debug ? "$id: " : "";
    my @files   = @{ $arg{-file} };
    my $regexp  = $arg{-regexp};
    my $linere  = $arg{-line};

    unless ( @files )
    {
	warn "$id: -file argument is empty: ",  $arg{-file};
	return;
    }

    $debug  and  print "$id: -file [@files], ",
		       "-regexp '$regexp' ",
		       "-line '$linere'\n"
		       ;

    my $ffile;

    sub Print(@);
    local *Print = sub (@)
    {
	print "${X}$ffile: ", @_, "\n";
    };

    local $ARG;

    for my $file ( @files )
    {
	$ffile = $file;                 # For Print()

	$debug  and  print "$id: $file: open\n";

	# ..................................................... read ...

	{
	    my $FILE;

	    unless ( open my $FILE, "<", $file )
	    {
		$verb  and  Print "ERROR: cannot open";
		next;
	    }
	    else
	    {
		binmode $FILE;
		local $INPUT_RECORD_SEPARATOR = undef;
		$ARG = <$FILE>;
		close $FILE  or  warn "Close $file error $ERRNO";

		unless ( /\w/ )
		{
		    $verb  and  Print "WARN: empty file";
		    return;
		}
	    }
	}

	if ( $regexp )
	{
	    unless ( /$regexp/o )
	    {
		$verb  and  Print "WARN: failed regexp check: $regexp";
		next;
	    }
	}

	my $done;
	my $msg = $test ? "Would change" : "Changed";

	if ( $OPT_FSF_ADDRESS  and  (my $fsf = FsfAddress $ARG, $file) )
	{
	    Print "$msg FSF address to URL";
	    $ARG = $fsf;
	    $done++;
	}

	# Perl Unicode also would accpt x{a9}/, but \N{} is more readable
	# http://en.wikipedia.org/wiki/Copyright_symbol

	my $ch   = "\N{COPYRIGHT SIGN}";
	my $sign = '(?:' . $ch . '|\([Cc]\))';
	my $yyyy = '\d{4}';
	my $copy = '(?:(?i)Copyright):?[ \t]+' . $sign . '[ \t]+' . $yyyy;

	# In manual pages the hyphen is quoted as:
	# Copyright (C) YYYY\-YYYY

	my $repeat  = '\x5C?-';         # HEX 5C = backslash (\)

	#  If we find the regexp, then check if YEAR is different
	#  and finally do substitution.
	#
	#  If everything went ok, replace file.

	unless ( /$copy$repeat($yyyy)/oi )
	{
	    $verb  > 1  and  Print "No Copyright line" ;
	    $debug > 2  and  print "$id: Match regexp: $copy$repeat($yyyy)\n";
	}

	my $y = $1;
	$y = "" if $OPT_NO_YEAR;

	if ( $y  and  $y eq $YEAR )
	{
	    $verb > 2  and  Print "Copyright is already $YEAR";
	    $y = "";
	}

	unless ( $OPT_NO_YEAR )
	{
	    my $i = 0;

	    if ( $linere )
	    {
		if ( $debug > 1 )
		{
		    warn "s/(?:$linere).*\\K($copy$repeat)($yyyy)/\${1}$YEAR/gmi\n";
		    warn "s/($copy$repeat)$yyyy(.*$linere)/\${1}$YEAR\${2}/gmi\n";
		}

		s/(?:$linere).*\K($copy$repeat)$yyyy/$1$YEAR/gmi and $i++;
		s/($copy$repeat)$yyyy(.*$linere)/$1$YEAR$2/gmi and $i++;

	    }
	    else
	    {
		s/($copy$repeat)$yyyy/$1$YEAR/gmi and $i++;
	    }

	    $done += $i;
	    $debug and $i and print "$id: matches --line '$linere'\n";

	    $y = ""  unless $i;
	}

	$verb   and  $y  and  Print "$msg $y => $YEAR";

	$test     and  next;
	not $done and  next;

	my $FILE;

	unless ( open $FILE, ">", $file )
	{
	    Print "ERROR: Cannot open for write";
	}
	else
	{
	    $verb > 2  and  Print "wrote";

	    binmode $FILE;
	    print $FILE $ARG;
	    close $FILE  or  warn "Close $file error $ERRNO";
	}
    }
}

# ****************************************************************************
#
#   DESCRIPTION
#
#       Check if FILE matches exclude regexps.
#
#   INPUT PARAMETERS
#
#       $       Filename
#
#   RETURN VALUES
#
#       true    File in exclude list
#       false   File NOT in exclude list
#
# ****************************************************************************

sub IsExclude ($)
{
    my $id   = "$LIB.IsExclude";
    local $ARG = shift;

    @OPT_FILE_REGEXP_EXCLUDE  or  return 0;

    for my $re ( @OPT_FILE_REGEXP_EXCLUDE )
    {

	if ( /$re/ )
	{
	    $verb > 2  and  print "$id: '$re' matches: $ARG\n";
	    return 1
	}
    }

    return 0;
}

# ****************************************************************************
#
#   DESCRIPTION
#
#       Check if FILE matches include regexps.
#
#   INPUT PARAMETERS
#
#       $       Filename
#
#   RETURN VALUES
#
#       true    File in include list
#       false   File NOT in include list
#
# ****************************************************************************

sub IsInclude ($)
{
    my $id   = "$LIB.IsInclude";
    local $ARG = shift;

    @OPT_FILE_REGEXP_INCLUDE  or  return 1;

    for my $re ( @OPT_FILE_REGEXP_INCLUDE )
    {

	if ( /$re/ )
	{
	    $verb > 2  and  print "$id: '$re' matches: $ARG\n";
	    return 1
	}
    }

    return 0;
}

# ****************************************************************************
#
#   DESCRIPTION
#
#       Recursively find out all files and change their content.
#
#   INPUT PARAMETERS
#
#       None. This function is called from File::FInd.pm library
#
#   RETURN VALUES
#
#       None.
#
# ****************************************************************************

sub wanted ()
{
    my $id = "$LIB.wanted";

    my $dir  = $File::Find::dir;
    my $file = $File::Find::name;  # complete path

    if ( $dir =~ m,$DEFAULT_PATH_EXCLUDE,o )
    {
	$File::Find::prune = 1;
	$debug  and  print "$id: DEfault path exclude: $dir\n";
	return;
    }

    if ( $file =~ m,$DEFAULT_FILE_EXCLUDE,o )
    {
	$debug  and  print "$id: Default file exclude: $file\n";
	return;
    }

    if ( -f )
    {
	if ( $verb > 3 )
	{
	    print "$id: $file\n";
	}

	unless ( -T )
	{
	    $debug  and
		print "$id: Exclude binary file (internal test): $file\n";
	}

	IsInclude $file  or  return;
	IsExclude $file  and return;

	HandleFile -file   => [$file],
	           -line   => $OPT_LINE_REGEXP,
	           -regexp => $OPT_REGEXP;
    }
}

# ****************************************************************************
#
#   DESCRIPTION
#
#       Expand files in list. Win32 support
#
#   INPUT PARAMETERS
#
#       @       list of file glob patterns.
#
#   RETURN VALUES
#
#       @       list of filenames
#
# ****************************************************************************

sub FileGlobs ( @ )
{
    my $id   = "$LIB.FileGlobs";
    my @list = @ARG;
    not @list  and  die "$id: No files to expand. Argument list is empty.";

    my @files;

    for my $glob ( @list )
    {
	#       Win32 can't expand "*". We must do it here.
	#       Grep only FILES, not directories.

	push @files, grep { -f } glob $glob;
    }

    $debug  and  print "$id: RETURN [@files]\n";
    @files;
}

# ****************************************************************************
#
#   DESCRIPTION
#
#       Main function
#
#   INPUT PARAMETERS
#
#       None
#
#   RETURN VALUES
#
#       None
#
# ****************************************************************************

sub Main ()
{
    my $id = "$LIB.Main";

    Initialize();
    HandleCommandLineArgs();

    unless ( @ARGV )
    {
	die "What files to change? See --help.";
    }

    $debug  and  print "$id: ARGV [@ARGV]\n";

    # .......................................... expand command line ...


    if ( $OPT_RECURSIVE )
    {
	find( {wanted => \&wanted, no_chdir => 1},  @ARGV );
    }
    else
    {
	my @files = FileGlobs @ARGV;

	unless (@files)
	{
	    $verb  and  warn "[WARN] No files matching glob(s): @ARGV\n";
	    return;
	}

	HandleFile -file   => [@files],
	           -line   => $OPT_LINE_REGEXP,
	           -regexp => $OPT_REGEXP;
    }
}

Main();

# End of file

