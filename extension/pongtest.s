@ Main program
.text

brl setvars

brl initdraw

brl draw

loop:
b loop

@ Includes
.include pong_common.s
.include graphics.s
.include ponglogic.s