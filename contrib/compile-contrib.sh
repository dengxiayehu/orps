#! /usr/bin/env bash
# compile-contrib.sh

ABS_DIR="$(cd "$(dirname "$0")"; pwd)"

export WEBRTC_ROOT="$ABS_DIR"/webrtc/src

WEBRTC_BUILD="$WEBRTC_ROOT/build"
mkdir -p "$WEBRTC_BUILD" && cd "$WEBRTC_BUILD"

cmake ..
make $MKFLAGS
