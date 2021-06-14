.text
	mov r13 :first8:stack_start
	orr r13, r13 :second8:stack_start
	orr r13, r13 :third8:stack_start
	orr r13, r13 :fourth8:stack_start
	brl initdraw
	brl draw
.include pong_common.s
.include graphics.s