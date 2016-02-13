//
// Created by zaak on 19.12.15.
//

#ifndef ZVM_VM_H
#define ZVM_VM_H

#include "CPU.h"
#include "Memory.h"
#include "Opcodes.h"

typedef struct _ZVM {
    CPU cpu;
    Memory memory;
    bool terminated;
    Opcode opcodes[256];
} ZVM;

void zvm_init(ZVM *vm);
bool zvm_load_program_from_file(ZVM *vm, char *filename);
void zvm_run(ZVM *vm);
void zvm_shutdown(ZVM *vm);

#endif //ZVM_VM_H
