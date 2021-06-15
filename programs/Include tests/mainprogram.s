@ main program where files are included
ldr r13, =0xFFF
mov r0, #6
brl factorialsub
andeq r0, r0, r0

@ includes
.include factorialsub.s