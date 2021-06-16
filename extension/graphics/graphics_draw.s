@ This file defines a draw subroutine used in the main loop
.text
	drawball:
		@ Setup
		push r14
		push r3
		push r2
		push r1
		push r0

		@ Logic
		mov r0, :first8:ball
		orr r0, r0, :second8:ball
		orr r0, r0, :third8:ball
		orr r0, r0, :fourth8:ball
		push r0

		ldr r0, [r2]
		ldr r1, [r2, #0x4]
		lsr r0, #8
		lsr r1, #8
		add r0, r0, ml
		add r1, r1, mt
		
		mov r2, ball_width
		mov r3, ball_height

		brl fill

		add r13, r13, #0x4

		@ Finish
		pop r0
		pop r1
		pop r2
		pop r3
		pop r14
		ret

	
	drawleftpaddle:
		@ Setup
		push r14
		push r3
		push r2
		push r1
		push r0

		@ Logic
		mov r0, :first8:paddle_left
		orr r0, r0, :second8:paddle_left
		orr r0, r0, :third8:paddle_left
		orr r0, r0, :fourth8:paddle_left
		push r0

		mov r0, ml
		ldr r1, [r4]
		lsr r1, #8
		add r1, r1, mt
		mov r2, paddlewidth
		mov r3, paddleheight
		brl fill

		add r13, r13, #0x4

		@ Finish
		pop r0
		pop r1
		pop r2
		pop r3
		pop r14
		ret

	drawrightpaddle:
		@ Setup
		push r14
		push r3
		push r2
		push r1
		push r0

		@ Logic
		mov r0, :first8:paddle_right
		orr r0, r0, :second8:paddle_right
		orr r0, r0, :third8:paddle_right
		orr r0, r0, :fourth8:paddle_right
		push r0

		mov r0, width
		sub r0, r0, mr
		sub r0, r0, paddlewidth
		ldr r1, [r4, #0x4]
		lsr r1, #8
		add r1, r1, mt
		mov r2, paddlewidth
		mov r3, paddleheight
		brl fill

		add r13, r13, #0x4

		@ Finish
		pop r0
		pop r1
		pop r2
		pop r3
		pop r14
		ret

	drawleftscore:
		@ Setup
		push r14
		push r3
		push r2
		push r1
		push r0

		@ Logic
		mov r0, :first8:digits
		orr r0, r0, :second8:digits
		orr r0, r0, :third8:digits
		orr r0, r0, :fourth8:digits
		
		mov r2, digits_width
		mov r3, digits_height

		ldr r1, [r6]
		lsl r1, #2
		mul r1, r2, r1
		mla r1, r3, r1, r0
		push r1

		mov r0, score_left_x
		mov r1, score_left_y
		brl fill

		add r13, r13, #0x4

		@ Finish
		pop r0
		pop r1
		pop r2
		pop r3
		pop r14
		ret

	drawrightscore:
		@ Setup
		push r14
		push r3
		push r2
		push r1
		push r0

		@ Logic
		mov r0, :first8:digits
		orr r0, r0, :second8:digits
		orr r0, r0, :third8:digits
		orr r0, r0, :fourth8:digits
		
		mov r2, digits_width
		mov r3, digits_height

		ldr r1, [r6, #4]
		lsl r1, #2
		mul r1, r2, r1
		mla r1, r3, r1, r0
		push r1

		mov r0, score_right_x
		mov r1, score_right_y
		brl fill

		add r13, r13, #0x4

		@ Finish
		pop r0
		pop r1
		pop r2
		pop r3
		pop r14
		ret

	update:
		push r0
		push r1

		mov r0, :first8:image_buffer_ptr
		orr r0, r0, :second8:image_buffer_ptr
		orr r0, r0, :third8:image_buffer_ptr
		orr r0, r0, :fourth8:image_buffer_ptr
		ldr r1 [r0]
		str r1 [r0]

		pop r1
		pop r0
		ret