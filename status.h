/**
 * status.h : struct definition and function declarations relating to the
 * processor status register in the 65816 processor. 
 *
 * Author: Collin Tod
 *
 * TODO: Find a way to condense the accessors and mutators of the psr, or get
 * rid of them entirely
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

// Setting, Clearing, and Getting functions for the negative flag
void setnegativeFlag(struct ProcessorStatusRegister* psr);
void clearnegativeFlag(struct ProcessorStatusRegister* psr);
uint8_t getnegativeFlag(struct ProcessorStatusRegister* psr);

// Setting, Clearing, and Getting functions for the overflow flag
void setoverflowFlag(struct ProcessorStatusRegister* psr);
void clearoverflowFlag(struct ProcessorStatusRegister* psr);
uint8_t getoverflowFlag(struct ProcessorStatusRegister* psr);

// Setting, Clearing, and Getting functions for the memWidth flag
void setmemWidthFlag(struct ProcessorStatusRegister* psr);
void clearmemWidthFlag(struct ProcessorStatusRegister* psr);
uint8_t getmemWidthFlag(struct ProcessorStatusRegister* psr);

// Setting, Clearing, and Getting functions for the idxWidth flag
void setidxWidthFlag(struct ProcessorStatusRegister* psr);
void clearidxWidthFlag(struct ProcessorStatusRegister* psr);
uint8_t getidxWidthFlag(struct ProcessorStatusRegister* psr);

// Setting, Clearing, and Getting functions for the deciMode flag
void setdeciModeFlag(struct ProcessorStatusRegister* psr);
void cleardeciModeFlag(struct ProcessorStatusRegister* psr);
uint8_t getdeciModeFlag(struct ProcessorStatusRegister* psr);

// Setting, Clearing, and Getting functions for the irqDisabl flag
void setirqDisableFlag(struct ProcessorStatusRegister* psr);
void clearirqDisableFlag(struct ProcessorStatusRegister* psr);
uint8_t getirqDisableFlag(struct ProcessorStatusRegister* psr);

// Setting, Clearing, and Getting functions for the zero flag
void setzeroFlag(struct ProcessorStatusRegister* psr);
void clearzeroFlag(struct ProcessorStatusRegister* psr);
uint8_t getzeroFlag(struct ProcessorStatusRegister* psr);

// Setting, Clearing, and Getting functions for the carry flag
void setcarryFlag(struct ProcessorStatusRegister* psr);
void clearcarryFlag(struct ProcessorStatusRegister* psr);
uint8_t getcarryFlag(struct ProcessorStatusRegister* psr);

// Setting, Clearing, and Getting functions for the emulation flag
void setemulationFlag(struct ProcessorStatusRegister* psr);
void clearemulationFlag(struct ProcessorStatusRegister* psr);
uint8_t getemulationFlag(struct ProcessorStatusRegister* psr);

// Setting, Clearing, and Getting functions for the break_ flag
void setbreak_Flag(struct ProcessorStatusRegister* psr);
void clearbreak_Flag(struct ProcessorStatusRegister* psr);
uint8_t getbreak_Flag(struct ProcessorStatusRegister* psr);

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
