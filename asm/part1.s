@ gcc part1.s -o part1

.global main                    @ Initialize main entrypoint
.extern printf                  @ printf libc extern function
.text                           @ .text section
main:
    LDR R1, =askuserprompt      @ Initial prompt string
    LDR R2, =askuserprompt_len  @ Initial prompt string length
    bl sys_write                @ Call sys_write function

    LDR R1, =message            @ Input buffer
    MOV R2, #30                 @ Read 30 characters
    bl sys_read                 @ Call sys_read function

    LDR R0, =returnprompt       @ Output prompt string
    LDR R1, =message            @ Input buffer
    bl printf                   @ Call printf function

    MOV R7, #1                  @ Syscall exit
    SWI 0                       @ Software Interrupt for syscall

sys_read:                       @ sys_read function label
    MOV R7, #3                  @ Syscall read from keyboard
    MOV R0, #0                  @ Input stream keyboard
    SWI 0                       @ Software Interrupt for syscall
    bx lr                       @ Return to caller

sys_write:                      @ sys_write function label
    MOV R7, #4                  @ Syscall write to screen
    MOV R0, #1                  @ Output to monitor
    SWI 0                       @ Software Interrupt for syscall
    bx lr                       @ Return to caller

.data
.balign 4
message: .skip 120              @ Initialize NULL 30B buffer

.balign 4
askuser: .asciz "Please Enter a number 1 to 3: "    @ Initial prompt string
askuser_len = . - askuser                           @ Initial prompt string length

.balign 4
returnprompt: .asciz "Your inputted number is: %s"  @ Output prompt string

