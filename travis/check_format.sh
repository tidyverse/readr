#!/usr/bin/env bash

shopt -s extglob

clang_format=$(command -v clang-format)
if $clang_format --version | grep -q '3.4'; then
  clang_format=$(command -v clang-format-3.9)
fi
if [ -z "$clang_format" ]; then
  echo "Could not find recent version of clang-format"
  exit 1
fi
"$clang_format" -i src/!(@(RcppExports|localtime|grisu3)).@(c|h|cpp) && git diff-files -U --exit-code
