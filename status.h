/**
 * status.h : struct definition and function declarations relating to the
 * processor status register in the 65816 processor. 
 *
 * Author: Collin Tod
 *
 * TODO: Possibly get idof the abstractions and just use an 8 bit value with a
 * phantom emulation bit.
 */
#include <stdint.h>

#ifndef _STATUS_
#define _STATUS_

#define CARRY_FLAG 							0x01
#define ZERO_FLAG							0x02
#define IRQ_DISABLE_FLAG					0x04
#define DECIMAL_FLAG						0x08

// Only in emu mode
#define BREAK_FLAG							0x10

// Only in native mode
#define INDEX_WIDTH_FLAG					0x10

// Only relevant in native mode
#define ACCUMULATOR_WIDTH_FLAG				0x20

#define OVERFLOW_FLAG						0x40
#define NEGATIVE_FLAG						0x80

struct ProcessorStatusRegister {
	uint8_t negative: 1;
	uint8_t overflow: 1;
	uint8_t memWidth: 1;
	uint8_t idxWidth: 1;
	uint8_t deciMode: 1;
	uint8_t irqDisable: 1;
	uint8_t zero: 1;
	uint8_t carry: 1;
	uint8_t emulation: 1;
	uint8_t break_: 1;
};	

// Allocates memory and returns a ptr to a new processor status register. 
struct ProcessorStatusRegister* newPSR();

/* 
 * Sets the processor status based on an 8bit number provided & the current 
 * state of the CPU (which mode it is in)
 */
void setProcessorStatus(struct ProcessorStatusRegister* psr, uint8_t value);

/*
 * Returns the processor status encoded into an 8bit number based on the current
 * mode of the CPU (native or emulation)
 */
uint8_t getProcessorStatus(struct ProcessorStatusRegister* psr);

#endif
