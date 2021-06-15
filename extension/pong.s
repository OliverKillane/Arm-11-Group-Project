@ Includes
.include pong_common.s

@ Main program
.text

@ global reg values:
@ r13 <- stack pointer (stack_start)
@ r0 <- current buffer index
@ r1 <- input buffer pointer
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
brl initdraw

@ set initial positions
brl newgame

@ the mainloop of the program (get user input, draw next frame)
mainloop:

@blackout the screen to remove the old frame
@ brl blackout

@ swap coordinates
brl swapcoors

@ get user input to paddles, update paddles
@ brl paddlereact

@ get next ball position
brl ballupdate

@ check win condition, go back top start if a win
brl wincheck

@ draw the display
brl draw

b mainloop
@ functions (move to another file later)

@ Includes
.include ponglogic.s
.include pong_common.s
.include graphics.s
