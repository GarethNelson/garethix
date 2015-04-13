#include "console.h"
#include "isr.h"
#include "fs.h"

unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

#include "stdarg.h"
#include "string.h"

u16int *video_memory = (u16int *)0xB8000;
u8int cursor_x = 0;
u8int cursor_y = 0;

void move_cursor() {
     u16int cursorLocation = cursor_y * 80 + cursor_x;
     outb(0x3D4, 14);
     outb(0x3D5, cursorLocation >> 8);
     outb(0x3D4, 15);
     outb(0x3D5, cursorLocation);
}

void reposition_cursor(u8int x, u8int y) {
     cursor_x = x;
     cursor_y = y;
}

void clear_console() {
     u8int attrib_byte = (0 << 4) | (15 & 0x0F);
     u16int blank      = 0x20 | (attrib_byte << 8);
     int i;
     for (i=0; i < 80*25; i++) {
          video_memory[i] = blank;
     }
}

static void scroll()
{

    // Get a space character with the default colour attributes.
    u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    u16int blank = 0x20 /* space */ | (attributeByte << 8);

    // Row 25 is the end, this means we need to scroll up
    if(cursor_y >= 25)
    {
        // Move the current text chunk that makes up the screen
        // back in the buffer by a line
        int i;
        for (i = 0*80; i < 24*80; i++)
        {
            video_memory[i] = video_memory[i+80];
        }

        // The last line should now be blank. Do this by writing
        // 80 spaces to it.
        for (i = 24*80; i < 25*80; i++)
        {
            video_memory[i] = blank;
        }
        // The cursor should now be on the last line.
        cursor_y = 24;
    }
}


void console_put(char c) {
    // The background colour is black (0), the foreground is white (15).
    u8int backColour = 0;
    u8int foreColour = 15;

    // The attribute byte is made up of two nibbles - the lower being the 
    // foreground colour, and the upper the background colour.
    u8int  attributeByte = (backColour << 4) | (foreColour & 0x0F);
    // The attribute byte is the top 8 bits of the word we have to send to the
    // VGA board.
    u16int attribute = attributeByte << 8;
    u16int *location;

    // Handle a backspace, by moving the cursor back one space
    if (c == 0x08 && cursor_x)
    {
        cursor_x--;
        move_cursor();
        console_put(0x20);
        cursor_x--;
    }

    // Handle a tab by increasing the cursor's X, but only to a point
    // where it is divisible by 8.
    else if (c == 0x09)
    {
        cursor_x = (cursor_x+8) & ~(8-1);
    }

    // Handle carriage return
    else if (c == '\r')
    {
        cursor_x = 0;
    }

    // Handle newline by moving cursor back to left and increasing the row
    else if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    // Handle any other printable character.
    else if(c >= ' ')
    {
        location = video_memory + (cursor_y*80 + cursor_x);
        *location = c | attribute;
        cursor_x++;
    }

    // Check if we need to insert a new line because we have reached the end
    // of the screen.
    if (cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y ++;
    }

    // Scroll the screen if needed.
    scroll();
    // Move the hardware cursor.
    move_cursor();

}

void console_write(char *c) {
     int i=0;
     while (c[i]) {
        console_put(c[i++]);
     }
}

char kbd_buf[4096];
unsigned int kbd_buf_pos=0;

static void keyboard_handler(registers_t *regs) {
     if (kbd_buf_pos > 4095) {
       kbd_buf_pos=0;
       // TODO: Beep or something
       return;
     }
     u8int scancode=inb(0x60);
     if(scancode & 0x80) {
     } else {
       kbd_buf[kbd_buf_pos] = kbdus[scancode];
       kbd_buf_pos++;
     }
}

void init_console() {
     clear_console();
     reposition_cursor(0,0);
     register_interrupt_handler(IRQ1,&keyboard_handler);
}

static u32int tty_read(fs_node_t *node, u32int offset, u32int size, u8int *buffer) {
     return 0;
}

static u32int tty_write(fs_node_t *node, u32int offset, u32int size, u8int *buffer) {
     console_write((char*)buffer);
}

void init_tty() {
     console_tty = (fs_node_t*)kmalloc(sizeof(fs_node_t));
     k_strcpy(console_tty->name,"tty0");
     console_tty->mask    = 0;
     console_tty->flags   = FS_CHARDEVICE;
     console_tty->read    = &tty_read;
     console_tty->write   = &tty_write;
     console_tty->readdir = 0;
     console_tty->finddir = 0;
     console_tty->open    = 0;
     console_tty->close   = 0;
     console_tty->impl    = 0;
}

static char buf[1024];

int kprintf(const char *fmt, ...)
{
        va_list args;
        int i;

        va_start(args, fmt);
        i=vsprintf(buf,fmt,args);
        va_end(args);
        console_write(buf);
        return i;
}

void dump_hex(u32int n)
{
    s32int tmp;

    kprintf("0x");

    char noZeroes = 1;

    int i;
    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && noZeroes != 0)
        {
            continue;
        }
    
        if (tmp >= 0xA)
        {
            noZeroes = 0;
            console_put (tmp-0xA+'a' );
        }
        else
        {
            noZeroes = 0;
            console_put( tmp+'0' );
        }
    }
  
    tmp = n & 0xF;
    if (tmp >= 0xA)
    {
        console_put (tmp-0xA+'a');
    }
    else
    {
        console_put (tmp+'0');
    }

}

