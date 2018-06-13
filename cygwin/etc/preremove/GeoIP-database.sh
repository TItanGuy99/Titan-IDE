for f in $(/usr/bin/find /usr/share/GeoIP -type l); do
    case $(readlink ${f}) in
    GeoLite*.dat) rm ${f} ;;
    esac
done
