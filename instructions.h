#ifndef _INSTRUCTIONS_
#define _INSTRUCTIONS_

void (*instJmpTab[0x100])(struct Registers *cpu, uint8_t *mem);

void ADC(struct Registers *cpu, uint8_t *mem);
void AND(struct Registers *cpu, uint8_t *mem);
void BCC(struct Registers *cpu, uint8_t *mem);
void BCS(struct Registers *cpu, uint8_t *mem);
void BEQ(struct Registers *cpu, uint8_t *mem);
void BMI(struct Registers *cpu, uint8_t *mem);
void BNE(struct Registers *cpu, uint8_t *mem);
void BRA(struct Registers *cpu, uint8_t *mem);
void BRL(struct Registers *cpu, uint8_t *mem);
void JMP(struct Registers *cpu, uint8_t *mem);
#endif
