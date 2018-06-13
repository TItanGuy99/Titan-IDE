#!/bin/sh

# This method gives some kind of status message in the title bar of Konsole,
# xterm, etc.. Thanks have to go to Malte Starostik
# <malte@kde.org> for the code :-)
set_title() {
if ([ "$TERM" = "xterm" ] || [ "$TERM" = "xterm-color" ] || [ "$TERM" = "screen" ]) && tty -s; then
  echo -ne "\033]0;$1\007"
fi
}
. ./kde-buildrc
set_title "Progress of kde-build script..."

cd $KDELOGDIR
while true; do 
    dir=`ls -t | head -n 1 | xargs grep "Entering directory" | tail -n 1 | awk "{print \\$4}" | sed "s'^$KDESRCDIR/''g"`
    set_title "Building $dir"
    clear
    grep -hi "time needed" *build* | \
	sed "s/\:T/ T/g"
    sleep 5
done;
