#!/bin/sh
qemu -m 1024 -k build/x86/kernel -initrd initrd/initrd.img
