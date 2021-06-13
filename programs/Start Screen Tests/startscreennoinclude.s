mov r0, #0x1000
call setstackpointer

call setR1white
call drawpong

@ white, then wait, then clear, then wait, repeat
startscreenloop:
mov r0, #0x1000
call setR1white
call drawspacetostart

mov r0, #0xF
call waitcycles

mov r0, #0x1000
mov r1, #0
call drawspacetostart

mov r0, #0xF
call waitcycles

b startscreenloop

@ waits a determined number of cycles
@ arguments are...
@ r0 <- number of cycles to wait

waitcycles:
push r0
waitcycleloop:
sub r0, r0, #1
cmp r0, #0
bne waitcycleloop
pop r0
ret

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

@ draws the press space to start on start screen
@ arguments are...
@ r0 <- location to start drawing
@ r1 <- the colour to draw with

drawspacetostart:
push r4
push r5
push r6
push r7
push r8
push r9
push r10
push r11
mov r4, r0
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #114
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #24
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #36
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #24
str r1, [r4]
add r4, r4, #32
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #24
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #24
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #5
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #24
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #24
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #32
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #13
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #24
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #32
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #32
str r1, [r4]
add r4, r4, #24
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #13
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #24
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #32
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #32
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #32
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #24
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #13
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #36
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #32
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #36
str r1, [r4]
add r4, r4, #24
str r1, [r4]
add r4, r4, #24
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #24
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #13
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #32
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #24
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #13
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #24
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #32
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #13
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #24
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #36
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #32
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #24
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #20
str r1, [r4]
ldr r4, =0x1000000
str r0, [r4]
pop r11
pop r10
pop r9
pop r8
pop r7
pop r6
pop r5
pop r4
ret

@ draws the bbig main pong word on start screen
@ arguments are...
@ r0 <- location to start drawing
@ r1 <- the colour to draw with

drawpong:
push r4
push r5
push r6
push r7
push r8
push r9
push r10
push r11
mov r4, r0
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #0xff
add r4, r4, #236
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #32
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #36
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #36
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #121
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #32
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #36
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #36
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #113
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #72
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #72
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #72
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #72
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #193
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #193
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #193
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #193
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #193
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #193
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #12
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #193
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #193
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #16
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #193
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #24
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #113
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #24
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #113
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #76
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #36
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #76
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #36
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #76
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #36
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #76
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #36
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #28
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #76
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #68
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #76
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #68
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #76
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #68
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #76
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #68
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #76
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #68
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #76
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #68
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #76
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #68
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #76
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #68
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #76
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #68
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #76
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #68
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #76
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #76
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #40
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #76
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #76
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #76
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #20
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #105
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #84
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #36
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #36
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #0xff
add r4, r4, #113
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #84
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #36
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #44
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #36
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
add r4, r4, #4
str r1, [r4]
ldr r4, =0x1000000
str r0, [r4]
pop r11
pop r10
pop r9
pop r8
pop r7
pop r6
pop r5
pop r4
ret