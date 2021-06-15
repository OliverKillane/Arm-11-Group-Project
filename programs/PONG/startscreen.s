@ displays the start screen, flashing press space to start.
@ when space is pressed, returns
@ arguments:
@ r0 <- pointer to where to draw the frame
@ uses registers:
@ r0 to r2 <- for aguments for functions
@ r3 <- current user input
@ r4 <- the input index
@ returns...
@ r0 <- the current index of input buffer

startscreen:
@ push registers to save values
push r0
push r1
push r2
push r3
push r4
push r5
push r14

@ start reading input buffer from 0
mov r4, #0

@ save location to draw the screen at
mov r5, r0

@ draw white PONG logo
mov r0, r5
brl setR1white
brl drawpongtitle

@ flashing loop
startscreenloop:

@ draw 'press space to start' in white
mov r0, r5
brl setR1white
brl drawspacetostart

@ wait
mov r0, #0xFF
brl waitcycles

@ clear 'press space to start'
mov r0, r5
mov r1, #0
brl drawspacetostart

@ wait
mov r0, #0xFF
brl waitcycles

@ check for user input
mov r0, #0x30000
mov r1, #64
mov r2, r4

@ remove all user input while not null, remove msb from input (KEYDOWN/UP bit)
startscreeninputloop:
brl getnextinput
and r3, r3, #0x7F

@ if a space, end
cmp r3, #0x20
beq startscreenend

@ if not null continue
cmp r3, #0
bne startscreeninputloop

@ store current input place (null) in r4
mov r4, r2

b startscreenloop

@ return from startscreen
startscreenend:

@ clear out the pong logo
mov r0, r5
mov r1, #0
brl drawpongtitle

pop r14
pop r5
pop r4
pop r3
pop r2
pop r1
pop r0
ret

@ needed graphics for pong title and the flashing message
.include pongtitle.s
.include spacetostart.s