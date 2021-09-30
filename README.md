# Arm 11 Group Project
![emulated pong](https://user-images.githubusercontent.com/44177991/127006347-d3f9beaa-f501-427a-b123-5fdad9e2cc8e.png)

This project was developed as coursework for Imperial College London's 40009 Practical Programming coursework. The assembler accepts a subset of the official ARM-11 assembly language and produces an executable binary. The emulator accepts the binary and will simulate the ARM-11 architecture. For our extension, we ported the pong game to ARM-11 Assembly language and compiled/simulated it with our developed tools.

SDL2 is statically linked with the extended emulator, if you require an ARM32 instead of x86_64 binary, there is one available to use by switching the filename in the src/emulate_extension makefile.

### Emulator Structure
The emulator pipeline works as follows:
 - Take program arguments for GPIO, memory dump, video output etc.
 - Read the assembled binary into memory (assumed little endian format), can run of both big and little endian systems.
 - Fetch, decode and execute each instruction, taking into account the ARm 3 stage pipeline.
 - Update memory, registers and upon video pointer write update the output display.
 - Take keyboard input and allow program interaction through special memory location.
 - Handle any errors with useful messages.

### Assembler Structure
The assembler pipeline works as follows:
 - Read the source code into memory.
 - Process the assembler directives, recursively read any external source files into memory.
 - Tokenize the source code and prime error handling library.
 - Perform syntax and semantic analysis on the token streams.
 - Encode the instructions and data into binary format.
 - Write the resulting binary to a file.

## Getting Started
If you want to get the project running immediately or wish to tinker around with the code, this is the place to start!

### Prerequisites
This project has only ever been run on Linux and WSL.
To get started, just clone this repository onto your machine.

### Installing
Download a clone of this repository and open up a terminal in that repository.
After that, make the source code:

    $ make all
Then simply enjoy the game of Pong (hint: the controls are 'W', 'S', 'Up' and 'Down'.

And that's it! You should have it up and running. Mess around with it for a while and have some fun with our project.

## Contributing
This code is not up for being modified as it is a showcase of our courework.

## Authors

* **Bartłomiej Cieślar** - *Developer*
* **Jordan Hall** - *Developer*
* **Ioana Mihăilescu** - *Developer*
* **Oliver Killane** - *Developer*

See also the list of [contributors](https://github.com/OliverKillane/Arm-11-Group-Project/graphs/contributors) who participated in this project.
