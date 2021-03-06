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

    @ push onto stack
    push r0         @ r0 to store any temporary variable
    push r9         @ r9 to store ball's x position
    push r11        @ r11 to store ball's y position
    push r12
    push r14

    checkleftpaddle:
    
    @ if ((ballY + ballHeight) >= paddleTop + paddleMargin && ballY <= (paddltTop + paddleHeight - paddleMargin) && ballX <= paddleWidth) {
    @     return 2
    @ }
    
    @ left paddleTop y position
    ldr r10, [r4]

    mov r12, paddlemargin
    add r10, r10, r12, lsl #8
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

    @ if ((ballY + ballHeight) >= paddleTop + paddleMargin && ballY <= (paddltTop + paddleHeight - paddleMargin) 
    @ && (ballX + ballWidth) >= (maxXcoor - paddleWidth)) {
    @     return 4
    @ }

    ldr r10, [r4, #4]           @ right paddleTop y position
    mov r12, paddlemargin
    ldr r11, [r2, #4]           @ ball y pos
    add r11, r11, #0xC00        @ bottom of the ball
    sub r11, r11, r12, lsl #8
    cmp r11, r10
    blt checkleft

    ldr r11, [r2, #4]           @ y of ball
    mov r0, paddleheight        @ move paddle height into r0 to be shifted during addition
    add r10, r10, r0, lsl #8    @ calculates the bottom of the left paddle.
    sub r10, r10, r12, lsl #8
    cmp r11, r10
    bgt checkleft

    ldr r9, [r2]                @ x of ball
    add r9, r9, #0xC00          @ far right of ball

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

    ldr r9, [r2, #4]     @ y coor of ball
    add r9, r9, #0xC00   @ bottom of the ball
    cmp r9, maxYcoor
    blt checktop
    mov r10, #6
    b endcheckcollision

    checktop:

    @ if (ballY <= 0) {
    @     return 3
    @ }

    ldr r9, [r2, #4]     @ y coor of ball
    cmp r9, #0
    bge endbottomcheck
    mov r10, #3
    b endcheckcollision

    endbottomcheck:
    mov r10, #0

    endcheckcollision:
    @ clean up stack
    pop r14
    pop r12
    pop r11
    pop r9
    pop r0
    ret

@===============================================================================
@ BALLUPDATE:
@
@ Determine if ball has hit a bat, alter velocity accordingly.
@ Change current ball position based off of the new velocity.
@ Add current ball positions with the velocity vectors.
@ Check that ball has hit the margins.
@
@ arguments:    None
@ returns:      None
@ side-effects: ball position, points, velocity
ballupdate:
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

    @ check for collisions
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
        @ erase paddles
        brl blackoutleftpaddle
        brl blackoutrightpaddle

        @ Player 2 score +1
        ldr r0, [r6, #4]
        add r0, r0, #1
        str r0, [r6, #4] 

        @ reset and redraw paddles
        brl resetballpaddles
        brl drawleftpaddle
        brl drawrightpaddle

        @ update scorechanged variable
        mov r0 :first8:scorechanged
        orr r0, r0, :second8:scorechanged
        orr r0, r0, :third8:scorechanged
        orr r0, r0, :fourth8:scorechanged
        mov r1, #1
        str r1, [r0]

        b end_ballupdate

    rightwall:
        @ erase paddles
        brl blackoutleftpaddle
        brl blackoutrightpaddle

        @ Player 1 score +1
        ldr r0, [r6]
        add r0, r0, #1
        str r0, [r6] 
        
        @ reset and redraw paddles
        brl resetballpaddles
        brl drawleftpaddle
        brl drawrightpaddle

        @ update scorechanged variable
        mov r0 :first8:scorechanged
        orr r0, r0, :second8:scorechanged
        orr r0, r0, :third8:scorechanged
        orr r0, r0, :fourth8:scorechanged
        mov r1, #1
        str r1, [r0]

        b end_ballupdate

    leftpaddle:
        mov r0, paddlewidth
        lsl r0, #8
        str r0, [r2]

        @ calculating the factor for the speed
        ldr r0, [r2, #4] @ ball y coord
        ldr r1, [r4]     @ left paddle position
        sub r0, r0, r1
        add r0, r0, #0x600 
        mov r1, paddleheight
        lsr r1, #1
        sub r0, r0, r1, lsl #8
        add r1, r1, #0x6
        brl div

        mov r1, #0
        cmp r0, #0
        rsblt r0, r0, #0
        movlt r1, #1

        lsl r0, #8
        brl sqrt

        cmp r1, #0
        rsbgt r0, r0, #0

        @ calculating the speeds
        mov r8, :first8:maxYspeed
        orr r8, r8 :second8:maxYspeed

        mul r8, r0, r8
        asr r8, #8
        
        mul r0, r8, r8

        mov r3, maxspeed
        mul r1, r3, r3
        sub r0, r1, r0
        brl sqrt

        mov r7, r0

        b end_ballupdate

    rightpaddle:
        mov r0, maxXcoor
        mov r1, paddlewidth
        add r1, r1, #0xC
        sub r0, r0, r1, lsl #8
        str r0, [r2]

        @ calculating the factor for the speed
        ldr r0, [r2, #4] @ ball y coord
        ldr r1, [r4, #4] @ right paddle position
        sub r0, r0, r1
        add r0, r0, #0x600 
        mov r1, paddleheight
        lsr r1, #1
        sub r0, r0, r1, lsl #8
        add r1, r1, #0x6
        brl div

        mov r1, #0
        cmp r0, #0
        rsblt r0, r0, #0
        movlt r1, #1

        lsl r0, #8
        brl sqrt

        cmp r1, #0
        rsbgt r0, r0, #0
        
        
        @ calculating the speeds
        mov r8, :first8:maxYspeed
        orr r8, r8 :second8:maxYspeed

        mul r8, r0, r8
        asr r8, #8
        
        mul r0, r8, r8

        mov r3, maxspeed
        mul r1, r3, r3
        sub r0, r1, r0
        brl sqrt

        rsb r0, r0, #0
        mov r7, r0

        b end_ballupdate
    
    topwall:
        @ reflect Y velocity
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
        @ reflect Y velocity
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
@ checks if any of the players has won
@ arguments:    None
@ returns:      None
@ side-effects: ball position, points, paddlepositions
@ alters regs:  r0
wincheck:
    @ push onto stack
    push r14

    @ load left score
    ldr r0, [r6]

    @ check for win
    cmp r0, #10
    blt checkrightscore
    brl newgame
    b wincheckend

    checkrightscore:
    @ load right score
    ldr r0, [r6, #4]

    @ check for win
    cmp r0, #10
    blt wincheckend
    brl newgame

    wincheckend:
    @ clean up stack
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
@ alters regs:  r0, r1 r12
@ const-used:   r2 (bcurr address)
resetballpaddles:
    push r14
    
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
 
    @ randomize starting velocity

    mov r8, :first8:maxrandomYspeed
    mov r8, :second8:maxrandomYspeed
    mov r0, minrandomYspeed
    sub r8, r8, r0
    mov r1, r12, lsr #2
    and r1, r1 #0xFF
    mul r8, r1, r8
    add r8, r0, r8, lsr #8

    mov r0, maxspeed
    mul r1, r0, r0
    mul r0, r8, r8
    sub r0, r1, r0
    brl sqrt
    mov r7, r0

    tst r12, #1
    rsbeq r7, r7, #0

    tst r12, #2
    rsbeq r8, r8, #0

    mul r0, r12, r12
    mov r12 r0, lsr #8
    mov r0, #0x10000
    sub r0, r0, #1
    and r12, r12, r0


    @ reset paddles to middle
    @ get the middle coor
    mov r0, maxYcoor - 0x1E00
    lsr r0, #1
    
    @ store to paddle pos
    str r0, [r4]
    str r0, [r4, #4]

    @ stack clean up
    pop r14
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
    mov r12, #420
    orr r12, r12 #0x6900

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

    @ stack clean up
    pop r2
    pop r1
    pop r0
    ret

@===============================================================================
@ WAITFORKEYDOWN:
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

    @ stack clean up
    pop r1
    pop r0
    ret

@===============================================================================
@ DIV:
@
@ divides two integers (r0/r1)
@ arguments:    r0 <- dividend, r1 <- divisor
@ returns       r0 <- quotient, r1 <- remainder
@ side-effects: r0, r1
div:
    push r4
    push r3
    push r2

    mov r2, #31
    mov r3, #0 @ Quotient
    mov r4, #0
    cmp r0, #0
    eorlt r4, r4, #1
    rsblt r0, r0, #0
    cmp r1, #0
    eorlt r4, r4, #1
    rsblt r1, r1, #0


    divloop:
        cmp r1, r0, lsr r2
        suble r0, r0, r1, lsl r2
        lsl r3, #1
        orrle r3, r3, #1

        cmp r2, #0
        sub r2, r2, #1
        bgt divloop

    mov r1, r0
    mov r0, r3
    cmp r4, #0
    rsbne r0, r0, #0

    pop r2
    pop r3
    pop r4
    ret

@===============================================================================
@ SQRT:
@
@ finds the square root of r0
@ arguments:    r0
@ returns       r0 <- square root
@ side-effects: r0
sqrt:
    push r14
    push r4
    push r3
    push r2
    push r1

    mov r2, #31
    mov r3, #1
    mov r4, r0

    sqrtloop:
        mov r0, r4
        mov r1, r3
        brl div
        add r3, r3, r0
        lsr r3, #1
        
        cmp r2, #0
        sub r2, r2, #1
        bgt sqrtloop

    pop r1
    pop r2
    pop r3
    pop r4
    pop r14
    ret