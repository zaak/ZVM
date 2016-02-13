//
// Created by zaak on 19.12.15.
//

#ifndef ZVM_OPCODES_H
#define ZVM_OPCODES_H

#include <stdint.h>

#define VMOV   0x00
#define VSET   0x01
#define VLD    0x02
#define VST    0x03
#define VLDB   0x04
#define VSTB   0x05

#define VADD   0x10
#define VSUB   0x11
#define VMUL   0x12
#define VDIV   0x13
#define VMOD   0x14
#define VOR    0x15
#define VAND   0x16
#define VXOR   0x17
#define VNOT   0x18
#define VSHL   0x19
#define VSHR   0x1A

#define VCMP   0x20
#define VJZ    0x21
#define VJNZ   0x22
#define VJC    0x23
#define VJNC   0x24
#define VJBE   0x25
#define VJA    0x26

#define VPUSH  0x30
#define VPOP   0x31

#define VJMP   0x40
#define VJMPR  0x41
#define VCALL  0x42
#define VCALLR 0x43
#define VRET   0x44

#define VCRL   0xF0
#define VCRS   0xF1
#define VOUTB  0xF2
#define VINB   0xF3
#define VIRET  0xF4
#define VCRSH  0xFE
#define VOFF   0xFF

struct _ZVM;

typedef struct {
    uint8_t size;
    void (*handler)(struct _ZVM *vm, uint8_t *args);
} Opcode;

#endif //ZVM_OPCODES_H
