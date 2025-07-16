#include "drivers/interrupts.h"
#include "pic.h"
#include "io.h"
#include "framebuffer.h"
#include "keyboard.h"
#define INTERRUPTS_DESCRIPTOR_COUNT 256
#define INTERRUPTS_KEYBOARD 33
#define INPUT_BUFFER_SIZE 256
#define PIC_1_OFFSET 0x20
#define PIC_2_OFFSET 0x28
volatile unsigned int head = 0; // write index
volatile unsigned int tail = 0; // read index

u8int input_buffer[INPUT_BUFFER_SIZE];
u8int buffer_index = 0;
struct IDTDescriptor idt_descriptors[INTERRUPTS_DESCRIPTOR_COUNT];
struct IDT idt;
u32int BUFFER_COUNT;
void interrupts_init_descriptor(s32int index, u32int address){
idt_descriptors[index].offset_high = (address >> 16) & 0xFFFF; // offset↪ bits 0..15
idt_descriptors[index].offset_low = (address & 0xFFFF); // offset bits↪ 16..31
idt_descriptors[index].segment_selector = 0x08; // The second (code)↪ segment selector in GDT: one segment is 64b.
idt_descriptors[index].reserved = 0x00; // Reserved.
/*
Bit: | 31 16 | 15 | 14 13 | 12 | 11 10 9 8 | 7 6
↪ 5 | 4 3 2 1 0 |
Content: | offset high | P | DPL | S | D and GateType | 0
↪ 0 0 | reserved
P If the handler is present in memory or not (1 = present, 0 = not
↪ present). Set to 0 for unused interrupts or for Paging.
DPL Descriptor Privilige Level, the privilege level the handler can
↪ be called from (0, 1, 2, 3).
S Storage Segment. Set to 0 for interrupt gates.
D Size of gate, (1 = 32 bits, 0 = 16 bits).
*/
idt_descriptors[index].type_and_attr = (0x01 << 7) | // P
(0x00 << 6) | (0x00 << 5) | // DPL
0xe; // 0b1110=0xE 32-bit interrupt gate
}
void interrupts_install_idt()
{
interrupts_init_descriptor(INTERRUPTS_KEYBOARD, (u32int)interrupt_handler_33);
idt.address = (s32int) &idt_descriptors;
idt.size = sizeof(struct IDTDescriptor) * INTERRUPTS_DESCRIPTOR_COUNT;
load_idt((s32int) &idt);
/*pic_remap(PIC_PIC1_OFFSET, PIC_PIC2_OFFSET);*/
pic_remap(PIC_1_OFFSET, PIC_2_OFFSET);
// Unmask keyboard interrupt (IRQ1)
outb(0x21, inb(0x21) & ~(1 << 1));
}
/* Interrupt handlers
↪ ********************************************************/
void interrupt_handler(__attribute__((unused)) struct cpu_state cpu, u32int interrupt, __attribute__((unused)) struct stack_state stack) {
u8int input;
u8int ascii;

switch (interrupt) {
    case INTERRUPTS_KEYBOARD:
        while ((inb(0x64) & 1)) {
            input = keyboard_read_scan_code();
            // Only process if it's not a break code
            if (!(input & 0x80)) {
                if (input <= KEYBOARD_MAX_ASCII) {
                    ascii = keyboard_scan_code_to_ascii(input);
                    if (ascii != 0) {
                        // Backspace
                        if (ascii == '\b') {
                            if (head != tail) {
                                head = (head + INPUT_BUFFER_SIZE - 1) % INPUT_BUFFER_SIZE;
                                input_buffer[head] = 0;
                                fb_backspace();
                            }
                        }
                        // Newline
                        else if (ascii == '\n') {
                            if (((head + 1) % INPUT_BUFFER_SIZE) != tail) { 
                                input_buffer[head] = '\n';
                                head = (head + 1) % INPUT_BUFFER_SIZE;
                                fb_write_char('\n');
                            }
                        }
                        // Characters
                        else {
                            if (((head + 1) % INPUT_BUFFER_SIZE) != tail) { 
                                input_buffer[head] = ascii;
                                head = (head + 1) % INPUT_BUFFER_SIZE;
                                fb_write_char(ascii);
                            }
                        }
                    }
                }
            }
        }
        pic_acknowledge(interrupt);
        break;

    default:
        break;
    }
}