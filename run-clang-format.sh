#!/bin/bash

find ./Luna/src/ -iname *.h -o -iname *.cpp | xargs clang-format -i
find ./Sandbox/src/ -iname *.h -o -iname *.cpp | xargs clang-format -i
