case $(LC_MESSAGES=C /usr/sbin/alternatives --display busybox) in
  *status\ is\ manual.*link\ currently\ points\ to\ /usr/libexec/busybox-standalone/bin/busybox.exe*)
    ;;
  *)
    /usr/sbin/alternatives --remove busybox \
                           /usr/libexec/busybox-standalone/bin/busybox.exe ||:
    ;;
esac

