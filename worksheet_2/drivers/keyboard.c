#include "io.h"
#include "framebuffer.h"
#include "types.h"
#include "keyboard.h"
#include "interrupts.h"
#define KEYBOARD_DATA_PORT 0x60
#define INPUT_BUFFER_SIZE 256
static u8int input_buffer[INPUT_BUFFER_SIZE];
static unsigned int head = 0;
static unsigned int tail = 0;
/** read_scan_code:
 *  Reads a scan code from the keyboard
 *
 *  @return The scan code (NOT an ASCII character!)
 */
u8int keyboard_read_scan_code(void)
{
    return inb(KEYBOARD_DATA_PORT);
}
u8int keyboard_scan_code_to_ascii(u8int scan_code)
{
    // Ignore key releases (scan codes with bit 7 set)
    if (scan_code & 0x80) {
              return 0;
    }
    // Scan code to ASCII mapping for standard US QWERTY keyboard
    switch(scan_code) {
        // Numbers row
        case 0x02: return '1';
        case 0x03: return '2';
        case 0x04: return '3';
        case 0x05: return '4';
        case 0x06: return '5';
        case 0x07: return '6';
        case 0x08: return '7';
        case 0x09: return '8';
        case 0x0A: return '9';
        case 0x0B: return '0';
        case 0x0C: return '-';
        case 0x0D: return '=';
        case 0x0E: return '\b'; // Backspace
        // Top letter row
        case 0x10: return 'q';
        case 0x11: return 'w';
        case 0x12: return 'e';
        case 0x13: return 'r';
        case 0x14: return 't';
        case 0x15: return 'y';
        case 0x16: return 'u';
        case 0x17: return 'i';
        case 0x18: return 'o';
        case 0x19: return 'p';
        case 0x1A: return '[';
        case 0x1B: return ']';
        case 0x1C: return '\n'; // Enter
        // Middle letter row
        case 0x1E: return 'a';
        case 0x1F: return 's';
        case 0x20: return 'd';
        case 0x21: return 'f';
        case 0x22: return 'g';
  case 0x23: return 'h';
        case 0x24: return 'j';
        case 0x25: return 'k';
        case 0x26: return 'l';
        case 0x27: return ';';
        case 0x28: return '\'';
        case 0x29: return '`';
        // Bottom letter row
        case 0x2B: return '\\';
        case 0x2C: return 'z';
        case 0x2D: return 'x';
        case 0x2E: return 'c';
        case 0x2F: return 'v';
        case 0x30: return 'b';
        case 0x31: return 'n';
        case 0x32: return 'm';
        case 0x33: return ',';
        case 0x34: return '.';
        case 0x35: return '/';
        case 0x39: return ' '; // Space bar
        // Numpad
        case 0x37: return '*'; // Numpad *
        case 0x47: return '7';
        case 0x48: return '8';
        case 0x49: return '9';
        case 0x4A: return '-';
        case 0x4B: return '4';
        case 0x4C: return '5';
        case 0x4D: return '6';
        case 0x4E: return '+';
        case 0x4F: return '1';
        case 0x50: return '2';
        case 0x51: return '3';
        case 0x52: return '0';
        case 0x53: return '.';
        default: return 0; // Unknown scan code
    }
}

int getc(void) {
    if (head == tail) {
        return -1; 
    }
    u8int c = input_buffer[tail];
    tail = (tail + 1) % INPUT_BUFFER_SIZE;
    return c;
}

char keyboard_getchar(void) {
    int c = getc();
    while (c == -1) {
        c = getc();
    }
    return (char)c;
}


int readline(char *buf, int max_len) {
    int i = 0;
    while (i < max_len - 1) {
        char c = keyboard_getchar(); {
            int c = -1;
            while ((c = getc()) == -1); 
            return (char)c;
        }

        if (c == '\n') {
            fb_write_char('\n');
            buf[i] = '\0';
            return i;
        } else if (c == '\b') {
            if (i > 0) {
                i--;
                fb_backspace();
            }
        } else {
            buf[i++] = c;
            fb_write_char(c);
        }
    }

    buf[i] = '\0';
    return i;
}

void keyboard_interrupt_handler() {
    u8int sc = keyboard_read_scan_code();
    u8int ch = keyboard_scan_code_to_ascii(sc);
    if (ch != 0) {
        input_buffer[head] = ch;
        head = (head + 1) % INPUT_BUFFER_SIZE;
    }
}


