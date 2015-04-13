// syscall.c -- Defines the implementation of a system call system.
//              Written for JamesM's kernel development tutorials.

#include "syscall.h"
#include "isr.h"
#include "console.h"

static void syscall_handler(registers_t *regs);

void sys_exit(unsigned int retval) {
   // placeholder
}

int sys_fork() {
   int ret=fork();
   kprintf("fork() returned %d\n",ret);
   return ret;
}

int sys_read(unsigned int fd, char* buf, unsigned int size) {
   kprintf("syscall read");
   return 0;
}

int sys_write(unsigned int fd, const char* buf, unsigned int size) {
   // TODO - find task, get fds list, write to correct fd
   console_write(buf);
   return 0;
}

DEFN_SYSCALL1(exit,0,int);
DEFN_SYSCALL0(fork,1);
DEFN_SYSCALL3(read,2,unsigned int,char *,unsigned int);
DEFN_SYSCALL3(write,3,unsigned int,const char *,unsigned int);

static void *syscalls[4] =
{
    &sys_exit,
    &sys_fork,
    &sys_read,
    &sys_write
};
u32int num_syscalls = 4;

void initialise_syscalls()
{
    // Register our syscall handler.
    register_interrupt_handler (0x80, &syscall_handler);
}

void syscall_handler(registers_t *regs)
{
    // Firstly, check if the requested syscall number is valid.
    // The syscall number is found in EAX.
    if (regs->eax >= num_syscalls) {
        kprintf("invalid syscall %d\n",regs->eax);
        return;
    }

    // Get the required syscall location.
    void *location = syscalls[regs->eax];

    // We don't know how many parameters the function wants, so we just
    // push them all onto the stack in the correct order. The function will
    // use all the parameters it wants, and we can pop them all back off afterwards.
    int ret;
    asm volatile (" \
      push %1; \
      push %2; \
      push %3; \
      push %4; \
      push %5; \
      call *%6; \
      pop %%ebx; \
      pop %%ebx; \
      pop %%ebx; \
      pop %%ebx; \
      pop %%ebx; \
    " : "=a" (ret) : "r" (regs->edi), "r" (regs->esi), "r" (regs->edx), "r" (regs->ecx), "r" (regs->ebx), "r" (location));
    regs->eax = ret;
}
