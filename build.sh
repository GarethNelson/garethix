#!/bin/bash
pushd src/kernel/
make clean
make
popd
pushd initrd/
make clean
make
popd
sudo mount floppy.img floppy
sudo rm floppy/kernel
sudo rm floppy/initrd
sudo cp src/kernel/kernel floppy/
sudo cp initrd/initrd.img floppy/initrd
sudo umount floppy

