mov r0, #0x1000
brl setstackpointer

brl setR1white
brl drawpong

@ white, then wait, then clear, then wait, repeat
startscreenloop:
mov r0, #0x1000
brl setR1white
brl drawspacetostart

mov r0, #0xF
brl waitcycles

mov r0, #0x1000
mov r1, #0
brl drawspacetostart

mov r0, #0xF
brl waitcycles

b startscreenloop

.include spacetostart.s
.include pong.s
.include waitcycles.s
.include setfunctions.s