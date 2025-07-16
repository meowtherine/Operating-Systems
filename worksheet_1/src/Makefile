all: task1 task2 loopsTask2 arrayTask2

task1: task1.asm
	nasm -f elf task1.asm -o task1.o
	gcc -m32 driver.o task1.o asm_io.o -o task1

task2: task2.asm
	nasm -f elf task2.asm -o task2.o
	gcc -m32 driver.o task2.o asm_io.o -o task2

loopsTask2: loopsTask2.asm
	nasm -f elf loopsTask2.asm -o loopsTask2.o
	gcc -m32 driver.o loopsTask2.o asm_io.o -o loopsTask2

arrayTask2: arrayTask2.asm
	nasm -f elf arrayTask2.asm -o arrayTask2.o
	gcc -m32 driver.o arrayTask2.o asm_io.o -o arrayTask2