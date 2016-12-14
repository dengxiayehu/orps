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
export -f gettop

function exit_msg() {
  echo $@
  exit 1
}
export -f exit_msg

export CONTRIB_DIR="$(gettop)/contrib"
export CONTRIB_LINUX_INSTALL_DIR="$CONTRIB_DIR/install"
export WEBRTC_ROOT="$CONTRIB_DIR/webrtc/src"
