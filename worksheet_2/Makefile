# Object files
OBJECTS = \
source/loader.o \
kernel/kernel.o \
drivers/framebuffer.o \
drivers/hardware_interrupt_enabler.o \
drivers/interrupt_asm.o \
drivers/interrupt_handlers.o \
drivers/interrupts.o \
drivers/keyboard.o \
drivers/pic.o \
drivers/io.o \
drivers/terminal.o \
cfunctions.o \
drivers/string.o

# Tools and flags
CC = gcc
CFLAGS = -I. -Isource -Ikernel -Idrivers -Ilibc -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T ./source/link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

# Targets
all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	cp /opt/os/stage2_eltorito iso/boot/grub/
	genisoimage -R \
		-b boot/grub/stage2_eltorito \
		-no-emul-boot \
		-boot-load-size 4 \
		-A os \
		-input-charset utf8 \
		-quiet \
		-boot-info-table \
		-o os.iso \
		iso

run: os.iso
	qemu-system-i386 -nographic -boot d -cdrom os.iso -m 32 -d cpu -D logQ.txt

run-curses: os.iso
	qemu-system-i386 -curses \
		-monitor telnet::75454,server,nowait \
		-chardev stdio,id=char0 \
		-serial chardev:char0 \
		-boot d \
		-cdrom os.iso \
		-m 32 \
		-d cpu \
		-no-reboot \
		-no-shutdown \
		-D logQ.txt

# Compilation rules
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.asm       
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o source/*.o drivers/*.o kernel.elf os.iso iso/boot/kernel.elf logQ.txt
