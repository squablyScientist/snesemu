#include "cpu.h"
#include "instructions.h"
#include "opcode.h"

void (*instJmpTab[])(struct Registers *cpu, uint8_t *mem) = {
    NULL, //&BRK,				// 0x00
    NULL, //&ORA,				// 0x01
    NULL, //&COP,				// 0x02
    NULL, //&ORA,				// 0x03
    NULL, //&TSB,				// 0x04
    NULL, //&ORA,				// 0x05
    NULL, //&ASL,				// 0x06
    NULL, //&ORA,				// 0x07
    NULL, //&PHP,				// 0x08
    NULL, //&ORA,				// 0x09
    NULL, //&ASL,				// 0x0A
    NULL, //&PHD,				// 0x0B
    NULL, //&TSB,				// 0x0C
    NULL, //&ORA,				// 0x0D
    NULL, //&ASL,				// 0x0E
    NULL, //&ORA,				// 0x0F
    NULL, //&BPL,				// 0x10
    NULL, //&ORA,				// 0x11
    NULL, //&ORA,				// 0x12
    NULL, //&ORA,				// 0x13
    NULL, //&TRB,				// 0x14
    NULL, //&ORA,				// 0x15
    NULL, //&ASL,				// 0x16
    NULL, //&ORA,				// 0x17
    NULL, //&CLC,				// 0x18
    NULL, //&ORA,				// 0x19
    NULL, //&INC,				// 0x1A
    NULL, //&TCS,				// 0x1B
    NULL, //&TRB,				// 0x1C
    NULL, //&ORA,				// 0x1D
    NULL, //&ASL,				// 0x1E
    NULL, //&ORA,				// 0x1F
    NULL, //&JSR,				// 0x20
    NULL, //&AND,				// 0x21
    NULL, //&JSR,				// 0x22
    NULL, //&AND,				// 0x23
    NULL, //&BIT,				// 0x24
    NULL, //&AND,				// 0x25
    NULL, //&ROL,				// 0x26
    NULL, //&AND,				// 0x27
    NULL, //&PLP,				// 0x28
    NULL, //&AND,				// 0x29
    NULL, //&ROL,				// 0x2A
    NULL, //&PLD,				// 0x2B
    NULL, //&BIT,				// 0x2C
    NULL, //&AND,				// 0x2D
    NULL, //&ROL,				// 0x2E
    NULL, //&AND,				// 0x2F
    &BMI,				// 0x30
    NULL, //&AND,				// 0x31
    NULL, //&AND,				// 0x32
    NULL, //&AND,				// 0x33
    NULL, //&BIT,				// 0x34
    NULL, //&AND,				// 0x35
    NULL, //&ROL,				// 0x36
    NULL, //&AND,				// 0x37
    NULL, //&SEC,				// 0x38
    NULL, //&AND,				// 0x39
    NULL, //&DEC,				// 0x3A
    NULL, //&TSC,				// 0x3B
    NULL, //&BIT,				// 0x3C
    NULL, //&AND,				// 0x3D
    NULL, //&ROL,				// 0x3E
    NULL, //&AND,				// 0x3F
    NULL, //&RTI,				// 0x40
    NULL, //&EOR,				// 0x41
    NULL, //&WDM,				// 0x42
    NULL, //&EOR,				// 0x43
    NULL, //&MVP,				// 0x44
    NULL, //&EOR,				// 0x45
    NULL, //&LSR,				// 0x46
    NULL, //&EOR,				// 0x47
    NULL, //&PHA,				// 0x48
    NULL, //&EOR,				// 0x49
    NULL, //&LSR,				// 0x4A
    NULL, //&PHK,				// 0x4B
    &JMP,				// 0x4C
    NULL, //&EOR,				// 0x4D
    NULL, //&LSR,				// 0x4E
    NULL, //&EOR,				// 0x4F
    NULL, //&BVC,				// 0x50
    NULL, //&EOR,				// 0x51
    NULL, //&EOR,				// 0x52
    NULL, //&EOR,				// 0x53
    NULL, //&MVN,				// 0x54
    NULL, //&EOR,				// 0x55
    NULL, //&LSR,				// 0x56
    NULL, //&EOR,				// 0x57
    NULL, //&CLI,				// 0x58
    NULL, //&EOR,				// 0x59
    NULL, //&PHY,				// 0x5A
    NULL, //&TCD,				// 0x5B
    &JMP,				// 0x5C
    NULL, //&EOR,				// 0x5D
    NULL, //&LSR,				// 0x5E
    NULL, //&EOR,				// 0x5F
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
    NULL, //&BVS,				// 0x70
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
    NULL, //&DEY,				// 0x88
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
    NULL, //&LDY,				// 0xA0
    NULL, //&LDA,				// 0xA1
    NULL, //&LDX,				// 0xA2
    NULL, //&LDA,				// 0xA3
    NULL, //&LDY,				// 0xA4
    NULL, //&LDA,				// 0xA5
    NULL, //&LDX,				// 0xA6
    NULL, //&LDA,				// 0xA7
    NULL, //&TAY,				// 0xA8
    NULL, //&LDA,				// 0xA9
    NULL, //&TAX,				// 0xAA
    NULL, //&PLB,				// 0xAB
    NULL, //&LDY,				// 0xAC
    NULL, //&LDA,				// 0xAD
    NULL, //&LDX,				// 0xAE
    NULL, //&LDA,				// 0xAF
    &BCS,				// 0xB0
    NULL, //&LDA,				// 0xB1
    NULL, //&LDA,				// 0xB2
    NULL, //&LDA,				// 0xB3
    NULL, //&LDY,				// 0xB4
    NULL, //&LDA,				// 0xB5
    NULL, //&LDX,				// 0xB6
    NULL, //&LDA,				// 0xB7
    NULL, //&CLV,				// 0xB8
    NULL, //&LDA,				// 0xB9
    NULL, //&TSX,				// 0xBA
    NULL, //&TYX,				// 0xBB
    NULL, //&LDY,				// 0xBC
    NULL, //&LDA,				// 0xBD
    NULL, //&LDX,				// 0xBE
    NULL, //&LDA,				// 0xBF
    NULL, //&CPY,				// 0xC0
    NULL, //&CMP,				// 0xC1
    NULL, //&REP,				// 0xC2
    NULL, //&CMP,				// 0xC3
    NULL, //&CPY,				// 0xC4
    NULL, //&CMP,				// 0xC5
    NULL, //&DEC,				// 0xC6
    NULL, //&CMP,				// 0xC7
    NULL, //&INY,				// 0xC8
    NULL, //&CMP,				// 0xC9
    NULL, //&DEX,				// 0xCA
    NULL, //&WAI,				// 0xCB
    NULL, //&CPY,				// 0xCC
    NULL, //&CMP,				// 0xCD
    NULL, //&DEC,				// 0xCE
    NULL, //&CMP,				// 0xCF
    &BNE,				// 0xD0
    NULL, //&CMP,				// 0xD1
    NULL, //&CMP,				// 0xD2
    NULL, //&CMP,				// 0xD3
    NULL, //&PEI,				// 0xD4
    NULL, //&CMP,				// 0xD5
    NULL, //&DEC,				// 0xD6
    NULL, //&CMP,				// 0xD7
    NULL, //&CLD,				// 0xD8
    NULL, //&CMP,				// 0xD9
    NULL, //&PHX,				// 0xDA
    NULL, //&STP,				// 0xDB
    &JMP,				// 0xDC
    NULL, //&CMP,				// 0xDD
    NULL, //&DEC,				// 0xDE
    NULL, //&CMP,				// 0xDF
    NULL, //&CPX,				// 0xE0
    NULL, //&SBC,				// 0xE1
    NULL, //&SEP,				// 0xE2
    NULL, //&SBC,				// 0xE3
    NULL, //&CPX,				// 0xE4
    NULL, //&SBC,				// 0xE5
    NULL, //&INC,				// 0xE6
    NULL, //&SBC,				// 0xE7
    NULL, //&INX,				// 0xE8
    NULL, //&SBC,				// 0xE9
    NULL, //&NOP,				// 0xEA
    NULL, //&XBA,				// 0xEB
    NULL, //&CPX,				// 0xEC
    NULL, //&SBC,				// 0xED
    NULL, //&INC,				// 0xEE
    NULL, //&SBC,				// 0xEF
    &BEQ,				// 0xF0
    NULL, //&SBC,				// 0xF1
    NULL, //&SBC,				// 0xF2
    NULL, //&SBC,				// 0xF3
    NULL, //&PEA,				// 0xF4
    NULL, //&SBC,				// 0xF5
    NULL, //&INC,				// 0xF6
    NULL, //&SBC,				// 0xF7
    NULL, //&SED,				// 0xF8
    NULL, //&SBC,				// 0xF9
    NULL, //&PLX,				// 0xFA
    NULL, //&XCE,				// 0xFB
    NULL, //&JSR,				// 0xFC
    NULL, //&SBC,				// 0xFD
    NULL, //&INC,				// 0xFE
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
