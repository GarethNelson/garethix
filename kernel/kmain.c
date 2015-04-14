#include <console.h>

#if defined(__i386__)
#include <arch/x86/idt.h>
#include <arch/x86/pic.h>
#endif

void kernel_early(void) {
     init_console();
}

void kmain(void) {
     kprintf("Booting...\n");
#if defined(__i386__)
//	idt_initialize();
//	pic_initialize();
#endif
}
