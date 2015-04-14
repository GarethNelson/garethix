#!/bin/bash
mkdir $HOME/opt
mkdir $HOME/opt/cross

rm -rf build/binutils/*
rm -rf build/gcc-4.7.2/*

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

pushd build/binutils
../binutils-2.22/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
popd

pushd build/gcc
../gcc-4.7.2/configure  --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
popd
