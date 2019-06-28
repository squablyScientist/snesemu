#include "cpu.h"
#include "instructions.h"
#include "opcode.h"

// TODO: use the program bank to index mem instead of just PC, currently locked
// to bank 0

void (*instJmpTab[])(struct Registers *cpu, uint8_t *mem) = {
    NULL, //&BRK,				// 0x00
    &ORA,				// 0x01
    NULL, //&COP,				// 0x02
    &ORA,				// 0x03
    NULL, //&TSB,				// 0x04
    &ORA,				// 0x05
    &ASL,				// 0x06
    &ORA,				// 0x07
    NULL, //&PHP,				// 0x08
    &ORA,				// 0x09
    &ASL,				// 0x0A
    NULL, //&PHD,				// 0x0B
    NULL, //&TSB,				// 0x0C
    &ORA,				// 0x0D
    &ASL,				// 0x0E
    &ORA,				// 0x0F
    NULL, //&BPL,				// 0x10
    &ORA,				// 0x11
    &ORA,				// 0x12
    &ORA,				// 0x13
    NULL, //&TRB,				// 0x14
    &ORA,				// 0x15
    &ASL,				// 0x16
    &ORA,				// 0x17
    &CLC,				// 0x18
    &ORA,				// 0x19
    &INC,				// 0x1A
    NULL, //&TCS,				// 0x1B
    NULL, //&TRB,				// 0x1C
    &ORA,				// 0x1D
    &ASL,				// 0x1E
    &ORA,				// 0x1F
    &JSR,				// 0x20
    &AND,				// 0x21
    &JSL,				// 0x22
    &AND,				// 0x23
    NULL, //&BIT,				// 0x24
    &AND,				// 0x25
    NULL, //&ROL,				// 0x26
    &AND,				// 0x27
    NULL, //&PLP,				// 0x28
    &AND,				// 0x29
    NULL, //&ROL,				// 0x2A
    NULL, //&PLD,				// 0x2B
    NULL, //&BIT,				// 0x2C
    &AND,				// 0x2D
    NULL, //&ROL,				// 0x2E
    &AND,				// 0x2F
    &BMI,				// 0x30
    &AND,				// 0x31
    &AND,				// 0x32
    &AND,				// 0x33
    NULL, //&BIT,				// 0x34
    &AND,				// 0x35
    NULL, //&ROL,				// 0x36
    &AND,				// 0x37
    NULL, //&SEC,				// 0x38
    &AND,				// 0x39
    &DEC,				// 0x3A
    NULL, //&TSC,				// 0x3B
    NULL, //&BIT,				// 0x3C
    &AND,				// 0x3D
    NULL, //&ROL,				// 0x3E
    &AND,				// 0x3F
    NULL, //&RTI,				// 0x40
    &EOR,				// 0x41
    NULL, //&WDM,				// 0x42
    &EOR,				// 0x43
    NULL, //&MVP,				// 0x44
    &EOR,				// 0x45
    NULL, //&LSR,				// 0x46
    &EOR,				// 0x47
    NULL, //&PHA,				// 0x48
    &EOR,				// 0x49
    NULL, //&LSR,				// 0x4A
    NULL, //&PHK,				// 0x4B
    &JMP,				// 0x4C
    &EOR,				// 0x4D
    NULL, //&LSR,				// 0x4E
    &EOR,				// 0x4F
    &BVC,				// 0x50
    &EOR,				// 0x51
    &EOR,				// 0x52
    &EOR,				// 0x53
    NULL, //&MVN,				// 0x54
    &EOR,				// 0x55
    NULL, //&LSR,				// 0x56
    &EOR,				// 0x57
    &CLI,				// 0x58
    &EOR,				// 0x59
    NULL, //&PHY,				// 0x5A
    NULL, //&TCD,				// 0x5B
    &JMP,				// 0x5C
    &EOR,				// 0x5D
    NULL, //&LSR,				// 0x5E
    &EOR,				// 0x5F
    NULL, //&RTS,				// 0x60
    &ADC,				// 0x61
    NULL, //&PER,				// 0x62
    &ADC,				// 0x63
    NULL, //&STZ,				// 0x64
    &ADC,				// 0x65
    NULL, //&ROR,				// 0x66
    &ADC,				// 0x67
    NULL, //&PLA,				// 0x68
    &ADC,				// 0x69
    NULL, //&ROR,				// 0x6A
    NULL, //&RTL,				// 0x6B
    &JMP,				// 0x6C
    &ADC,				// 0x6D
    NULL, //&ROR,				// 0x6E
    &ADC,				// 0x6F
    &BVS,				// 0x70
    &ADC,				// 0x71
    &ADC,				// 0x72
    &ADC,				// 0x73
    NULL, //&STZ,				// 0x74
    &ADC,				// 0x75
    NULL, //&ROR,				// 0x76
    &ADC,				// 0x77
    NULL, //&SEI,				// 0x78
    &ADC,				// 0x79
    NULL, //&PLY,				// 0x7A
    NULL, //&TDC,				// 0x7B
    &JMP,				// 0x7C
    &ADC,				// 0x7D
    NULL, //&ROR,				// 0x7E
    &ADC,				// 0x7F
    &BRA,				// 0x80
    NULL, //&STA,				// 0x81
   	&BRL,				// 0x82
    NULL, //&STA,				// 0x83
    NULL, //&STY,				// 0x84
    NULL, //&STA,				// 0x85
    NULL, //&STX,				// 0x86
    NULL, //&STA,				// 0x87
    &DEY,				// 0x88
    NULL, //&BIT,				// 0x89
    NULL, //&TXA,				// 0x8A
    NULL, //&PHB,				// 0x8B
    NULL, //&STY,				// 0x8C
    NULL, //&STA,				// 0x8D
    NULL, //&STX,				// 0x8E
    NULL, //&STA,				// 0x8F
    &BCC,				// 0x90
    NULL, //&STA,				// 0x91
    NULL, //&STA,				// 0x92
    NULL, //&STA,				// 0x93
    NULL, //&STY,				// 0x94
    NULL, //&STA,				// 0x95
    NULL, //&STX,				// 0x96
    NULL, //&STA,				// 0x97
    NULL, //&TYA,				// 0x98
    NULL, //&STA,				// 0x99
    NULL, //&TXS,				// 0x9A
    NULL, //&TXY,				// 0x9B
    NULL, //&STZ,				// 0x9C
    NULL, //&STA,				// 0x9D
    NULL, //&STZ,				// 0x9E
    NULL, //&STA,				// 0x9F
    &LDY,				// 0xA0
    &LDA,				// 0xA1
    &LDX,				// 0xA2
    &LDA,				// 0xA3
    &LDY,				// 0xA4
    &LDA,				// 0xA5
    &LDX,				// 0xA6
    &LDA,				// 0xA7
    NULL, //&TAY,				// 0xA8
    &LDA,				// 0xA9
    NULL, //&TAX,				// 0xAA
    NULL, //&PLB,				// 0xAB
    &LDY,				// 0xAC
    &LDA,				// 0xAD
    &LDX,				// 0xAE
    &LDA,				// 0xAF
    &BCS,				// 0xB0
    &LDA,				// 0xB1
    &LDA,				// 0xB2
    &LDA,				// 0xB3
    &LDY,				// 0xB4
    &LDA,				// 0xB5
    &LDX,				// 0xB6
    &LDA,				// 0xB7
    NULL, //&CLV,				// 0xB8
    &LDA,				// 0xB9
    NULL, //&TSX,				// 0xBA
    NULL, //&TYX,				// 0xBB
    &LDY,				// 0xBC
    &LDA,				// 0xBD
    &LDX,				// 0xBE
    &LDA,				// 0xBF
    &CPY,				// 0xC0
    &CMP,				// 0xC1
    NULL, //&REP,				// 0xC2
    &CMP,				// 0xC3
    &CPY,				// 0xC4
    &CMP,				// 0xC5
    &DEC,				// 0xC6
    &CMP,				// 0xC7
    &INY,				// 0xC8
    &CMP,				// 0xC9
    &DEX,				// 0xCA
    NULL, //&WAI,				// 0xCB
    &CPY,				// 0xCC
    &CMP,				// 0xCD
    &DEC,				// 0xCE
    &CMP,				// 0xCF
    &BNE,				// 0xD0
    &CMP,				// 0xD1
    &CMP,				// 0xD2
    &CMP,				// 0xD3
    &PEI,				// 0xD4
    &CMP,				// 0xD5
    &DEC,				// 0xD6
    &CMP,				// 0xD7
    &CLD,				// 0xD8
    &CMP,				// 0xD9
    NULL, //&PHX,				// 0xDA
    NULL, //&STP,				// 0xDB
    &JMP,				// 0xDC
    &CMP,				// 0xDD
    &DEC,				// 0xDE
    &CMP,				// 0xDF
    &CPX,				// 0xE0
    NULL, //&SBC,				// 0xE1
    NULL, //&SEP,				// 0xE2
    NULL, //&SBC,				// 0xE3
    &CPX,				// 0xE4
    NULL, //&SBC,				// 0xE5
    &INC,				// 0xE6
    NULL, //&SBC,				// 0xE7
    &INX,				// 0xE8
    NULL, //&SBC,				// 0xE9
    &NOP,				// 0xEA
    NULL, //&XBA,				// 0xEB
    &CPX,				// 0xEC
    NULL, //&SBC,				// 0xED
    &INC,				// 0xEE
    NULL, //&SBC,				// 0xEF
    &BEQ,				// 0xF0
    NULL, //&SBC,				// 0xF1
    NULL, //&SBC,				// 0xF2
    NULL, //&SBC,				// 0xF3
    &PEA,				// 0xF4
    NULL, //&SBC,				// 0xF5
    &INC,				// 0xF6
    NULL, //&SBC,				// 0xF7
    NULL, //&SED,				// 0xF8
    NULL, //&SBC,				// 0xF9
    NULL, //&PLX,				// 0xFA
    NULL, //&XCE,				// 0xFB
    &JSR,				// 0xFC
    NULL, //&SBC,				// 0xFD
    &INC,				// 0xFE
    NULL, //&SBC,				// 0xFF
}; 

