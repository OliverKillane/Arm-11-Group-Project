.text
fill:
	
	@ Function parameters: 
	@ r0  <- x0 
	@ r1  <- y0 
	@ r2  <- width  (X axis)
	@ r3  <- height (Y axis) 
	@ r13 <- memory pointer register

	@ Internal registers for local variables: 
    @ r4  <- write_image_buffer register	
	@ r5  <- X-axis iterator
	@ r6  <- Y-axis iterator
	@ r7  <- auxiliary register
	@ r8  <- X-axis target pixel index
	@ r9  <- Y-axis target pixel index
	@ r10 <- array iterator index
    @ r11 <- auxiliary register 
	@ r12 <- background register
	
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
	push r13

    @ y-axis iterator
	mov r6, r1
    @ x-axis iterator
	mov r5, r0

    @ set target width-X
	add r8, r2, r0

    @ set target height-Y 
	add r9, r3, r1

    @ array iterator
	mov r11, width
	mla r10, r0, r11, r1

	@ load background values into register
    mov r12, :first8:background
    orr r12, r12, :second8:background
    orr r12, r12, :third8:background
    orr r12, r12, :fourth8:background

	@ load write_image_buffer values into register
    mov r4, :first8:write_image_buffer
    orr r4, r4, :second8:write_image_buffer
    orr r4, r4, :third8:write_image_buffer
    orr r4, r4, :fourth8:write_image_buffer

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
		cmp r6, r9
		bgt end_fill @ Y-iterator > target-Y

	condX_fill:
		cmp r5, r8
		ble loop_fill @ X-iterator <= target-X

		@ reinitialize X-iterator
		sub r5, r5, r2

		@ move matrix iterator to next row
		sub r10, r10, r2
		add r10, r10, width

		@ increment Y-iterator
		add r6, r6, #1
		b condY_fill	

	loop_fill:
		@ load pixel from memory to be displayed
		ldr r0, [r10, r13]
		@ load pixel from background 
		ldr r7, [r10, r12]

		@ separate pixel into channels by byte
		@ r3 - Alpha channel (Byte 3)
		@ r2 - Blue channel  (Byte 2)
		@ r1 - Green channel (Byte 1)
		@ r0 - Red channel   (Byte 0)

		mov r3, r0, lsl #24
		mov r2, r0, lsl #16
		mov r1, r0, lsl #8
		and r2, r2, #0xFF
		and r1, r1, #0xFF
		and r0, r0, #0xFF

		@ mix background with new pixel
		rsb r11, r3, #255

		@ mix Red channel
		mul r0, r3, r0
		mla r0, r11, r7, r0
		add r0, r0, r0, lsl #8
		lsl r0, #8 

		@ mix Green channel
		mul r1, r3, r1
		mla r1, r11, r7, r1
		add r1, r1, r1, lsl #8
		lsl r1, #8 

		@ mix Blue channel
		mul r2, r3, r2
		mla r2, r11, r7, r2
		add r2, r2, r2, lsl #8
		lsl r2, #8 

		@ add Green and Blue channels
		add r0, r0, r1, lsr #8
		add r0, r0, r2, lsr #16

		@ store new pixel value in the write image buffer
		str r0, [r10, r4] 

		@ increment iterators
		add r5,  r5,  #1
		add r10, r10, #1

		b condX_fill

	@ Cleaning up
	end_fill:
		pop r13
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