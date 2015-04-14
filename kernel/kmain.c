#include <console.h>
#include <multiboot.h>
#include <stdint.h>
#include <version.h>

#if defined(__i386__)
#include <arch/x86/idt.h>
#include <arch/x86/pic.h>
#endif

void kmain(struct multiboot_info *mboot_ptr, uint32_t initial_stack) {
     init_console();
     kprintf("Booting garethix, SVN version %s...\n", KERNEL_SVN_REV);
     kprintf("Build: %s, Build host: %s\n", BUILDTIME, BUILDHOST);
     kprintf("command line: %s\n",(char*)mboot_ptr->cmdline);
     kprintf("Dumping memory map:\n");
     memory_map_t* mmap = mboot_ptr->mmap_addr;
     while(mmap < mboot_ptr->mmap_addr + mboot_ptr->mmap_length) {
                kprintf("0x%x, %d kb", mmap->base_addr_low, mmap->length_low/1024);
                if (mmap->type==1) { 
                   kprintf(" FREE\n");
                } else {
                   kprintf(" RESERVED, type %d\n", mmap->type);
                }
		mmap = (memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(unsigned int) );
     }
#if defined(__i386__)
//	idt_initialize();
//	pic_initialize();
#endif
}
