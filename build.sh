#!/bin/bash

pushd src/kernel/
make clean
make
popd

pushd initrd/
make clean
make
popd


