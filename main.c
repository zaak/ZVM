#include <stdio.h>
#include "ZVM.h"

#include "debug.h"

int main(int argc, char *argv[]) {

    ZVM vm;
    zvm_init(&vm);

    if (argc != 2 || !zvm_load_program_from_file(&vm, argv[1])) {
        puts("Usage: zvm <filename>");

        return 0;
    }

    zvm_run(&vm);

    zvm_dump_registers(&vm);
    zvm_dump_memory(&vm);

    zvm_shutdown(&vm);

    return 0;
}