void ADC(struct Registers* cpu, uint8_t* mem) {

	enum addrmode mode = modeMap[mem[cpu->PC]];
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);

	// If the accumulator/mem width is 16bit
	if(cpu -> P -> memWidth == 0) {

		uint16_t operand = mode == Immediate ? (uint16_t)effAddr : (uint16_t)mem[effAddr] | ((uint16_t)mem[effAddr + 1]) << 8;

		uint16_t accumulator = cpu->acc.C;


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

		uint8_t operand = mode == Immediate ? (uint8_t)effAddr : mem[effAddr];

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

void AND(struct Registers *cpu, uint8_t *mem){
	enum addrmode mode = modeMap[mem[cpu->PC]];
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	uint16_t operand = mode == Immediate ? (uint16_t)effAddr : (uint16_t)mem[effAddr] | ((uint16_t)mem[effAddr + 1]) << 8;

	// The procrssor is either in emulation mode or the memwidth is 8 bits
	if(cpu->P->emulation || cpu->P->memWidth){

		// Perform the and operation
		cpu->acc.split.A &= (uint8_t)operand;

		// Set/unset processor flags
		cpu->P->negative = cpu->acc.split.A & 0x80 ? 1 : 0;
	}

	// The processor is in native mode and memwidth for the accumulator is 16bit
	else{
		cpu->acc.C &= operand;
		cpu->P->negative = cpu->acc.C & 0x8000 ? 1 : 0;
	}

	cpu->P->zero = cpu->acc.split.A ? 0 : 1;
}

/**
 * ASL: Shift memory or accumulator left
 */
void ASL(struct Registers *cpu, uint8_t *mem){
	enum addrmode mode = modeMap[mem[cpu->PC]];
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);

	// If the mem/acc width is 16 bits
	if(!cpu->P->memWidth){
		
		// Either follows effaddr or takes the accumulator value from call
		uint16_t operand = mode == Accumulator ? (uint16_t)effAddr : (uint16_t)mem[effAddr] | ((uint16_t)mem[effAddr + 1]) << 8;

		// The leftmost bit becomes the carry flag
		cpu->P->carry = operand & 0x8000 ? 1 : 0;

		// Perform the left shift 
		operand <<= 1;

		// The negative flag is the leftmost bif after the shift
		cpu->P->negative = operand & 0x8000 ? 1 : 0;

		// The zero flag is set iff the result of the shift is 0
		cpu->P->zero = operand ? 0 : 1;

		// If it's shifting the accumulator, put the value back in the acc.
		if(mode == Accumulator){
			cpu->acc.C = operand;
		}

		// Otherwise, put the data back into memory
		else{
			mem[effAddr] = (uint8_t)(operand & 0x00FF);
			mem[effAddr + 1] = (uint8_t)(operand & 0xFF00 >> 8);
		}
	}
	else{
		uint8_t operand = mode == Accumulator ? (uint8_t)effAddr : mem[effAddr];

		cpu->P->carry = operand & 0x80 ? 1 : 0;

		operand <<= 1;

		cpu->P->negative = operand & 0x80 ? 1 : 0;

		// The zero flag is set iff the result of the shift is 0
		cpu->P->zero = operand ? 0 : 1;
		
		// If it's shifting the accumulator, put the value back in the acc.
		if(mode == Accumulator){
			cpu->acc.split.A = operand;
		}

		// Otherwise, put the data back into memory
		else{
			mem[effAddr] = operand;
		}

	}

}

