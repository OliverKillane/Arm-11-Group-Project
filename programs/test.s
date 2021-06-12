.data
	x:
		.long 0x5
	.set y 0x6
.text
	mov r2, :first8:x
	orr r2, r2, :second8:x
	orr r2, r2, :third8:x
	orr r2, r2, :fourth8:x
	ldr r2, [r2]

	mov r1, :first8:y
	orr r1, r1, :second8:y
	orr r1, r1, :third8:y
	orr r1, r1, :fourth8:y

	mov r0, #1

	hlt

	cmp r1, #0
	ble end
	loop:
		mul r0, r2, r0
		sub r1, r1, #1
		cmp r1 #0
		bgt loop
	end:
		mov r2, #0
		mov r1, #0
		hlt
