@ This file defines a draw subroutine used in the main loop
.text
	draw:
		@ Saving onto the stack
		push r14
		push r4
		push r5
		push r6

		@ Drawing the ball
		mov r5, :first8:bcurr
		orr r5, :second8:bcurr
		orr r5, :third8:bcurr
		orr r5, :fourth8:bcurr
		ldr r0, [r5]
		ldr r1, [r5, #0x4]
		add r0, r0, ml
		add r1, r1, mt
		mov r2, ball_width
		mov r3, ball_height
		mov r4, :first8:ball
		orr r4, :second8:ball
		orr r4, :third8:ball
		orr r4, :fourth8:ball
		push r4
		bln fill

		@ Drawing the paddles
		mov r5, :first8:pcurr
		orr r5, :second8:pcurr
		orr r5, :third8:pcurr
		orr r5, :fourth8:pcurr
		mov r0, ml
		ldr r1, [r5]
		add r1, r1, mt
		mov r2, paddlewidth
		mov r3, paddleheight
		mov r4, :first8:paddle_left
		orr r4, :second8:paddle_left
		orr r4, :third8:paddle_left
		orr r4, :fourth8:paddle_left
		str r4, [r13]
		bln fill

		mov r0, ml
		ldr r1, [r5, #0x4]
		add r1, r1, mt
		mov r2, paddlewidth
		mov r3, paddleheight
		mov r4, :first8:paddle_right
		orr r4, :second8:paddle_right
		orr r4, :third8:paddle_right
		orr r4, :fourth8:paddle_right
		str r4, [r13]
		bln fill
		
		@ Drawing the score
		mov r5, :first8:score
		orr r5, :second8:score
		orr r5, :third8:score
		orr r5, :fourth8:score
		mov r0, score_left_x
		mov r1, score_left_y
		mov r2, digits_width
		mov r3, digits_height
		mov r4, :first8:digits
		orr r4, :second8:digits
		orr r4, :third8:digits
		orr r4, :fourth8:digits
		ldr r6, [r5]
		mul r6, r2, r6
		mla r6, r3, r6, r4
		str r6, [r13]
		bln fill
		
		mov r0, score_right_x
		mov r1, score_right_y
		mov r2, digits_width
		mov r3, digits_height
		ldr r6, [r5, #0x4]
		mul r6, r2, r6
		mla r6, r3, r6, r4
		str r6, [r13]
		bln fill
		
		@ Changing the drawing buffers
		mov r0, :first8:read_image_buffer
		orr r0, :second8:read_image_buffer
		orr r0, :third8:read_image_buffer
		orr r0, :fourth8:read_image_buffer
		mov r1, :first8:write_image_buffer
		orr r1, :second8:write_image_buffer
		orr r1, :third8:write_image_buffer
		orr r1, :fourth8:write_image_buffer
		ldr r2, [r0]
		ldr r3, [r1]
		str r3, [r0]
		str r2, [r1]

		@ Cleaning everything up
		sub r13, r13, #0x4
		pop r6
		pop r5
		pop r4
		pop r14
		ret