void BCC(struct Registers *cpu, uint8_t *mem){
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	if(!cpu->P->carry){
		cpu->PC = (uint16_t)effAddr;
	}
}

void BCS(struct Registers *cpu, uint8_t *mem){
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	if(cpu->P->carry){
		cpu->PC = (uint16_t)effAddr;
	}
}

void BEQ(struct Registers *cpu, uint8_t *mem){
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	if(cpu->P->zero){
		cpu->PC = (uint16_t)effAddr;
	}
}

void BNE(struct Registers *cpu, uint8_t *mem){
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	if(!cpu->P->zero){
		cpu->PC = (uint16_t)effAddr;
	}
}

void BMI(struct Registers *cpu, uint8_t *mem){
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	if(cpu->P->negative){
		cpu->PC = (uint16_t)effAddr;
	}
}

void BRA(struct Registers *cpu, uint8_t *mem){
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	cpu->PC = (uint16_t)effAddr;
}

void JMP(struct Registers *cpu, uint8_t *mem){
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	cpu->PBR = effAddr >> 16;
	cpu->PC = effAddr & 0xFFFF;
}

void BRL(struct Registers *cpu, uint8_t *mem){
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	cpu->PC = (uint16_t)effAddr;
}

/**
 * BVC: Branch if overflow clear
 * Takes the offset given by the one byte operand iff the overflow bit in the
 * processor status register is clear.
 */
