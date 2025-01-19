#!/bin/bash
set -e
find src/ tests/ -name *.cpp -o -name *.h -exec clang-format -i {} \;
