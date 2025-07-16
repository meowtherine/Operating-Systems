// drivers/framebuffer.c

#include "framebuffer.h"
#include "io.h"

#define FB_BASE_ADDR 0xB8000
#define FB_WIDTH 80
#define FB_HEIGHT 25
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15
#define SERIAL_COM1_BASE 0x3F8 /* COM1 base port */
#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_FIFO_COMMAND_PORT(base) (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base) (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base) (base + 5)
#define SERIAL_LINE_ENABLE_DLAB 0x80

static volatile char *fb = (char *) FB_BASE_ADDR;
static unsigned short cursor_pos = 0;
static unsigned char fb_fg = 15; // white
static unsigned char fb_bg = 0;  // black

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[i * 2] = c;
    fb[i * 2 + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void fb_write(char *buf, unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
        fb_write_char(buf[i]);
    }
}

void fb_write_string(const char* str) {
    while (*str) {
        fb_write_char(*str++);
    }
}

void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, (pos >> 8) & 0xFF);
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0xFF);
    cursor_pos = pos;
}
void serial_configure_baud_rate(unsigned short com, unsigned short divisor){
    outb(SERIAL_LINE_COMMAND_PORT(com),
    SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com),
    (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com),
    divisor & 0x00FF);
}

void serial_configure_line(unsigned short com){
    /* Bit: | 7 | 6 | 5 4 3 | 2 | 1 0 |
    * Content: | d | b | prty | s | dl |
    * Value: | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
    */
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

int serial_is_transmit_fifo_empty(unsigned int com){
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void fb_move(unsigned short x, unsigned short y) {
    fb_move_cursor(y * FB_WIDTH + x);
}

void fb_write_char(char c) {
    if (c == '\n') {
        cursor_pos += FB_WIDTH - (cursor_pos % FB_WIDTH);
    } else {
        fb_write_cell(cursor_pos, c, fb_fg, fb_bg);
        cursor_pos++;
    }

    fb_move_cursor(cursor_pos);
}

void fb_clear() {
    for (unsigned int i = 0; i < FB_WIDTH * FB_HEIGHT; i++) {
        fb_write_cell(i, ' ', fb_fg, fb_bg);
    }
    fb_move_cursor(0);
}

void fb_set_color(unsigned char fg, unsigned char bg) {
    fb_fg = fg & 0x0F;
    fb_bg = bg & 0x0F;
}

unsigned short fb_get_cursor() {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    unsigned char high = inb(FB_DATA_PORT);
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    unsigned char low = inb(FB_DATA_PORT);
    return ((high << 8) | low);
}

void fb_backspace(void) {
    int pos = fb_get_cursor();
    if (pos > 0) {
        pos--;
        fb_write_cell(pos, ' ', 0, 15);  // black bg, white fg
        fb_move_cursor(pos);
    }
}


