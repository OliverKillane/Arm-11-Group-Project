.text
@===============================================================================
@ FILL:
	@ Function parameters: 
	@ r0  <- x0 
	@ r1  <- y0 
	@ r2  <- width  (X axis)
	@ r3  <- height (Y axis) 
	@ r13 <- memory pointer register

	@ Internal registers for local variables: 
    @ r4  <- image_buffer_ptr register	
	@ r5  <- X-axis iterator
	@ r6  <- Y-axis iterator
	@ r7  <- background pixel register
	@ r8  <- X-axis target pixel index
	@ r9  <- Y-axis target pixel index
	@ r10 <- array iterator index
    @ r11 <- auxiliary register 
	@ r12 <- background register

	@ Effects: paste image (whose pointer is held in r13) onto the background
	@ at coordinates (x0, y0) (held in registers r0 and r1).
	@ The function features alpha channel mixing between image and background.

fill:
		
	@ Saving onto the stack
	push r4
	push r5
	push r6
	push r7
	push r8
	push r9
	push r10
	push r11
    push r12
	
    @ y-axis iterator
	mov r6, #0
    @ x-axis iterator
	mov r5, #0

    @ set target width-X
	add r8, r2, r0

    @ set target height-Y 
	add r9, r3, r1

    @ compute array iterator
	mov r11, width
	mla r10, r1, r11, r0

	@ load image_buffer_ptr values into register
    ldr r4, [r13, #0x24]

	@ ensure X coordinate is within image bounds
	boundX_fill:
		cmp r8, width
		ble boundY_fill
		mov r8, width 

	@ ensure Y coordinate is within image bounds
	boundY_fill:
		cmp r9, height
		ble condX_fill
		mov r9, height

	condY_fill:
		cmp r6, r3
		bge end_fill @ Y-iterator > target-Y

	condX_fill:
		cmp r5, r2
		blt loop_fill @ X-iterator < target-X

		@ reinitialize X-iterator
		mov r5, #0

		@ increment Y-iterator
		add r6, r6, #1
		b condY_fill	

	loop_fill:
		ldr r11, [r13, #0x28]

		push r3
		push r2
		push r1
		push r0

		mla r10, r6, r2, r5
		add r8, r5, r0
		add r9, r6, r1

		@ load pixel from memory to be displayed
		ldr r0, [r11, r10, lsl #2]

		@ compute array iterator
		mov r11, width
		mla r10, r9, r11, r8
	
		@ load pixel from background 
		ldr r7, [r4, r10, lsl #2]

		@ separate pixel into channels by byte
		@ r3 - Alpha channel (Byte 3)
		@ r2 - Blue channel  (Byte 2)
		@ r1 - Green channel (Byte 1)
		@ r0 - Red channel   (Byte 0)

		mov r3, r0, lsr #0x18
		mov r2, r0, lsr #0x10
		mov r1, r0, lsr #0x8
		and r2, r2, #0xFF
		and r1, r1, #0xFF
		and r0, r0, #0xFF

		@ mix background with new pixel
		rsb r11, r3, #0xFF

		@ mix Red channel
		push r7
		and r7, r7, #0xFF
		mul r0, r3, r0
		mla r0, r11, r7, r0
		add r0, r0, r0, lsr #8
		lsr r0, #8
		ldr r7 [r13]

		@ mix Green channel
		lsr r7, #8
		and r7, r7, #0xFF
		mul r1, r3, r1
		mla r1, r11, r7, r1
		add r1, r1, r1, lsr #8
		lsr r1, #8 
		ldr r7 [r13]

		@ mix Blue channel
		lsr r7 #16
		and r7, r7, #0xFF
		mul r2, r3, r2
		mla r2, r11, r7, r2
		add r2, r2, r2, lsr #8
		lsr r2, #8 
		ldr r7 [r13] #4

		@ add Green and Blue channels
		add r0, r0, r1, lsl #8
		add r0, r0, r2, lsl #16

		@ store new pixel value in the write image buffer
		str r0, [r4, r10, lsl #2]

		@ increment iterators
		add r5, r5, #1

		pop r0
		pop r1
		pop r2
		pop r3

		b condX_fill

	@ Cleaning up
	end_fill:
		pop r12
		pop r11
		pop r10
		pop r9
		pop r8
		pop r7
		pop r6
		pop r5
		pop r4
		
		ret	