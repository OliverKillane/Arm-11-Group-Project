@ gets the next input as an ascii, assumes little endian storage
@ arguments...
@ r0 <- the buffer start
@ r1 <- the buffer size
@ r2 <- buffer index to read from
@ returns...
@ r2 <- next index
@ r3 <- the next character

getnextinput:
push r4

@ load the next word, get most significant byte
ldr r4, [r0, r2]
and r3, r4, #0xFF

@ if still zero, ignore
cmp r3, #0
beq getinputend

@ store the rest back
sub r4, r4, r3
str r4, [r0, r2]

@ move r2 to next index, set to zero if at end
cmp r2, r1
bne getinputnextindex

@ reset to start
mov r2, #0
b getinputend

@ increment the index
getinputnextindex:
add r2, r2, #1

getinputend:
@ restore the local var registers and return
pop r4
ret