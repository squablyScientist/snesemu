#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "instructions.h"
#include "opcode.h"
void run(struct Registers *cpu, uint8_t *mem);

int main() {
	struct Registers* cpu = initReg();
	uint8_t* mem = malloc(16777216);
	cpu->P->emulation=0;


	// some data or something
	mem[0] = 0xEF;
	mem[1] = 0xCD;
	mem[2] = 0xAB;
	mem[3] = 0x7F;
	mem[4] = 0x00;
	mem[5] = 0x00;
	mem[6] = 0x00;
	mem[7] = 0xFF;
	mem[8] = 0xFF;

	// Text
	mem[300] = 0x6D;
	mem[301] = 0x01;
	mem[302] = 0x00;
	mem[303] = 0x6D;
	mem[304] = 0x07;
	mem[305] = 0x00;
	//mem[306] = 0x4C;
	//mem[307] = 0x32;
	//mem[308] = 0x01;
	
	
	cpu->PC = 300;

	dumpRegisters(cpu, mem, stdout);
	run(cpu, mem);
	return 0;
}

void run(struct Registers *cpu, uint8_t *mem){
	while(1){
		instJmpTab[mem[cpu->PC]](cpu, mem);
		dumpRegisters(cpu, mem, stdout);
	}
}
