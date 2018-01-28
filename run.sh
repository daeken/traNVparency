#!/bin/bash

LD_PRELOAD=./hooks.so DISPLAY=:0 "$@"
