------------------------------------------------------------------------------
--                                                                          --
--                         GNAT COMPILER COMPONENTS                         --
--                                                                          --
--                  S Y S T E M . O S _ C O N S T A N T S                   --
--                                                                          --
--                                 S p e c                                  --
--                                                                          --
--          Copyright (C) 2000-2015, Free Software Foundation, Inc.         --
--                                                                          --
-- GNAT is free software;  you can  redistribute it  and/or modify it under --
-- terms of the  GNU General Public License as published  by the Free Soft- --
-- ware  Foundation;  either version 3,  or (at your option) any later ver- --
-- sion.  GNAT is distributed in the hope that it will be useful, but WITH- --
-- OUT ANY WARRANTY;  without even the  implied warranty of MERCHANTABILITY --
-- or FITNESS FOR A PARTICULAR PURPOSE.                                     --
--                                                                          --
-- As a special exception under Section 7 of GPL version 3, you are granted --
-- additional permissions described in the GCC Runtime Library Exception,   --
-- version 3.1, as published by the Free Software Foundation.               --
--                                                                          --
-- You should have received a copy of the GNU General Public License and    --
-- a copy of the GCC Runtime Library Exception along with this program;     --
-- see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see    --
-- <http://www.gnu.org/licenses/>.                                          --
--                                                                          --
-- GNAT was originally developed  by the GNAT team at  New York University. --
-- Extensive contributions were provided by Ada Core Technologies Inc.      --
--                                                                          --
------------------------------------------------------------------------------

pragma Style_Checks ("M32766");
--  Allow long lines

--  This package provides target dependent definitions of constant for use
--  by the GNAT runtime library. This package should not be directly with'd
--  by an application program.

--  This file is generated automatically, do not modify it by hand! Instead,
--  make changes to s-oscons-tmplt.c and rebuild the GNAT runtime library.
--  This is the version for i686-pc-cygwin

