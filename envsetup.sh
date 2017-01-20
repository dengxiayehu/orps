#! /usr/bin/env bash
# envsetup.sh

if [ -z "$NPROC" ]; then
  UNAMES=$(uname -s)
  if which nproc >/dev/null; then
    export NPROC=`nproc`
  elif [ "$UNAMES" == "Darwin" ] && which sysctl >/dev/null; then
    export NPROC=`sysctl -n machdep.cpu.thread_count`
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

# usage: c 2.. is equals to c ../..
function c() {
  if [ $# -eq 0 ]; then
    cd
    return $?
  fi

  if [ $# -ne 1 ]; then
    echo "usage: `basename $0` <dir>"
    return 1
  fi

  local _dir="$1"
  local _up_num=`echo $_dir | sed -e 's/^\([1-9][0-9]*\)*\.\.$/\1/'`
  if [ $(( ${#_up_num} + 2 )) -eq ${#_dir} ]; then
    local _dst_dir=".."
    while [ $(( _up_num-- )) -gt 1 ]
    do
      _dst_dir=$_dst_dir/..
    done
    cd $_dst_dir
  else
    cd $_dir
  fi
  return $?
}
export -f c

function croot() {
  local T=$(gettop)
  if [ "$T" ]; then
    \cd "$T"
  else
    echo "Couldn't locate the top of the tree"
  fi
}
export -f croot

function jgrep() {
  find . -name .repo -prune -o -name .git -prune -o  -type f -name "*\.java" -print0 | xargs -0 grep --color -n "$@"
}
export -f jgrep

function cgrep() {
  find . -name .repo -prune -o -name .git -prune -o -type f \( -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.h' \) -print0 | xargs -0 grep --color -n "$@"
}
export -f cgrep

export TARGET_OUT="$(gettop)/build/out"
export CONTRIB_DIR="$(gettop)/contrib"
export CONTRIB_LINUX_INSTALL_DIR="$CONTRIB_DIR/install"
export WEBRTC_ROOT="$CONTRIB_DIR/webrtc/src"
