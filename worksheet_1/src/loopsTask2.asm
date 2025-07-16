%include "asm_io.inc"
segment .data
msg1 db "Enter your name: ", 0 ;input name
msg2 db "How many times do you want the message printed?: ", 0 ;input times
num1 dd 100
num2 dd 50
;num3 dd 0
msg3 db "Welcome", 0
msg4 db "Enter value between 50-100", 0

segment .bss
;name resd 1 ;name
printTimes resd 2 ;integer
num3 resd 1 ;counter

segment .text
global asm_main ; set main func
asm_main:
    ;mov eax, msg1
    ;call print_string        ;print msg1
    ;call read_string         ;read name THERE IS NO READ_STRING IN ASM_IO??
    ;mov [name], eax         ; store name

    mov eax, msg2
    call print_string       ;print msg2
    call read_int         ;read times
    mov [printTimes], eax         ; store times

    mov eax, [printTimes] ;get times value
    cmp eax, [num1]  ; compare w num1
    jl lessThan100 ;if less than send there

    jmp end_error ;if greater than send there

lessThan100:
    cmp eax, [num2] ;compare w num2 ;compate w num2
    jg greaterThan50 ;if greater send there

    jmp end_error ;if less than send there

greaterThan50:
    mov dword [num3], 0

    loop_start:
        mov eax, [num3]
        cmp eax, [printTimes]
        je end_loop

        mov eax, msg3 ; welcome message
        call print_string ;print
        call print_nl ;new line

        push eax
        ;mov eax, [name] ; get name
        ;call print_string ;print name ITS NOT IN ASM_IO
        pop eax

        mov eax, [num3]
        add eax, 1        ; add 1 to count
        mov [num3], eax  
        jmp loop_start
 
end_error:
    mov eax, msg4   
    call print_string
    call print_nl

end_loop:
end_if:
mov eax, 0 ; return back to C
ret