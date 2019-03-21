#include <stdint.h>
#include "cpu.h"

// Different addressing modes that the different instructions might use.
enum addrmode {
    Implied,            
    Absolute,           
    AbsoluteIndexedWithX,       
    AbsoluteIndexedWithY,       
    AbsoluteIndexedIndirectWithX,     
    AbsoluteIndirect,        
    AbsoluteIndirectLong,    
    AbsoluteLong,       
    AbsoluteLongIndexedWithX,   
    Accumulator,        
    BlockMove,          
    DirectPage,                 
    DirectPageIndexedWithX,             
    DirectPageIndexedWithY,             
    DirectPageIndexedIndirectWithX,          
    DirectPageIndirect,              
    DirectPageIndirectLong,          
    DirectPageIndexedIndirectWithY,          
    DirectPageIndirectIndexedWithY,
    DirectPageIndirectLongIndexedWithY,      
    Immediate,          
    StackImplied,            
    ProgramCounterRelative,         
    ProgramCounterRelativeLong,     
    StackAbsolute,      
    StackDirectPageIndirect,         
    Interrupt,     
    StackProgramCounterRelativeLong,         
    StackPull,          
    StackPush,          
    StackRTI,           
    StackRTL,           
    StackRTS,           
    StackRelative,           
    StackRelativeIndirectIndexedWithY     
};

// Map of opcode -> addrMode. Access it with the opcode as the idx.
extern const enum addrmode modeMap[0x100];

/**
 * Given the addressing mode of an instruction, this function will return the
 * effective address of the arguments.
 *
 * Required CPU state:
 *      - PC points to byte directly after opcode in memory
 *
 */
uint32_t getEffectiveAddress(Registers* cpu, uint8_t opcode, uint8_t* mem);

