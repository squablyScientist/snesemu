#include <stdlib.h>
#include "opcode.h"

// TODO make sure it cares about idxwidth as well

static inline uint16_t sign_extend8to16(uint8_t num);

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
uint64_t getEffectiveAddress(Registers* cpu, uint8_t opcode, uint8_t* mem)
{

	// Retrieves the addr mode from the opcode
	enum addrmode mode = modeMap[opcode];

	// Starts out with an empty addr 
	uint32_t effectiveAddress = 0;

	// Indirect address that some modes use:
	uint32_t indirectAddr = 0;

	// Temporary effective address for addition
	uint32_t tempEffAddr = 0;

	// Grab the program counter
	uint16_t *pc = &(cpu->PC);

	uint16_t sign_extension = 0;

	// 16 bit mask for use with register masking for emulation mode. If the
	// processor is in native mode, then no shift is performed and the mask
	// allows all 16 bits through. If the processor is in emulation mode, the
	// mask only allows the lower 8 bits through.
	uint16_t mask = 0xFFFF >> cpu->P->emulation * 8;

	switch(mode){

		/* 
		 * The instruction uses the next 2 bytes after opcode appended to either
		 * the DBR or the PBR depending on whether the instruction is locating
		 * data or tranferring control respectively
		 */ 
		case Absolute:

		/*
		 * Used for PEA, which pushes the 16 bit operand onto the stack. It
		 * behaves identical to Absolute addressing. The bank doesn't matter
		 * since the lower 16 bits of the effective address is all PEA needs.
		 */
		case StackAbsolute:
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
			effectiveAddress |= (mem[*pc++]);
			effectiveAddress |= (mem[*pc++] << 8);
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
			effectiveAddress |= mem[*pc++];
			effectiveAddress |= mem[*pc++] << 8;

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
			effectiveAddress |= mem[*pc++];
			effectiveAddress |= mem[*pc++] << 8;

			// Adds the Y register to the EA 
			effectiveAddress += (cpu->Y) & mask;

			break;

		/*
		 * The instruction uses a 2 byte argument that is then added to the
		 * contents of the X register. Iff the processor is in native
		 * mode(processor flag x = 0), then the full 16bit X register is
		 * used. Otherwise, only the lower 8 bits are used for this addition.
		 *
		 * This resulting address is appended to the PBR to make a 24 bit
		 * address. This address is the location of the lower byte of the little
		 * endian effective address. The higher byte of the effective address is 
		 * located directly above. This 2 byte address is then appended to the
		 * PBR to create the full effective address
		 */
		case AbsoluteIndexedIndirectWithX:
			
			// Sets the bank byte as PBR
			effectiveAddress = cpu->PBR << 16;

			// The address that the effective address will be located at 
			indirectAddr = cpu->PBR << 16;

			// The 16 bit operand is switched and appended to the indirect addr
			indirectAddr |= mem[*pc++];
			indirectAddr |= mem[*pc++] << 8;

			// Adds the X register to the indirect addr 
			indirectAddr += (cpu->X) & mask;

			// The 16 bit operand is switched and appended to the EA
			effectiveAddress |= (mem[indirectAddr + 1] << 8);
			effectiveAddress |= mem[indirectAddr];

			break;

		/*
		 * Same as Absolute Indexed Indirect w/ X but it doesn't add the X idx
		 * register
		 */
		case AbsoluteIndirect:

			// Sets the bank byte as PBR
			effectiveAddress = cpu->PBR << 16;

			// The address that the effective address will be located at 
			indirectAddr = cpu->PBR << 16;

			// The 16 bit operand is switched and appended to the indirect addr
			indirectAddr |= mem[*pc++];
			indirectAddr |= mem[*pc++] << 8;

			// The 16 bit operand is switched and appended to the EA
			effectiveAddress |= (mem[indirectAddr + 1] << 8);
			effectiveAddress |= mem[indirectAddr];

			break;

		/*
		 * Instruction uses little endian double byte operand as an address in
		 * bank 0. This address is the address of a 24bit little endian addr
		 * that is the effective address.
		 */
		case AbsoluteIndirectLong:

			// The indirect addr is in bank 0, and starts as 0 so no need to
			// reinitialize.

			// The 16 bit operand is switched and appended to the indirect addr
			indirectAddr |= mem[*pc++];
			indirectAddr |= mem[*pc++] << 8;

			// The 24 bit addr is loaded into the effective address
			effectiveAddress |= mem[indirectAddr + 2] << 16;
			effectiveAddress |= mem[indirectAddr + 1] << 8;
			effectiveAddress |= mem[indirectAddr];
			break;

		/*
		 * Instruction takes 3 bytes as the effective address in little endian
		 */
		case AbsoluteLong:

			// Just loads the addr into the EA
			effectiveAddress |= mem[*pc++];
			effectiveAddress |= mem[*pc++] << 8;
			effectiveAddress |= mem[*pc++] << 16;
			break;

		/*
		 * Instruction takes 3 bytes as the effective address in little endian,
		 * and then the contents of X is added for the final effective address.
		 * If the processor is in native mode(processor status flag x = 0) then
		 * all 16 bits of X are used in this addition, o/wise only the lower 8
		 * bits are used.
		 */
		case AbsoluteLongIndexedWithX:

			// Just loads the addr into the EA
			effectiveAddress |= mem[*pc++];
			effectiveAddress |= mem[*pc++] << 8;
			effectiveAddress |= mem[*pc++] << 16;

			// Adds the X register to the effective addr 
			effectiveAddress += (cpu->X) & mask;

			break;

		/*
		 * This is less of an address and just the value in the accumulator.
		 * Depending on the state of the processor, different things are
		 * returned:
		 * When in emulation mode, the """effective address""" is 8 bits and the
		 * byte in A. 
		 *
		 * When in native mode, the """effective address""" depends on the
		 * memory width flag. When m = 0, it's C. When m = 1, then it is just
		 * the 8 bits in A.
		 */
		case Accumulator:

			if(cpu->P->emulation || cpu->P->memWidth){
				effectiveAddress = cpu->acc.split.A;
			}
			else{
				effectiveAddress = cpu->acc.C;
			}

			break;

		/*
		 * Src Addr: located in bits 23- 0
		 * Dst Addr: located in bits 47-24
		 *
		 * Instruction gives 2 operand bytes. The first of which is the bank
		 * byte of the destination address, and the second of which is the bank
		 * byte of the source address.
		 *
		 * The rest of the src address is the contents of the X register. If the
		 * processor is in emulation mode or the idx width flag is set, then the
		 * high byte of the X register is 0ed out for this purpose.
		 *
		 * The rest of the dst address is the contents of the Y register. If the
		 * processor is in emulation mode or the idx width flag is set, then the
		 * high byte of the Y register is 0ed out for this purpose.
		 */
		case BlockMove:
			effectiveAddress |= (uint64_t)mem[*pc++] << 40;
			effectiveAddress |= (uint16_t)(cpu->X & mask) << 24;
			effectiveAddress |= mem[*pc++] << 16;
			effectiveAddress |= (uint16_t)(cpu->Y & mask);
			break;
			
		/*
		 * Bank: 0
		 * The effective address is generated by adding the direct page register
		 * to the 1 byte operand.
		 */
		case DirectPage:

			// EA starts as 0 so no need to clear high byte
			effectiveAddress |= mem[*pc++] + cpu->D;
			break;

		/*
		 * Bank: 0
		 * The effective address in bank 0 is calculated by adding the Direct
		 * Page register, the one byte operand, and the X register(all 16 if in
		 * native mode, lower 8 bytes o/wise)
		 */
		case DirectPageIndexedWithX:
		
			effectiveAddress |= mem[*pc++] + cpu->D + ((cpu->X) & mask);
			break;

		/*
		 * Bank: 0
		 * The effective address in bank 0 is calculated by adding the Direct
		 * Page register, the one byte operand, and the Y register(all 16 if in
		 * native mode, lower 8 bytes o/wise)
		 */
		case DirectPageIndexedWithY:

			effectiveAddress |= mem[*pc++] + cpu->D + ((cpu->Y) & mask);
			break;

		/*
		 * Bank: Data Bank Reg
		 * The indirect address is calculated by summing the one byte operand,
		 * the direct page register, and the X register(16 bits if in native
		 * mode, lower 8 bits o/wise). 
		 * The effective address is located in bank 0 at the indirect address
		 * in little endian.
		 */
		case DirectPageIndexedIndirectWithX:

			// indirectAddr starts as 0, no need to clear the high byte
			indirectAddr = mem[*pc++] + cpu->D + ((cpu->X) & mask);

			// Load the effective addr from memory at the indirect addr
			effectiveAddress |= cpu->DBR << 16;
			effectiveAddress |= mem[indirectAddr + 1] << 8;
			effectiveAddress |= mem[indirectAddr];

			break;

		/*
		 * Bank: Data Bank Reg
		 * Same as Direct Page Indirect Indexed w/ X but it doesn't add the X
		 * register to the indirect address.
		 */
		case DirectPageIndirect:

		/*
		 * Used for PEI, which pushes 2 bytes located at the sum of the one byte
		 * operand and the direct page register. This behaves identically to how
		 * DirectPageIndirect addressing works, and the effective address of
		 * this the DirectPageIndirect is what is stored on the stack, making it
		 * essentially an _effective indirect address_
		 */
		case StackDirectPageIndirect:

			// indirectAddr starts as 0, no need to clear the high byte
			indirectAddr = mem[*pc++] + cpu->D;

			// Load the effective addr from memory at the indirect addr
			effectiveAddress |= cpu->DBR << 16;
			effectiveAddress |= mem[indirectAddr + 1] << 8;
			effectiveAddress |= mem[indirectAddr];

			break;


		/*
		 * Same as Direct Page Indirect, but the bank byte is stored above the 
		 * effective address in memory at the indirect address;
		 */
		case DirectPageIndirectLong:
			
			// indirectAddr starts as 0, no need to clear the high byte
			indirectAddr = mem[*pc++] + cpu->D;

			// Load the effective addr from memory at the indirect addr
			effectiveAddress |= mem[indirectAddr + 2] << 16;
			effectiveAddress |= mem[indirectAddr + 1] << 8;
			effectiveAddress |= mem[indirectAddr];

			break;

		/*
		 * Bank: Data Bank Reg
		 * The indirect address is found by summing the one byte operand and the
		 * direct page register. 
		 * The effective address is found by summing the Y register(all 16 bits
		 * if in native mode, only the low 8 bits o/wise) and the 2 byte value
		 * located at the indirect address in bank 0.
		 */
		case DirectPageIndirectIndexedWithY:

			// indirectAddr starts as 0, no need to clear high byte
			indirectAddr = mem[*pc++] + cpu->D;

			effectiveAddress |= cpu->DBR << 16;

			// Loads the effective addr into the temp
			tempEffAddr |= mem[indirectAddr + 1] << 8;
			tempEffAddr |= mem[indirectAddr];

			// Performs masking and addition, and loads result into lower bytes
			// of the EA
			effectiveAddress |= tempEffAddr + (cpu->Y & mask);

			break;

		/*
		 * Same as Direct Page Indirect Indexed w/ Y, but the bank of the EA is
		 * located above the EA at the indirect address.
		 */
		case DirectPageIndirectLongIndexedWithY:

			// indirectAddr starts as 0, no need to clear high byte
			indirectAddr = mem[*pc++] + cpu->D;

			// Loads the effective addr into the temp
			tempEffAddr |= mem[indirectAddr + 2] << 16;
			tempEffAddr |= mem[indirectAddr + 1] << 8;
			tempEffAddr |= mem[indirectAddr];

			// Performs masking and addition, and loads result into lower bytes
			// of the EA
			effectiveAddress = tempEffAddr + (cpu->Y & mask);

			break;

		/*
		 * The """effective address""" in this case is provided directly in the
		 * operand of the instruction. The amount of operand bytes depends on
		 * the processor state:
		 *
		 * If the processor is in emulation mode, then all instructions have
		 * only one operand byte. 
		 *
		 * If the processor is in native mode, then depending either the index
		 * width or the memory width flag (the flag to look at depends on the
		 * opcode) there are 2 operand bytes if the flag is unset. 
		 */
		case Immediate:

			// In either case, the low byte must be loaded
			effectiveAddress = mem[*pc++];

			// The REP & SEP instructions always only takes one operand
			if(opcode == 0xC2 || opcode == 0xE2){
				break;
			}

			// If the CPU is in native mode, then we need to check the
			// instructions for which flag they listen to
			if(!cpu->P->emulation){

				// The flag that will be checked
				uint8_t flag;
				switch(opcode){
					
					// Instructions that look at the memory width flag
					case 0x69:	// ADC
					case 0x29:	// AND
					case 0x89: 	// BIT
					case 0xC9: 	// CMP
					case 0x49:	// EOR
					case 0xA9:	// LDA
					case 0x09:	// ORA
					case 0xE9:	// SBC
						flag = cpu->P->memWidth;
						break;

					// Instructions that look at the index width flag
					case 0xE0: 	// CPX
					case 0xC0:	// CPY
					case 0xA2: 	// LDX
					case 0xA0:	// LDY
						flag = cpu->P->idxWidth;
						break;

					default:
						fprintf(stderr, "%X is not an immediate"
								"addr mode instruction!\n", opcode);
				}

				// If the flag is 0, then we need another operand byte
				if(!flag){
					effectiveAddress |= mem[*pc++] << 8;
				}
			}
			break;

		/*
		 * Bank: Program Bank Register
		 * The instruction supplies a one byte operand that is a twos compliment
		 * signed value. It is sign extended to 16 bits and then added to the 
		 * program counter to result in the EA.
		 */
		case ProgramCounterRelative:
			sign_extension = sign_extend8to16(mem[*pc++]);
			effectiveAddress |= cpu->PBR << 16;
			effectiveAddress |= sign_extension + *pc;
			break;

		/*
		 * Bank: Program Bank Register
		 * Takes a double byte as operand and adds it to the program counter to
		 * get the effective address. 
		 */
		case ProgramCounterRelativeLong:
			sign_extension |= mem[*pc++];
			sign_extension |= mem[*pc++] << 8;
			effectiveAddress |= cpu->PBR << 16;
			effectiveAddress |= sign_extension + *pc;
			break;

		/*
		 * TODO: to implement this, the way the program counter works must be
		 * redone.
		 */
		case StackProgramCounterRelativeLong:
			break;

		/*
		 * For instructions whose EA is just the stack pointer. Remember that
		 * the bank of the stack pointer is locked to bank 0.
		 */
		case StackImplied:

			// effectiveAddress starts as 0, no need to set bank byte to 0.
			effectiveAddress |= cpu->SP;
			break;

		/*
		 * Bank: Data Bank Reg
		 * The Indirect Address is the sum of the one byte operand and the stack
		 * pointer. It is located in bank 0
		 * The Effective Address is calculated by cating the Indirect Address
		 * added to Y(16 bits in native mode, only the lower 8 o/wise) to the
		 * Data Bank Register.
		 */
		case StackRelativeIndirectIndexedWithY:

			// Sets the bank byte to the data bank register
			effectiveAddress |= cpu->DBR << 16;

			// indirectAddr starts at 0, no need to clear high byte
			indirectAddr = mem[*pc++] + cpu->SP;

			// Retrieves the unsummed EA from the indirect address
			tempEffAddr |= mem[indirectAddr + 1] << 8;
			tempEffAddr |= mem[indirectAddr];

			// Performs the indexing addition and loads the rest of the EA
			effectiveAddress |= tempEffAddr + (cpu->Y & mask);

			break;

		/*
		 * The Effective Address is the sum of the one byte operand and the
		 * stack pointer, in bank 0;
		 */
		case StackRelative:
			effectiveAddress |= mem[*pc++] + cpu->SP;
			break;

		/*
		 * The behaviour of implied addr instructions is entirely dependent on
		 * the instruction itself, and no operands. There is no address to be
		 * gathered from this, the opcode itself specifies what is to be
		 * done in all cases.
		 */
		case Implied:
			break;

		case Interrupt:
			break;
	}

	return effectiveAddress;
}

static inline uint16_t sign_extend8to16(uint8_t num){
	uint8_t extension;
	// if the most significant bit is set, it's a negative number
	if(0x80 & num){
		extension = 0xFF;
	}
	else{
		extension = 0x00;
	}

	return ((uint16_t)extension) << 8 | num;
}
