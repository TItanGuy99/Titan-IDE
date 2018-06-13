#!/usr/bin/perl
#
#   ddir - Displayhierarchical directory tree
#
#   Copyright
#
#       Copyright (C) 1995-2010 Jari Aalto
#       Copyright (C) 1994 Brian Blackmore
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
#
#       Origianally by Brian Blackmore. Modernized by Jari Aalto

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
#use File::Find;

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

my $VERSION = '2010.0316.1052';

my $DEFAULT_PATH_EXCLUDE = ''		# Matches *only path component
    . '(CVS|RCS|\.(bzr|svn|git|darcs|arch|mtn|hg))$'
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
        $LIB
        $PROGNAME
        $CONTACT
	$LICENSE
        $URL
    );

    $LICENSE	= "GPL-2+";
    $LIB        = basename $PROGRAM_NAME;
    $PROGNAME   = $LIB;

    $CONTACT     = "Jari Aalto";
    $URL         = "http://freshmeat.net/projects/ddir";

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

ddir - display hierarchical directory tree

=head1 SYNOPSIS

  ddir [options] DIR

=head1 DESCRIPTION

Display an indented directory tree using ASCII graphical characters to
represent the hierarchical structure. The directories to include or
exclude can be specified with command line options. Ddir is a Perl
implementation of the tree(1) program.

=head1 OPTIONS

=over 4

=item B<-d, --dir>

Display only directories.

=item B<-h, --help>

Print text help

=item B<--help-exclude>

Print default exclude path value when B<--exclude-vcs> is used.

=item B<--help-html>

Print help in HTML format.

=item B<--help-man>

Print help in manual page C<man(1)> format.

=item B<-i, --include REGEXP>

Include files mathing regexp. The match is done against whole path. The option
can be used multiple times.

If this option is not supplied, every file is automatically included.
The matches can be further filtered by using options B<--exclude>.

=item B<-v, --verbose LEVEL>

Print informational messages. Increase numeric LEVEL for more
verbosity.

=item B<-V, --version>

Print contact and version information.

=item B<-x, --exclude REGEXP>

Ignore files mathing regexp. The match is done against whole path. The option
can be used multiple times.

This option is applied after possible B<--include> matches.

=item B<-C, --exclude-vcs>

Exclude version control directories. See B<--help-exclude>.

=back

=head1 EXAMPLES

Show directory tree by excluding version control directories. Display
only directories:

    ddir --x-vcs --dir .

    .
    +--doc/
    |  +--manual/
    +--bin/

=head1 TROUBLESHOOTING

None.

=head1 EXAMPLES

None.

=head1 ENVIRONMENT

None.

=head1 FILES

None.

=head1 SEE ALSO

tree(1)

=head1 COREQUISITES

Uses standard Perl modules.

=head1 AVAILABILITY

Homepage is at http://freshmeat.net/projects/ddir

=head1 AUTHORS

Copyright (C) 1995-2010 Jari Aalto.
Copyright (C) 1994 Brian Blackmore.

=head1 LICENSE

This program is free software; you can redistribute and/or modify
program under the terms of GNU General Public license either version 2
of the License, or (at your option) any later version.

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
	eval "use Pod::Man;";
        $EVAL_ERROR  and  die "$id: Cannot generate Man: $EVAL_ERROR";

        my %options;
        $options{center} = 'cvs status - formatter';

        my $parser = Pod::Man->new(%options);
        $parser->parse_from_file ($PROGRAM_NAME);
    }
    else
    {
	if ( $^V =~ /5\.10/ )
	{
	    # Bug in 5.10. Cant use string ("") as a symbol ref
	    # while "strict refs" in use at
	    # /usr/share/perl/5.10/Pod/Text.pm line 249.

	    system("pod2text $PROGRAM_NAME");
	}
	else
	{
	    pod2text $PROGRAM_NAME;
	}
    }

    defined $msg  and  print $msg;
    exit 0;
}

# ****************************************************************************
#
#   DESCRIPTION
#
#       Return current year YYYY
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

