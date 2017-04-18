#!/usr/bin/env bash

set -e

shopt -s extglob
clang-format -i src/!(@(RcppExports|localtime|grisu3)).@(c|h|cpp) && git diff-files -U --exit-code
