// kernel/kernel.c

#include "../drivers/framebuffer.h"
#include "../drivers/types.h"
#include "../drivers/interrupts.h"
#include "../drivers/terminal.h"    

void kernel_main() {
    fb_clear();
    fb_set_color(2, 0); // Green text, black background
    fb_move(0, 0);
    fb_write("Hello, OS World!\n", 17);

    fb_set_color(4, 0);
    fb_write("Framebuffer driver initialized.\n", 32);

    fb_move(0, 10);
    fb_set_color(15, 0);
    fb_write("Cursor moved to (0,10).", 24);

    terminal_run();
}
