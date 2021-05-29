mov r0,[r2,+r3,#4]
loop:
mul r2,r1,r0
bne loop
bruh: mov r3,#0x100
