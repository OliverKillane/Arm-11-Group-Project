@ This file defines a blackout subroutine used in the main loop
.text
	blackout:
		@ Saving onto the stack
		push r14
		push r4

		@ Blacking out the ball
		mov r4, :first8:bprev
		orr r4, r4, :second8:bprev
		orr r4, r4, :third8:bprev
		orr r4, r4, :fourth8:bprev
		ldr r0, [r4]
		ldr r1, [r4, #0x4]
		lsl r0, #8
		lsl r1, #8
		add r0, r0, ml
		add r1, r1, mt
		mov r2, ball_width
		mov r3, ball_height
		brl reset

		@ Blacking out the paddles
		mov r4, :first8:pprev
		orr r4, r4, :second8:pprev
		orr r4, r4, :third8:pprev
		orr r4, r4, :fourth8:pprev
		mov r0, ml
		ldr r1, [r4]
		lsl r1, #8
		add r1, r1, mt
		mov r2, paddlewidth
		mov r3, paddleheight
		brl reset

		mov r0, ml
		ldr r1, [r4, #0x4]
		lsl r1, #8
		add r1, r1, mt
		mov r2, paddlewidth
		mov r3, paddleheight
		brl reset
		
		@ Blacking out the score
		mov r0, score_left_x
		mov r1, score_left_y
		mov r2, digits_width
		mov r3, digits_height
		brl reset
		
		mov r0, score_right_x
		mov r1, score_right_y
		mov r2, digits_width
		mov r3, digits_height
		brl reset

		@ Cleaning everything up
		pop r4
		pop r14
		ret