CC=~/opt/cross/bin/i686-elf-gcc
SOURCES=x86/init.o \
        x86/gdt.o \
        x86/portio.o \
        vsprintf.o \
        console.o \
        kmain.o

CFLAGS=-Iinclude/ -nostdlib -lgcc -ffreestanding -g
LDFLAGS=-Tx86/linker.ld
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm *.o kernel version.h

version.h:
	./make-version.sh

link:
	$(CC) $(CFLAGS) $(LDFLAGS) -o kernel $(SOURCES)
.s.o:
	nasm $(ASFLAGS) $<
