#ifndef __CONSOLE_H_
#define __CONSOLE_H_

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#if defined(__i386__)
#include <arch/x86/portio.h>
#endif

void init_console();
void move_cursor();
void reposition_cursor(uint8_t x, uint8_t y);
void clear_console();
void console_put(char c);
void console_write(char *c);
int kprintf(const char *fmt, ...);

#endif
