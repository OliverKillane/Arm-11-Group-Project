ldr r0, =0x1000000
ldr r1, =0x1000 
mov r2, #0
str r1, [r0]
loop:
str r2, [r1, r2]
add r2, r2, #4
cmp r2, #82944
bne loop
andeq r0,r0,r0
