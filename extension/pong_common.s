.data
@ Common Hyperconstants
@ Precision integer shift: 8
@ Ball diameter:           12
@ Common Variables
	bcurr:
		.long 0  @ ball current position x coord
		.long 0  @ ball current position y coord
	bprev:
		.long 0  @ ball previous position x coord
		.long 0  @ ball previous position y coord
	pcurr:
		.long 0  @ left paddle current position
		.long 0  @ right paddle current position
	pprev:
		.long 0  @ left paddle previous position
		.long 0  @ right paddle previous position
	score:
		.long 0  @ left player score
		.long 0  @ right player score
@ Common Constants
	.set width 192
	.set height 108
	.set paddlewidth 5
	.set paddleheight 30
	.set mt 5
	.set mb 5
	.set ml 5
	.set mr 5
	.set stack_start 0x7FFFF