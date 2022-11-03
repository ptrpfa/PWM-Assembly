@ gcc part1.s -o part1

.global main                    @ Initialize main entrypoint

.extern scanf                   @ scanf libc extern function
.extern printf                  @ printf libc extern function

.text                           @ .text section
main:
    LDR R0, =askuserprompt      @ Initial prompt string
    BL printf                   @ Call printf function

    LDR R0, =scanf_fmt          @ scanf format specifier
    LDR R1, =message            @ Input buffer address
    BL scanf                    @ Call scanf function

    LDR R2, =message            @ Input buffer address
    LDR R1, [R2]                @ Dereference input buffer

    CMP R1, #0                  @ Compare value with 0
    BLE wrong_input             @ If value <= 0, goto wrong_input
    CMP R1, #4                  @ Compare value with 4
    BGE wrong_input             @ If value >= 4, goto wrong_input

    LDR R0, =returnprompt       @ Output prompt string
    BL printf                   @ Call printf function
    B exit                      @ Goto exit

wrong_input:
    LDR R0, =wrongprompt        @ Wrong input prompt string
    BL printf                   @ Call printf function

exit:
    MOV R7, #1                  @ Syscall exit
    SWI 0                       @ Software Interrupt for syscall

.data
message: .word 0                @ Initialize input buffer

.balign 4
scanf_fmt: .string "%d"         @ scanf format specifier

.balign 4
askuserprompt: .asciz "Please Enter a number 1 to 3: "              @ Initial prompt string

.balign 4
returnprompt: .asciz "Your inputted number is: %d, stored at %p\n"                @ Output prompt string

.balign 4
wrongprompt: .asciz "Your inputted number is not within 1 to 3\n"   @ Wrong input prompt string

