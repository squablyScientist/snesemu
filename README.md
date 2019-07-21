# SNES CPU Emulator
This project is a WIP emulator for the 65816 instruction set, most notably used
as the main processor for the Super Nintendo Entertainment System (SNES). 

## Building
Just run `make`

## Usage 
This project is not really user ready as of this moment, but that doesn't mean
that you can't see it run. To enter a program and have it run you can manually
enter your program through the `src/main.c` file There is already a program
there that loads `0x00ff` into the accumulator and then decrements it until it
reaches 0. Once it reaches 0 it will recursively call a function until a stack
overflow occurs and the stack overwrites text, at which point undefined
behaviour will ensue due to self modifying code. To edit this program simply
replace the instructions starting at memory location `0x0129` with the
instructions you would like executed instead. You may manually set the sate of
all memory at the beginning of runtime, allowing you to insert global variables
and constants as well. Note that in the future this will be able to loadan
assembled 65816 file into a memory image.  

## Features
- A large subset of instructions are implemented, allowing any program that could
be written with the full instruction set to be written. This is a  result of
the project being a work in progress. 
- Each addressing mode is implemented, allowing for quick additions of new 
instructions, not having to worry about how to get each effective address. 
- Small debugger that allows you to view the the processor state as well as a 
range of memory during execution. This debugger highlights the PC and SP of 
in the memory dump, and the range of memory displayed may be customized in 
the call to `dumpMemory()` in the main loop of `src/main.c`.

## TODO
- Implement the remaining instructions
- Fully implement the 'emulation mode' that the 65816 had, allowing it to
perfectly emulate it's predecessor, the 6502

