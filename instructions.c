#include "cpu.h"

void ADC(struct Registers* cpu, uint8_t* mem) {

	// If the accumulator/mem width is 16bit
	if(cpu -> P -> memWidth == 0) {
		uint16_t accumulator = cpu->acc.C;

		// TODO: replace grabbing the operand with a switch case or something
		// that depnds on the addressing mode of the instruction. Using a lookup
		// table would be the best way to do this quickly. 
		uint16_t operand = (mem[(cpu->PBR << 8) | cpu->PC]) | 
			(mem[(cpu->PBR << 8) | ((cpu->PC)+1)] << 8);
		//TODO: This must be changed for addressing modes as well
		cpu->PC += 2;
		

		uint8_t carryIn = cpu->P->carry;

		// Performs the operation, store in a 16 bit int to detect carry out
		uint32_t result = accumulator + operand + carryIn;

		/*
		 * Performs the operation again to detect the carry bit coming into the
		 * sign bit to calculate whether or not an overflow occurs.
		 */
		accumulator &= 0x7FFF;
		operand &= 0x7FFF;
		uint16_t partialResult = accumulator + operand + carryIn;

		/* 
		 * The overflow flag is the XOR of the carryin and carryout bits of the
		 * sign bit, i.e. the most significant bit of the 8 bit. If an overflow
		 * has occured, the overflow flag is set. Otherwise it is cleared.
		 */
		if ((result & 0x10000) ^ (partialResult & 0x8000)) {
			cpu->P->overflow = 1;
		}

		// No overflow occurs, clears the overflow flag
		else{
			cpu->P->overflow = 0;
		}

		// The carry flag is just the carryout of the addition
		cpu->P->carry = result & 0x10000 ? 1 : 0;

		// The negative flag is the sign bit of the result of the addition
		cpu->P->negative = result & 0x8000 ? 1 : 0;


		// The zero flag is 1 when the result is 0, and 0 otherwise
		cpu->P->zero = !(result & 0xFFFF) ? 1 : 0;

		// Stores the 8 bit value into the B section of the accumulator 
		cpu->acc.C = (uint16_t)result & 0xFFFF;
	}

	// If the accumulator/mem width is 8bit
	else {
		uint8_t accumulator = cpu->acc.split.A;

		// TODO: replace grabbing the operand with a switch case or something
		// that depnds on the addressing mode of the instruction. Using a lookup
		// table would be the best way to do this quickly. 
		uint8_t operand = mem[(cpu->PBR << 8) | cpu->PC++];

		uint8_t carryIn = cpu->P->carry ? 1 : 0;

		// Performs the operation, store in a 16 bit int to detect carry out
		uint16_t result = accumulator + operand + carryIn;

		/*
		 * Performs the operation again to detect the carry bit coming into the
		 * sign bit to calculate whether or not an overflow occurs.
		 */
		accumulator &= 0x7F;
		operand &= 0x7F;
		uint8_t partialResult = accumulator + operand + carryIn;

		/* 
		 * The overflow flag is the XOR of the carryin and carryout bits of the
		 * sign bit, i.e. the most significant bit of the 8 bit. If an overflow
		 * has occured, the overflow flag is set. Otherwise it is cleared.
		 */
		if ((result & 0x100) ^ (partialResult & 0x80)) {
			cpu->P->overflow = 1;
		}

		// No overflow occurs, clears the overflow flag
		else{
			cpu->P->overflow = 0;
		}

		// The carry flag is just the carryout of the addition
		cpu->P->carry = result & 0x100 ? 1 : 0;

		// The negative flag is the sign bit of the result of the addition
		cpu->P->negative = result & 0x80 ? 1 : 0;


		// The zero flag is 1 when the result is 0, and 0 otherwise
		cpu->P->zero = !(result & 0xFF) ? 1 : 0;

		// Stores the 8 bit value into the B section of the accumulator 
		cpu->acc.split.A = (uint8_t)result & 0xFF;
	}

}
