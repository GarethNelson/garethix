#!/bin/bash

rm build/x86/kernel
rm build/x86/initrd.img

pushd kernel/
make clean
make
cp kernel ../build/x86/
popd

pushd initrd/
make clean
make
cp initrd.img ../build/x86/
popd