void BVC(struct Registers *cpu, uint8_t *mem){
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	if(!cpu->P->overflow){
		cpu->PC = (uint16_t)effAddr;
	}
}

/**
 * BVS: Branch if overflow is set
 * Takes the offset given by the one byte operand iff the overflow bit in the
 * processor status register is set.
 */
void BVS(struct Registers *cpu, uint8_t *mem){
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	if(cpu->P->overflow){
		cpu->PC = (uint16_t)effAddr;
	}
}

/**
 * CLC: Clear Carry Flag
 * Clears the carry flag in the processor status register
 */
void CLC(struct Registers *cpu, uint8_t *mem){

	// Moves the program counter past the instruction
	cpu->PC++;

	// Silence unused variable warning from compiler
	(void)mem;
	cpu->P->carry=0;
}

/**
 * CLD: Clear Decimal Mode Flag
 * Clears the decimal mode flag in the processor status register
 */
void CLD(struct Registers *cpu, uint8_t *mem){

	// Moves the program counter past the instruction
	cpu->PC++;

	// Silence unused variable warning from compiler
	(void)mem;
	cpu->P->deciMode=0;
}

/**
 * CLI: Clear Interrupt Disable Flag
 */
void CLI(struct Registers *cpu, uint8_t *mem){

	// Moves the program counter past the instruction
	cpu->PC++;

	// Silence unused variable warning from compiler
	(void)mem;
	cpu->P->irqDisable=0;
}

/**
 * CLV: Clear Overflow Flag
 */
void CLV(struct Registers *cpu, uint8_t *mem){

	// Moves the program counter past the instruction
	cpu->PC++;

	// Silence unused variable warning from compiler
	(void)mem;
	cpu->P->overflow=0;
}

/**
 * CMP: Compare Accumulator w Memory
 * Subtracts the data located at the effective addr (or provided by the operand
 * byte(s) if the immediate addressing mode version is used) from the contents
 * of the accumulator. The carry, zero, and negative flags are then set based on
 * the result of this subtraction. Neither the memory nor the accumulator is
 * changed. 
 */
void CMP(struct Registers *cpu, uint8_t *mem){
	enum addrmode mode = modeMap[mem[cpu->PC]];
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	
	// if the acc/mem width is 16 bit
	if(!cpu->P->memWidth){

		// Gets the operand whether it's in memory or it's the immediate
		uint16_t operand = mode == Immediate ? (uint16_t)effAddr : (uint16_t)mem[effAddr] | ((uint16_t)mem[effAddr + 1]) << 8;
		uint16_t accumulator = cpu->acc.C;

		// Sets the carry flag iff a borrow is required (acc >= operand)
		cpu->P->carry = accumulator >= operand ? 1 : 0;

		uint16_t result = accumulator - operand;

		// Sets the zero flag iff the result is 0. Cleared o/wise
		cpu->P->zero = result ? 0 : 1;

		// Sets the negative flag iff the high bit is set, cleared o/wise
		cpu->P->negative = result & 0x8000 ? 1 : 0;
	}
	
	// If the acc/mem width is 8 bit
	else{
		uint8_t accumulator = cpu->acc.split.A;
		uint8_t operand = mode == Immediate ? (uint8_t)effAddr : mem[effAddr];

		// Sets the carry flag iff a borrow is required (acc >= operand)
		cpu->P->carry = accumulator >= operand ? 1 : 0;

		uint8_t result = accumulator - operand;

		// Sets the zero flag iff the result is 0. Cleared o/wise
		cpu->P->zero = result ? 0 : 1;

		// Sets the negative flag iff the high bit is set, cleared o/wise
		cpu->P->negative = result & 0x80 ? 1 : 0;

	}
}

/**
 * CPX: Compare idx register X w/ Memory
 * Same as CMP but uses the X register instead of the accumulator. The flag that
 * switches between 8 and 16 bit is now the idxwidth(x) flag rather than the
 * mem/acc width(m) flag.
 */
