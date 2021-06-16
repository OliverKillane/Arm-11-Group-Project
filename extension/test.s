.text
	mov r13 :first8:stack_start
	orr r13, r13 :second8:stack_start
	orr r13, r13 :third8:stack_start
	orr r13, r13 :fourth8:stack_start
	
	@ bcurr address
	mov r2 :first8:bcurr
	orr r2, r2 :second8:bcurr
	orr r2, r2 :third8:bcurr
	orr r2, r2 :fourth8:bcurr

	@ pcurr address
	mov r4 :first8:pcurr
	orr r4, r4 :second8:pcurr
	orr r4, r4 :third8:pcurr
	orr r4, r4 :fourth8:pcurr

	@ score address
	mov r6 :first8:score
	orr r6, r6 :second8:score
	orr r6, r6 :third8:score
	orr r6, r6 :fourth8:score

	brl initdraw

	brl blackouttext
	brl update

	mainloop:

	brl blackoutball
	brl blackoutleftpaddle
	brl blackoutleftscore
	brl blackoutrightpaddle
	brl blackoutrightscore

	ldr r7 [r2]
	add r7, r7, #100
	str r7 [r2]

	ldr r7 [r2, #0x4]
	add r7, r7, #100
	str r7 [r2, #0x4]

	brl drawleftpaddle
	brl drawrightpaddle
	brl drawleftscore
	brl drawrightscore
	brl drawball
	brl update

	b mainloop
	
.include pong_common.s
.include graphics.s