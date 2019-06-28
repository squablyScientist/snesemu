#ifndef _INSTRUCTIONS_
#define _INSTRUCTIONS_

void (*instJmpTab[0x100])(struct Registers *cpu, uint8_t *mem);

void ADC(struct Registers *cpu, uint8_t *mem);
void AND(struct Registers *cpu, uint8_t *mem);
void ASL(struct Registers *cpu, uint8_t *mem);
void BCC(struct Registers *cpu, uint8_t *mem);
void BCS(struct Registers *cpu, uint8_t *mem);
void BEQ(struct Registers *cpu, uint8_t *mem);
void BMI(struct Registers *cpu, uint8_t *mem);
void BNE(struct Registers *cpu, uint8_t *mem);
void BRA(struct Registers *cpu, uint8_t *mem);
void BRL(struct Registers *cpu, uint8_t *mem);
void JMP(struct Registers *cpu, uint8_t *mem);
void BRL(struct Registers *cpu, uint8_t *mem);
void BVS(struct Registers *cpu, uint8_t *mem);
void BVC(struct Registers *cpu, uint8_t *mem);
void CLC(struct Registers *cpu, uint8_t *mem);
void CLD(struct Registers *cpu, uint8_t *mem);
void CLI(struct Registers *cpu, uint8_t *mem);
void CLV(struct Registers *cpu, uint8_t *mem);
void CMP(struct Registers *cpu, uint8_t *mem);
void CPX(struct Registers *cpu, uint8_t *mem);
void CPY(struct Registers *cpu, uint8_t *mem);
void DEC(struct Registers *cpu, uint8_t *mem);
void DEX(struct Registers *cpu, uint8_t *mem);
void DEY(struct Registers *cpu, uint8_t *mem);
void INC(struct Registers *cpu, uint8_t *mem);
void INX(struct Registers *cpu, uint8_t *mem);
void INY(struct Registers *cpu, uint8_t *mem);
void EOR(struct Registers *cpu, uint8_t *mem);
void JSL(struct Registers *cpu, uint8_t *mem);
void JSR(struct Registers *cpu, uint8_t *mem);
void LDA(struct Registers *cpu, uint8_t *mem);
void LDX(struct Registers *cpu, uint8_t *mem);
void LDY(struct Registers *cpu, uint8_t *mem);
void NOP(struct Registers *cpu, uint8_t *mem);
void ORA(struct Registers *cpu, uint8_t *mem);
void PEA(struct Registers *cpu, uint8_t *mem);
void PEI(struct Registers *cpu, uint8_t *mem);

#endif
