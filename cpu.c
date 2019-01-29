#include <stdio.h>
#include "cpu.h"
#include "status.h"

int main() {
	struct ProcessorStatusRegister* psr = newPSR();
	setnegativeFlag(psr);
	printf("0x%x\n", getProcessorStatus(psr));
	return 0;
}
