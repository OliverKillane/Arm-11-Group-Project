.text
	mov r13 :first8:stack_start
	orr r13, r13 :second8:stack_start
	orr r13, r13 :third8:stack_start
	orr r13, r13 :fourth8:stack_start
	brl initdraw
	

	mov r5 #0
	testloop:
	add r5, r5 #1
	cmp r5 #0x10000
	ble testloop

	brl blackout
	brl draw

	mov r5 #0
	testloop2:
	add r5, r5 #1
	cmp r5 #0x10000000
	b testloop2
	
.include pong_common.s
.include graphics.s