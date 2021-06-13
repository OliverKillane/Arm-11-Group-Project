@ factorial subroutine, 
@ arguments...
@ r0 <- the number to get factorial of
@ returns...
@ r0 <- factorial result

factorialsub:
push r1
push r2
mov r1, #1
factorialloop:
mul r2, r1, r0
mov r1, r2
sub r0, r0, #1
cmp r0, #1
bne factorialloop
mov r0, r1
pop r2
pop r1
ret