//
// Created by zaak on 19.12.15.
//

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "Memory.h"

bool zvm_memory_init(Memory *memory)
{
    memory->data = (uint8_t *) malloc(ZVM_MEMORY_SIZE);
    memset(memory->data, 0, ZVM_MEMORY_SIZE);

    return true;
}

uint32_t zvm_memory_fetch_dword(Memory *memory, uint32_t address)
{
    return *(uint32_t*)&memory->data[address];
}

void zvm_memory_store_dword(Memory *memory, uint32_t address, uint32_t value)
{
    *(uint32_t*)&memory->data[address] = value;
}

uint8_t zvm_memory_fetch_byte(Memory *memory, uint32_t address)
{
    return memory->data[address];
}

void zvm_memory_store_byte(Memory *memory, uint32_t address, uint8_t value)
{
    memory->data[address] = value;
}