#!/bin/bash

source "$(dirname "$0")/global.sh"

build_type="Release"

call_dir=$(pwd)
root=""

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -b|--build-type) build_type="$2"; shift ;;
    -r|--root) root="$2"; shift ;;
    *) echo "Unknown parameter passed: $1"; exit 1 ;;
  esac
  shift
done

cd "$root" || exit 2

cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="$build_type" -DCMAKE_TOOLCHAIN_FILE="$root/build/$build_type/generators/conan_toolchain.cmake" -S"$root" -B"$root/build/$build_type"

cmake --build "$root/build/$build_type" --parallel 10 --target wind-asset-bundler

cd build/"$build_type"/wind/asset-pipeline || exit 2

if echo "$OS" | grep -qi "Windows"; then
  mkdir -p "$root"/apps
  make install DESTDIR="$root"/apps
  ls -a "$root"/apps/usr/local/bin
else
  make install
fi

cd "$call_dir" || exit 2