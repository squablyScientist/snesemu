#include <stdlib.h>
#include "opcode.h"

// Map of opcode -> addrMode. Access it with the opcode as the idx.
const enum addrmode modeMap[] = {
    Interrupt,                              // 0x00: BRK
    DirectPageIndexedIndirectWithX,         // 0x01: ORA
    Interrupt,                              // 0x02: COP
    StackRelative,                          // 0x03: ORA
    DirectPage,                             // 0x04: TSB
    DirectPage,                             // 0x05: ORA
    DirectPage,                             // 0x06: ASL
    DirectPageIndirectLong,                 // 0x07: ORA
    StackImplied,                           // 0x08: PHP
    Immediate,                              // 0x09: ORA
    Accumulator,                            // 0x0A: ASL
    StackImplied,                           // 0x0B: PHD
    Absolute,                               // 0x0C: TSB
    Absolute,                               // 0x0D: ORA
    Absolute,                               // 0x0E: ASL
    AbsoluteLong,                           // 0x0F: ORA
    ProgramCounterRelative,                 // 0x10: BPL
    DirectPageIndirectIndexedWithY,         // 0x11: ORA
    DirectPageIndirect,                     // 0x12: ORA
    StackRelativeIndirectIndexedWithY,      // 0x13: ORA
    DirectPage,                             // 0x14: TRB
    DirectPageIndexedWithX,                 // 0x15: ORA
    DirectPageIndexedWithX,                 // 0x16: ASL
    DirectPageIndirectLongIndexedWithY,     // 0x17: ORA
    Implied,                                // 0x18: CLC
    AbsoluteIndexedWithY,                   // 0x19: ORA
    Accumulator,                            // 0x1A: INC
    Implied,                                // 0x1B: TCS
    Absolute,                               // 0x1C: TRB
    AbsoluteIndexedWithX,                   // 0x1D: ORA
    AbsoluteIndexedWithX,                   // 0x1E: ASL
    AbsoluteLongIndexedWithX,               // 0x1F: ORA
    Absolute,                               // 0x20: JSR
    DirectPageIndexedIndirectWithX,         // 0x21: AND
    AbsoluteLong,                           // 0x22: JSR
    StackRelative,                          // 0x23: AND
    DirectPage,                             // 0x24: BIT
    DirectPage,                             // 0x25: AND
    DirectPage,                             // 0x26: ROL
    DirectPageIndirectLong,                 // 0x27: AND
    StackImplied,                           // 0x28: PLP
    Immediate,                              // 0x29: AND
    Accumulator,                            // 0x2A: ROL
    StackImplied,                           // 0x2B: PLD
    Absolute,                               // 0x2C: BIT
    Absolute,                               // 0x2D: AND
    Absolute,                               // 0x2E: ROL
    AbsoluteLong,                           // 0x2F: AND
    ProgramCounterRelative,                 // 0x30: BMI
    DirectPageIndirectIndexedWithY,         // 0x31: AND
    DirectPageIndirect,                     // 0x32: AND
    StackRelativeIndirectIndexedWithY,      // 0x33: AND
    DirectPageIndexedWithX,                 // 0x34: BIT
    DirectPageIndexedWithX,                 // 0x35: AND
    DirectPageIndexedWithX,                 // 0x36: ROL
    DirectPageIndirectLongIndexedWithY,     // 0x37: AND
    Implied,                                // 0x38: SEC
    AbsoluteIndexedWithY,                   // 0x39: AND
    Accumulator,                            // 0x3A: DEC
    Implied,                                // 0x3B: TSC
    AbsoluteIndexedWithX,                   // 0x3C: BIT
    AbsoluteIndexedWithX,                   // 0x3D: AND
    AbsoluteIndexedWithX,                   // 0x3E: ROL
    AbsoluteLongIndexedWithX,               // 0x3F: AND
    StackImplied,                           // 0x40: RTI
    DirectPageIndexedIndirectWithX,         // 0x41: EOR
    Implied,                                // 0x42: WDM
    StackRelative,                          // 0x43: EOR
    BlockMove,                              // 0x44: MVP
    DirectPage,                             // 0x45: EOR
    DirectPage,                             // 0x46: LSR
    DirectPageIndirectLong,                 // 0x47: EOR
    StackImplied,                           // 0x48: PHA
    Immediate,                              // 0x49: EOR
    Accumulator,                            // 0x4A: LSR
    StackImplied,                           // 0x4B: PHK
    Absolute,                               // 0x4C: JMP
    Absolute,                               // 0x4D: EOR
    Absolute,                               // 0x4E: LSR
    AbsoluteLong,                           // 0x4F: EOR
    ProgramCounterRelative,                 // 0x50: BVC
    DirectPageIndirectIndexedWithY,         // 0x51: EOR
    DirectPageIndirect,                     // 0x52: EOR
    StackRelativeIndirectIndexedWithY,      // 0x53: EOR
    BlockMove,                              // 0x54: MVN
    DirectPageIndexedWithX,                 // 0x55: EOR
    DirectPageIndexedWithX,                 // 0x56: LSR
    DirectPageIndirectLongIndexedWithY,     // 0x57: EOR
    Implied,                                // 0x58: CLI
    AbsoluteIndexedWithY,                   // 0x59: EOR
    StackImplied,                           // 0x5A: PHY
    Implied,                                // 0x5B: TCD
    AbsoluteLong,                           // 0x5C: JMP
    AbsoluteIndexedWithX,                   // 0x5D: EOR
    AbsoluteIndexedWithX,                   // 0x5E: LSR
    AbsoluteLongIndexedWithX,               // 0x5F: EOR
    StackImplied,                           // 0x60: RTS
    DirectPageIndexedIndirectWithX,         // 0x61: ADC
    StackProgramCounterRelativeLong,        // 0x62: PER
    StackRelative,                          // 0x63: ADC
    DirectPage,                             // 0x64: STZ
    DirectPage,                             // 0x65: ADC
    DirectPage,                             // 0x66: ROR
    DirectPageIndirectLong,                 // 0x67: ADC
    StackImplied,                           // 0x68: PLA
    Immediate,                              // 0x69: ADC
    Accumulator,                            // 0x6A: ROR
    StackImplied,                           // 0x6B: RTL
    AbsoluteIndirect,                       // 0x6C: JMP
    Absolute,                               // 0x6D: ADC
    Absolute,                               // 0x6E: ROR
    AbsoluteLong,                           // 0x6F: ADC
    ProgramCounterRelative,                 // 0x70: BVS
    DirectPageIndirectIndexedWithY,         // 0x71: ADC
    DirectPageIndirect,                     // 0x72: ADC
    StackRelativeIndirectIndexedWithY,      // 0x73: ADC
    DirectPageIndexedWithX,                 // 0x74: STZ
    DirectPageIndexedWithX,                 // 0x75: ADC
    DirectPageIndexedWithX,                 // 0x76: ROR
    DirectPageIndirectLongIndexedWithY,     // 0x77: ADC
    Implied,                                // 0x78: SEI
    AbsoluteIndexedWithY,                   // 0x79: ADC
    StackImplied,                           // 0x7A: PLY
    Implied,                                // 0x7B: TDC
    AbsoluteIndexedIndirectWithX,           // 0x7C: JMP
    AbsoluteIndexedWithX,                   // 0x7D: ADC
    AbsoluteIndexedWithX,                   // 0x7E: ROR
    AbsoluteLongIndexedWithX,               // 0x7F: ADC
    ProgramCounterRelative,                 // 0x80: BRA
    DirectPageIndexedIndirectWithX,         // 0x81: STA
    ProgramCounterRelativeLong,             // 0x82: BRL
    StackRelative,                          // 0x83: STA
    DirectPage,                             // 0x84: STY
    DirectPage,                             // 0x85: STA
    DirectPage,                             // 0x86: STX
    DirectPageIndirectLong,                 // 0x87: STA
    Implied,                                // 0x88: DEY
    Immediate,                              // 0x89: BIT
    Implied,                                // 0x8A: TXA
    StackImplied,                           // 0x8B: PHB
    Absolute,                               // 0x8C: STY
    Absolute,                               // 0x8D: STA
    Absolute,                               // 0x8E: STX
    AbsoluteLong,                           // 0x8F: STA
    ProgramCounterRelative,                 // 0x90: BCC
    DirectPageIndirectIndexedWithY,         // 0x91: STA
    DirectPageIndirect,                     // 0x92: STA
    StackRelativeIndirectIndexedWithY,      // 0x93: STA
    DirectPageIndexedWithX,                 // 0x94: STY
    DirectPageIndexedWithX,                 // 0x95: STA
    DirectPageIndexedWithY,                 // 0x96: STX
    DirectPageIndirectLongIndexedWithY,     // 0x97: STA
    Implied,                                // 0x98: TYA
    AbsoluteIndexedWithY,                   // 0x99: STA
    Implied,                                // 0x9A: TXS
    Implied,                                // 0x9B: TXY
    Absolute,                               // 0x9C: STZ
    AbsoluteIndexedWithX,                   // 0x9D: STA
    AbsoluteIndexedWithX,                   // 0x9E: STZ
    AbsoluteLongIndexedWithX,               // 0x9F: STA
    Immediate,                              // 0xA0: LDY
    DirectPageIndexedIndirectWithX,         // 0xA1: LDA
    Immediate,                              // 0xA2: LDX
    StackRelative,                          // 0xA3: LDA
    DirectPage,                             // 0xA4: LDY
    DirectPage,                             // 0xA5: LDA
    DirectPage,                             // 0xA6: LDX
    DirectPageIndirectLong,                 // 0xA7: LDA
    Implied,                                // 0xA8: TAY
    Immediate,                              // 0xA9: LDA
    Implied,                                // 0xAA: TAX
    StackImplied,                           // 0xAB: PLB
    Absolute,                               // 0xAC: LDY
    Absolute,                               // 0xAD: LDA
    Absolute,                               // 0xAE: LDX
    AbsoluteLong,                           // 0xAF: LDA
    ProgramCounterRelative,                 // 0xB0: BCS
    DirectPageIndirectIndexedWithY,         // 0xB1: LDA
    DirectPageIndirect,                     // 0xB2: LDA
    StackRelativeIndirectIndexedWithY,      // 0xB3: LDA
    DirectPageIndexedWithX,                 // 0xB4: LDY
    DirectPageIndexedWithX,                 // 0xB5: LDA
    DirectPageIndexedWithY,                 // 0xB6: LDX
    DirectPageIndirectLongIndexedWithY,     // 0xB7: LDA
    Implied,                                // 0xB8: CLV
    AbsoluteIndexedWithY,                   // 0xB9: LDA
    Implied,                                // 0xBA: TSX
    Implied,                                // 0xBB: TYX
    AbsoluteIndexedWithX,                   // 0xBC: LDY
    AbsoluteIndexedWithX,                   // 0xBD: LDA
    AbsoluteIndexedWithY,                   // 0xBE: LDX
    AbsoluteLongIndexedWithX,               // 0xBF: LDA
    Immediate,                              // 0xC0: CPY
    DirectPageIndexedIndirectWithX,         // 0xC1: CMP
    Immediate,                              // 0xC2: REP
    StackRelative,                          // 0xC3: CMP
    DirectPage,                             // 0xC4: CPY
    DirectPage,                             // 0xC5: CMP
    DirectPage,                             // 0xC6: DEC
    DirectPageIndirectLong,                 // 0xC7: CMP
    Implied,                                // 0xC8: INY
    Immediate,                              // 0xC9: CMP
    Implied,                                // 0xCA: DEX
    Implied,                                // 0xCB: WAI
    Absolute,                               // 0xCC: CPY
    Absolute,                               // 0xCD: CMP
    Absolute,                               // 0xCE: DEC
    AbsoluteLong,                           // 0xCF: CMP
    ProgramCounterRelative,                 // 0xD0: BNE
    DirectPageIndirectIndexedWithY,         // 0xD1: CMP
    DirectPageIndirect,                     // 0xD2: CMP
    StackRelativeIndirectIndexedWithY,      // 0xD3: CMP
    StackDirectPageIndirect,                // 0xD4: PEI
    DirectPageIndexedWithX,                 // 0xD5: CMP
    DirectPageIndexedWithX,                 // 0xD6: DEC
    DirectPageIndirectLongIndexedWithY,     // 0xD7: CMP
    Implied,                                // 0xD8: CLD
    AbsoluteIndexedWithY,                   // 0xD9: CMP
    StackImplied,                           // 0xDA: PHX
    Implied,                                // 0xDB: STP
    AbsoluteIndirectLong,                   // 0xDC: JMP
    AbsoluteIndexedWithX,                   // 0xDD: CMP
    AbsoluteIndexedWithX,                   // 0xDE: DEC
    AbsoluteLongIndexedWithX,               // 0xDF: CMP
    Immediate,                              // 0xE0: CPX
    DirectPageIndexedIndirectWithX,         // 0xE1: SBC
    Immediate,                              // 0xE2: SEP
    StackRelative,                          // 0xE3: SBC
    DirectPage,                             // 0xE4: CPX
    DirectPage,                             // 0xE5: SBC
    DirectPage,                             // 0xE6: INC
    DirectPageIndirectLong,                 // 0xE7: SBC
    Implied,                                // 0xE8: INX
    Immediate,                              // 0xE9: SBC
    Implied,                                // 0xEA: NOP
    Implied,                                // 0xEB: XBA
    Absolute,                               // 0xEC: CPX
    Absolute,                               // 0xED: SBC
    Absolute,                               // 0xEE: INC
    AbsoluteLong,                           // 0xEF: SBC
    ProgramCounterRelative,                 // 0xF0: BEQ
    DirectPageIndirectIndexedWithY,         // 0xF1: SBC
    DirectPageIndirect,                     // 0xF2: SBC
    StackRelativeIndirectIndexedWithY,      // 0xF3: SBC
    StackAbsolute,                          // 0xF4: PEA
    DirectPageIndexedWithX,                 // 0xF5: SBC
    DirectPageIndexedWithX,                 // 0xF6: INC
    DirectPageIndirectLongIndexedWithY,     // 0xF7: SBC
    Implied,                                // 0xF8: SED
    AbsoluteIndexedWithY,                   // 0xF9: SBC
    StackImplied,                           // 0xFA: PLX
    Implied,                                // 0xFB: XCE
    AbsoluteIndexedIndirectWithX,           // 0xFC: JSR
    AbsoluteIndexedWithX,                   // 0xFD: SBC
    AbsoluteIndexedWithX,                   // 0xFE: INC
    AbsoluteLongIndexedWithX,               // 0xFF: SBC
}; 

