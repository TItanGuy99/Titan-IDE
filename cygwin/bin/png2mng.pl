#! /usr/bin/perl

## This script is based on cyclo.cgi, see http://homepage2.nifty.com/sophia0/
## cyclo.cgi v0.3c (CYCLIC IMAGE) 2001.04.15 by techan

# Made slightly less brain-damaged in 2007 by Michael Pyne <michael.pyne@kdemail.net>
# * Added command line arguments.
# * Wee bit more error checking.
# * Help output.
#
# usage: png2mng <basename> <width> <height>

use Getopt::Long;
use Pod::Usage;

$basename = $ARGV[0];

# Image Width Height
$width = $ARGV[1];
$height = $ARGV[2];

# The number of repeats for base (integer > 1)
$b_repeat = 1;

# Ticks per second
$tps = 20;

# Width of number portion of filename.
$fieldWidth = 4;

# Number of file name to start with. (i.e. 0 or 1)
$start = 1;

# User wants help?
$help = 0;

## Main

$result = GetOptions(
	"basename:s" => \$basename,
	"width:i" => \$width,
	"height:i" => \$height,
	"fps:i" => \$tps,
	"fieldwidth:i" => \$fieldWidth,
	"start-number:i" => \$start,
	"help|h|?" => \$help,
	) or pod2usage(-exitstatus => 2);

pod2usage(-verbose => 1, -exitstatus => 0) if $help;

&InitCrcTable;

$r = "NG\r\n\x1a\n";
$sig_p = "\x89P".$r;
$sig_m = "\x8aM".$r;

# Check File
@png = ();
$size = 1;
for ($i=0;$size > 0;) {
	$file = $basename.sprintf('%.*d.png', $fieldWidth, $i+$start);
	$size = -s $file;
        if ($size > 0)
        {
		open(IN, "< $file") || &Error(1);
		binmode(IN);
		read(IN, $sig, 8);
		if ($sig ne $sig_p) { close(IN); &Error(2); }
		read(IN, $png[$i], $size-8);
		close(IN);
		$i++;
	}
}
$number = $i;
$it = $number * $b_repeat;
$ti = $it;

if ($number == 0) {
	print STDERR "No files were read.\n";
	exit 1;
}

$|=1;
binmode(STDOUT);

# Signature
print $sig_m;

# MHDR
$data = 'MHDR'.pack("N7",
	$width,
	$height,
	$tps,		# Ticks per second
	$number,	# Layers
	$ti,		# Frames
	$ti,		# Time
	583);		# Simplicity
&OutputData;

# DEFI define objects of the number specified by $number
for ($i=0;$i<$number;$i++) {
	$data = 'DEFI'.pack("n",
		$i+1);	# Object_id
			# Do_not_show: 1 byte (unsigned integer)
			# Concrete_flag: 1 byte (unsigned integer)
			# X_location: 4 bytes (signed integer)
			# Y_location: 4 bytes (signed integer)
			# Left_cb: 4 bytes (signed integer)
			# Right_cb: 4 bytes (signed integer)
			# Top_cb: 4 bytes (signed integer)
			# Bottom_cb: 4 bytes (signed integer)
	&OutputData;
	print $png[$i];
}
undef(@png);

# LOOP
$data = 'LOOP'.pack("CNC",
	0,	# Nest_level
	$it,	# Iteration_count
	6);	# Termination_condition:
		#  1: Decoder discretion, not cacheable.
		#  2: User discretion, not cacheable.
		# *3: External signal, not cacheable.
		#  4: Deterministic, cacheable.
		#  5: Decoder discretion, cacheable.
		#  6: User discretion, cacheable.
		# *7: External signal, cacheable.
		# Iteration_min: 4 bytes(unsigned integer)
		# Iteration_max: 4 bytes (unsigned integer)
		# Signal_number: 4 bytes (unsigned integer)
		# Additional signal_number: 4 bytes (unsigned integer)
&OutputData;

# SHOW
$data = 'SHOW'.pack("nnC",
	1,		# First_image
	$number,	# Last_image
	6);		# Show_mode:
			#  0:  Make the images potentially visible and display them.
			#  1:  Make the images invisible.
			#  2:  Display those that are potentially visible.
			#  3:  Mark images "potentially visible" but do not display
			#      them.
			#  4:  Display any that are potentially visible after toggling.
			#  5:  Do not display even if potentially visible after toggling.
			#  6:  Step through the images in the given range, making the
			#      next image potentially visible and display it.  Jump to
			#      the beginning of the range when reaching the end of the
			#      range.  Perform one step for each SHOW chunk (in reverse
			#      order if last_image < first_image).
			#  7:  Make the next image in the range (cycle) potentially
			#      visible but do not display it.
