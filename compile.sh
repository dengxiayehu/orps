#! /usr/bin/env bash
# compile.sh

ABS_DIR="$(cd "$(dirname "$0")"; pwd)"

if [ -z "$WEBRTC_ROOT" ]; then
  echo "You should source envsetup.sh first."
  exit 1
fi

export MKFLAGS="$MKFLAGS VERBOSE=1"
export MKFLAGS_NPROC="$MKFLAGS -j$NPROC"

CONTRIB_DIR="$ABS_DIR"/contrib
bash "$CONTRIB_DIR"/compile-contrib.sh
[ $? -ne 0 ] && exit 1

BUILD_DIR="$ABS_DIR"/build
[ ! -d "$BUILD_DIR" ] && mkdir "$BUILD_DIR"
cd "$BUILD_DIR" && cmake .. && make $MKFLAGS_NPROC

$CONTRIB_LINUX_INSTALL_DIR/bin/omxregister-bellagio $CONTRIB_LINUX_INSTALL_DIR/lib/bellagio:$TARGET_OUT
