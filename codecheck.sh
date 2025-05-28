#!/bin/bash
cppcheck \
  --enable=all \
  --inconclusive \
  --force \
  --std=c99 \
  -I src/slib \
  -I src/unix/include \
  -I src \
  -D__UNIX__=1 \
  -D__LINUX__=1 \
  --suppress=missingIncludeSystem \
  "$@"
