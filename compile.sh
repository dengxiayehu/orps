#! /usr/bin/env bash
# compile.sh

if [ -z "$WEBRTC_ROOT" ]; then
  echo "You should source envsetup.sh first."
  exit 1
fi

if [ -z "$MKFLAGS" ]; then
  UNAMES=$(uname -s)
  MKFLAGS=
  if which nproc >/dev/null; then
    export MKFLAGS=-j`nproc`
  elif [ "$UNAMES" == "Darwin" ] && which sysctl >/dev/null; then
    export MKFLAGS=-j`sysctl -n machdep.cpu.thread_count`
  fi

  export MKFLAGS="$MKFLAGS VERBOSE=1"
fi

bash contrib/compile-contrib.sh

[ ! -d build ] && mkdir build
cd build && cmake .. && make "$MKFLAGS"

$CONTRIB_LINUX_INSTALL_DIR/bin/omxregister-bellagio $CONTRIB_LINUX_INSTALL_DIR/lib/bellagio:$TARGET_OUT
