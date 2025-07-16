%include "asm_io.inc"
segment .data
msg1 db "Sum of array is: ", 0
msg2 db "Enter number: ",0
msg3 db "Sum of range is: ", 0
num1 dd 100 ;100 nums in loop
num2 dd 0
arrayTotal dd 0
rangeTotal dd 0

segment .bss
array resd 100
integer1 resd 1 ; first integer
integer2 resd 1 ; second integer

segment .text
global asm_main ; set main func
asm_main:

mov eax, msg2 ; 
call print_string
call read_int ; read the first integer
mov [integer1], eax ; store it in memory
mov eax, msg2 ; 
call print_string
call read_int ; read the second integer
mov [integer2], eax ; store it in memory
call print_nl

mov dword [num2], 0

loop_start:

        mov eax, [num2]
        cmp eax, [num1]
        je end_loop

        mov [array + eax*4], eax ; add num to array

        mov ebx, [arrayTotal]
        add ebx, [array + eax*4] ;add current array num to arrayTotal
        mov [arrayTotal], ebx

        mov eax, [num2]
        add eax, 1        ; add 1 to count
        mov [num2], eax   
        jmp loop_start

end_loop:

range_loop:

        mov eax, [integer1]
        cmp eax, [integer2]
        je end_rangeloop

        mov ebx, [rangeTotal]
        add ebx, eax ;add current range num to rangeTotal
        mov [rangeTotal], ebx

        mov eax, [integer1]
        add eax, 1        ; add 1 to count
        mov [integer1], eax   
        jmp range_loop
end_rangeloop:

mov eax, msg1
call print_string
mov eax, [arrayTotal]
call print_int
call print_nl

mov eax, msg3
call print_string
mov eax, [rangeTotal]
call print_int
call print_nl

mov eax, 0 ; return back to C
ret