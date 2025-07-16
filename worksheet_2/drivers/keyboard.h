#ifndef INCLUDE_KEYBOARD_H
#define INCLUDE_KEYBOARD_H
#define KEYBOARD_MAX_ASCII 83
#include "drivers/types.h"
u8int keyboard_read_scan_code(void);
u8int keyboard_scan_code_to_ascii(u8int);
u8int keyboard_read_scan_code(void);
u8int keyboard_scan_code_to_ascii(u8int scan_code);
char keyboard_getchar();
int readline(char *buf, int max_len);
void keyboard_interrupt_handler();
#endif /* INCLUDE_KEYBOARD_H */