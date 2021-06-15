@ waits a determined number of cycles
@ arguments are...
@ r0 <- number of cycles to wait

waitcycles:
push r0
waitcycleloop:
sub r0, r0, #1
cmp r0, #0
bne waitcycleloop
pop r0
ret