#!/bin/sh
python ioctlgen.py
g++-7 -std=c++17 -fpermissive -g -O0 -o hooks.so -shared -fPIC *.cpp
