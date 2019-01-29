/*
 *  status.c: Implementations for functions that manipulate and define the
 *  processor status register
 *
 *  Author: Collin Tod
 *
 * TODO: Convert functionality to using an actual 8 bit value rather than an
 * abstraction for efficiency.
 */
#include <stdlib.h>
#include <stdio.h>
#include "status.h"


struct ProcessorStatusRegister* newPSR() {
    struct ProcessorStatusRegister* new = 
        malloc(sizeof(struct ProcessorStatusRegister));

    if(!new) {
        perror("Can't allocate memory for processor status register");
        return NULL;
    }

    new->negative = 0;
    new->overflow = 0;
    new->memWidth = 0;
    new->idxWidth = 0;
    new->deciMode = 0;
    new->irqDisable = 0;
    new->zero = 0;
    new->carry = 0;
    new->emulation = 1;      // 65816 starts in emulation mode
    new->break_ = 0;

    return new;
}


/**
 * Given an 8 bit value, the processor status register will be set to the
 * correct state based on the current emulation state of the 65816.
 */
void setProcessorStatus(struct ProcessorStatusRegister* psr, uint8_t value) {
    //TODO condense this entire funtion into a for loop using bitshifting & fxn
    //ptrs
    if (value & CARRY_FLAG) {
        setcarryFlag(psr);
    }
    else{
        clearcarryFlag(psr);
    }

    if (value & ZERO_FLAG) {
        setzeroFlag(psr);
    }
    else{
        clearzeroFlag(psr);
    }

    if (value & IRQ_DISABLE_FLAG) {
        setirqDisableFlag(psr);
    }
    else{
        clearirqDisableFlag(psr);
    }

    if (value & DECIMAL_FLAG) {
        setdeciModeFlag(psr);
    }
    else {
        cleardeciModeFlag(psr);
    }

    if (getemulationFlag(psr)) {
        // 65816 is in emulation mode, and thus uses the BREAK flag
        if (value & BREAK_FLAG) {
            setbreak_Flag(psr);
        }
        else {
            clearbreak_Flag(psr);
        }
    }
    else {
        // 65816 is in native mode, and thus uses the IDX_WIDTH flag
        if (value & INDEX_WIDTH_FLAG) {
            setidxWidthFlag(psr);
        }
        else {
            clearidxWidthFlag(psr);
        }
    }

    // Accumulator/Memory width flag. This is only used in native mode.
    if (!getemulationFlag(psr) && (value & ACCUMULATOR_WIDTH_FLAG)) {
        setmemWidthFlag(psr);
    }
    else {
        clearmemWidthFlag(psr);
    }

    if (value & OVERFLOW_FLAG) {
        setoverflowFlag(psr);
    }
    else {
        clearoverflowFlag(psr);
    }

    if (value & NEGATIVE_FLAG) {
        setnegativeFlag(psr);
    }
    else {
        clearnegativeFlag(psr);
    }
}


uint8_t getProcessorStatus(struct ProcessorStatusRegister* psr){
    uint8_t status = 0x00;
    if (getcarryFlag(psr)) {
        status |= CARRY_FLAG;
    }

    if (getzeroFlag(psr)) {
        status |= ZERO_FLAG;
    }

    if (getirqDisableFlag(psr)) {
        status |= IRQ_DISABLE_FLAG;
    }

    if (getdeciModeFlag(psr)) {
        status |= DECIMAL_FLAG;
    }

    // TODO make this a switch statement?
    if (getemulationFlag(psr)) {
        // 65816 is in emulation mode, using the break flag
        if (getbreak_Flag(psr)) {
            status |= BREAK_FLAG;
        }
    }
    else {
        // 65816 is in native mode, using the index width flag
        if (getidxWidthFlag(psr)) {
            status |= INDEX_WIDTH_FLAG;
        }
    }

    if (!getemulationFlag(psr) && getmemWidthFlag(psr)) {
        status |= ACCUMULATOR_WIDTH_FLAG;
    }

    if (getoverflowFlag(psr)) {
        status |= OVERFLOW_FLAG;
    }

    if (getnegativeFlag(psr)) {
        status |= NEGATIVE_FLAG;
    }

    return status;
}

