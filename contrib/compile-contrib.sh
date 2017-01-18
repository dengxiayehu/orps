#! /usr/bin/env bash
# compile-contrib.sh

TARBALLS_DIR="$CONTRIB_DIR/tarballs"
CONTRIB_LINUX_SRC_DIR="$CONTRIB_DIR/contrib-linux"

NO_OUTPUT="1>/dev/null 2>&1"

TARS_HDLR_ARR=(
"$TARBALLS_DIR/zlib-1.2.8.tar.gz:compile_zlib"
"$TARBALLS_DIR/openssl-1.0.2g.tar.gz:compile_openssl"
"$TARBALLS_DIR/librtmp.tar.bz2:compile_librtmp"
"$TARBALLS_DIR/libomxil-bellagio-0.9.3.tgz:compile_libomxil_bellagio"
"$CONTRIB_DIR/webrtc:compile_webrtc"
)

[ ! -d "$TARBALLS_DIR" ] && \
  exit_msg "tarballs dir not found"
[ ! -d "$CONTRIB_LINUX_SRC_DIR" ] && mkdir "$CONTRIB_LINUX_SRC_DIR"

function compile_zlib() {
  CFLAGS="-fPIC" ./configure --const --static --64 --prefix="$CONTRIB_LINUX_INSTALL_DIR" &&
    make $MKFLAGS &&
    make install && return 0
  return 1
}

function compile_openssl() {
  ./Configure linux-x86_64 -fPIC threads zlib no-shared --prefix="$CONTRIB_LINUX_INSTALL_DIR" --with-zlib-lib="$CONTRIB_LINUX_INSTALL_DIR/lib" --with-zlib-include="$CONTRIB_LINUX_INSTALL_DIR/include" &&
    make depend &&
    make &&
    make install && return 0
  return 1
}

function compile_librtmp() {
  make clean && \
    make $MKFLAGS \
      INC=-I"$CONTRIB_LINUX_INSTALL_DIR/include" XCFLAGS="-fPIC" XLDFLAGS="-L$CONTRIB_LINUX_INSTALL_DIR/lib" \
      prefix="$CONTRIB_LINUX_INSTALL_DIR" \
      install && return 0
  return 1
}

function compile_libomxil_bellagio() {
  export PATH=$CONTRIB_LINUX_INSTALL_DIR/bin:$PATH
  export LD_LIBRARY_PATH=$CONTRIB_LINUX_INSTALL_DIR/lib:$LD_LIBRARY_PATH
  export BELLAGIO_SEARCH_PATH=$CONTRIB_LINUX_INSTALL_DIR/lib/bellagio/:$CONTRIB_LINUX_INSTALL_DIR/lib/extern_omxcomp/lib/:$CONTRIB_LINUX_INSTALL_DIR/lib/
  export PKG_CONFIG_PATH=$CONTRIB_LINUX_INSTALL_DIR/lib/pkgconfig/:/usr/local/lib/pkgconfig/:/usr/lib/pkgconfig/:$PKG_CONFIG_PATH
  local _cflags="-g -O0 -Wno-error=switch"
  autoreconf -i -f . &&
    ./configure --enable-debug --prefix="$CONTRIB_LINUX_INSTALL_DIR" &&
    make $MKFLAGS CFLAGS="$_cflags" &&
    make $MKFLAGS CFLAGS="$_cflags" check &&
    make $MKFLAGS CFLAGS="$_cflags" install && return 0
  return 1
}

function compile_webrtc() {
  WEBRTC_BUILD="$WEBRTC_ROOT/build"
  mkdir -p "$WEBRTC_BUILD" && cd "$WEBRTC_BUILD"

  cmake ..
  make $MKFLAGS
}

function extract() {
  local tar="$1" bn=`basename "$tar"`
  local dst_parent="$2"
  local tar_suffix_hdlr=(
    ".tar:tar_xvf_@_-C"
    ".tar.gz|.tgz:tar_zxvf_@_-C"
    ".tar.bz|.tar.bz2:tar_jxvf_@_-C"
    ".tar.Z:tar_Zxvf_@_-C"
    ".zip:unzip_-e_@_-d"
  )

  for tsh in ${tar_suffix_hdlr[@]}; do
    local suffix=`echo $tsh | cut -d: -f1`
    local suffix_arr=(${suffix//|/ })
    for sf in ${suffix_arr[@]}; do
      local fm=`echo $bn | sed -n "s/\(.*\)$sf$/\1/p"`
      [ -z "$fm" ] && continue
      local dstsrc="$dst_parent/$fm"
      [ -d  "$dstsrc" ] && \
        { echo "$dstsrc" && return 0; }
      local hdlr=`echo $tsh | cut -d: -f2 | tr -s '_' ' ' | sed -n 's/ @ / $tar /p'`" $dst_parent"
      eval "$hdlr $NO_OUTPUT" || \
        { echo "" && return 1; }
      echo "$dstsrc"
      return 0
    done
  done
}

function compile() {
  local tar="$1"
  local hdlr="$2"
  if [ -f "$tar" ]; then
    local dstsrc=`extract "$tar" "$CONTRIB_LINUX_SRC_DIR"`
    [ -n "$dstsrc" ] || \
      exit_msg "extract \"$tar\" failed"
  else
    local dstsrc="$tar"
  fi
  cd "$dstsrc"
  local stamp=".stamp"
  [ -f "$stamp" ] && return 0
  $hdlr || \
    exit_msg "compile `basename $tar` failed"
  cd "$dstsrc"
  touch "$stamp"
}

for th in ${TARS_HDLR_ARR[@]}; do
  tar=`echo "$th" | cut -d: -f1`
  hdlr=`echo "$th" | cut -d: -f2`
  echo "----------------------------"
  echo "[*] $hdlr"
  echo "----------------------------"
  compile "$tar"  "$hdlr"
  echo -e "Done\n"
done
