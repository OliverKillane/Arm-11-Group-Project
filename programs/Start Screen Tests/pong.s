brl setstackpointer
brl startscreen
andeq r0, r0, r0

.include startscreen.s
.include spacetostart.s
.include pongscreen.s
.include waitcycles.s
.include setfunctions.s
.include getinput.s