#! /usr/bin/env bash
# compile-contrib.sh

#######################################
# WebRTC
#######################################
WEBRTC_BUILD="$WEBRTC_ROOT/build"
mkdir -p "$WEBRTC_BUILD" && cd "$WEBRTC_BUILD"

cmake ..
make $MKFLAGS

#######################################
# libomxil-bellagio 
#######################################
cd "$LIBOMXIL_BELLAGIO_ROOT"

autoreconf -i -f .
./configure --enable-debug --prefix="$LIBOMXIL_BELLAGIO_ROOT/build"
make $MKFLAGS CFLAGS="-g -O0 -Wno-error=switch"
make install
make check
