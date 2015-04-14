#include <console.h>

uint16_t *video_memory = (uint16_t *)0xB8000;
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;

void move_cursor() {
     uint16_t cursorLocation = cursor_y * 80 + cursor_x;
     outb(0x3D4, 14);
     outb(0x3D5, cursorLocation >> 8);
     outb(0x3D4, 15);
     outb(0x3D5, cursorLocation);
}

void reposition_cursor(uint8_t x, uint8_t y) {
     cursor_x = x;
     cursor_y = y;
     move_cursor();
}

void clear_console() {
     uint8_t  attrib_byte = (0 << 4) | (15 & 0x0F);
     uint16_t blank       = 0x20 | (attrib_byte << 8);
     int i;
     for (i=0; i < 80*25; i++) {
          video_memory[i] = blank;
     }
}

static void scroll() {
    uint8_t  attributeByte = (0 << 4) | (15 & 0x0F);
    uint16_t blank         = 0x20     | (attributeByte << 8);

    if(cursor_y >= 25) {
       int i;
       for (i = 0*80; i < 24*80; i++) {
           video_memory[i] = video_memory[i+80];
       }
       for (i = 24*80; i < 25*80; i++) {
            video_memory[i] = blank;
       }
       cursor_y = 24;
    }
}


void console_put(char c) {
     uint8_t  backColour = 0;
     uint8_t  foreColour = 15;
     uint8_t  attributeByte = (backColour << 4) | (foreColour & 0x0F);
     uint16_t attribute = attributeByte << 8;
     uint16_t *location;

     if (c == 0x08 && cursor_x) {  // backspace
        cursor_x--;
        move_cursor();
        console_put(0x20);
        cursor_x--;
     } else if (c == 0x09) {       // tab
        cursor_x = (cursor_x+8) & ~(8-1);
     } else if (c == '\r') {       // carriage return
        cursor_x = 0;
     } else if (c == '\n') {       // newline
        cursor_x = 0;
        cursor_y++;
     } else if(c >= ' ') {         // all other printables
        location = video_memory + (cursor_y*80 + cursor_x);
        *location = c | attribute;
        cursor_x++;
     } 

     // Check if we need to insert a new line because we have reached the end
     // of the screen.
     if (cursor_x >= 80) {
         cursor_x = 0;
         cursor_y ++;
     }

     scroll();
     move_cursor();
}

void console_write(char *c) {
     int i=0;
     while (c[i]) {
        console_put(c[i++]);
     }
}

void init_console() {
     clear_console();
     reposition_cursor(0,0);
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