&OutputData;

# ENDL
$data = "ENDL\0";	# Nest_level: 1 byte
&OutputData;

# MEND
print "\0\0\0\0MEND! \xf7\xd5";

exit(0);

sub Error
{
my $e = $_[0];

$black = "\0\0\0";
$red = "\xff\0\0";
$white = "\xff\xff\xff";

if ($e == 1) { $plte = $white.$black; }
elsif ($e == 2) { $plte = $white.$red; }
else { $plte = $red.$white; }

$plte = "PLTE".$plte;

$p = $sig_p;
$p.="\0\0\0\rIHDR";
$p.="\0\0\0\x1e\0\0\0\x0c\x01\x03\0\0\0";
$p.="\x4f\xe0\x9f\x71";
$p.="\0\0\0\x06".$plte.&CalcCrc($plte);
$p.="\0\0\0\x2eIDAT";
$p.="\x78\x9c\x63\x60\x40\x05\xbf\xcf\xcb\x7c\x60\x68\xd2\x58\xd4\x01";
$p.="\x21\x3e\x81\x88\xe6\xf3\x4a\x40\xb1\x2e\xa5\x05\x0c\x4d\x9e\x4a";
$p.="\x13\x18\x7e\x69\xcc\xe9\0\xab\x05\0\xb0\x88\x10\xb8";
$p.="\x57\x3a\0\xa1";
$p.="\0\0\0\0IEND\xaeB`\x82";

$|=1;
# print "Content-type: $mime\n";
# print "Content-length: 121\n\n";
binmode(STDOUT);
print $p;
exit(1);
}

sub InitCrcTable
{
my $d;
@crc_table = ();
for (0 .. 255) {
	$d = $_;
	for (0 .. 7) {
		if ($d & 1) { $d = 0xedb88320 ^ (($d >> 1) & 0x7fffffff); }
		else { $d = ($d >> 1) & 0x7fffffff; }
	}
	$crc_table[$_] = $d;
}
}

sub CalcCrc
{
my $data = $_[0];
my $c = 0xffffffff;
foreach (unpack("C*", $data)) {
	$c = $crc_table[($c ^ $_) & 0xff] ^ (($c >> 8) & 0xffffff);
}
return(pack("N", ~$c));
}

sub OutputData
{
print pack("N", length($data)-4).$data.&CalcCrc($data);
undef($data);
}

sub usage()
{
}

__END__

=head1 NAME

png2mng.pl - Converts PNG files in a sequence to a MNG animation.

=head1 SYNOPSIS

png2mng.pl basename width height [options] > output.mng

Options:

    --basename     Base file name of the PNG frames.  The script adds numbers to
                   the file name until it can find no more frames.

    --width        Width of the animation.  Each PNG frame should be this width.

    --height       Height of the animation.  Each PNG frame should be this
                   height.

    --fps          Frames of animation per second (Default 20)

    --fieldwidth   Number of characters in the number (Default 4)

    --start-number Start looking for files from the given number. (e.g. foo002
                   rather than foo001.png)  (Default 1)

    --help         Show help output.

The MNG output file is printed straight to standard out so be sure to redirect
to where you want it to go.

=head1 DESCRIPTION

This script reads in a collection of PNG frames, and assembles them into a
MNG animation file.  This file can be read in any MNG viewer, including
Konqueror and Gwenview (when appropriately configured).

=head1 BUGS

Width and height are not checked to make sure individual frames are the
required size.  In fact very little to no error checking is done.

Must specify a basename.  It is not possible to just specify all the PNG files
on the command line.

All the PNG files are read into memory before the MNG starts to output.  This
makes the script unsuitable for converting a large amount of PNGs to a MNG
animation.

=head1 AUTHOR

This script is based on cyclo.cgi, see http://homepage2.nifty.com/sophia0/
 cyclo.cgi v0.3c (CYCLIC IMAGE) 2001.04.15 by techan.

Man page was written, and a few changes were made by Michael Pyne
<michael.pyne@kdemail.net>

=cut
