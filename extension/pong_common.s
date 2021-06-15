.data
@ Common Hyperconstants
@ Precision integer shift: 8
@ Ball diameter:           12
@ Common Variables
	bcurr:
		.long 0 @ ball current position x coord
		.long 0  @ ball current position y coord
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
	.set stack_start 0x7FFFF @ the stack start
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
	.set paddlespeed 0x400
	.set paddlemaxY 0x4400

	@ the maximum coordinates for the ml, mr mb mt and width/height
	.set maxYcoor 0x6200
	.set maxXcoor 0xB600

	@ the input buffer start
	.set input_buffer_start  0x42000
