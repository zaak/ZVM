//
// Created by zaak on 19.12.15.
//

#include <string.h>
#include "CPU.h"

void zvm_cpu_init(CPU *cpu)
{
    memset(cpu, 0, sizeof(CPU));
    cpu->sp = &cpu->reg[14];
    cpu->pc = &cpu->reg[15];
    *cpu->sp = 0x10000;
}