void CPX(struct Registers *cpu, uint8_t *mem){
	enum addrmode mode = modeMap[mem[cpu->PC]];
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	
	// if the idx width is 16 bit
	if(!cpu->P->idxWidth){

		// Gets the operand whether it's in memory or it's the immediate
		uint16_t operand = mode == Immediate ? (uint16_t)effAddr : (uint16_t)mem[effAddr] | ((uint16_t)mem[effAddr + 1]) << 8;
		uint16_t index = cpu->X;

		// Sets the carry flag iff a borrow is required (acc >= operand)
		cpu->P->carry = index >= operand ? 1 : 0;

		uint16_t result = index - operand;

		// Sets the zero flag iff the result is 0. Cleared o/wise
		cpu->P->zero = result ? 0 : 1;

		// Sets the negative flag iff the high bit is set, cleared o/wise
		cpu->P->negative = result & 0x8000 ? 1 : 0;
	}
	
	// If the idx width is 8 bit
	else{
		uint8_t index = cpu->X & 0x00FF;
		uint8_t operand = mode == Immediate ? (uint8_t)effAddr : mem[effAddr];

		// Sets the carry flag iff a borrow is required (acc >= operand)
		cpu->P->carry = index >= operand ? 1 : 0;

		uint8_t result = index - operand;

		// Sets the zero flag iff the result is 0. Cleared o/wise
		cpu->P->zero = result ? 0 : 1;

		// Sets the negative flag iff the high bit is set, cleared o/wise
		cpu->P->negative = result & 0x80 ? 1 : 0;

	}
}

/**
 * CPY: Compare idx register Y w/ Memory
 * Same as CMP but uses the Y register instead of the accumulator. The flag that
 * switches between 8 and 16 bit is now the idxwidth(x) flag rather than the
 * mem/acc width(m) flag.
 */
void CPY(struct Registers *cpu, uint8_t *mem){
	enum addrmode mode = modeMap[mem[cpu->PC]];
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	
	// if the idx width is 16 bit
	if(!cpu->P->idxWidth){

		// Gets the operand whether it's in memory or it's the immediate
		uint16_t operand = mode == Immediate ? (uint16_t)effAddr : (uint16_t)mem[effAddr] | ((uint16_t)mem[effAddr + 1]) << 8;
		uint16_t index = cpu->Y;

		// Sets the carry flag iff a borrow is required (acc >= operand)
		cpu->P->carry = index >= operand ? 1 : 0;

		uint16_t result = index - operand;

		// Sets the zero flag iff the result is 0. Cleared o/wise
		cpu->P->zero = result ? 0 : 1;

		// Sets the negative flag iff the high bit is set, cleared o/wise
		cpu->P->negative = result & 0x8000 ? 1 : 0;
	}
	
	// If the idx width is 8 bit
	else{
		uint8_t index = cpu->Y & 0x00FF;
		uint8_t operand = mode == Immediate ? (uint8_t)effAddr : mem[effAddr];

		// Sets the carry flag iff a borrow is required (acc >= operand)
		cpu->P->carry = index >= operand ? 1 : 0;

		uint8_t result = index - operand;

		// Sets the zero flag iff the result is 0. Cleared o/wise
		cpu->P->zero = result ? 0 : 1;

		// Sets the negative flag iff the high bit is set, cleared o/wise
		cpu->P->negative = result & 0x80 ? 1 : 0;

	}
}

/**
 * DEC: Decrements either memory or the accumulator
 */
void DEC(struct Registers *cpu, uint8_t *mem){

	enum addrmode mode = modeMap[mem[cpu->PC]];
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);


	// If the mem/acc width is 16 bits
	if(!cpu->P->memWidth){
		uint16_t operand = mode == Accumulator ? (uint16_t)effAddr : (uint16_t)mem[effAddr] | ((uint16_t)mem[effAddr + 1]) << 8;

		// If it's just the accumulator
		if(mode == Accumulator){
			cpu->acc.C--;
			cpu->P->negative = cpu->acc.C & 0x8000 ? 1 : 0;
			cpu->P->zero = cpu->acc.C ? 0 : 1;
		}

		// If we got the value from mem, we need to put it back
		else{
			operand--;
			cpu->P->negative = operand & 0x8000 ? 1 : 0;
			cpu->P->zero = operand ? 0 : 1;
			mem[effAddr] = (uint8_t)(operand & 0x00FF);
			mem[effAddr + 1] = (uint8_t)(operand & 0xFF00 >> 8);
		}

	}
	else{

		uint8_t operand = mode == Accumulator ? (uint8_t)effAddr : mem[effAddr];

		// If it's just the accumulator
		if(mode == Accumulator){
			cpu->acc.split.A--;
			cpu->P->negative = cpu->acc.split.A & 0x80 ? 1 : 0;
			cpu->P->zero = cpu->acc.split.A ? 0 : 1;
		}

		// If we got the value from mem, we need to put it back
		else{
			operand--;
			cpu->P->negative = operand & 0x80 ? 1 : 0;
			cpu->P->zero = operand ? 0 : 1;
			mem[effAddr] = operand;
		}
	}
}
/**
 * DEX: Decrements the X register
 * Decrements the X register, doesn't affect the carry flag, and sets the z and
 * n flags accordingly to the end result of the X register
 */
