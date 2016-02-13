#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ZVM.h"

void zvm_register_opcode_handlers(ZVM *vm);

void zvm_init(ZVM *vm) {
    vm->terminated = false;
    zvm_cpu_init(&vm->cpu);
    zvm_memory_init(&vm->memory);
    memset(&vm->opcodes, 0, sizeof(vm->opcodes));
    zvm_register_opcode_handlers(vm);
}

bool zvm_load_program_from_file(ZVM *vm, char *filename) {
    FILE *f = fopen(filename, "rb");

    if (!f) {
        return false;
    }

    return (bool) fread(vm->memory.data, sizeof(uint8_t), ZVM_MEMORY_SIZE - 1000, f);
}


void zvm_run(ZVM *vm) {
    while (!vm->terminated) {
//        sleep(1);
        uint8_t opcode = zvm_memory_fetch_byte(&vm->memory, *vm->cpu.pc);
        void *args = (void *) &vm->memory.data[*vm->cpu.pc + 1];
        *vm->cpu.pc += 1 + vm->opcodes[opcode].size;
        vm->opcodes[opcode].handler(vm, args);
    }
}

void zvm_shutdown(ZVM *vm) {
    if (vm->memory.data) {
        free(vm->memory.data);
    }
}

// ==== Opcode handlers ====

void zvm_opcode_handler_VMOV(ZVM *vm, uint8_t *args) {
    vm->cpu.reg[*args & 0x0F] = vm->cpu.reg[*(args + 1) & 0x0F];
}

void zvm_opcode_handler_VSET(ZVM *vm, uint8_t *args) {
    vm->cpu.reg[*args & 0x0F] = *(uint32_t *) (args + 1);
}

void zvm_opcode_handler_VLD(ZVM *vm, uint8_t *args) {
    vm->cpu.reg[*args & 0x0F] = zvm_memory_fetch_dword(&vm->memory, vm->cpu.reg[*(args + 1) & 0x0F]);
}

void zvm_opcode_handler_VST(ZVM *vm, uint8_t *args) {
    zvm_memory_store_dword(&vm->memory, vm->cpu.reg[*args & 0x0F], vm->cpu.reg[*(args + 1) & 0x0F]);
}

void zvm_opcode_handler_VLDB(ZVM *vm, uint8_t *args) {
    vm->cpu.reg[*args & 0x0F] = zvm_memory_fetch_byte(&vm->memory, vm->cpu.reg[*(args + 1) & 0x0F]);
}

void zvm_opcode_handler_VSTB(ZVM *vm, uint8_t *args) {
    zvm_memory_store_byte(&vm->memory, vm->cpu.reg[*args & 0x0F], (uint8_t) vm->cpu.reg[*(args + 1) & 0x0F]);
}

void zvm_opcode_handler_VOFF(ZVM *vm, uint8_t *args) {
    vm->terminated = true;
}


void zvm_opcode_handler_VADD(ZVM *vm, uint8_t *args) {
    vm->cpu.reg[*args & 0x0F] += vm->cpu.reg[*(args + 1) & 0x0F];
}

void zvm_opcode_handler_VSUB(ZVM *vm, uint8_t *args) {
    vm->cpu.reg[*args & 0x0F] -= vm->cpu.reg[*(args + 1) & 0x0F];
}

void zvm_opcode_handler_VMUL(ZVM *vm, uint8_t *args) {
    vm->cpu.reg[*args & 0x0F] *= vm->cpu.reg[*(args + 1) & 0x0F];
}

void zvm_opcode_handler_VDIV(ZVM *vm, uint8_t *args) {
    vm->cpu.reg[*args & 0x0F] /= vm->cpu.reg[*(args + 1) & 0x0F];
}

void zvm_opcode_handler_VMOD(ZVM *vm, uint8_t *args) {
    vm->cpu.reg[*args & 0x0F] %= vm->cpu.reg[*(args + 1) & 0x0F];
}

void zvm_opcode_handler_VOR(ZVM *vm, uint8_t *args) {
    vm->cpu.reg[*args & 0x0F] |= vm->cpu.reg[*(args + 1) & 0x0F];
}

void zvm_opcode_handler_VAND(ZVM *vm, uint8_t *args) {
    vm->cpu.reg[*args & 0x0F] &= vm->cpu.reg[*(args + 1) & 0x0F];
}

void zvm_opcode_handler_VXOR(ZVM *vm, uint8_t *args) {
    vm->cpu.reg[*args & 0x0F] ^= vm->cpu.reg[*(args + 1) & 0x0F];
}

