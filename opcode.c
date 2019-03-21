#include "opcode.h"
uint32_t getEffectiveAddress(Registers* cpu, uint8_t opcode, uint8_t* mem){

	// Retrieves the addr mode from the opcode
	enum addrmode mode = modeMap[opcode];

	// Starts out with an empty addr 
	uint32_t effectiveAddress = 0;

	// Grab the program counter
	uint8_t pc = cpu.PC;

	switch(mode){

		/* 
		 * The instruction uses the next 2 bytes after opcode appended to either
		 * the DBR or the PBR depending on whether the instruction is locating
		 * data or tranferring control respectively
		 */ 
		case Absolute:
			switch(opcode){
				
				// Instructions that transfer control addr
				case 0x4C:	// JMP
				case 0x20: 	// JSR
					effectiveAddress = cpu.PBR << 16;
					break;

				// Instructions that locate data
				default:
					effectiveAddress = cpu.DBR << 16;
					break;

				effectiveAddress |= (mem[pc + 2] << 8);
				effectiveAddress |= (mem[pc + 1])
			}
			break;
	}

	return effectiveAddress;
}
