/*
 *  status.c: Implementations for functions that manipulate and define the
 *  processor status register
 *
 *  Author: Collin Tod
 *
 * TODO: Convert functionality to using an actual 8 bit value rather than an
 * abstraction for efficiency.
 * TODO: Create function to dump human readable status.
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
        psr->carry = 1;
    }
    else{
        psr->carry = 0;
    }

    if (value & ZERO_FLAG) {
        psr->zero = 1;
    }
    else{
        psr->zero = 0;
    }

    if (value & IRQ_DISABLE_FLAG) {
        psr->irqDisable = 1;
    }
    else{
        psr->irqDisable = 0;
    }

    if (value & DECIMAL_FLAG) {
        psr->deciMode = 1;
    }
    else {
        psr->deciMode = 0;
    }

    if (psr->emulation) {
        // 65816 is in emulation mode, and thus uses the BREAK flag
        if (value & BREAK_FLAG) {
            psr->break_ = 1;
        }
        else {
            psr->break_ = 0;
        }
    }
    else {
        // 65816 is in native mode, and thus uses the IDX_WIDTH flag
        if (value & INDEX_WIDTH_FLAG) {
            psr->idxWidth = 1;
        }
        else {
            psr->idxWidth = 0;
        }
    }

    // Accumulator/Memory width flag. This is only used in native mode.
    if (!psr->emulation && (value & ACCUMULATOR_WIDTH_FLAG)) {
        psr->memWidth = 1;
    }
    else {
        psr->memWidth = 0;
    }

    if (value & OVERFLOW_FLAG) {
        psr->overflow = 1;
    }
    else {
        psr->overflow = 0;
    }

    if (value & NEGATIVE_FLAG) {
        psr->negative = 1;
    }
    else {
        psr->negative = 0;
    }
}


uint8_t getProcessorStatus(struct ProcessorStatusRegister* psr){
    uint8_t status = 0x00;
    if (psr->carry) {
        status |= CARRY_FLAG;
    }

    if (psr->zero) {
        status |= ZERO_FLAG;
    }

    if (psr->irqDisable) {
        status |= IRQ_DISABLE_FLAG;
    }

    if (psr->deciMode) {
        status |= DECIMAL_FLAG;
    }

    // TODO make this a switch statement?
    if (psr->emulation) {
        // 65816 is in emulation mode, using the break flag
        if (psr->break_) {
            status |= BREAK_FLAG;
        }
    }
    else {
        // 65816 is in native mode, using the index width flag
        if (psr->idxWidth) {
            status |= INDEX_WIDTH_FLAG;
        }
    }

    if (!psr->emulation && psr->memWidth) {
        status |= ACCUMULATOR_WIDTH_FLAG;
    }

    if (psr->overflow) {
        status |= OVERFLOW_FLAG;
    }

    if (psr->negative) {
        status |= NEGATIVE_FLAG;
    }

    return status;
}

