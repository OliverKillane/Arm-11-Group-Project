@ Includes
.include pong_common.s

@ Main program
.text

@ set up the stack pointer
mov r13 :first8:stack_start
orr r13, r13 :second8:stack_start
orr r13, r13 :third8:stack_start
orr r13, r13 :fourth8:stack_start

@ startup draw the display
brl initdraw

@ set initial positions
brl newgame

@ the mainloop of the program (get user input, draw next frame)
mainloop:

@blackout the screen to remove the old frame
brl blackout

@ swap coordinates
brl swapcoors

@ get user input to paddles, update paddles
brl paddlereact

@ get next ball position
brl ballupdate

@ check win condition, go back top start if a win
brl wincheck

@ draw the display
brl draw

b mainloop
@ functions (move to another file later)


@===============================================================================
@ SWAPCOORS:
@
@ move current coors to prev positions
@ arguments:    None
@ returns:      None
@ side-effects: current->prev
swapcoors:
push r0 @ Push r0 to stack in case it was used in caller function.

@ Move and store the ball's current x position to the previous x position.
mov r0, [bcurrent]
str r0, [bprev]

@ Move and store the ball's current x position to the previous x position.
mov r0, [bcurrent, #4]
str r0, [bprev, #4]

mov r0, [pcurrent]
str r0, [pprev]

mov r0, [pcurrent, #4]
str r0, [pprev, #4]

pop r0 @ Pop r0 from stack so there are no side effects apart from the specified side effects.
ret

@===============================================================================
@ PADDLEREACT:
@
@ go through input buffer determine each character, run appropriate function
@ arguments:
@ r0 <- current buffer index
@ returns:
@ r0 <- current buffer index
@ side effects: alters current positions of paddles
paddlereact:
mov r2, r0

@ save registers, convention
push r1
push r2
push r3

@ store link register for return
push r14

@ setup arguments for getting input
mov r0, input_buffer_start
mov r1, inputbuffersize

@ following is basically:
@ while (not 0) {
@   keyinput = getnextinput
@   switch(keyinput) {
@       case THISKEY:
@           paddlepos = paddlebounds?newpos:samepos
@           break
@    }
@ }

paddlereactloop:

@ get the next input (r3) next pointer (r2)
brl getnextinput

@ get lower 7 bits
and r3, r3, #0x7F

@ if null, at end of written buffer, return
cmp r3, #0
beq paddlereactend

@ if an up arrow (code = 7)
cmp r3, #7
bne notuparrow

ldr r3, [pprev]
cmp r3, #0
addgt r3, r3, paddlespeed
str r3, [pprev]

b paddlereactloop

notuparrow:
@ if a down arrow (code = 6)
cmp r3, #6
bne notdownarrow

ldr r3, [pprev]
cmp r3, @ max y coordinate - paddleheight !!PLACEHOLDER!!
sublt r3, r3, paddlespeed
str r3, [pprev]

b paddlereactloop

notdownarrow:
@ if a w (code = 119)
cmp r3, #119
bne notwkey

ldr r3, [pprev, #4]
cmp r3, #0
addgt r3, r3, paddlespeed
str r3, [pprev, #4]

b paddlereactloop

notwkey:
@ if an s (code = 115)
cmp r3, #115
bne paddlereactloop

ldr r3, [pprev, #4]
cmp r3, @ max y coordinate - paddleheight !!PLACEHOLDER!!
sublt r3, r3, paddlespeed
str r3, [pprev, #4]

b paddlereactloop


paddlereactend:
@ return the current buffer index
mov r0, r2

@ restore registers
pop r14
pop r3
pop r2
pop r1

ret

@===============================================================================
@ BALLUPDATE:
@
@ arguments:    None
@ returns:      None
@ side-effects: ball position, points
ballupdate:

@ determine if the ball is at side edge
@ if so, then add 1 to score based on pos, and resetball

@ determine if ball on top/bottom edge if so change velocity accordingly

@determine if ball has hit a bat, alter velocity accordingly


ret

@===============================================================================
@ WINCHECK:
@
@ arguments:    None
@ returns:      None
@ side-effects: ball position, points, paddlepositions
wincheck:
push r0
push r14
ldr r0, [score]
cmp r0, #10
brl newgame

ldr r0, [score, #4]
cmp r0, #10
brl newgame

wincheckend:
pop r14
pop r0
ret

@===============================================================================
@ NEWGAME:
@
@ place the paddles, ball in starting position, scores at 0 and the ball velocity random
@ arguments:    None
@ returns:      None
@ side-effects: ball position, points, paddlepositions
newgame:
push r0
push r14

@ reset scores
mov r0, #0
str r0, [score]
str r0, [score, #4]

@ set score to 0
pop r14
pop r0
ret

@===============================================================================
@ RESETBALL:
@
@ place ball in starting position and the ball velocity random
@ arguments:    None
@ returns:      None
@ side-effects: ball position, ball velocity
resetball:
push r0

mov r0, @middle position x !!PLACEHOLDER!!
str r0, [bcurr]

mov r0, @middle position y !!PLACEHOLDER!!
str r0, [bcurr, #4]

pop r0
ret

@===============================================================================
@ GETNEXTINPUT:
@
@ gets the next input as an ascii, assumes little endian storage
@ arguments:
@ r0 <- buffer index to read from
@ r1 <- the buffer size
@ r2 <- buffer index to read from
@ returns:
@ r2 <- next index
@ r3 <- the next character
getnextinput:
push r4

@ load the next word, get most significant byte
ldr r4, [r0, r2]
and r3, r4, #0xFF

@ if still zero, ignore
cmp r3, #0
beq getinputend

@ store the rest back
sub r4, r4, r3
str r4, [r0, r2]

@ move r2 to next index, set to zero if at end
cmp r2, r1
bne getinputnextindex

@ reset to start
mov r2, #0
b getinputend

@ increment the index
getinputnextindex:
add r2, r2, #1

getinputend:
@ restore the local var registers and return
pop r4
ret