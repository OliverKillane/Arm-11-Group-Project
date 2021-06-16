@ This file defines an initdraw subroutine used in the main loop
.text
    initdraw:
        @ Saving onto the stack
        push r14
        push r3
        push r2
        push r1
        push r0

        @ Initializing the write image buffer
        mov r2, :first8:image_buffer
        orr r2, r2, :second8:image_buffer
        orr r2, r2, :third8:image_buffer
        orr r2, r2, :fourth8:image_buffer
        mov r3, :first8:image_buffer_ptr
        orr r3, r3, :second8:image_buffer_ptr
        orr r3, r3, :third8:image_buffer_ptr
        orr r3, r3, :fourth8:image_buffer_ptr
        str r2 [r3]

        @ Drawing the press any key text
        mov r0, :first8:press_key
        orr r0, r0 :second8:press_key
        orr r0, r0 :third8:press_key
        orr r0, r0 :fourth8:press_key
        push r0
        mov r0 press_key_x
        mov r1 press_key_y
        mov r2 press_key_width
        mov r3 press_key_height
        brl fill
        add r13, r13, #0x4

        @ Cleaning everything up
        pop r0
        pop r1
        pop r2
        pop r3
        pop r14
        ret