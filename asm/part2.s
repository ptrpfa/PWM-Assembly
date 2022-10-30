@ gcc part2.s -o part2

.global main

.extern scanf
.extern printf
.extern open
.extern mmap
.extern usleep

/*
//Raspberry Pi 2 IO base address
#if(RPI == RPI2)
    #define ARM_IO_BASE        0x3F000000
#elif(RPI == RPI1)
    #define ARM_IO_BASE        0x20000000
#else
    #error "Please define Raspberry Pi version"
#endif

//
// General Purpose I/O
//
#define ARM_GPIO_BASE        (ARM_IO_BASE + 0x200000)

#define ARM_GPIO_GPFSEL0     (*(volatile uint32_t *)(ARM_GPIO_BASE + 0x00))
#define ARM_GPIO_GPFSEL1     (*(volatile uint32_t *)(ARM_GPIO_BASE + 0x04))
#define ARM_GPIO_GPFSEL2     (*(volatile uint32_t *)(ARM_GPIO_BASE + 0x08))
#define ARM_GPIO_GPFSEL4     (*(volatile uint32_t *)(ARM_GPIO_BASE + 0x10))
#define ARM_GPIO_GPSET0      (*(volatile uint32_t *)(ARM_GPIO_BASE + 0x1C))
#define ARM_GPIO_GPSET1      (*(volatile uint32_t *)(ARM_GPIO_BASE + 0x20))
#define ARM_GPIO_GPCLR0      (*(volatile uint32_t *)(ARM_GPIO_BASE + 0x28))
#define ARM_GPIO_GPCLR1      (*(volatile uint32_t *)(ARM_GPIO_BASE + 0x2C))
#define ARM_GPIO_GPLEV0      (*(volatile uint32_t *)(ARM_GPIO_BASE + 0x34))
#define ARM_GPIO_GPEDS0      (*(volatile uint32_t *)(ARM_GPIO_BASE + 0x40))
#define ARM_GPIO_GPREN0      (*(volatile uint32_t *)(ARM_GPIO_BASE + 0x4C))
#define ARM_GPIO_GPFEN0      (*(volatile uint32_t *)(ARM_GPIO_BASE + 0x58))
#define ARM_GPIO_GPHEN0      (*(volatile uint32_t *)(ARM_GPIO_BASE + 0x64))
#define ARM_GPIO_GPLEN0      (*(volatile uint32_t *)(ARM_GPIO_BASE + 0x70))
#define ARM_GPIO_GPAREN0     (*(volatile uint32_t *)(ARM_GPIO_BASE + 0x7C))
#define ARM_GPIO_GPAFEN0     (*(volatile uint32_t *)(ARM_GPIO_BASE + 0x88))
#define ARM_GPIO_GPPUD       (*(volatile uint32_t *)(ARM_GPIO_BASE + 0x94))
#define ARM_GPIO_GPPUDCLK0   (*(volatile uint32_t *)(ARM_GPIO_BASE + 0x98))

#endif //MEMIO_H
*/

@ GPFSEL1 [Offset: 0x04] responsible for GPIO Pins 10 to 19
@ GPSET0  [Offset: 0x1C] responsible for GPIO Pins 0 to 31
@ GPCLR0  [Offset: 0x28] responsible for GPIO Pins 0 to 31

@ GPIO Constants
.equ PIN16,   16             @ GPIO Pin 16
.equ PIN17,   17		     @ GPIO Pin 17
.equ GPFSEL1, 0x04           @ Function register offset
.equ GPSET0,  0x1C           @ Set register offset
.equ GPCLR0,  0x28           @ Clear register offset
.equ GPFSEL1_MASK, 0b1       @ Mask for function register

@ mmap Constants
.equ BLOCK_SIZE, 4096        @ Memory page size
.equ PROT_RDWR,  0x3         @ Read-write protection (PROT_READ|PROT_WRITE)
.equ MAP_SHARED, 1           @ Shared permissions

@ Misc Constants
.equ SLEEP_SEC,    1         @ Seconds for sleep
.equ STACK_OFFSET, 4         @ Stack offset size