/**
 * Given the addressing mode of an instruction, this function will return the
 * effective address of the arguments. 
 *
 * NOTE:
 * If the instruction passed in has an immediate value addr mode, then the 
 * value returned by this function is that immediate value. This may or may
 * not be an address depending on the instruction being used. 
 *
 * Required CPU state:
 *      - PC points to byte directly after opcode in memory
 *
 */
uint32_t getEffectiveAddress(Registers* cpu, uint8_t opcode, uint8_t* mem){

	// Retrieves the addr mode from the opcode
	enum addrmode mode = modeMap[opcode];

	// Starts out with an empty addr 
	uint32_t effectiveAddress = 0;

	// Grab the program counter
	uint8_t pc = cpu->PC;

	// 16 bit mask for use with register masking for emulation mode
	uint16_t mask;

	switch(mode){

		/* 
		 * The instruction uses the next 2 bytes after opcode appended to either
		 * the DBR or the PBR depending on whether the instruction is locating
		 * data or tranferring control respectively
		 */ 
		case Absolute:
			switch(opcode){
				
				// Instructions that transfer control addr
				case 0x4C:	// JMP
				case 0x20: 	// JSR
					effectiveAddress = cpu->PBR << 16;
					break;

				// Instructions that locate data
				default:
					effectiveAddress = cpu->DBR << 16;
					break;
			}
			
			// In both cases the next two bytes after opcode are appended.
			effectiveAddress |= (mem[pc + 2] << 8);
			effectiveAddress |= (mem[pc + 1]);
			break;

		/*
		 * The instruction uses the next 2 bytes after the opcode, appended to 
		 * the DBR of the CPU, and then added to the contents of the X register.
		 * Iff the processor is in native mode (processor flag x = 0), then the 
		 * full 16bit X register is used. O/wise, only the lower 8 bits of the 
		 * X register are added to the 24bit EA.
		 */
		case AbsoluteIndexedWithX:
			
			// The data bank register is set as the bank of the EA
			effectiveAddress = cpu->DBR << 16;

			// The 16 bit operand is switched and appended to the EA
			effectiveAddress |= (mem[pc + 2] << 8);
			effectiveAddress |= mem[pc +1];

			// The mask will mask out any bits of X that aren't needed.
			// if the x flag == 1, mask should be 0xFF. o/wise, it is 0xFFF
			mask = 0xFFFF >> cpu->P->emulation * 8;

			// Adds the X register to the EA 
			effectiveAddress += (cpu->X) & mask;

			break;
		/*
		 * The instruction uses the next 2 bytes after the opcode, appended to 
		 * the DBR of the CPU, and then added to the contents of the Y register.
		 * Iff the processor is in native mode (processor flag x = 0), then the 
		 * full 16bit Y register is used. O/wise, only the lower 8 bits of the 
		 * Y register are added to the 24bit EA.
		 */
		case AbsoluteIndexedWithY:
			
			// The data bank register is set as the bank of the EA
			effectiveAddress = cpu->DBR << 16;

			// The 16 bit operand is switched and appended to the EA
			effectiveAddress |= (mem[pc + 2] << 8);
			effectiveAddress |= mem[pc +1];

			// The mask will mask out any bits of Y that aren't needed.
			// if the x flag == 1, mask should be 0xFF. o/wise, it is 0xFFF
			mask = 0xFFFF >> cpu->P->emulation * 8;

			// Adds the Y register to the EA 
			effectiveAddress += (cpu->Y) & mask;

			break;

		default:
			exit(1);
	}

	return effectiveAddress;
}
