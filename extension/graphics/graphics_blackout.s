@ This file defines a blackout subroutine used in the main loop
.text
	blackout:
		@ Saving onto the stack
		push r14
		push r4

		@ Blacking out the text
		mov r4 :first8:push_button_erased
		orr r4, r4 :second8:push_button_erased
		orr r4, r4 :third8:push_button_erased
		orr r4, r4 :fourth8:push_button_erased
		
		ldr r0 [r4]
		cmp r0, #0
		beq continue_blackout
		sub r0, r0, #1
		str r0 [r4]

		mov r0, #0
		mov r1, #0
		mov r2, width
		mov r3, height
		brl reset
		b end_blackout

		continue_blackout:
		@ Blacking out the ball
		mov r4, :first8:bprev
		orr r4, r4, :second8:bprev
		orr r4, r4, :third8:bprev
		orr r4, r4, :fourth8:bprev
		ldr r0, [r4]
		ldr r1, [r4, #0x4]
		lsr r0, #8
		lsr r1, #8
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
		lsr r1, #8
		add r1, r1, mt
		mov r2, paddlewidth
		mov r3, paddleheight
		brl reset

		mov r0, width
		sub r0, r0, ml
		sub r0, r0, paddlewidth
		ldr r1, [r4, #0x4]
		lsr r1, #8
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
		end_blackout:
		pop r4
		pop r14
		ret