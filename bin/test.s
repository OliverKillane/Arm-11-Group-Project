ldr r0 =50000000
loop:
sub r0 r0 #1
cmp r0 #0
bgt loop
andeq r0 r0 r0
