SOURCES=x86/init.o x86/gdt.o

CFLAGS=-Iinclude/ -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -ffreestanding -g
LDFLAGS= -melf_i386  -Tx86/linker.ld
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	$(CC) $(CFLAGS) -c $< -o $@
