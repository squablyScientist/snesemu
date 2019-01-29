#include <stdio.h>
#include "cpu.h"
#include "status.h"

int main() {
	struct ProcessorStatusRegister* psr = newPSR();
	setProcessorStatus(psr, 0x80);
	printf("0x%x\n", getProcessorStatus(psr));
	return 0;
}
