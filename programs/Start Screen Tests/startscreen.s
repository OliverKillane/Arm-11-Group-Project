mov r0, #0x1000
call setstackpointer

call setR1white
call drawpong

@ white, then wait, then clear, then wait, repeat
startscreenloop:
mov r0, #0x1000
call setR1white
call drawspacetostart

mov r0, #0xF
call waitcycles

mov r0, #0x1000
mov r1, #0
call drawspacetostart

mov r0, #0xF
call waitcycles

b startscreenloop

.include spacetostart.s
.include pong.s
.include waitcycles.s
.include setfunctions.s