with Interfaces.C;
package System.OS_Constants is

   pragma Pure;

   ---------------------------------
   -- General platform parameters --
   ---------------------------------

   type OS_Type is (Windows, Other_OS);
   Target_OS                     : constant OS_Type := Other_OS;
   pragma Warnings (Off, Target_OS);
   --  Suppress warnings on Target_OS since it is in general tested for
   --  equality with a constant value to implement conditional compilation,
   --  which normally generates a constant condition warning.

   Target_Name                   : constant String  := "i686-pc-cygwin";
   SIZEOF_unsigned_int           : constant := 4;           --  Size of unsigned int

   -------------------
   -- System limits --
   -------------------

   IOV_MAX                       : constant := 1024;        --  Maximum writev iovcnt
   NAME_MAX                      : constant := 255;         --  Maximum file name length

   ---------------------
   -- File open modes --
   ---------------------

   O_RDWR                        : constant := 2;           --  Read/write
   O_NOCTTY                      : constant := 32768;       --  Don't change ctrl tty
   O_NDELAY                      : constant := 16384;       --  Nonblocking

   ----------------------
   -- Fcntl operations --
   ----------------------

   F_GETFL                       : constant := 3;           --  Get flags
   F_SETFL                       : constant := 4;           --  Set flags

   -----------------
   -- Fcntl flags --
   -----------------

   FNDELAY                       : constant := 16384;       --  Nonblocking

   ----------------------
   -- Ioctl operations --
   ----------------------

   subtype IOCTL_Req_T is Interfaces.C.int;
   FIONBIO                       : constant := -2147195266; --  Set/clear non-blocking io
   FIONREAD                      : constant := 1074030207;  --  How many bytes to read

   ------------------
   -- Errno values --
   ------------------

   --  The following constants are defined from <errno.h>

   EAGAIN                        : constant := 11;          --  Try again
   ENOENT                        : constant := 2;           --  File not found
   ENOMEM                        : constant := 12;          --  Out of memory
   EACCES                        : constant := 13;          --  Permission denied
   EADDRINUSE                    : constant := 112;         --  Address already in use
   EADDRNOTAVAIL                 : constant := 125;         --  Cannot assign address
   EAFNOSUPPORT                  : constant := 106;         --  Addr family not supported
   EALREADY                      : constant := 120;         --  Operation in progress
   EBADF                         : constant := 9;           --  Bad file descriptor
   ECONNABORTED                  : constant := 113;         --  Connection aborted
   ECONNREFUSED                  : constant := 111;         --  Connection refused
   ECONNRESET                    : constant := 104;         --  Connection reset by peer
   EDESTADDRREQ                  : constant := 121;         --  Destination addr required
   EFAULT                        : constant := 14;          --  Bad address
   EHOSTDOWN                     : constant := 117;         --  Host is down
   EHOSTUNREACH                  : constant := 118;         --  No route to host
   EINPROGRESS                   : constant := 119;         --  Operation now in progress
   EINTR                         : constant := 4;           --  Interrupted system call
   EINVAL                        : constant := 22;          --  Invalid argument
   EIO                           : constant := 5;           --  Input output error
   EISCONN                       : constant := 127;         --  Socket already connected
   ELOOP                         : constant := 92;          --  Too many symbolic links
   EMFILE                        : constant := 24;          --  Too many open files
   EMSGSIZE                      : constant := 122;         --  Message too long
   ENAMETOOLONG                  : constant := 91;          --  Name too long
   ENETDOWN                      : constant := 115;         --  Network is down
   ENETRESET                     : constant := 126;         --  Disconn. on network reset
   ENETUNREACH                   : constant := 114;         --  Network is unreachable
   ENOBUFS                       : constant := 105;         --  No buffer space available
   ENOPROTOOPT                   : constant := 109;         --  Protocol not available
   ENOTCONN                      : constant := 128;         --  Socket not connected
   ENOTSOCK                      : constant := 108;         --  Operation on non socket
   EOPNOTSUPP                    : constant := 95;          --  Operation not supported
   EPIPE                         : constant := 32;          --  Broken pipe
   EPFNOSUPPORT                  : constant := 96;          --  Unknown protocol family
   EPROTONOSUPPORT               : constant := 123;         --  Unknown protocol
   EPROTOTYPE                    : constant := 107;         --  Unknown protocol type
   ERANGE                        : constant := 34;          --  Result too large
   ESHUTDOWN                     : constant := 110;         --  Cannot send once shutdown
   ESOCKTNOSUPPORT               : constant := 124;         --  Socket type not supported
   ETIMEDOUT                     : constant := 116;         --  Connection timed out
   ETOOMANYREFS                  : constant := 129;         --  Too many references
   EWOULDBLOCK                   : constant := 11;          --  Operation would block
   E2BIG                         : constant := 7;           --  Argument list too long
   EILSEQ                        : constant := 138;         --  Illegal byte sequence

   ----------------------
   -- Terminal control --
   ----------------------

   TCSANOW                       : constant := 2;           --  Immediate
   TCIFLUSH                      : constant := 0;           --  Flush input
   IXON                          : constant := 1024;        --  Output sw flow control
   CLOCAL                        : constant := 2048;        --  Local
   CRTSCTS                       : constant := 32768;       --  Output hw flow control
   CREAD                         : constant := 128;         --  Read
   CS5                           : constant := 0;           --  5 data bits
   CS6                           : constant := 16;          --  6 data bits
   CS7                           : constant := 32;          --  7 data bits
   CS8                           : constant := 48;          --  8 data bits
   CSTOPB                        : constant := 64;          --  2 stop bits
   PARENB                        : constant := 256;         --  Parity enable
   PARODD                        : constant := 512;         --  Parity odd
   B0                            : constant := 0;           --  0 bps
   B50                           : constant := 1;           --  50 bps
   B75                           : constant := 2;           --  75 bps
   B110                          : constant := 3;           --  110 bps
   B134                          : constant := 4;           --  134 bps
   B150                          : constant := 5;           --  150 bps
   B200                          : constant := 6;           --  200 bps
   B300                          : constant := 7;           --  300 bps
   B600                          : constant := 8;           --  600 bps
   B1200                         : constant := 9;           --  1200 bps
   B1800                         : constant := 10;          --  1800 bps
   B2400                         : constant := 11;          --  2400 bps
   B4800                         : constant := 12;          --  4800 bps
   B9600                         : constant := 13;          --  9600 bps
   B19200                        : constant := 14;          --  19200 bps
   B38400                        : constant := 15;          --  38400 bps
   B57600                        : constant := 4097;        --  57600 bps
   B115200                       : constant := 4098;        --  115200 bps
   B230400                       : constant := 4100;        --  230400 bps
   B460800                       : constant := 4102;        --  460800 bps
   B500000                       : constant := 4103;        --  500000 bps
   B576000                       : constant := 4104;        --  576000 bps
   B921600                       : constant := 4105;        --  921600 bps
   B1000000                      : constant := 4106;        --  1000000 bps
   B1152000                      : constant := 4107;        --  1152000 bps
   B1500000                      : constant := 4108;        --  1500000 bps
   B2000000                      : constant := 4109;        --  2000000 bps
   B2500000                      : constant := 4110;        --  2500000 bps
   B3000000                      : constant := 4111;        --  3000000 bps
   B3500000                      : constant := 4294967295;  --  3500000 bps
   B4000000                      : constant := 4294967295;  --  4000000 bps

   ---------------------------------
   -- Terminal control characters --
   ---------------------------------

   VINTR                         : constant := 6;           --  Interrupt
   VQUIT                         : constant := 10;          --  Quit
   VERASE                        : constant := 5;           --  Erase
   VKILL                         : constant := 7;           --  Kill
   VEOF                          : constant := 4;           --  EOF
   VTIME                         : constant := 16;          --  Read timeout
   VMIN                          : constant := 9;           --  Read min chars
   VSWTC                         : constant := 15;          --  Switch
   VSTART                        : constant := 12;          --  Flow control start
   VSTOP                         : constant := 13;          --  Flow control stop
   VSUSP                         : constant := 14;          --  Suspend
   VEOL                          : constant := 2;           --  EOL
   VREPRINT                      : constant := 11;          --  Reprint unread
   VDISCARD                      : constant := 1;           --  Discard pending
   VWERASE                       : constant := 17;          --  Word erase
   VLNEXT                        : constant := 8;           --  Literal next
   VEOL2                         : constant := 3;           --  Alternative EOL
   DTR_CONTROL_ENABLE            : constant := 1;           --  Enable DTR flow ctrl
   RTS_CONTROL_ENABLE            : constant := 1;           --  Enable RTS flow ctrl

   -----------------------------
   -- Pseudo terminal library --
   -----------------------------

   PTY_Library                   : constant String  := "";            --  for g-exptty

   --------------
   -- Families --
   --------------

   AF_INET                       : constant := 2;           --  IPv4 address family
   AF_INET6                      : constant := 23;          --  IPv6 address family

   ------------------
   -- Socket modes --
   ------------------

   SOCK_STREAM                   : constant := 1;           --  Stream socket
   SOCK_DGRAM                    : constant := 2;           --  Datagram socket

   -----------------
   -- Host errors --
   -----------------

   HOST_NOT_FOUND                : constant := 1;           --  Unknown host
   TRY_AGAIN                     : constant := 2;           --  Host name lookup failure
   NO_DATA                       : constant := 4;           --  No data record for name
   NO_RECOVERY                   : constant := 3;           --  Non recoverable errors

   --------------------
   -- Shutdown modes --
   --------------------

   SHUT_RD                       : constant := 0;           --  No more recv
   SHUT_WR                       : constant := 1;           --  No more send
   SHUT_RDWR                     : constant := 2;           --  No more recv/send

   ---------------------
   -- Protocol levels --
   ---------------------

   SOL_SOCKET                    : constant := 65535;       --  Options for socket level
   IPPROTO_IP                    : constant := 0;           --  Dummy protocol for IP
   IPPROTO_UDP                   : constant := 17;          --  UDP
   IPPROTO_TCP                   : constant := 6;           --  TCP

   -------------------
   -- Request flags --
   -------------------

   MSG_OOB                       : constant := 1;           --  Process out-of-band data
   MSG_PEEK                      : constant := 2;           --  Peek at incoming data
   MSG_EOR                       : constant := -1;          --  Send end of record
   MSG_WAITALL                   : constant := 8;           --  Wait for full reception
   MSG_NOSIGNAL                  : constant := 32;          --  No SIGPIPE on send
   MSG_Forced_Flags              : constant := 0;
   --  Flags set on all send(2) calls

   --------------------
   -- Socket options --
   --------------------

   TCP_NODELAY                   : constant := 1;           --  Do not coalesce packets
   SO_REUSEADDR                  : constant := 4;           --  Bind reuse local address
   SO_REUSEPORT                  : constant := -1;          --  Bind reuse port number
   SO_KEEPALIVE                  : constant := 8;           --  Enable keep-alive msgs
   SO_LINGER                     : constant := 128;         --  Defer close to flush data
   SO_BROADCAST                  : constant := 32;          --  Can send broadcast msgs
   SO_SNDBUF                     : constant := 4097;        --  Set/get send buffer size
   SO_RCVBUF                     : constant := 4098;        --  Set/get recv buffer size
   SO_SNDTIMEO                   : constant := 4101;        --  Emission timeout
   SO_RCVTIMEO                   : constant := 4102;        --  Reception timeout
   SO_ERROR                      : constant := 4103;        --  Get/clear error status
   IP_MULTICAST_IF               : constant := 9;           --  Set/get mcast interface
   IP_MULTICAST_TTL              : constant := 10;          --  Set/get multicast TTL
   IP_MULTICAST_LOOP             : constant := 11;          --  Set/get mcast loopback
   IP_ADD_MEMBERSHIP             : constant := 12;          --  Join a multicast group
   IP_DROP_MEMBERSHIP            : constant := 13;          --  Leave a multicast group
   IP_PKTINFO                    : constant := 19;          --  Get datagram info

   ----------------------
   -- Type definitions --
   ----------------------

   --  Sizes (in bytes) of the components of struct timeval
   SIZEOF_tv_sec                 : constant := 4;           --  tv_sec
   SIZEOF_tv_usec                : constant := 4;           --  tv_usec

   --  Maximum allowed value for tv_sec
   MAX_tv_sec                    : constant := 2 ** (SIZEOF_tv_sec * 8 - 1) - 1;

   --  Sizes of various data types
   SIZEOF_sockaddr_in            : constant := 16;          --  struct sockaddr_in
   SIZEOF_sockaddr_in6           : constant := 28;          --  struct sockaddr_in6
   SIZEOF_fd_set                 : constant := 8;           --  fd_set
   FD_SETSIZE                    : constant := 64;          --  Max fd value
   SIZEOF_struct_hostent         : constant := 16;          --  struct hostent
   SIZEOF_struct_servent         : constant := 16;          --  struct servent

   --  Fields of struct msghdr
   subtype Msg_Iovlen_T is Interfaces.C.size_t;

   ----------------------------------------
   -- Properties of supported interfaces --
   ----------------------------------------

   Need_Netdb_Buffer             : constant := 0;           --  Need buffer for Netdb ops
   Need_Netdb_Lock               : constant := 1;           --  Need lock for Netdb ops
   Has_Sockaddr_Len              : constant := 0;           --  Sockaddr has sa_len field
   Thread_Blocking_IO            : constant Boolean := True;
   --  Set False for contexts where socket i/o are process blocking

   Inet_Pton_Linkname            : constant String  := "inet_pton";

   ---------------------
   -- Threads support --
   ---------------------

   --  Clock identifier definitions

   CLOCK_REALTIME                : constant := 1;           --  System realtime clock
   CLOCK_MONOTONIC               : constant := 4;           --  System monotonic clock
   CLOCK_THREAD_CPUTIME_ID       : constant := 3;           --  Thread CPU clock
   CLOCK_RT_Ada                  : constant := CLOCK_REALTIME;

   --------------------------------
   -- File and directory support --
   --------------------------------

   SIZEOF_struct_file_attributes : constant := 24;          --  struct file_attributes
   SIZEOF_struct_dirent_alloc    : constant := 276;         --  struct dirent allocation

end System.OS_Constants;
