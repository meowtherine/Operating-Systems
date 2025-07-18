global loader ; the entry symbol for ELF
    MAGIC_NUMBER equ 0x1BADB002 ; define the magic number constant
    FLAGS equ 0x0 ; multiboot flags
    CHECKSUM equ -MAGIC_NUMBER ; calculate the checksum
                               ; (magic number + checksum + flags should ↪ equal 0)
    KERNEL_STACK_SIZE equ 4096 ; size of stack in bytes
    
    section .multiboot
    align 4
    dd 0x1BADB002          ; magic number
    dd 0x00                ; flags (set bits as needed)
    dd -(0x1BADB002 + 0x00) ; checksum
    
    section .bss
    align 4 ; align at 4 bytes
    kernel_stack: 
        resb KERNEL_STACK_SIZE 

    section .text: ; start of the text (code) section
    align 4 ; the code must be 4 byte aligned
        dd MAGIC_NUMBER ; write the magic number to the machine ↪ code,
        dd FLAGS ; the flags,
        dd CHECKSUM ; and the checksum

    loader: ; the loader label (defined as entry ↪ point in linker script)
        mov esp, kernel_stack + KERNEL_STACK_SIZE 

        extern sum_of_three ; the function sum_of_three is defined elsewhere
        extern multiply_two
        extern subtract_three

        ; The assembly code for sum_of_three

        push dword 3 ; arg3
        push dword 2 ; arg2
        push dword 1 ; arg1
        call sum_of_three ; call the function, the result will be in eax
        mov ebx, eax
        add esp, 12 ;clear, 12(3 * 4 bytes)

        push dword 4 ; arg4
        push dword 5 ; arg5
        call multiply_two
        mov ecx, eax
        add esp, 8

        push dword 8 ; arg6
        push dword 7 ; arg7
        push dword 6 ; arg8
        call subtract_three
        mov edx, eax
        add esp, 12
    
    mov eax, 0xCAFEBABE 

    .loop:
        jmp .loop ; loop forever