.text
main:
    SUB SP, SP, #STACK_OFFSET   @ Allocate stack by 4 bytes

    @ Open /dev/gpiomem for read-write and syncing
    @ fd = open("/dev/gpiomem\0", O_RDWR)
    LDR R0, =addr_file          @ GPIO Controller address
    LDR R1, flags               @ Open flag permissions
    BL open                     @ Call open function

    @ Memory map the GPIO registers to an accessible memory location
    @ mmap(GPIO base address, pagesize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, GPIO physical address)
    MOV R4, R0                  @ GPIO Controller file descriptor
    STR R4, [sp, #0]            @ Store file descriptor
    LDR R0, gpiobase            @ GPIO base address
    MOV R1, #BLOCK_SIZE         @ Memory page size
    MOV R2, #PROT_RDWR          @ Read-write protection
    MOV R3, #MAP_SHARED         @ Shared permissions
    BL mmap                     @ Call mmap function

    @ Check mmap returns an accessible memory location
    @ If not, mmap returns -1 and goto exit
    CMP R0, #-1                 @ Compare mmap return value to -1
    BEQ exit                    @ If value == -1, goto exit

    STR R0, [SP, #STACK_OFFSET] @ Store memory mapped GPIO register location in stack

    MOV R1, #PIN16              @ Set PIN 16 to be used
    BL init_output              @ Setup GPIO pin function register
    B exit                      @ Goto exit

loop:
    LDR R0, =askuserprompt      @ Initial prompt string
    BL printf                   @ Call printf function

    LDR R0, =scanf_fmt          @ scanf format specifier
    LDR R1, =message            @ Input buffer address
    BL scanf                    @ Call scanf function

    LDR R4, =message            @ Input buffer address
    LDR R1, [R4]                @ Dereference input buffer

    CMP R1, #0                  @ Compare value with 0
    BLE wrong_input             @ If value <= 0, goto wrong_input
    CMP R1, #4                  @ Compare value with 4
    BGE wrong_input             @ If value >= 4, goto wrong_input

    LDR R0, =returnprompt       @ Output prompt string
    BL printf                   @ Call printf function

    CMP R1, #1           	  @ Compare value with 1    
    ITT EQ				  @ If-then-then
    MOVEQ R1, #PIN16		  @ Set PIN 16 to be used
    BEQ set_pin 			  @ Set pin to turn on LED

    CMP R1, #2           	  @ Compare value with 2    
    ITT EQ				  @ If-then-then
    MOVEQ R1, #PIN17		  @ Set PIN 17 to be used
    BEQ set_pin 			  @ Set pin to turn on LED

    CMP R1, #3           	  @ Compare value with 3  
    ITTTT EQ		        @ If-then-then
    MOVEQ R1, #PIN16		  @ Set PIN 16 to be used
    BEQ clear_pin 		  @ Set pin to turn on LED
    MOVEQ R1, #PIN17		  @ Set PIN 17 to be used
    BEQ clear_pin 		  @ Set pin to turn on LED

    BL wait                     @ Wait a second

    B loop                      @ Loopback

wrong_input:
    LDR R0, =wrongprompt        @ Wrong input prompt string
    BL printf                   @ Call printf function

exit:
    MOV R7, #1                  @ Syscall exit
    SWI 0                       @ Software Interrupt for syscall

wait:
    PUSH { R0, lr }             @ Save used registers on stack
    MOV R0, #SLEEP_SEC          @ Seconds for sleep
    BL sleep                    @ Call sleep function
    POP { R0, pc }              @ Return to caller

init_output:
    LDR R3, [sp, #STACK_OFFSET] @ Load GPIO memory location
    ADD R3, R3, #GPFSEL1        @ Add offset to GPFSEL1
    LDR R2, [R3]                @ Get value of GPFSEL1
    MOV R4, #GPFSEL1_MASK       @ Initialize GPFSEL1_MASK
    LSL R4, R4, R1              @ Shift bit to PIN number
    ORR R2, R2, #GPFSEL1_MASK   @ Set mask for FSEL output
    STR R2, [R3]                @ Store set bits at GPFSEL1
    BX lr                       @ Return to caller

set_pin:
    LDR R3, [sp, #STACK_OFFSET] @ Load GPIO memory location
    ADD R3, R3, #GPSET0         @ Add offset to GPSET0
    MOV R2, #1                  @ Turn on bit
    LSL R2, R2, R1              @ Shift bit to PIN number
    STR R2,[R3]                 @ Update PIN number at GPSET0
    BX lr                       @ Return to caller

clear_pin:
    LDR R3, [sp, #STACK_OFFSET] @ Load GPIO memory location
    ADD R3, R3, #GPCLR0         @ Add offset to GPCLR0
    MOV R2, #1                  @ Turn off bit
    LSL R2, R2, R1              @ Shift bit to PIN number
    STR R2,[R3]                 @ Update PIN number at GPCLR0
    BX lr                       @ Return to caller


gpiobase:  .word   0xfe200000   @ GPIO base address for Raspberry Pi 3
flags:     .word   2|256        @ Open flag permissions (O_RDWR|O_SYNC)

.data
message: .word 0                @ Initialize input buffer

.balign 4
addr_file: .asciz  "/dev/gpiomem\0"   @ GPIO Controller

.balign 4
scanf_fmt: .string "%d"         @ scanf format specifier

.balign 4
askuserprompt: .asciz "Please Enter a number 1 to 3: "              @ Initial prompt string

.balign 4
returnprompt: .asciz "Your inputted number is: %d\n"                @ Output prompt string

.balign 4
wrongprompt: .asciz "Your inputted number is not within 1 to 3\n"   @ Wrong input prompt string
