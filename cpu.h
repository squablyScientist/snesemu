#include <stdint.h>
#include "status.h"


// The accumulator reg, either 1 16bit reg or 2 8bit regs.
union Accumulator {
	uint16_t C;			// The full 16bit register

	// TODO: make sure that the endianess lines up ane that this works.
	struct {
		uint8_t A;		// The lo byte of the accumulator
		uint8_t B;		// The hi byte of the accumulator
	} split;
};



struct Registers {

	// The accumulator register
	union Accumulator acc;

	// The Data Bank Register
	uint8_t DBR;

	// The X idx register
	uint16_t X;

	// The Y idx register
	uint16_t Y;

	// The Direct Page Register
	uint16_t D;

	// The Program Bank Register
	uint8_t PBR;

	// The Stack Pointer
	uint16_t SP;

	// The Program Counter
	uint16_t PC;

	// The Processor Status Register
	struct ProcessorStatusRegister* P;
};

/**
 * Allocates memory and initiallises the state of the register file
 */
struct Registers* initReg();

/**
 *  Writes a nicely formatted string to the stream given that desribes the
 *  current state of all the registers of the 65816. This is a debugging tool
 *  mostly.
 */
void dumpRegisters(struct Registers* reg, FILE *stream);

