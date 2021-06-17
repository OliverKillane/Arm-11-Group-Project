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

@ the main program loop
mainloop:
@ load scorechanged variable
mov r0 :first8:scorechanged
orr r0, r0, :second8:scorechanged
orr r0, r0, :third8:scorechanged
orr r0, r0, :fourth8:scorechanged
ldr r1, [r0]

@ if score hasn't changed don't wait for key press 
cmp r1, #0
beq notwaitforkeydown

@ display score and stop ball until a key is pressed
push r1
push r0
brl blackoutleftscore
brl blackoutrightscore
brl drawleftscore
brl drawrightscore
brl update
brl waitforkeydown
pop r0
pop r1

mov r1, #0
str r1, [r0]

notwaitforkeydown:

@ clear and redraw ball, score, paddles dependinbg on ball physics adn user input
brl blackoutball
brl ballupdate
brl drawball

@ move the paddles and redraw
brl userinput

brl movepaddles

@ check the win condition
brl wincheck

@ update the display
brl update

@ add r12, r12, #1
@ cmp r12, #8
@ movge r12, #0
b mainloop

@ Includes
.include ponglogic.s
.include pong_common.s
.include graphics.s
