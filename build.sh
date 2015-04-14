#!/bin/bash

rm build/kernel

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