void DEX(struct Registers *cpu, uint8_t *mem){

	// Moves the program counter 
	cpu->PC++;

	// Silence compiler warning
	(void)mem;

	// If the index width if 16 bit
	if(!cpu->P->idxWidth){
		cpu->X--;
	}
	else{
		// Extract low byte from X register
		uint8_t X = cpu->X & 0x00FF;
		
		// Clears the low byte from the X register
		cpu->X &= 0xFF00;

		// Decrement
		X--;

		// Replace the decremented X value
		cpu->X |= X;
	}

	// Sets the zero flag iff the bits affected are 0. The bit shift adjusts the
	// bits that are examined depending on whether or not the idxWidth is set or
	// not.
	cpu->P->zero = cpu->X & (0xFFFF >> 8*cpu->P->idxWidth) ? 0 : 1;

	// Sets the negative flag iff the most sig. bit (15 or 7 depending on
	// idxwidth) is set. Cleared o/wise
	cpu->P->negative = cpu->X & (0x8000 >> 8*cpu->P->idxWidth) ? 1 : 0;
}

/**
 * DEY: Decrements the Y register
 * Decrements the Y register, doesn't affect the carry flag, and sets the z and
 * n flags accordingly to the end result of the Y register
 */
void DEY(struct Registers *cpu, uint8_t *mem){

	// Moves the program counter 
	cpu->PC++;

	// Silence compiler warning
	(void)mem;

	// If the index width if 16 bit
	if(!cpu->P->idxWidth){
		cpu->Y--;
	}
	else{
		// Extract low byte from Y register
		uint8_t Y = cpu->Y & 0x00FF;
		
		// Clears the low byte from the Y register
		cpu->Y &= 0xFF00;

		// Decrement
		Y--;

		// Replace the decremented Y value
		cpu->Y |= Y;
	}

	// Sets the zero flag iff the bits affected are 0. The bit shift adjusts the
	// bits that are examined depending on whether or not the idxWidth is set or
	// not.
	cpu->P->zero = cpu->Y & (0xFFFF >> 8*cpu->P->idxWidth) ? 0 : 1;

	// Sets the negative flag iff the most sig. bit (15 or 7 depending on
	// idxwidth) is set. Cleared o/wise
	cpu->P->negative = cpu->Y & (0x8000 >> 8*cpu->P->idxWidth) ? 1 : 0;
}

/**
 * INC:Increments either memory or the accumulator
 */
void INC(struct Registers *cpu, uint8_t *mem){

	enum addrmode mode = modeMap[mem[cpu->PC]];
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);


	// If the mem/acc width is 16 bits
	if(!cpu->P->memWidth){
		uint16_t operand = mode == Accumulator ? (uint16_t)effAddr : (uint16_t)mem[effAddr] | ((uint16_t)mem[effAddr + 1]) << 8;

		// If it's just the accumulator
		if(mode == Accumulator){
			cpu->acc.C++;
			cpu->P->negative = cpu->acc.C & 0x8000 ? 1 : 0;
			cpu->P->zero = cpu->acc.C ? 0 : 1;
		}

		// If we got the value from mem, we need to put it back
		else{
			operand++;
			cpu->P->negative = operand & 0x8000 ? 1 : 0;
			cpu->P->zero = operand ? 0 : 1;
			mem[effAddr] = (uint8_t)(operand & 0x00FF);
			mem[effAddr + 1] = (uint8_t)(operand & 0xFF00 >> 8);
		}

	}
	else{

		uint8_t operand = mode == Accumulator ? (uint8_t)effAddr : mem[effAddr];

		// If it's just the accumulator
		if(mode == Accumulator){
			cpu->acc.split.A++;
			cpu->P->negative = cpu->acc.split.A & 0x80 ? 1 : 0;
			cpu->P->zero = cpu->acc.split.A ? 0 : 1;
		}

		// If we got the value from mem, we need to put it back
		else{
			operand++;
			cpu->P->negative = operand & 0x80 ? 1 : 0;
			cpu->P->zero = operand ? 0 : 1;
			mem[effAddr] = operand;
		}
	}
}

/**
 * INX: Increments the X register
 * Increments the X register, doesn't affect the carry flag, and sets the z and
 * n flags accordingly to the end result of the X register
 */
void INX(struct Registers *cpu, uint8_t *mem){

	// Moves the program counter 
	cpu->PC++;

	// Silence compiler warning
	(void)mem;

	// If the index width if 16 bit
	if(!cpu->P->idxWidth){
		cpu->X++;
	}
	else{
		// Extract low byte from X register
		uint8_t X = cpu->X & 0x00FF;
		
		// Clears the low byte from the X register
		cpu->X &= 0xFF00;

		// Decrement
		X++;

		// Replace the decremented X value
		cpu->X |= X;
	}

	// Sets the zero flag iff the bits affected are 0. The bit shift adjusts the
	// bits that are examined depending on whether or not the idxWidth is set or
	// not.
	cpu->P->zero = cpu->X & (0xFFFF >> 8*cpu->P->idxWidth) ? 0 : 1;

	// Sets the negative flag iff the most sig. bit (15 or 7 depending on
	// idxwidth) is set. Cleared o/wise
	cpu->P->negative = cpu->X & (0x8000 >> 8*cpu->P->idxWidth) ? 1 : 0;
}

