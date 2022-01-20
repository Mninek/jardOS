#!/bin/sh
# This needs to be run after my PC resets
# run by executing "source ./first_setup.sh"

export JHOME="/mnt/h/jardOS_barebones"
export PREFIX="$JHOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
export DISPLAY=:0