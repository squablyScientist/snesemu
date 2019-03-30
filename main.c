#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "instructions.h"
#include "opcode.h"

int main() {
	struct Registers* cpu = initReg();
	uint8_t* mem = malloc(16777216);
	dumpRegisters(cpu, stdout);
	cpu->P->emulation = 0;


	mem[0] = 0xEF;
	mem[1] = 0xCD;
	mem[2] = 0xAB;
	mem[3] = 0x7F;
	mem[4] = 0x00;
	mem[5] = 0x00;
	mem[6] = 0x00;

	mem[300] = 0x6D;
	mem[301] = 0x01;
	mem[302] = 0x00;

	cpu->PC = 300;

	ADC(cpu, mem);
	dumpRegisters(cpu, stdout);

	return 0;
}
