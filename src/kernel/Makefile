SOURCES=init.o common.o gdt.o isr.o interrupt.o descriptor_tables.o console.o vsprintf.o cpudetect.o timer.o ordered_array.o process.o paging.o kheap.o syscall.o task.o fs.o initrd.o \
        kmain.o

CFLAGS=-I. -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -ffreestanding -g
LDFLAGS= -melf_i386  -Tlink.ld
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
