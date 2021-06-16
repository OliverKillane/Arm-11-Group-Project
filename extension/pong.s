@ Main 
.text

@ loading globals:
brl setvars

@ global reg values:
@ r0  <- EMPTY
@ r1  <- EMPTY
@ r2  <- bcurr address
@ r3  <- EMPTY
@ r4  <- pcurr address
@ r5  <- pvel address
@ r6  <- score address
@ r7  <- ball x velocity
@ r8  <- ball y velocity
@ r9  <- EMPTY
@ r10 <- EMPTY
@ r11 <- EMPTY
@ r12 <- global loop counter
@ r13 <- stack pointer (stack_start)

@ draw 'press any key'
brl initdraw

@ wait for the user to press a key, then transition to next stage
brl waitforkeypress

@ remove the 'press any key' text
brl blackouttext

@ setup ball position, scores
brl newgame

@ draw the game initially
brl drawball
brl drawleftpaddle
brl drawrightpaddle
brl drawleftscore
brl drawrightscore

@ update the display
brl update

@ before starting to move the ball
brl waitforkeydown

@ the main program loop
mainloop:

@ clear and redraw ball, score, paddles dependinbg on ball physics adn user input
brl blackoutball
brl ballupdate
brl ballscorecollision
brl drawball

@ move the paddles and redraw
brl userinput

brl movepaddles

@ check the win condition
brl wincheck

@ update the display
brl update

add r12, r12, #1
cmp r12, #8
movge r12, #0
b mainloop

@ Includes
.include ponglogic.s
.include pong_common.s
.include graphics.s