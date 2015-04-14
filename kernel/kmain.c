#include <console.h>
#include <multiboot.h>
#include <stdint.h>
#include <version.h>
#include <cpudetect.h>

#if defined(__i386__)
#include <arch/x86/idt.h>
#include <arch/x86/pic.h>
#endif

void kmain(struct multiboot_info *mboot_ptr, uint32_t initial_stack) {
     init_console();
     kprintf("Booting garethix, SVN version %s...\n", KERNEL_SVN_REV);
     kprintf("Build: %s, Build host: %s\n", BUILDTIME, BUILDHOST);
     kprintf("command line: %s\n",(char*)mboot_ptr->cmdline);
     detect_cpu();
     kprintf("Kernel initrd should be at 0x%x\n", mboot_ptr->mods_addr);
     kprintf("Dumping memory map:\n");
     memory_map_t* mmap = mboot_ptr->mmap_addr;
     uint32_t largest_mem=0;
     uint32_t largest_mem_size=0;
     while(mmap < mboot_ptr->mmap_addr + mboot_ptr->mmap_length) {
                if (mmap->length_low > largest_mem_size) {
                   largest_mem      = mmap->base_addr_low;
                   largest_mem_size = mmap->length_low;
                }
                kprintf("0x%x, %d kb", mmap->base_addr_low, mmap->length_low/1024);
                if (mmap->type==1) { 
                   kprintf(" FREE\n");
                } else {
                   kprintf(" RESERVED, type %d\n", mmap->type);
                }
		mmap = (memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(unsigned int) );
     }
     kprintf("Will allocate memory in 0x%x - 0x%x slot\n", largest_mem,largest_mem+largest_mem_size);
     kprintf("%d pages available\n", largest_mem_size/(4*1024));
#if defined(__i386__)
//	idt_initialize();
//	pic_initialize();
#endif
}