void zvm_opcode_handler_VNOT(ZVM *vm, uint8_t *args) {
    vm->cpu.reg[*args & 0x0F] = ~vm->cpu.reg[*(args + 1) & 0x0F];
}

void zvm_opcode_handler_VSHL(ZVM *vm, uint8_t *args) {
    vm->cpu.reg[*args & 0x0F] <<= vm->cpu.reg[*(args + 1) & 0x0F];
}

void zvm_opcode_handler_VSHR(ZVM *vm, uint8_t *args) {
    vm->cpu.reg[*args & 0x0F] >>= vm->cpu.reg[*(args + 1) & 0x0F];
}

void zvm_opcode_handler_VCMP(ZVM *vm, uint8_t *args) {
    int32_t result = vm->cpu.reg[*args & 0x0F] - vm->cpu.reg[*(args + 1) & 0x0F];

    vm->cpu.fr &= 0xfffffffc;

    if (result == 0) {
        vm->cpu.fr |= ZVM_CPU_FLAG_ZF;
    }

    if (result < 0) {
        vm->cpu.fr |= ZVM_CPU_FLAG_CF;
    }
}

void zvm_opcode_handler_VJZ(ZVM *vm, uint8_t *args) {
    if (vm->cpu.fr & ZVM_CPU_FLAG_ZF) {
        *vm->cpu.pc = (*vm->cpu.pc + *(uint16_t *) args) & 0xFFFF;
    }
}

void zvm_opcode_handler_VJNZ(ZVM *vm, uint8_t *args) {
    if (!(vm->cpu.fr & ZVM_CPU_FLAG_ZF)) {
        *vm->cpu.pc = (*vm->cpu.pc + *(uint16_t *) args) & 0xFFFF;
    }
}

void zvm_opcode_handler_VJC(ZVM *vm, uint8_t *args) {
    if (vm->cpu.fr & ZVM_CPU_FLAG_CF) {
        *vm->cpu.pc = (*vm->cpu.pc + *(uint16_t *) args) & 0xFFFF;
    }
}

void zvm_opcode_handler_VJNC(ZVM *vm, uint8_t *args) {
    if (!(vm->cpu.fr & ZVM_CPU_FLAG_CF)) {
        *vm->cpu.pc = (*vm->cpu.pc + *(uint16_t *) args) & 0xFFFF;
    }
}

void zvm_opcode_handler_VJBE(ZVM *vm, uint8_t *args) {
    if (vm->cpu.fr & ZVM_CPU_FLAG_CF || vm->cpu.fr & ZVM_CPU_FLAG_ZF) {
        *vm->cpu.pc = (*vm->cpu.pc + *(uint16_t *) args) & 0xFFFF;
    }
}

void zvm_opcode_handler_VJA(ZVM *vm, uint8_t *args) {
    if (!(vm->cpu.fr & ZVM_CPU_FLAG_CF) && !(vm->cpu.fr & ZVM_CPU_FLAG_ZF)) {
        *vm->cpu.pc = (*vm->cpu.pc + *(uint16_t *) args) & 0xFFFF;
    }
}

void zvm_opcode_handler_VPUSH(ZVM *vm, uint8_t *args) {
    *vm->cpu.sp -= 4;
    zvm_memory_store_dword(&vm->memory, *vm->cpu.sp, vm->cpu.reg[*args & 0x0F]);
}

void zvm_opcode_handler_VPOP(ZVM *vm, uint8_t *args) {
    vm->cpu.reg[*args & 0x0F] = zvm_memory_fetch_dword(&vm->memory, *vm->cpu.sp);
    *vm->cpu.sp += 4;
}

void zvm_opcode_handler_VJMP(ZVM *vm, uint8_t *args) {
    *vm->cpu.pc = (*vm->cpu.pc + *(uint16_t *) args) & 0xFFFF;
}

void zvm_opcode_handler_VJMPR(ZVM *vm, uint8_t *args) {
    *vm->cpu.pc = vm->cpu.reg[*args & 0x0F] & 0xFFFF;
}

void zvm_opcode_handler_VCALL(ZVM *vm, uint8_t *args) {
    *vm->cpu.sp -= 4;
    zvm_memory_store_dword(&vm->memory, *vm->cpu.sp, *vm->cpu.pc);
    *vm->cpu.pc = (*vm->cpu.pc + *(uint16_t *) args) & 0xFFFF;
}

