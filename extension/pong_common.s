.data
@ Common Hyperconstants
@ Precision integer shift: 8
@ Ball diameter:           12
@ Common Variables
	bcurr:
		.long   @ ball current position x coord
		.long 40  @ ball current position y coord
	bprev:
		.long 0  @ ball previous position x coord
		.long 0  @ ball previous position y coord
	bvel:
		.long 0 @ ball x velocity
		.long 0 @ ball y velocity
	pcurr:
		.long 0  @ left paddle current position
		.long 0  @ right paddle current position
	pprev:
		.long 0  @ left paddle previous position
		.long 0  @ right paddle previous position
	score:
		.long 0  @ left player score
		.long 0  @ right player score
	stack_start:
		.long 0x7FFFF @ the stack start
@ Common Constants
	.set width 192
	.set height 108
	.set paddlewidth 5
	.set paddleheight 30
	.set mt 5
	.set mb 5
	.set ml 5 
	.set mr 5
	.set inputbuffersize 64
	.set paddlespeed 4
	.set paddlemaxY 44

	@ the maximum coordinates for the ml, mr mb mt and width/height
	.set maxYcoor 98
	.set maxXcoor 182

	@ the input buffer start
	.set input_buffer_start  0x42000
