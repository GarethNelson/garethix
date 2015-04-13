#include "console.h"
#include "descriptor_tables.h"
#include "cpudetect.h"
#include "multiboot.h"
#include "timer.h"
#include "task.h"
#include "fs.h"
#include "initrd.h"

u32int initial_esp;

extern u32int placement_address;

void k_dumpfs(fs_node_t* n) {
    int i = 0;
    struct dirent *node = 0;
     kprintf("Dumping %s\n",n->name);
     while ((node = readdir_fs(n,i))!=0) {
        fs_node_t *fsnode = finddir_fs(n, node->name);
        kprintf("%s/%s\n",n->name,node->name);
        if((fsnode->flags&0x7) == FS_DIRECTORY) {
          k_dumpfs(fsnode);
        }
        i++;
     }
}

int kmain(struct multiboot *mboot_ptr, u32int initial_stack) {
  initial_esp = initial_stack;
  init_descriptor_tables();

  init_console();
  kprintf("IDT and GDT loaded\n");

  kprintf("Init PIT...");
  asm volatile("sti");
  init_timer(50);
  kprintf("PIT initalised.\n");

  detect_cpu();

  ASSERT(mboot_ptr->mods_count > 0);
  kprintf("%d mb memory lower\n",mboot_ptr->mem_lower/1024);
  kprintf("%d mb memory upper\n",mboot_ptr->mem_upper/1024);
  kprintf("Will allocate %d pages\n", (mboot_ptr->mem_upper*1024)/0x1000);

  kprintf("Checking initrd....\n");

  u32int initrd_location = *((u32int*)mboot_ptr->mods_addr);
  u32int initrd_end = *(u32int*)(mboot_ptr->mods_addr+4);
  placement_address = initrd_end;

  kprintf("Loading initrd...\n");
  fs_root = initialise_initrd(initrd_location);

  kprintf("Setting up tty0...\n");
  init_tty();

  kprintf("Setting up paging...\n");
  initialise_paging(mboot_ptr->mem_upper*1024);

  kprintf("Switching to multitasking...\n");
  initialise_tasking();

  kprintf("Loading syscalls...\n");
  initialise_syscalls();

  int ret = fork();
  if(getpid()==0) {
    kprintf("Kernel PID 0 loaded\n");
   
    asm volatile("cli");
    k_dumpfs(fs_root);
    asm volatile("sti");

    while(1) {asm volatile("hlt");};
  }
  if(getpid()==1) {
    kprintf("PID 1 loaded, switching to userland...\n");
    switch_to_user_mode();
    syscall_write(0,"userland write to /dev/tty0 test\n",0);
    syscall_write(0,"about to test userland fork()\n",0);
    syscall_fork();
    syscall_write(0,"userland hello\n",0);
  }
  
}
