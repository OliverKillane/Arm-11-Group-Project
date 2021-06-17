@===============================================================================
@ USERINPUT:
@ 
@ Get the user's key inputs, and either end (ESC) or for w/s and UP/DOWN keys
@ change the paddle veloctiy
@ arguments:    NONE
@ returns:      NONE
@ side effects: paddle velocity
@ alters regs:  r0, r1, r3, r9, r10

userinput:
    
    @ store pointer to input buffer
    mov r0, input_buffer

    @ store 0 for nullifying
    mov r1, #0

    inputloop:
        @ get the user input keycode
        ldr r3, [r0]

        @ if at a null character, return
        cmp r3, #0
        reteq

        @ nullify the character buffer
        str r1, [r0]

        @ test the key UP/DOWN bit
        and r9, r3, #0x80

        @ get lower 7 bits
        and r3, r3, #0x7F

        @ if an up arrow (code = 5)
        cmp r3, #5
        bne testdownarrowDOWN

        cmp r9, #0
        ldr r10, [r5, #4]
        addne r10, r10, paddlespeed
        subeq r10, r10, paddlespeed
        str r10, [r5, #4]

        b inputloop

        @ if a down arrow (code = 4)
        testdownarrowDOWN:
        cmp r3, #4
        bne testWkeyDOWN

        cmp r9, #0
        ldr r10, [r5, #4]
        addeq r10, r10, paddlespeed
        subne r10, r10, paddlespeed
        str r10, [r5, #4]

        b inputloop

        @ if a w (code = 119)
        testWkeyDOWN:
        cmp r3, #119
        bne testSkeyDOWN

        cmp r9, #0
        ldr r10, [r5]
        addne r10, r10, paddlespeed
        subeq r10, r10, paddlespeed
        str r10, [r5]

        b inputloop

        @ if an s (code = 115)
        testSkeyDOWN:
        cmp r3, #115
        bne testESCkey

        cmp r9, #0
        ldr r10, [r5]
        addeq r10, r10, paddlespeed
        subne r10, r10, paddlespeed
        str r10, [r5]

        b inputloop

        @ if an ESC key (code = 27)
        testESCkey:
        cmp r3, #27
        bne inputloop
        hlt

@===============================================================================
@ MOVEPADDLES:
@
@ using velocity, determine if a paddle must be moved, if so clear, calaculate
@ new position and redraw.
@ arguments:    NONE
@ returns:      NONE
@ side effects: Ball position
@ alters regs:  r0, r1
@ const-used:   r5 (pvel address), r4 (pcurr address)

movepaddles:
    push r14

    @get left paddle velocity
    ldr r0, [r5]
    @cmp r0, #0
    @beq rightpaddlecheck

    @ clear the paddle
    brl blackoutleftpaddle

    @calculate the new position
    ldr r1, [r4]


    add r1, r1, r0
    cmp r1, paddlemaxY
    movgt r1, paddlemaxY
    cmp r1, #0
    movlt, r1, #0
    str r1, [r4]

    @ draw paddle at new position
    brl drawleftpaddle

    @rightpaddlecheck:

    ldr r0, [r5, #4]
    @cmp r0, #0
    @beq endpaddlemove

    @ clear the paddle
    brl blackoutrightpaddle

    @calculate the new position

    ldr r1, [r4, #4]
    add r1, r1, r0
    cmp r1, paddlemaxY
    movgt r1, paddlemaxY
    cmp r1, #0
    movlt, r1, #0
    str r1, [r4, #4]

    @ draw paddle at new position
    brl drawrightpaddle

    endpaddlemove:
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
@ returns:      r10 <- COLLIDE_ENUM
@ side-effects: None
checkcollision:
    push r0         @ r0 to store any temporary variable
    push r9         @ r9 to store ball's x position
    push r11        @ r11 to store ball's y position
    push r12
    push r14

    checkleftpaddle:
    
    @ if ((ballY + ballHeight) >= paddleTop + paddleMargin && ballY <= (paddltTop + paddleHeight - paddleMargin) && ballX <= paddleWidth) {
    @     return 2
    @ }
    
    ldr r10, [r4]               @ left paddleTop y position
    mov r12, paddlemargin
    sub r10, r10, r12, lsl #8
    ldr r11, [r2, #4]           @ ball y pos
    add r11, r11, #0xC00        @ bottom of the ball
    cmp r11, r10
    blt checkrightpaddle

    ldr r11, [r2, #4]           @ ball y pos
    mov r0, paddleheight        @ move paddle height into r0 to be shifted during addition
    add r10, r10, r0, lsl #8    @ calculates the bottom of the left paddle.
    sub r10, r10, r12, lsl #9
    cmp r11, r10
    bgt checkrightpaddle

    ldr r9, [r2]                @ top of ball
    mov r0, paddlewidth
    lsl r0, #8
    cmp r9, r0
    bgt checkrightpaddle

    mov r10, #2
    b endcheckcollision

    checkrightpaddle:

    @ if ((ballY + ballHeight) >= paddleTop + paddleMargin && ballY <= (paddltTop + paddleHeight - paddleMargin) && (ballX + ballWidth) >= (maxXcoor - paddleWidth)) {
    @     return 4
    @ }

    ldr r10, [r4, #4]           @ right paddleTop y position
    mov r12, paddlemargin
    ldr r11, [r2, #4]           @ ball y pos
    add r11, r11, #0xC00        @ bottom of the ball
    sub r11, r11, r12, lsl #8
    cmp r11, r10
    blt checkleft

    ldr r11, [r2, #4]            @ y of ball
    mov r0, paddleheight        @ move paddle height into r0 to be shifted during addition
    add r10, r10, r0, lsl #8    @ calculates the bottom of the left paddle.
    sub r10, r10, r12, lsl #8
    cmp r11, r10
    bgt checkleft

    ldr r9, [r2]                @ x of ball
    add r9, r9, #0xC00              @ far right of ball
    @ calculate maxXcoor - paddlewidth
    mov r10, paddlewidth            
    mov r0, maxXcoor
    sub r0, r0, r10, lsl #8

    cmp r9, r0
    blt checkleft

    mov r10, #4
    b endcheckcollision


    checkleft:
    ldr r9, [r2]    @ move ball x position into r9
    cmp r9, #0
    bgt checkright

    mov r10, #1
    b endcheckcollision

    checkright: 
    add r9, r9, #0xC00
    cmp r9, maxXcoor
    blt checkbottom
    mov r10, #5
    b endcheckcollision

    checkbottom:

    @ if (ballY + ballwidth >= maxYcoor) {
    @     return 6
    @ }

    ldr r9, [r2, #4]    @ y coor of ball
    add r9, r9, #0xC00   @ bottom of the ball
    cmp r9, maxYcoor
    blt checktop
    mov r10, #6
    b endcheckcollision

    checktop:

    @ if (ballY <= 0) {
    @     return 3
    @ }

    ldr r9, [r2, #4]    @ y coor of ball
    cmp r9, #0
    bge endbottomcheck
    mov r10, #3
    b endcheckcollision

    endbottomcheck:
    mov r10, #0

    endcheckcollision:
    pop r14
    pop r12
    pop r11
    pop r9
    pop r0
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
    push r10
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

   
    brl checkcollision
    cmp r10, #0
    beq end_ballupdate

    cmp r10, #1
    beq leftwall
    cmp r10, #5
    beq rightwall


    cmp r10, #2
    beq leftpaddle
    cmp r10, #3
    beq topwall
    cmp r10, #4
    beq rightpaddle
    cmp r10, #6
    beq bottomwall

    leftwall:
        brl blackoutleftpaddle
        brl blackoutrightpaddle

        @ Player 2 score +1
        ldr r0, [r6, #4]
        add r0, r0, #1
        str r0, [r6, #4] 

        brl resetballpaddles

        brl drawleftpaddle
        brl drawrightpaddle

        mov r0 :first8:scorechanged
        orr r0, r0, :second8:scorechanged
        orr r0, r0, :third8:scorechanged
        orr r0, r0, :fourth8:scorechanged
        mov r1, #1
        str r1, [r0]

        b end_ballupdate

    rightwall:

        brl blackoutleftpaddle
    brl blackoutrightpaddle

        @ Player 1 score +1
        ldr r0, [r6]
        add r0, r0, #1
        str r0, [r6] 
        
        
        brl resetballpaddles

        brl drawleftpaddle
        brl drawrightpaddle

        mov r0 :first8:scorechanged
        orr r0, r0, :second8:scorechanged
        orr r0, r0, :third8:scorechanged
        orr r0, r0, :fourth8:scorechanged
        mov r1, #1
        str r1, [r0]

        b end_ballupdate

    leftpaddle:

        rsb r7, r7, #0

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

        rsb r7, r7, #0
     
        @ load ball current X coord
        ldr r0, [r2]

        @ updated ball X coord = 
        @ 2 x (width - paddle width - ball width) - current ball X-coord
        mov r1, maxXcoor - 0xC00
        rsb r0, r0, r1, lsl #1
        mov r1, paddlewidth
        sub r0, r0, r1, lsl #9

        str r0, [r2]

        b end_ballupdate
    
    topwall:

        rsb r8, r8, #0
             
        @ ball current Y coord
        ldr r0, [r2, #4]

        @ updated ball Y coord = 
        @ - 2 x current ball Y-coord
        rsb r0, r0, #0
        lsl r0, #1
        str r0, [r2, #4]

        b end_ballupdate

    bottomwall:

        rsb r8, r8, #0
    
        @ load ball current Y coord
        ldr r0, [r2, #4]

        @ updated ball Y coord = 
        @ 2 x (height - ball width) - current ball Y-coord
        mov r1, maxYcoor - 0xC00
        lsl r1, #1
        sub r0, r1, r0

        str r0, [r2, #4]

        b end_ballupdate

    end_ballupdate:
        @ stack clean up
        pop r14
        pop r10
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
@ alters regs:  r0
wincheck:
    push r14
    ldr r0, [r6]
    cmp r0, #10
    blt checkrightscore
    brl newgame
    b wincheckend

    checkrightscore:
    ldr r0, [r6, #4]
    cmp r0, #10
    blt wincheckend
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
@ alters regs:  r0, r1
@ const-used:   r6 (score address), r2 (bcurr address), r4 (pcurr address)
newgame:
    push r14

    brl blackoutleftpaddle
    brl blackoutrightpaddle
    brl blackoutball

    @ reset scores to 0
    mov r0, #0
    str r0, [r6]
    str r0, [r6, #4]

    @ move ball to the center
    brl resetballpaddles

    brl drawleftpaddle
    brl drawrightpaddle
    brl drawball

    pop r14
    ret

@===============================================================================
@ RESETBALLPADDLES:
@
@ place ball in starting position and the ball velocity random
@ arguments:    None
@ returns:      None
@ side-effects: ball position, ball velocity
@ alters regs:  r0
@ const-used:   r2 (bcurr address)
resetballpaddles:
    push r9
    push r14
    ldr r9, [r12]
    
    @ set ball x to the center
    mov r0, maxXcoor
    lsr r0, #1
    sub r0, r0, #0x600
    str r0, [r2]

    @ set ball y to the center
    mov r0, maxYcoor
    lsr r0, #1
    sub r0, r0, #0x600
    str r0, [r2, #4]
 
    tst r9, #4
    movne r7, #0xA7
    orrne r7, r7, #0x200
    movne r8, r7

    moveq r8, #0x3F
    orreq r8, r8 #0x300
    moveq r7 #0x1E0

    tst r9, #1
    rsbeq r7, r7, #0

    tst r9, #2
    rsbeq r8, r8, #0

    add r9, r9, #5
    str r9, [r12] 

    @ reset paddles to middle
    @ get the middle coor
    mov r9, maxYcoor - 0x1E00
    lsr r9, #1
    
    @ store to paddle pos
    str r9, [r4]
    str r9, [r4, #4]

    pop r14
    pop r9
    ret

@===============================================================================
@ SETVARS:
@
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
@ r12 <- EMPTY
@ r13 <- stack pointer (stack_start)
@
@ arguments:    NONE
@ returns:      NONE
@ alters regs:  r3,r4,r5,r6,r13

setvars:
    @ loading globals:

    @ r0:  NOTHING
    @ r1:  NOTHING

    @ r3: bcurr address
    mov r2 :first8:bcurr
    orr r2, r2 :second8:bcurr
    orr r2, r2 :third8:bcurr
    orr r2, r2 :fourth8:bcurr

    @ r3:  NOTHING

    @ r4:  pcurr address
    mov r4 :first8:pcurr
    orr r4, r4 :second8:pcurr
    orr r4, r4 :third8:pcurr
    orr r4, r4 :fourth8:pcurr

    @ r5:  pvel address
    mov r5 :first8:pvel
    orr r5, r5 :second8:pvel
    orr r5, r5 :third8:pvel
    orr r5, r5 :fourth8:pvel

    @ r6:  score address
    mov r6 :first8:score
    orr r6, r6 :second8:score
    orr r6, r6 :third8:score
    orr r6, r6 :fourth8:score

    @ r7:  BALL X VELOCITY
    @ r8:  BALL Y VELOCITY

    @ r9:  NOTHING
    @ r10: NOTHING
    @ r11: NOTHING

    @ r12: global loop counter
    mov r12 :first8:loopiterator
    orr r12, r12, :second8:loopiterator
    orr r12, r12, :third8:loopiterator
    orr r12, r12, :fourth8:loopiterator

    @ r13: stack_pointer
    mov r13 :first8:stack_start
    orr r13, r13 :second8:stack_start
    orr r13, r13 :third8:stack_start
    orr r13, r13 :fourth8:stack_start

    ret

@===============================================================================
@ WAITKEYPRESS:
@
@ waits for a keypress
@ arguments:    NONE
@ returns       NONE
@ side-effects: r0, r1, r2
waitforkeypress:
    push r0
    push r1
    push r2

    mov r1, input_buffer
    
    waitpressedloop:
    ldr r0, [r1]
    cmp r0, #0
    beq waitpressedloop
    tst r0, #0x80
    mov r2, #0
    str r2, [r1]
    bne waitpressedloop


    waitreleasedloop:
    ldr r2, [r1]
    cmp r2, #0
    beq waitreleasedloop
    tst r2, #0x80
    moveq r0, #0
    streq r0, [r1]
    beq waitreleasedloop
    and r2, r2, #0x7F
    cmp r2, r0
    mov r2, #0
    str r2, [r1]
    bne waitreleasedloop

    pop r2
    pop r1
    pop r0
    ret

@===============================================================================
@ WAITKEYPRESS:
@
@ waits for a keypress
@ arguments:    NONE
@ returns       NONE
@ side-effects: r0, r1
waitforkeydown:
    push r0
    push r1

    mov r1, input_buffer
    
    waitdownloop:
    ldr r0, [r1]
    cmp r0, #0
    beq waitdownloop

    pop r1
    pop r0
    ret