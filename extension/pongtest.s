@ Main program
.text

brl setvars

brl resetball

brl draw

loop:
b loop

@ Includes
.include pong_common.s
.include graphics.s
.include ponglogic.s