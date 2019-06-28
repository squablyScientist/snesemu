#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "instructions.h"
#include "opcode.h"
void run(struct Registers *cpu, uint8_t *mem);

int main() {
	struct Registers* cpu = initReg();
	uint8_t* mem = malloc(16777216);


	// Turn off emulation mode for conveinience while developing
	cpu->P->emulation=0;


	// some data or something
	mem[0] = 0xEF;
	mem[1] = 0x34;
	mem[2] = 0x12;
	mem[3] = 0x7F;
	mem[4] = 0x00;
	mem[5] = 0x00;
	mem[6] = 0x00;
	mem[7] = 0x01;
	mem[8] = 0x00;

	// Text
	mem[0x129] = 0xA9; 	// LDA 
	mem[0x12A] = 0xFF; 	//	0x00FF
	mem[0x12B] = 0x00;
	mem[0x12C] = 0x3A; 	// DEC A
	mem[0x12D] = 0xD0; 	// BNE 
	mem[0x12E] = 0xFD; 	// 	-3
	mem[0x12F] = 0x6D;
	mem[0x130] = 0x07;
	mem[0x131] = 0x00;
	mem[0x132] = 0xD5;
	mem[0x133] = 0x01;
	mem[0x134] = 0x22;
	mem[0x135] = 0x2C;
	mem[0x136] = 0x01;
	mem[0x137] = 0x00;
	//mem[306] = 0x4C;
	//mem[307] = 0x32;
	//mem[308] = 0x01;
	
	
	cpu->PC = 0x129;
	cpu->SP = 0xFFF;

	dumpRegisters(cpu, mem, stdout);
	run(cpu, mem);
	return 0;
}

void run(struct Registers *cpu, uint8_t *mem){
	while(1){
		instJmpTab[mem[cpu->PC]](cpu, mem);
		system("clear");
		dumpRegisters(cpu, mem, stdout);
		dumpMemory(cpu, mem, 0x0ff0, 0xfff, stdout);
		getchar();
	}
}
