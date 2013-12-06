#!/bin/bash
cd "$(dirname "$0")"

if [ ! -d ./bin ]; then
  mkdir -p ./bin
fi

# Ensure we fail immediately if any command fails.
set -e

pushd ./bin > /dev/null
  cmake -DUSE_OS_MESA=ON ..
  make -j4
  ./glm_aabb_test
popd

