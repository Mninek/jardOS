#!/bin/sh
# This needs to be run after my PC resets
# run by executing "source ./first_setup.sh"

export JHOME="/mnt/j/jardos_stuff"
export PREFIX="$JHOME/opt/cross"
export TARGET=/mnt/j/jardos_stuff/opt/cross/bin/i686-elf
export PATH="$PREFIX/bin:$PATH"
export DISPLAY=:0
export JOSLOG="python3 ../jardOSLogViewer/LogViewer.py debug.log"
