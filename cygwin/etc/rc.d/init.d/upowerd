#! /bin/bash
#
# upowerd   Start/Stop the UPower daemon.
# v1.0 2004-10-18 Reini Urban
# v2.0 2014-07-24 Yaakov Selkowitz yselkowitz@cygwin.com
#
# chkconfig: 2345 90 60
# description: UPower daemon
# processname: upowerd

PREFIX=/usr
LOGFILE=/var/log/upowerd.log

# Source function library.
if [ -f /etc/init.d/functions ] ; then
  . /etc/init.d/functions
fi

RETVAL=0

# See how we were called.

prog="upowerd"
DAEMON="/usr/libexec/upowerd"
DESCRIPTION="UPower daemon"

test -f $DAEMON || exit 0

# Source configuration
if [ -f /etc/sysconfig/$prog ] ; then
    . /etc/sysconfig/$prog
fi

start() {
        echo -n $"Starting $prog: "
	# check if cygrunsrv process
        cygrunsrv --start $prog
        RETVAL=$?
        echo
        [ $RETVAL -eq 0 ] && echo "done."
        return $RETVAL
}

stop() {
        echo -n $"Stopping $prog: "
	cygrunsrv --stop $prog
	# this really needs a long time to stop.
        RETVAL=$?
        echo "."
        [ $RETVAL -eq 0 ] && echo "done."
        return $RETVAL
}

status() {
        # service status
        cygrunsrv -Q $prog
}

restart() {
        echo -n $"Restarting $prog: "
        $0 stop
        sleep 1
        $0 start
        echo "done."
}

install() {
        echo -n $"Installing $prog daemon: "
	# some safety measures
	touch $LOGFILE
	chgrp 18 $LOGFILE
	chmod g+w $LOGFILE
	#it was compiled with uid=18
	cygrunsrv --install $prog --path $DAEMON --disp "CYGWIN $DESCRIPTION" --dep messagebus
        echo "done."
}

uninstall() {
        echo -n $"Uninstalling $prog daemon: "
	stop
	cygrunsrv --remove $prog
        echo "done."
}

case "$1" in
  start)
        start
        ;;
  stop)
        stop
        ;;
  restart)
        restart
        ;;
  install)
        install
        ;;
  uninstall)
        uninstall
        ;;
  status)
        status
        ;;
  condrestart)
        [ -f $PIDFILE ] && restart || :
        ;;
  *)
        echo $"Usage: $0 {start|stop|status|install|uninstall|restart|condrestart}"
        exit 1
esac

exit $?
