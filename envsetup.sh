#! /usr/bin/env bash
# envsetup.sh

if [ -z "$MKFLAGS" ]; then
  UNAMES=$(uname -s)
  if which nproc >/dev/null; then
    export MKFLAGS=-j`nproc`
  elif [ "$UNAMES" == "Darwin" ] && which sysctl >/dev/null; then
    export MKFLAGS=-j`sysctl -n machdep.cpu.thread_count`
  fi
fi

function gettop() {
  local TOPFILE=envsetup.sh
  if [ -n "$TOP" -a -f "$TOP/$TOPFILE" ]; then
    echo $TOP
  else
    if [ -f "$TOPFILE" ]; then
      PWD= /bin/pwd
    else
      local HERE="$PWD"
      T=
      while [ \( ! \( -f $TOPFILE \) \) -a \( $PWD != "/" \) ]; do
        cd .. > /dev/null
        T=`PWD= /bin/pwd`
      done
      cd "$HERE" > /dev/null
      if [ -f "$T/$TOPFILE" ]; then
        echo $T
      fi
    fi
  fi
}

export WEBRTC_ROOT=$(gettop)/contrib/webrtc/src

export LIBOMXIL_BELLAGIO_ROOT=$(gettop)/contrib/libomxil-bellagio-0.9.3
export BELLAGIO_INSTALL_DIR="$LIBOMXIL_BELLAGIO_ROOT/build"
export PATH=$BELLAGIO_INSTALL_DIR/bin:$PATH
export LD_LIBRARY_PATH=$BELLAGIO_INSTALL_DIR/lib:$LD_LIBRARY_PATH
export BELLAGIO_SEARCH_PATH=$BELLAGIO_INSTALL_DIR/lib/bellagio/:$BELLAGIO_INSTALL_DIR/lib/extern_omxcomp/lib/:$BELLAGIO_INSTALL_DIR/lib/
export PKG_CONFIG_PATH=$BELLAGIO_INSTALL_DIR/lib/pkgconfig/:/usr/local/lib/pkgconfig/:/usr/lib/pkgconfig/:$PKG_CONFIG_PATH
