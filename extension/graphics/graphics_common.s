@ This file contains the common variables and constants for the graphics part of the pong game
.data
    @ Coordinates for the left score digit
    .set score_left_x 79
    .set score_left_y 5
    @ Coordinates for the right score digit
    .set score_right_x 100
    .set score_right_y 5
    @ Coordinates for the initial "Push any button" text
    .set press_key_x 49
    .set press_key_y 70
    .set read_image_buffer 0x1000000
    write_image_buffer:
        .long 0x0
    image_buffer_0:
        .include graphics_background_raw.s
    image_buffer_1:
        .include graphics_background_raw.s
