#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "instructions.h"

int main() {
	struct Registers* cpu = initReg();
	uint8_t* mem = malloc(16777216);
	dumpRegisters(cpu, stdout);


	mem[0] = 0x69;
	mem[1] = 0xFF;
	mem[2] = 0x7F;
	mem[3] = 0x69;
	mem[4] = 0x01;
	mem[5] = 0x00;

	cpu->PC++;
	ADC(cpu, mem);

	dumpRegisters(cpu, stdout);

	cpu->PC++;
	ADC(cpu, mem);

	dumpRegisters(cpu, stdout);
	return 0;
}
