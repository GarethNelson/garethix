#!/bin/sh
qemu -m 1024 -kernel build/x86/kernel -initrd build/x86/initrd.img -append "test"