void zvm_opcode_handler_VCALLR(ZVM *vm, uint8_t *args) {
    *vm->cpu.sp -= 4;
    zvm_memory_store_dword(&vm->memory, *vm->cpu.sp, *vm->cpu.pc);
    *vm->cpu.pc = vm->cpu.reg[*args & 0x0F] & 0xFFFF;
}

void zvm_opcode_handler_VRET(ZVM *vm, uint8_t *args) {
    *vm->cpu.pc = zvm_memory_fetch_dword(&vm->memory, *vm->cpu.sp);
    *vm->cpu.sp += 4;
}

// ==== END: Opcode handlers ====

void zvm_register_opcode_handler(ZVM *vm, uint8_t opcode, uint8_t size, void (*handler)(ZVM *, uint8_t *)) {
    vm->opcodes[opcode].size = size;
    vm->opcodes[opcode].handler = handler;
}

void zvm_register_opcode_handlers(ZVM *vm) {
    zvm_register_opcode_handler(vm, VMOV, 1 + 1, zvm_opcode_handler_VMOV);
    zvm_register_opcode_handler(vm, VSET, 1 + 4, zvm_opcode_handler_VSET);
    zvm_register_opcode_handler(vm, VLD, 1 + 1, zvm_opcode_handler_VLD);
    zvm_register_opcode_handler(vm, VST, 1 + 1, zvm_opcode_handler_VST);
    zvm_register_opcode_handler(vm, VLDB, 1 + 1, zvm_opcode_handler_VLDB);
    zvm_register_opcode_handler(vm, VSTB, 1 + 1, zvm_opcode_handler_VSTB);
    zvm_register_opcode_handler(vm, VOFF, 0, zvm_opcode_handler_VOFF);

    zvm_register_opcode_handler(vm, VADD, 1 + 1, zvm_opcode_handler_VADD);
    zvm_register_opcode_handler(vm, VSUB, 1 + 1, zvm_opcode_handler_VSUB);
    zvm_register_opcode_handler(vm, VMUL, 1 + 1, zvm_opcode_handler_VMUL);
    zvm_register_opcode_handler(vm, VDIV, 1 + 1, zvm_opcode_handler_VDIV);
    zvm_register_opcode_handler(vm, VMOD, 1 + 1, zvm_opcode_handler_VMOD);
    zvm_register_opcode_handler(vm, VOR, 1 + 1, zvm_opcode_handler_VOR);
    zvm_register_opcode_handler(vm, VAND, 1 + 1, zvm_opcode_handler_VAND);
    zvm_register_opcode_handler(vm, VXOR, 1 + 1, zvm_opcode_handler_VXOR);
    zvm_register_opcode_handler(vm, VNOT, 1 + 1, zvm_opcode_handler_VNOT);
    zvm_register_opcode_handler(vm, VSHL, 1 + 1, zvm_opcode_handler_VSHL);
    zvm_register_opcode_handler(vm, VSHR, 1 + 1, zvm_opcode_handler_VSHR);

    zvm_register_opcode_handler(vm, VCMP, 1 + 1, zvm_opcode_handler_VCMP);
    zvm_register_opcode_handler(vm, VJZ, 2, zvm_opcode_handler_VJZ);
    zvm_register_opcode_handler(vm, VJNZ, 2, zvm_opcode_handler_VJNZ);
    zvm_register_opcode_handler(vm, VJC, 2, zvm_opcode_handler_VJC);
    zvm_register_opcode_handler(vm, VJNC, 2, zvm_opcode_handler_VJNC);
    zvm_register_opcode_handler(vm, VJBE, 2, zvm_opcode_handler_VJBE);
    zvm_register_opcode_handler(vm, VJA, 2, zvm_opcode_handler_VJA);

    zvm_register_opcode_handler(vm, VPUSH, 1, zvm_opcode_handler_VPUSH);
    zvm_register_opcode_handler(vm, VPOP, 1, zvm_opcode_handler_VPOP);

    zvm_register_opcode_handler(vm, VJMP, 2, zvm_opcode_handler_VJMP);
    zvm_register_opcode_handler(vm, VJMPR, 1, zvm_opcode_handler_VJMPR);
    zvm_register_opcode_handler(vm, VCALL, 2, zvm_opcode_handler_VCALL);
    zvm_register_opcode_handler(vm, VCALLR, 1, zvm_opcode_handler_VCALLR);
    zvm_register_opcode_handler(vm, VRET, 0, zvm_opcode_handler_VRET);
}

