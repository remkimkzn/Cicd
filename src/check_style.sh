#!/bin/bash

clang-format -i -style=file -assume-filename=../linters/.clang-format ./**/*.c ./**/*.h

git diif -exit-code

if [$& -ne 0 ]; then
  echo "Codestyle violations detected! FIX "
  exit 1
else 
  echo "Codestyle check passed."
fi 
