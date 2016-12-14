#! /usr/bin/env bash
# compile.sh

if [ -z "$WEBRTC_ROOT" ]; then
  echo "You should source envsetup.sh first."
  exit 1
fi

bash contrib/compile-contrib.sh