// Setting, Clearing, and Getting functions for the negative flag
void setnegativeFlag(struct ProcessorStatusRegister* psr) {
    psr->negative = 1;
}
void clearnegativeFlag(struct ProcessorStatusRegister* psr){
    psr->negative = 0;
}
uint8_t getnegativeFlag(struct ProcessorStatusRegister* psr){
    return psr->negative;
}

// Setting, Clearing, and Getting functions for the overflow flag
void setoverflowFlag(struct ProcessorStatusRegister* psr) {
	psr->overflow = 1;
}
void clearoverflowFlag(struct ProcessorStatusRegister* psr) {
	psr->overflow = 0;
}
uint8_t getoverflowFlag(struct ProcessorStatusRegister* psr) {
	return psr->overflow;
}

// Setting, Clearing, and Getting functions for the memWidth flag
void setmemWidthFlag(struct ProcessorStatusRegister* psr) {
	psr->memWidth = 1;
}
void clearmemWidthFlag(struct ProcessorStatusRegister* psr) {
	psr->memWidth = 0;
}
uint8_t getmemWidthFlag(struct ProcessorStatusRegister* psr) {
	return psr->memWidth;
}

// Setting, Clearing, and Getting functions for the idxWidth flag
void setidxWidthFlag(struct ProcessorStatusRegister* psr) {
	psr->idxWidth = 1;
}
void clearidxWidthFlag(struct ProcessorStatusRegister* psr) {
	psr->idxWidth = 0;
}
uint8_t getidxWidthFlag(struct ProcessorStatusRegister* psr) {
	return psr->idxWidth;
}

// Setting, Clearing, and Getting functions for the deciMode flag
void setdeciModeFlag(struct ProcessorStatusRegister* psr) {
	psr->deciMode = 1;
}
void cleardeciModeFlag(struct ProcessorStatusRegister* psr) {
	psr->deciMode = 0;
}
uint8_t getdeciModeFlag(struct ProcessorStatusRegister* psr) {
	return psr->deciMode;
}

// Setting, Clearing, and Getting functions for the irqDisabl flag
void setirqDisableFlag(struct ProcessorStatusRegister* psr) {
	psr->irqDisable = 1;
}
void clearirqDisableFlag(struct ProcessorStatusRegister* psr) {
	psr->irqDisable = 0;
}
uint8_t getirqDisableFlag(struct ProcessorStatusRegister* psr) {
	return psr->irqDisable;
}

// Setting, Clearing, and Getting functions for the zero flag
void setzeroFlag(struct ProcessorStatusRegister* psr) {
	psr->zero = 1;
}
void clearzeroFlag(struct ProcessorStatusRegister* psr) {
	psr->zero = 0;
}
uint8_t getzeroFlag(struct ProcessorStatusRegister* psr) {
	return psr->zero;
}

// Setting, Clearing, and Getting functions for the carry flag
void setcarryFlag(struct ProcessorStatusRegister* psr) {
	psr->carry = 1;
}
void clearcarryFlag(struct ProcessorStatusRegister* psr) {
	psr->carry = 0;
}
uint8_t getcarryFlag(struct ProcessorStatusRegister* psr) {
	return psr->carry;
}

// Setting, Clearing, and Getting functions for the emulation flag
void setemulationFlag(struct ProcessorStatusRegister* psr) {
	psr->emulation = 1;
}
void clearemulationFlag(struct ProcessorStatusRegister* psr) {
	psr->emulation = 0;
}
uint8_t getemulationFlag(struct ProcessorStatusRegister* psr) {
	return psr->emulation;
}

// Setting, Clearing, and Getting functions for the break_ flag
void setbreak_Flag(struct ProcessorStatusRegister* psr) {
	psr->break_ = 1;
}
void clearbreak_Flag(struct ProcessorStatusRegister* psr) {
	psr->break_ = 0;
}
uint8_t getbreak_Flag(struct ProcessorStatusRegister* psr) {
	return psr->break_;
}
