#include "drivers/pic.h"
#include "drivers/types.h"
#include "drivers/io.h"

void pic_remap(s32int offset1, s32int offset2) {
    u8int mask1 = inb(PIC_1_DATA);
    u8int mask2 = inb(PIC_2_DATA);

    outb(PIC_1_COMMAND, PIC_ICW1_INIT | PIC_ICW1_ICW4);
    outb(PIC_2_COMMAND, PIC_ICW1_INIT | PIC_ICW1_ICW4);

    outb(PIC_1_DATA, offset1);
    outb(PIC_2_DATA, offset2);

    outb(PIC_1_DATA, 0x04);
    outb(PIC_2_DATA, 0x02);

    outb(PIC_1_DATA, PIC_ICW4_8086);
    outb(PIC_2_DATA, PIC_ICW4_8086);

    outb(PIC_1_DATA, mask1);
    outb(PIC_2_DATA, mask2);
}

void pic_acknowledge(u32int interrupt) {
    if (interrupt >= PIC_2_OFFSET && interrupt <= PIC_2_END) {
        outb(PIC_2_COMMAND, PIC_ACKNOWLEDGE);
    }
    outb(PIC_1_COMMAND, PIC_ACKNOWLEDGE);
}
