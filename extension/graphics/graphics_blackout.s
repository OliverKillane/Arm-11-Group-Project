@ This file defines a blackout subroutine used in the main loop
.text
	blackouttext:
		@ Setup
		push r14
		push r3
		push r2
		push r1
		push r0

		@ Logic
		mov r0, #0
		mov r1, #1
		mov r2, width
		mov r3, height
		brl reset

		@ Finish
		pop r0
		pop r1
		pop r2
		pop r3
		pop r14
		ret

	blackoutball:
		@ Setup
		push r14
		push r3
		push r2
		push r1
		push r0

		@ Logic
		ldr r0, [r2]
		ldr r1, [r2, #0x4]
		lsr r0, #8
		lsr r1, #8
		add r0, r0, ml
		add r1, r1, mt

		mov r2, ball_width
		mov r3, ball_height
		
		brl reset

		@ Finish
		pop r0
		pop r1
		pop r2
		pop r3
		pop r14
		ret

	blackoutleftpaddle:
		@ Setup
		push r14
		push r3
		push r2
		push r1
		push r0

		@ Logic
		mov r0, ml
		ldr r1, [r4]
		lsr r1, #8
		add r1, r1, mt

		mov r2, paddlewidth
		mov r3, paddleheight

		brl reset
		

		@ Finish
		pop r0
		pop r1
		pop r2
		pop r3
		pop r14
		ret

	blackoutrightpaddle:
		@ Setup
		push r14
		push r3
		push r2
		push r1
		push r0

		@ Logic
		mov r0, width
		sub r0, r0, ml
		sub r0, r0, paddlewidth
		ldr r1, [r4, #0x4]
		lsr r1, #8
		add r1, r1, mt

		mov r2, paddlewidth
		mov r3, paddleheight

		brl reset
		

		@ Finish
		pop r0
		pop r1
		pop r2
		pop r3
		pop r14
		ret

	blackoutleftscore:
		@ Setup
		push r14
		push r3
		push r2
		push r1
		push r0

		@ Logic
		mov r0, score_left_x
		mov r1, score_left_y
		mov r2, digits_width
		mov r3, digits_height
		brl reset

		@ Finish
		pop r0
		pop r1
		pop r2
		pop r3
		pop r14
		ret

	blackoutrightscore:
		@ Setup
		push r14
		push r3
		push r2
		push r1
		push r0

		@ Logic
		mov r0, score_right_x
		mov r1, score_right_y
		mov r2, digits_width
		mov r3, digits_height
		brl reset

		@ Finish
		pop r0
		pop r1
		pop r2
		pop r3
		pop r14
		ret