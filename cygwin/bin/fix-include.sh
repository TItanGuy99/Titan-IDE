#!/bin/sh
# fix-include.sh 
#
# By Laurent Montel <montel@kde.org>  (2007)
# Licenced under the LGPL

# How to test it ? 
# go into <kde4_install_dir>/include/KDE/
# sh fix-include.sh

test_include() {
  for file in $path/* ;
  do
        if test -d $file ; then
		echo "Check include into directory : $file";
		path=$file;
	else
		# Search file which have  "#include" 
        	include=`echo "$file" | xargs grep "#include"`;
		# Get include file
        	new=`echo "$include" |perl -pi -e 's!#include !!'`;
        	new=`echo "$new" |perl -pi -e 's!\\"!!g'`;
        	# Get absolute include
		headerfile=$PWD/$new;
		# Test error
        	if test ! -f "$headerfile" ; then
                	echo "Header <$file> is not correct it try to load <$new>";
		 else
			oldpath=$PWD;
			# remove path from file => we can get class name.
			classname=`echo "$file" | perl -pi -e "s!$oldpath/!!"`;
			classexist=`grep -l $classname $headerfile`;
			if test -z "$classexist" ; then
				echo "Header <$file> which try to load  <$new> doesn't have $classname into this file. Fix it please";
				currentpath=`echo "$headerfile" | perl -pi -e "s!$new!!"`;
				#remove KDE
				currentpath=`echo "$currentpath" | perl -pi -e "s!KDE!!"`;
				classexist=`grep -lr $classname $currentpath/*`;
				if test ! -z "$classexist" ; then
					echo "This class <$classname> is defined into other header <$classexist>";
				fi
			fi
        	fi
	fi
  done 
}

path=$PWD;
test_include

