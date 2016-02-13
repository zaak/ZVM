//
// Created by zaak on 19.12.15.
//

#ifndef ZVM_MEMORY_H
#define ZVM_MEMORY_H

#include <stdbool.h>

#define ZVM_MEMORY_SIZE 0x10000

typedef struct {
    uint8_t *data;
} Memory;

bool zvm_memory_init(Memory *memory);

uint32_t zvm_memory_fetch_dword(Memory *memory, uint32_t address);
void zvm_memory_store_dword(Memory *memory, uint32_t address, uint32_t value);
uint8_t zvm_memory_fetch_byte(Memory *memory, uint32_t address);
void zvm_memory_store_byte(Memory *memory, uint32_t address, uint8_t value);

#endif //ZVM_MEMORY_H
