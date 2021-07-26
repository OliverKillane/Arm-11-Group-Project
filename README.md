# Arm-11-Group-Project

![emulated pong](https://user-images.githubusercontent.com/44177991/127006347-d3f9beaa-f501-427a-b123-5fdad9e2cc8e.png)

An assembler and emulator using a subset of the arm assembly language. Extended to allow for video output, keyboard input and demonstrated with a game of pong written in slightly modified ARM assembly.

Once cloned, run make to:
- compile the assembler, emulator and extended emulator
- assemble the pong game to am ARM32 binary
- launch the extended emulator with the pong binary

SDL2 is statically linked with the extended emulator, if you require an ARM32 instead of x86_64 binary, there is one available to use by switching the filename in the src/emulate_extension makefile.

Created by Bartłomiej Cieślar, Jordan Hall, Ioana Mihăilescu and Oliver Killane.
