@TODO:
@ need to set !!Placeholder!! vars
@ need to store ball x, y velocity


@ Main program
.text

@ global reg values:
@ r13 <- stack pointer (stack_start)
@ r0 <- the input buffer pointer
@ r1 <- EMPTY
@ r2 <- bcurr address
@ r3 <- EMPTY
@ r4 <- pcurr address
@ r5 <- EMPTY
@ r6 <- score address
@ r7 <- ball x velocity
@ r8 <- ball y velocity

@ loading globals:

brl setvars

@ error: text not being drawn

brl initdraw

brl waitforkeypress

brl blackouttext

@ draw the start
brl drawball
brl drawleftpaddle
brl drawrightpaddle
brl drawleftscore
brl drawrightscore


brl update


@ start the new game
brl newgame

mainloop:

@blackout, recalculate and redraw the ball
brl blackoutball

@ note: ballupdate calls for the score to be redrawn if updated
@brl ballupdate

brl ballscorecollision

brl drawball

@ get user input and move the paddles
brl paddlereact

@check win condition
brl wincheck

@ update scores
@ todo

brl update

b mainloop

@ Includes
.include ponglogic.s
.include pong_common.s
.include graphics.s