/**
 * INY: Increments the Y register
 * Increments the Y register, doesn't affect the carry flag, and sets the z and
 * n flags accordingly to the end result of the Y register
 */
void INY(struct Registers *cpu, uint8_t *mem){

	// Moves the program counter 
	cpu->PC++;

	// Silence compiler warning
	(void)mem;

	// If the index width if 16 bit
	if(!cpu->P->idxWidth){
		cpu->Y++;
	}
	else{
		// Extract low byte from Y register
		uint8_t Y = cpu->Y & 0x00FF;
		
		// Clears the low byte from the Y register
		cpu->Y &= 0xFF00;

		// Decrement
		Y++;

		// Replace the decremented Y value
		cpu->Y |= Y;
	}

	// Sets the zero flag iff the bits affected are 0. The bit shift adjusts the
	// bits that are examined depending on whether or not the idxWidth is set or
	// not.
	cpu->P->zero = cpu->Y & (0xFFFF >> 8*cpu->P->idxWidth) ? 0 : 1;

	// Sets the negative flag iff the most sig. bit (15 or 7 depending on
	// idxwidth) is set. Cleared o/wise
	cpu->P->negative = cpu->Y & (0x8000 >> 8*cpu->P->idxWidth) ? 1 : 0;
}


/**
 * Exclusive ors the operand and the accumulator
 */
void EOR(struct Registers *cpu, uint8_t *mem){
	enum addrmode mode = modeMap[mem[cpu->PC]];
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	uint16_t operand = mode == Immediate ? (uint16_t)effAddr : (uint16_t)mem[effAddr] | ((uint16_t)mem[effAddr + 1]) << 8;

	// The procrssor is either in emulation mode or the memwidth is 8 bits
	if(cpu->P->emulation || cpu->P->memWidth){

		// Perform the and operation
		cpu->acc.split.A ^= (uint8_t)operand;

		// Set/unset processor flags
		cpu->P->negative = cpu->acc.split.A & 0x80 ? 1 : 0;
	}

	// The processor is in native mode and memwidth for the accumulator is 16bit
	else{
		cpu->acc.C ^= operand;
		cpu->P->negative = cpu->acc.C & 0x8000 ? 1 : 0;
	}

	cpu->P->zero = cpu->acc.split.A ? 0 : 1;
}
/**
 * JSL: Jump to subroutine long (inter-bank)
 *
 * Pushes the 24 bit program counter and PBR of the next instruction - 1 onto
 * the stack, adjusting the stack pointer as each byte is pushed. Then the new
 * PBR and PC are loaded into the cpu and control is transferred.
 */
void JSL(struct Registers *cpu, uint8_t *mem){

	// Retrieves the jump destination
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);

	// Put the return addr onto the stack
	mem[cpu->SP--] = cpu->PBR;
	mem[cpu->SP--] = (uint8_t)((cpu->PC - 1) >> 8);
	mem[cpu->SP--] = (uint8_t)((cpu->PC - 1) & 0x00FF);


	cpu->PBR = (uint8_t)(effAddr >> 16);
	cpu->PC = (uint16_t)(effAddr & 0x00FFFF);
}

/**
 * JSR: Jump to subroutine
 * Pushes the return addr (the addr of the next instruction - 1) onto the stack
 * and then transfers control to the operand bytes
 */
void JSR(struct Registers *cpu, uint8_t *mem){
	
	// Retrieves the jump destination
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);

	// Put the return addr onto the stack
	mem[cpu->SP--] = (uint8_t)((cpu->PC - 1) >> 8);
	mem[cpu->SP--] = (uint8_t)((cpu->PC - 1) & 0x00FF);

	cpu->PC = (uint16_t)(effAddr & 0x00FFFF);
}

/**
 * LDA: Load accumulator from memory (or immediate)
 *
 * Flags affected: n_____z_
 */
void LDA(struct Registers *cpu, uint8_t *mem){
	enum addrmode mode = modeMap[mem[cpu->PC]];
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	uint16_t operand = mode == Immediate ? (uint16_t)effAddr : (uint16_t)mem[effAddr] | ((uint16_t)mem[effAddr + 1]) << 8;

	// If the mem/acc width is 16bit
	if(!cpu->P->memWidth){
		cpu->acc.C = operand;
		cpu->P->zero = operand ? 0 : 1;
		cpu->P->negative = operand & 0x8000 ? 1 : 0;
	}

	// If the mem/acc width is 8bit
	else{
		cpu->acc.split.A = (uint8_t)operand;
		cpu->P->zero = (uint8_t)operand ? 0 : 1;
		cpu->P->negative = operand & 0x0080 ? 1 : 0;
	}

}

/**
 * LDX: Load X register from memory (or immediate)
 *
 * Flags affected: n_____z_
 */
