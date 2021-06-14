@ set the stack pointer
mov r13, #0x80000
sub r13, r13, #1

@ setup register arguments
mov r0, #0x20000
mov r1, #64
mov r2, #0

inputloop:
brl getnextinput
and r3, r3, #0x7F

@ if a space, end
cmp r3, #0x20
bne inputloop

andeq r0, r0, r0

.include getinput.s