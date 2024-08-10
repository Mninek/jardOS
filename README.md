# jardOS

how to create the .iso (on my PC)

run source ./first_setup.sh

export JHOME="/mnt/j/jardos_stuff"
export PREFIX="$JHOME/opt/cross"
export TARGET="/mnt/j/jardos_stuff/opt/cross/bin/i686-elf"
export PATH="$PREFIX/bin:$PATH"
export DISPLAY=:0

start xming server by opening the app

./clean.sh
./headers.sh
./iso.sh
./qemu.sh

# TODO
## Bigger tasks
- [x] Serial port debugging
- [] Basic interrupt/exception handling
- [] Memory Stuff
- [] terminal scrolling
- [] user input
- [] terminal resizing

## Smaller tasks
- [] move location of binutils and gcc from barebones directory