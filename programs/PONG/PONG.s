
@ set up screen pointer
mov r0, #0x10000

@ Set the stack pointer to max
brl setstackpointer

@ go to start screen, then when that ius done, the pong
brl startscreen

@ draw pong message in white
brl setR1white
brl drawpongscreen

@ to keep screen on
loop:
b loop
andeq r0, r0, r0


@ the screens
.include startscreen.s
.include pongscreen.s

@ the utilities
.include waitcycles.s
.include setfunctions.s
.include getinput.s
