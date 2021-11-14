#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/jardOS.kernel isodir/boot/jardOS.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "jardOS" {
	multiboot /boot/jardOS.kernel
}
EOF
grub-mkrescue -o jardOS.iso isodir
