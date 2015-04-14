#!/bin/sh

printf "#define KERNEL_SVN_REV \"%b\"\n" `svnversion .` >include/version.h
printf "#define BUILDTIME \"%b\"\n" "`date`" >>include/version.h
printf "#define BUILDHOST \"%b\"\n" "`uname -a`" >>include/version.h
