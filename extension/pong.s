@TODO:
@ need to set !!Placeholder!! vars
@ need to store ball x, y velocity


@ Main program
.text

@ global reg values:
@ r13 <- stack pointer (stack_start)
@ r0 <- current buffer index
@ r1 <- EMPTY (for the gui mode later - startscreen, quitmenu etc)
@ r2 <- bcurr address
@ r3 <- bprev address
@ r4 <- pcurr address
@ r5 <- pprev address
@ r6 <- score address
@ r7 <- ball x velocity
@ r8 <- ball y velocity

@ loading globals:

brl setvars

@ startup draw the display
push r0
push r1
push r2
push r3
brl initdraw
pop r3
pop r2
pop r1
pop r0

@ set initial positions
push r0
brl newgame
pop r0

@ the mainloop of the program (get user input, draw next frame)
mainloop:

@blackout the screen to remove the old frame
push r0
push r1
push r2
push r3
brl blackout
pop r3
pop r2
pop r1
pop r0

@ swap coordinates
brl swapcoors

@ get user input to paddles, update paddles
push r0
push r1
push r3
brl paddlereact
pop r3
pop r1
pop r0

@ get next ball position
@brl ballupdate

@ check win condition, go back top start if a win
@ push r0
@ brl wincheck
@ pop r0

@ draw the display

push r0
push r1
push r2
push r3
brl draw
pop r3
pop r2
pop r1
pop r0

b mainloop
@ functions (move to another file later)

@ Includes
.include ponglogic.s
.include pong_common.s
.include graphics.s