void LDX(struct Registers *cpu, uint8_t *mem){
	enum addrmode mode = modeMap[mem[cpu->PC]];
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	uint16_t operand = mode == Immediate ? (uint16_t)effAddr : (uint16_t)mem[effAddr] | ((uint16_t)mem[effAddr + 1]) << 8;

	// If the index width is 16bit
	if(!cpu->P->idxWidth){
		cpu->X = operand;
		cpu->P->zero = operand ? 0 : 1;
		cpu->P->negative = operand & 0x8000 ? 1 : 0;
	}

	// If the index width is 8bit
	else{
		
		// Clear the lower byte of X
		cpu->X &= 0xFF00; 

		// Put the lower byte of the operand into the lower byte of X
		cpu->X |= (uint8_t)operand;
		cpu->P->zero = (uint8_t)operand ? 0 : 1;
		cpu->P->negative = operand & 0x0080 ? 1 : 0;
	}

}

/**
 * LDY: Load Y register from memory (or immediate)
 *
 * Flags affected: n_____z_
 */
void LDY(struct Registers *cpu, uint8_t *mem){
	enum addrmode mode = modeMap[mem[cpu->PC]];
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	uint16_t operand = mode == Immediate ? (uint16_t)effAddr : (uint16_t)mem[effAddr] | ((uint16_t)mem[effAddr + 1]) << 8;

	// If the index width is 16bit
	if(!cpu->P->idxWidth){
		cpu->Y = operand;
		cpu->P->zero = operand ? 0 : 1;
		cpu->P->negative = operand & 0x8000 ? 1 : 0;
	}

	// If the index width is 8bit
	else{
		
		// Clear the lower byte of Y
		cpu->Y &= 0xFF00; 

		// Put the lower byte of the operand into the lower byte of Y
		cpu->Y |= (uint8_t)operand;
		cpu->P->zero = (uint8_t)operand ? 0 : 1;
		cpu->P->negative = operand & 0x0080 ? 1 : 0;
	}

}

/**
 * Ors the operand and the accumulator
 */
void ORA(struct Registers *cpu, uint8_t *mem){
	enum addrmode mode = modeMap[mem[cpu->PC]];
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	uint16_t operand = mode == Immediate ? (uint16_t)effAddr : (uint16_t)mem[effAddr] | ((uint16_t)mem[effAddr + 1]) << 8;

	// The procrssor is either in emulation mode or the memwidth is 8 bits
	if(cpu->P->emulation || cpu->P->memWidth){

		// Perform the and operation
		cpu->acc.split.A |= (uint8_t)operand;

		// Set/unset processor flags
		cpu->P->negative = cpu->acc.split.A & 0x80 ? 1 : 0;
	}

	// The processor is in native mode and memwidth for the accumulator is 16bit
	else{
		cpu->acc.C |= operand;
		cpu->P->negative = cpu->acc.C & 0x8000 ? 1 : 0;
	}

	cpu->P->zero = cpu->acc.split.A ? 0 : 1;
}

/**
 * No operation takes plac, program counter is simply incremented
 */
void NOP(struct Registers *cpu, uint8_t *mem){
	cpu->PC++;
	(void)mem;
}

/**
 * PEA: Push Effective Absolute Address
 *
 * Pushes the 16 bit operand onto the stack, regardless of the m and x flags.
 */
void PEA(struct Registers *cpu, uint8_t *mem){
	uint16_t effAddr = (uint16_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	mem[cpu->SP--] = (uint8_t)(effAddr >> 8);
	mem[cpu->SP--] = (uint8_t)effAddr;
}

/**
 * PEI: Push effective Indirect Address
 *
 * Pushes the 16 bit value located at the address formed by adding the one byte
 * operand to the direct page register.
 */
void PEI(struct Registers *cpu, uint8_t *mem){
	uint32_t effAddr = (uint32_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);

	// Pushes the high byte
	mem[cpu->SP--] = mem[effAddr + 1];

	// Pushes the low byte
	mem[cpu->SP--] = mem[effAddr];
}


/**
 * PER: Push Effective PC Relative Indirect Address
 *
 * Pushes the sum of the current PC and the 16 bit operand onto the stack
 */
void PER(struct Registers *cpu, uint8_t *mem){
	uint16_t effAddr = (uint16_t)getEffectiveAddress(cpu, mem[cpu->PC++], mem);
	mem[cpu->SP--] = (uint8_t)(effAddr >> 8);
	mem[cpu->SP--] = (uint8_t)effAddr;
}


/**
 * PHA: Push Accumulator
 *
 * Pushes the accumulator onto the stack. Number of bytes pushed depends on the
 * mem width flag.
 */
void PHA(struct Registers *cpu, uint8_t *mem){

	// The high byte of the accumulator is only pushed when memWidth is 0
	if(!cpu->P->memWidth){
		mem[cpu->PC--] = cpu->acc.split.B;
	}

	// The low byte is always pushed
	mem[cpu->PC--] = cpu->acc.split.A;
}
