@ main program where files are included

mov r0, #6
brl factorialsub

@ includes
@ factorial subroutine, 
@ arguments...
@ r0 <- the number to get factorial of
@ returns...
@ r0 <- factorial result

factorialsub:
push r1
mov r1, #1
factorialloop:
mul r1, r1, r0
sub r0, r0, #1
cmp r0, #1
bne factorialloop
mov r0, r1
pop r1
ret