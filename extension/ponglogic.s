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
ldr r0, [r2]
str r0, [r3]

@ Move and store the ball's current x position to the previous x position.
ldr r0, [r2, #4]
str r0, [r3, #4]

ldr r0, [r4]
str r0, [r5]

ldr r0, [r4, #4]
str r0, [r5, #4]

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

@ save registers, convention
push r14

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

@ if null, at end of written buffer, return
cmp r3, #0
beq paddlereactend

@ get lower 7 bits
and r3, r3, #0x7F

@ if an up arrow (code = 7)
cmp r3, #7
bne notuparrow

ldr r3, [r5]
cmp r3, #0
addgt r3, r3, paddlespeed
str r3, [r4]

b paddlereactloop

notuparrow:
@ if a down arrow (code = 6)
cmp r3, #6
bne notdownarrow

ldr r3, [r5]
cmp r3, paddlemaxY
sublt r3, r3, paddlespeed
str r3, [r4]

b paddlereactloop

notdownarrow:
@ if a w (code = 119)
cmp r3, #119
bne notwkey

ldr r3, [r5, #4]
cmp r3, #0
addgt r3, r3, paddlespeed
str r3, [r4, #4]

b paddlereactloop

notwkey:
@ if an s (code = 115)
cmp r3, #115
bne paddlereactloop

ldr r3, [r5, #4]
cmp r3, paddlemaxY
sublt r3, r3, paddlespeed
str r3, [r4, #4]

b paddlereactloop


paddlereactend:
@ restore registers
pop r14
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
push r14
ldr r0, [r6]
cmp r0, #10
brl newgame

ldr r0, [r6, #4]
cmp r0, #10
brl newgame

wincheckend:
pop r14
ret

@===============================================================================
@ NEWGAME:
@
@ place the paddles, ball in starting position, scores at 0 and the ball velocity random
@ arguments:    None
@ returns:      None
@ side-effects: ball position, points, paddlepositions
@ uses constants: r6 (score address), r2 (bcurr address)
newgame:
push r14

@ reset scores to 0
mov r0, #0
str r0, [r6]
str r0, [r6, #4]

@ move ball to the center
brl resetball

pop r14
ret

@===============================================================================
@ RESETBALL:
@
@ place ball in starting position and the ball velocity random
@ arguments:    None
@ returns:      None
@ side-effects: ball position (), ball velocity
resetball:
@ set ball x and y to the center

mov r0, maxXcoor
lsr r0, #1
sub r0, r0, #0x600
str r0, [r2]

mov r0, maxYcoor
lsr r0, #1
sub r0, r0, #0x600
str r0, [r2, #4]

@set ball velocity
ret

@===============================================================================
@ GETNEXTINPUT:
@
@ gets the next input as an ascii, assumes little endian storage
@ arguments:
@ r0 <- buffer index to read from
@ r1 <- the buffer start/pointer
@ r2 <- buffer index to read from
@ returns:
@ r0 <- next index
@ r3 <- the next character
getnextinput:
push r4

mov r1, input_buffer_start

@ load the next word, get most significant byte
ldr r4, [r1, r0]
and r3, r4, #0xFF

@ if still zero, ignore
cmp r3, #0
beq getinputend

@ store the rest back
sub r4, r4, r3
str r4, [r1, r0]

@ move r2 to next index, set to zero if at end
cmp r0, inputbuffersize
bne getinputnextindex

@ reset to start
mov r0, #0
b getinputend

@ increment the index
getinputnextindex:
add r0, r0, #1

getinputend:
@ restore the local var registers and return
pop r4
ret

@===============================================================================
@ SETVARS:
@
@ sets up the local variables for the main loop as follows:
@ global reg values:
@ r13 <- stack pointer (stack_start)
@ r0 <- current buffer index
@ r1 <- EMPTY (uSE FOR gui MODE LATER)
@ r2 <- bcurr address
@ r3 <- bprev address
@ r4 <- pcurr address
@ r5 <- pprev address
@ r6 <- score address
@ r7 <- ball x velocity
@ r8 <- ball y velocity

setvars:
@ loading globals:

@ stack pointer
mov r13 :first8:stack_start
orr r13, r13 :second8:stack_start
orr r13, r13 :third8:stack_start
orr r13, r13 :fourth8:stack_start
ldr r13, [r13]

@ current buffer index
mov r0, #0

@ anything you want in r1

@ bcurr address
mov r2 :first8:bcurr
orr r2, r2 :second8:bcurr
orr r2, r2 :third8:bcurr
orr r2, r2 :fourth8:bcurr

@ bprev address
mov r3 :first8:bprev
orr r3, r3 :second8:bprev
orr r3, r3 :third8:bprev
orr r3, r3 :fourth8:bprev

@ pcurr address
mov r4 :first8:pcurr
orr r4, r4 :second8:pcurr
orr r4, r4 :third8:pcurr
orr r4, r4 :fourth8:pcurr

@ pprev address
mov r5 :first8:pprev
orr r5, r5 :second8:pprev
orr r5, r5 :third8:pprev
orr r5, r5 :fourth8:pprev

@ score address
mov r6 :first8:score
orr r6, r6 :second8:score
orr r6, r6 :third8:score
orr r6, r6 :fourth8:score

ret