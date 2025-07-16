// drivers/framebuffer.h

#ifndef INCLUDE_FRAMEBUFFER_H
#define INCLUDE_FRAMEBUFFER_H

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
void fb_write(char *buf, unsigned int len);
void fb_write_string(const char* str);
void fb_move_cursor(unsigned short pos);
void serial_configure_baud_rate(unsigned short com, unsigned short divisor);
void serial_configure_line(unsigned short com);
int serial_is_transmit_fifo_empty(unsigned int com);
void fb_move(unsigned short x, unsigned short y);
void fb_print_char(char c);
void fb_set_color(unsigned char foreground, unsigned char background);
void fb_clear();
void fb_set_color(unsigned char fg, unsigned char bg);
void fb_backspace(void);
unsigned short fb_get_cursor();
void fb_write_char(char c);

#endif
