#!/bin/bash
find . -name *.cpp -o -name *.h -exec clang-format -i {} \;
