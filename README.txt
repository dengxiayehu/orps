README for orps
===============================

Compile
====================
$ source ./envsetup.sh
$ ./compile.sh

NOTE
====================
With the following tool |omxrtmpredirecttest|, we can redirect rtmp-stream
to another rtmpserver:
$ build/out/omxrtmpredirecttest --help
Flags from /home/jwf/workspace/orps/test/components/rtmpredirect/flagdefs.h:
  --dst_rtmp (The destination rtmp url to push to.)  type: string  default:
rtmp://127.0.0.1/live/xyz
  --src_rtmp (The source rtmp url to connect to.)  type: string  default:
rtmp://127.0.0.1/live/va
  --help (Print this message [dengxiayehu@yeah.net])  type: bool  default:
false

Other
====================
mail: dengxiayehu@yeah.net
