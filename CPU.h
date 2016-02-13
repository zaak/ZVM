//
// Created by zaak on 19.12.15.
//

#ifndef ZVM_CPU_H
#define ZVM_CPU_H

#include <stdint.h>

#define ZVM_CPU_FLAG_ZF 1
#define ZVM_CPU_FLAG_CF 2

typedef struct {
    uint32_t reg[16];
    uint32_t *pc;
    uint32_t *sp;
    uint32_t fr;
} CPU;

void zvm_cpu_init(CPU *cpu);

#endif //ZVM_CPU_H
