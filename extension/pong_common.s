.data
@ Common Hyperconstants
@ Precision integer shift: 8
@ Ball diameter:           12

@ Common Variables
	bcurr:
		.long 0 @ ball current position x coord
		.long 0  @ ball current position y coord
	bvel:
		.long 0 @ ball x velocity
		.long 0 @ ball y velocity
	pcurr:
		.long 0  @ left paddle current position
		.long 0  @ right paddle current position
	pvel:
		.long 0 @ left y paddle velocity
		.long 0 @ right y paddle velocity
	score:
		.long 0  @ left player score
		.long 0  @ right player score
	scorechanged:
		.long 1
	loopiterator:
		.long 0	
	

@ Common Constants
	.set width 192
	.set height 108
	.set paddlewidth 5
	.set paddleheight 30
	.set mt 2
	.set mb 2
	.set ml 5 
	.set mr 5
	.set paddlespeed 0x150
	.set paddlemaxY 0x4A00

	@ the maximum coordinates for the ml, mr mb mt and width/height
	.set maxYcoor 0x6800
	.set maxXcoor 0xB600

	@ the input buffer start
	.set input_buffer 0x3000000

	@ the start of the descending stack
	.set stack_start 0x7FFFF @ the stack start
