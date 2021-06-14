.text
reset:
	
	@ function parameters: 
	@ r0  <- x0
	@ r1  <- y0
	@ r2  <- width  (X axis)
	@ r3  <- height (Y axis)

	@ internal registers for local variables: 
    @ r4 <- write_image_buffer register
	@ r5  <- x iterator
	@ r6  <- y iterator
	@ r8  <- X-axis target pixel index
	@ r9  <- Y-axis target pixel index
	@ r10 <- array iterator index
    @ r11 <- auxiliary register 
    @ r12 <- background register
		
	@ Saving onto the stack	
    push r4
    push r5
	push r6
	push r8
	push r9
	push r10
	push r11
    push r12


    @ y-axis iterator
	mov r6, r1
    @ x-axis iterator
	mov r5, r0

    @ set target width-x
	add r8, r2, r1

    @ set target height-y
	add r9, r3, r1

    @ array iterator
	mov r11, height
	mla r10, r0, r11, r1

	@ load background values into register
    mov r12 :first8:background
    orr r12, r12 :second8:background
    orr r12, r12 :third8:background
    orr r12, r12 :fourth8:background

	@ load write_image_buffer values into register
    mov r4 :first8:write_image_buffer
    orr r4, r4 :second8:write_image_buffer
    orr r4, r4 :third8:write_image_buffer
    orr r4, r4 :fourth8:write_image_buffer

	@ ensure X coordinate is within image bounds
	cmp r8, height
	ble condX
	mov r8, height 

	@ ensure Y coordinate is within image bounds
	cmp r9, width
	ble condX
	mov r9, width

	condX:
		cmp r5, r8
		bgt end @ X-iterator > target-X

	condY:
		cmp r6, r9
		ble loop @ Y-iterator <= target-Y

		@ reinitialize Y-iterator
		sub r6, r6, r3

		@ move matrix iterator to next row
		sub r10, r10, r3
		add r10, r10, height

		@ increment X-iterator
		add r5, r5, #1
		b condX	

	loop:
		@ load pixel from background
        ldr r11, [r12, r10]
		@ store background pixel value into the write image buffer
		str r11, [r4, r10] 

		@ increment iterators
		add r6,  r6, #1
		add r10, r10, #1

		b condY

	@ Clean up
    end:
        pop r12
		pop r11
		pop r10
		pop r9
		pop r8
		pop r6
		pop r5
        pop r4

		ret    