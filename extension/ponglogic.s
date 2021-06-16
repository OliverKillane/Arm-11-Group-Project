
@===============================================================================
@ PADDLEREACT:
@
@ go through input buffer determine each character, change appropriate paddle
@ arguments:    None
@ returns:      None
@ side effects: alters current positions of paddles
paddlereact:
    push r14

    @ save registers, convention

    @ following is basically:
    @ while (not 0) {
    @   keyinput = getnextinput
    @   switch(keyinput) {
    @       case THISKEY:
    @           paddlepos = paddlebounds?newpos:samepos
    @           break
    @    }
    @ }

    @ get input buffer location and 0 (for nullifying) in a register
    mov r0, input_buffer
    mov r1, #0

    paddlereactloop:

    @ get the next input (r3) next pointer (r2)
    ldr r3, [r0]

    @ if null, at end of written buffer, return
    cmp r3, #0
    beq paddlereactend

    @ nullify the character
    str r1, [r0]

    @ get lower 7 bits
    and r3, r3, #0x7F

    @ if an up arrow (code = 5)
    cmp r3, #5
    bne notuparrow

    brl blackoutrightpaddle

    ldr r3, [r4, #4]
    cmp r3, #0
    subgt r3, r3, paddlespeed
    str r3, [r4, #4]

    brl drawrightpaddle

    b paddlereactloop

    notuparrow:
    @ if a down arrow (code = 4)
    cmp r3, #4
    bne notdownarrow

    brl blackoutrightpaddle

    ldr r3, [r4, #4]
    cmp r3, paddlemaxY
    addlt r3, r3, paddlespeed
    str r3, [r4, #4]

    brl drawrightpaddle

    b paddlereactloop

    notdownarrow:
    @ if a w (code = 119)
    cmp r3, #119
    bne notwkey

    brl blackoutleftpaddle

    ldr r3, [r4]
    cmp r3, #0
    subgt r3, r3, paddlespeed
    str r3, [r4]

    brl drawleftpaddle

    b paddlereactloop

    notwkey:
    @ if an s (code = 115)
    cmp r3, #115
    bne notskey

    brl blackoutleftpaddle

    ldr r3, [r4]
    cmp r3, paddlemaxY
    addlt r3, r3, paddlespeed
    str r3, [r4]

    brl drawleftpaddle

    b paddlereactloop

    notskey:
    @ if an ESC (code = 27)
    cmp r3, #27
    bne paddlereactloop

    b paddlereactloop

    paddlereactend:
    pop r14
    ret

@===============================================================================
@ CHECKCOLLISION:
@
@ COLLIDE_ENUM:
@   0 - NO_COLLISION
@   1 - LEFT_WALL
@   2 - LEFT_PADDLE
@   3 - TOP_WALL
@   4 - RIGHT_PADDLE
@   5 - RIGHT WALL
@   6 - BOTTOM_WALL
@ arguments:    None
@ returns:      r12 <- COLLIDE_ENUM
@ side-effects: None
checkcollision:
    push r9         @ r9 to store ball's x position
    push r10        @ r10 to paddle top y position
    push r11        @ r11 to store ball's y position
    push r0         @ r0 to store any temporary variable
    @ check if ball has collided with left wall
    ldr r9, [r2]    @ move ball x position into r9
    cmp r9, #0
    bgt checkright
    mov r12, #1
    b endcheckcollision

    checkright: 
    add r9, r9, #0xC00
    cmp r9, maxXcoor
    blt checkleftpaddle
    mov r12, #5
    b endcheckcollision

    checkleftpaddle:
    
    @ if ((ballY + ballHeight) >= paddleTop && ballY <= (paddltTop + paddleHeight) && ballX <= paddleWidth) {
    @     return 2
    @ }
          
    ldr r10, [r4]               @ left paddleTop y position
    ldr r11, [r2, #4]           @ ball y pos
    add r11, r11, #0xC00        @ bottom of the ball
    cmp r11, r10
    blt endleftpaddlecheck

    ldr r9, [r2]                @ top of ball
    mov r0, paddleheight        @ move paddle height into r0 to be shifted during addition
    add r10, r10, r0, lsl #8    @ calculates the bottom of the left paddle.
    cmp r9, r10
    bgt endleftpaddlecheck

    ldr r9, [r2]
    mov r0, paddlewidth
    lsl r0, #8
    cmp r9, r0
    bgt endleftpaddlecheck

    mov r12, #2
    b endcheckcollision

    endleftpaddlecheck:

    @ if ((ballY + ballHeight) >= paddleTop && ballY <= (paddltTop + paddleHeight) && (ballX + ballWidth) >= (maxXcoor - paddleWidth)) {
    @     return 4
    @ }

    ldr r10, [r4, #4]           @ right paddleTop y position
    ldr r11, [r2, #4]           @ ball y pos
    add r11, r11, #0xC00        @ bottom of the ball
    cmp r11, r10
    blt endrightpaddlecheck

    ldr r9, [r2, #4]            @ y of ball
    mov r0, paddleheight        @ move paddle height into r0 to be shifted during addition
    add r10, r10, r0, lsl #8    @ calculates the bottom of the left paddle.
    cmp r9, r10
    bgt endrightpaddlecheck

    ldr r9, [r2]                @ x of ball
    add r9, r9, #0xC00              @ far right of ball
    @ calculate maxXcoor - paddlewidth
    mov r10, paddlewidth            
    lsl r10, #8
    mov r0, maxXcoor
    sub r0, r0, paddlewidth

    cmp r9, r0
    blt endrightpaddlecheck

    mov r12, #4
    b endcheckcollision

    endrightpaddlecheck:

    @ if (ballY + ballwidth >= maxYcoor) {
    @     return 6
    @ }

    ldr r9, [r2, #4]    @ y coor of ball
    add r9, r9, #0xC00   @ bottom of the ball
    cmp r9, maxYcoor
    blt endtopcheck
    mov r12, #6
    b endcheckcollision

    endtopcheck:

    @ if (ballY <= 0) {
    @     return 3
    @ }

    ldr r9, [r2, #4]    @ y coor of ball
    cmp r9, #0
    blt endbottomcheck
    mov r12, #3
    b endcheckcollision

    endbottomcheck:

    mov r12, #0

    endcheckcollision:
    pop r0
    pop r11
    pop r10
    pop r9
    ret

@===============================================================================
@ BALLUPDATE:
@
@ arguments:    None
@ returns:      None
@ side-effects: ball position, points
ballupdate:
    @ determine if ball has hit a bat, alter velocity accordingly

    @ change current ball position based off of the new velocity.

    @ add current ball positions with the velocity vectors

    @ check that ball has hit the margins
    
    @ push registers onto stack
    push r0
    push r1
    push r9 @ aux register
    push r14


    @ load coordinates of the ball
    ldr r0, [r2] 
    ldr r1, [r2, #4]

    @ add velocity to coordinates
    add r0, r0, r7
    add r1, r1, r8

    @ update current coordinates of the ball
    str r0, [r2]
    str r1, [r2, #4]

   
    push r12
    brl checkcollision

    cmp r12, #0
    beq end_ballupdate

    cmp r12, #1
    beq leftwall
    cmp r12, #5
    beq rightwall

    @ reflect velocity by XY axis
    ldr r0, [r7]
    rsb r0, r0, #0
    str r0, [r7] 

    ldr r0, [r8]
    rsb r0, r0, #0
    str r0, [r8]
    
    
    cmp r12, #2
    beq leftpaddle
    cmp r12, #3
    beq topwall
    cmp r12, #4
    beq rightpaddle
    cmp r12, #6
    beq bottomwall

    leftwall:

        brl blackoutleftscore

        @ Player 2 score +1
        ldr r0, [r6, #4]
        add r0, r0, #1
        str r0, [r6, #4] 
        brl resetball

        brl drawleftscore

        b end_ballupdate

    rightwall:
        brl blackoutrightscore

        @ Player 1 score +1
        ldr r0, [r6]
        add r0, r0, #1
        str r0, [r6] 
        brl resetball

        brl drawrightscore

        b end_ballupdate

    leftpaddle:

        @ ball current X coord
        ldr r0, [r2]

        @ updated ball X coord = 
        @ 2 x paddle width - current ball X-coord
        rsb r0, r0, #0
        mov r1, paddlewidth
        add r0, r0, r1, lsl #9

        str r0, [r2]

        b end_ballupdate

    rightpaddle:
       
        @ load ball current X coord
        ldr r0, [r2]

        @ updated ball X coord = 
        @ 2 x (width - paddle width - ball width) - current ball X-coord
        rsb r0, r0, #0
        mov r1, width
        mov r9, paddlewidth
        sub r1, r1, r9
        mov r9, #12 @ ball width
        add r1, r1, r9
        add r0, r0, r1, lsl #9

        str r0, [r2]

        b end_ballupdate
    
    topwall:
            
        @ ball current Y coord
        ldr r0, [r2, #4]

        @ updated ball Y coord = 
        @ - 2 x current ball Y-coord
        rsb r0, r0, #0
        lsl r0, #1
        str r0, [r2, #4]

        b end_ballupdate

    bottomwall:
        @ load ball current Y coord
        ldr r0, [r2, #4]

        @ updated ball Y coord = 
        @ 2 x (height - ball width) - current ball Y-coord
        mov r1, height
        mov r9, #12 @ ball width
        sub r1, r1, r9
        rsb r0, r0, #0
        add r0, r0, r1, lsl #9

        str r0, [r2]

        b end_ballupdate

    end_ballupdate:
        @ stack clean up
        pop r14
        pop r12
        pop r9
        pop r1
        pop r0
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

    @ set ball x to the center
    mov r0, maxXcoor
    lsr r0, #1
    sub r0, r0, #0x600
    str r0, [r2]
    str r0, [r3]

    @ set ball y to the center
    mov r0, maxYcoor
    lsr r0, #1
    sub r0, r0, #0x600
    str r0, [r2, #4]
    str r0, [r3, #4]

ret

@===============================================================================
@ SETVARS:
@
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

setvars:
@ loading globals:

@ stack pointer
mov r13 :first8:stack_start
orr r13, r13 :second8:stack_start
orr r13, r13 :third8:stack_start
orr r13, r13 :fourth8:stack_start

@ place the input buffer
mov r0, input_buffer

@ anything you want in r1

@ bcurr address
mov r2 :first8:bcurr
orr r2, r2 :second8:bcurr
orr r2, r2 :third8:bcurr
orr r2, r2 :fourth8:bcurr

@ anything for r3


@ pcurr address
mov r4 :first8:pcurr
orr r4, r4 :second8:pcurr
orr r4, r4 :third8:pcurr
orr r4, r4 :fourth8:pcurr

@ anything for r6

@ score address
mov r6 :first8:score
orr r6, r6 :second8:score
orr r6, r6 :third8:score
orr r6, r6 :fourth8:score

ret

@===============================================================================
@ WAITKEYPRESS:
@
@ waits for a keypress
@ side-effects: 
 waitforkeypress:
    push r0
    push r1

    mov r1, input_buffer
    
    waitloop:
    ldr r0, [r1]
    cmp r0, #0
    beq waitloop

    mov r0, #0
    str r0, [r1]

    pop r1
    pop r0
    ret


@===============================================================================
@ BALLSCORECOLLISION:
@
@ determines if the ball is intersecting with the scoreboard, if so redraws it
@ side-effects: redraws the scoreboard
@ 

ballscorecollision:
    
    @ calling convention
    push r1
    push r14

    @ check if ball y coor high enough
    ldr r1, [r2, #4]
    cmp r1, digits_height
    bgt ballscoreend

    @ if x is smaller than 100 - 5 + 13 and larger than 100 - 5, right digit
    ldr r1, [r2]
    cmp r1, #0x5F00
    blt notright

    cmp r1, #0x6C00
    bgt ballscoreend

    @ it is blocking the right digit, so draw right over it 
    @ (score has not changed, so no need to blackout)
    brl drawrightscore

    notright:
    @ if x smaller than 79 - 5 + 13 and larger than 79 - 5, left digit

    cmp r1, #0x5C00
    blt ballscoreend

    cmp r1, #0x6900
    bgt ballscoreend

    @ it is blocking the left digit, so redraw it

    brl drawleftscore

    ballscoreend:
    pop r14
    pop r1
    ret
    





    

