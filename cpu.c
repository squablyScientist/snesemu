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
void dumpRegisters(struct Registers* reg, FILE* stream) {
	fprintf(stream,
			"Acc:\t%04x\tPBR:\t%02x\n" "X:\t%04x\tDBR:\t%02x\n" "Y:\t%04x\n"
			"D:\t%04x\n" "S:\t%04x\n" "PC:\t%04x\tP:\t%02x\n\n",
			reg->acc.C, reg->PBR, reg->X, reg->DBR, reg->Y, reg->D, reg->SP,
			reg->PC, getProcessorStatus(reg->P));
}
