#include "opcode.h"
uint32_t getEffectiveAddress(Registers* cpu, uint8_t opcode, uint8_t* mem){

	// Retrieves the addr mode from the opcode
	enum addrmode mode = modeMap[opcode];

	// Starts out with an empty addr 
	uint32_t effectiveAddress = 0;

	switch(mode){

		/* 
		 * The instruction uses the next 2 bytes after opcode appended to either
		 * the DBR or the PBR depending on whether the instruction is locating
		 * data or tranferring control respectively
		 */ 
		case Absolute:
			switch(opcode){

			}
			break;
	}
}
