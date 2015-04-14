#include <console.h>
#include <multiboot.h>
#include <stdint.h>

#if defined(__i386__)
#include <arch/x86/idt.h>
#include <arch/x86/pic.h>
#endif


void kmain(struct multiboot *mboot_ptr, uint32_t initial_stack) {
     init_console();
     kprintf("Booting...\n");
#if defined(__i386__)
//	idt_initialize();
//	pic_initialize();
#endif
}
