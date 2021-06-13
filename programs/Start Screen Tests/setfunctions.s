@ set the stack pointer without using ldr
setstackpointer:
mov r13, #0x80000
sub r13, r13, #1
ret

@ set the r1 register to white
setR1white:
mov r1,     #0x00FF0000
orr r1, r1, #0x0000FF00
orr r1, r1, #0x000000FF
ret