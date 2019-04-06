#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "status.h"


struct Registers* initReg() {
	struct Registers* new = malloc(sizeof(struct Registers));

	// Makes sure that memory was successfully allocated
	if(!new) {
		perror("Can't allocate memory for register file");
		return NULL;
	}

	new->P = newPSR();
	return new;
}
// TODO: Maybe convert this into an entire cpu state report?
void dumpRegisters(struct Registers* reg, uint8_t *mem, FILE* stream) {
	fprintf(stream,
			"Acc:\t%04x\tPBR:\t%02x\n" "X:\t%04x\tDBR:\t%02x\n" "Y:\t%04x\n"
			"D:\t%04x\nS:\t%04x\nPC:\t%04x\tP:\t%02x\nCurrent Opcode:\t %X\n\n",
			reg->acc.C, reg->PBR, reg->X, reg->DBR, reg->Y, reg->D, reg->SP,
			reg->PC, getProcessorStatus(reg->P), mem[reg->PC]);
}

void dumpMemory(struct Registers *cpu, uint8_t *mem, uint32_t start, uint32_t end, FILE* stream){

	for(int i = 0; i < 32; i++){
		fprintf(stream, "\x1B[32m%2X ", i);
	}
	fprintf(stream, "\x1B[37m\n");
	for(;start < end; start+=32){
		for(int i = 0; i < 32; i++){
			if(start + i == cpu->SP){
				fprintf(stream, "\x1B[31m");
			}
			else if(start + i == 
					((uint32_t)cpu->PC | (uint32_t)cpu->PBR << 16)){
				fprintf(stream, "\x1B[34m");
			}
			fprintf(stream, "%2X ", mem[start + i]);
			fprintf(stream, "\x1B[37m");
		}
		fprintf(stream, "\n");
	}

}
uint32_t getBankedPC(struct Registers* cpu){
	return (uint32_t)cpu->PBR << 16 | cpu->PC;
}