sub HelpExclude ()
{
    my $id = "$LIB.HelpExclude";

    print "Default path exclude regexp: '$DEFAULT_PATH_EXCLUDE'\n";
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
        @OPT_FILE_REGEXP_EXCLUDE
        $OPT_FILE
    );

    Getopt::Long::config( qw
    (
        require_order
        no_ignore_case
        no_ignore_case_always
    ));

    my ( $help, $helpMan, $helpHtml, $version ); # local variables to function
    my ( $helpExclude, $excludeVcs , $optDir, $optVcs );

    $debug = -1;
    $OPT_FILE = 1;

    GetOptions      # Getopt::Long
    (
	  "dir"			=> \$optDir
	, "help-exclude"	=> \$helpExclude
	, "help-html"		=> \$helpHtml
	, "help-man"	        => \$helpMan
	, "h|help"	        => \$help
	, "v|verbose:i"	        => \$verb
	, "V|version"	        => \$version
	, "x|exclude=s"	        => \@OPT_FILE_REGEXP_EXCLUDE
	, "X|exclude-vcs"       => \$optVcs
    );

    $version		and  die "$VERSION $CONTACT $LICENSE $URL\n";
    $helpExclude 	and  HelpExclude();
    $help		and  Help();
    $helpMan		and  Help(-man);
    $helpHtml		and  Help(-html);
    $version		and  Version();

    $debug = 1          if $debug == 0;
    $debug = 0          if $debug < 0;

    $OPT_FILE = 0	if $optDir;

    push @OPT_FILE_REGEXP_EXCLUDE, $DEFAULT_PATH_EXCLUDE if $optVcs;
}


# ****************************************************************************
#
#   DESCRIPTION
#
#       Check if FILE matches exclude regexps.
#
#   INPUT PARAMETERS
#
#       $	Filename
#
#   RETURN VALUES
#
#       true	File in exclude list
#       false	File NOT in exclude list
#
# ****************************************************************************

sub IsExclude ($)
{
    my $id = "$LIB.IsExclude";
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
#       Resolve a pathname into its shortest version Removing any
#       references to the directory ".", any references to // , any
#       references to directory/.. and any final /
#
#   INPUT PARAMETERS
#
#       $
#	$
#
#   RETURN VALUES
#
#       $
#
# ****************************************************************************

sub Resolve ($$)
{
    my $id = "$LIB.Resolve";
    my ( $file, $direct ) = @ARG;

    $ARG = $file;        # DO NOT 'local' this variable.

    m,^/, || s,^,$direct/,;

    while ( s,/\.?/,/,  or  s,/[^/]+/\.\./,/,  or  s,/\.?$,, )
    {
        #  run the substitutions
    }

    $ARG = '/'  if  $ARG eq "";

    $ARG;
}

# ****************************************************************************
#
#   DESCRIPTION
#
#       Scan a directory and print out the files in each directory in
#	a pretty format. Note: recursive.
#
#   INPUT PARAMETERS
#
#       $
#	$
#
#   RETURN VALUES
#
#       $
#
# ****************************************************************************

sub Tree ($$);   # Forward declaration for recursive use.

sub Tree ($$)
{
    my $id = "$LIB.Tree";
    my ( $dir, $level ) = @ARG;

    local *DIRECT;

    unless ( opendir DIRECT, $dir )
    {
        warn "Could not open directory $dir\n";
        return;
    }

    my @files = readdir DIRECT ;

    # sort out non-dirs to display first, then directories.

    local $ARG;
    my ( @d, @f);

    for ( @files )
    {
	-d "$dir/$ARG" and  push(@d, $ARG), next;
	push @f, $ARG;
    }

    @files = (sort(@f), sort (@d));		# Rearrange nicely

    while ( my $name = shift @files )
    {
        #  Skip directories .  and  ..
        next if $name =~ /^\.\.?$/;

        $ARG = Resolve $name, $dir;

	next if IsExclude $ARG;

	if ( $OPT_FILE  and  -f )
	{
	    s,.*/,,;

	    print "$level$ARG\n";
	}
        elsif ( -d )
        {
            my $newname = $ARG;

            if ( -l $newname )
            {
                 #   Do not follow symlinks

                 $newname = readlink $ARG;
                 print "$level+--$name -> $newname\n";
            }
            elsif ( -r _ && -x _ )
            {
                #   We must be able to enter a directory in order to tree it

                print "$level+--$name/\n";

                if ( @files )
                {
                    Tree $newname, "$level|  ";
                }
                else
                {
                    Tree $newname, "$level   ";
                }
            }
            else
            {
                print "$level\--$name/ (unreadable)\n";
            }
        }
    }
}

# ****************************************************************************
#
#   DESCRIPTION
#
#       Main progra.
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
    Initialize();
    HandleCommandLineArgs();

    my $dir = $ARGV[0] or die "Missing directory argument. See --help.\n";

    print "$dir\n";
    Tree $dir, "";
}

Main();

# End of file
