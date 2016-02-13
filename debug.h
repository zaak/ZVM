#include <stdio.h>
#include "ZVM.h"

void zvm_dump_registers(ZVM *vm) {
    puts("Registers:");
    for (int i = 0; i < 16; i++) {
        if (i == 14) {
            printf("R%d[SP]\t%08X\n", i, vm->cpu.reg[i]);

            continue;
        }
        if (i == 15) {
            printf("R%d[PC]\t%08X\n", i, vm->cpu.reg[i]);

            continue;
        }
        printf("R%d\t%08X\n", i, vm->cpu.reg[i]);
    }

    printf("FR\t%08X\n", vm->cpu.fr);
}

void zvm_dump_memory(ZVM *vm) {
    puts("\nMemory (first 300 bytes):");
    for (int i = 0; i < 300; i++) {
        printf("%02X ", vm->memory.data[i]);
        if (i % 20 == 19) {
            puts("");
        }
    }

    puts("\nStack (last 100 bytes):");
    for (int i = ZVM_MEMORY_SIZE - 100; i < ZVM_MEMORY_SIZE; i++) {
        printf("%02X ", vm->memory.data[i]);
        if (i % 20 == 15) {
            puts("");
        }
    }
}
