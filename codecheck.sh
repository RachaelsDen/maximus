#!/bin/bash
cppcheck \
  --enable=all \
  --inconclusive \
  --force \
  --std=c99 \
  --suppress=missingIncludeSystem \
  --project=build/compile_commands.json \
  2> cppcheck.log
