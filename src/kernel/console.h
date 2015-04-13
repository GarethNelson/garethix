#ifndef __CONSOLE_H_
#define __CONSOLE_H_
#include "common.h"
#include "fs.h"


char* keyboard_buffer;
fs_node_t *console_tty;

void init_console();
void move_cursor();
void reposition_cursor(u8int x, u8int y);
void clear_console();
void console_put(char c);
void console_write(char *c);
int kprintf(const char *fmt, ...);

#endif
