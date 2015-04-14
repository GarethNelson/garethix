#!/bin/bash

pushd kernel/
make clean
make
popd

pushd initrd/
make clean
make
popd


