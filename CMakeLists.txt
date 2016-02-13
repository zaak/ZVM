cmake_minimum_required(VERSION 2.8)
project(zvm)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pedantic -Wall")

set(SOURCE_FILES ZVM.h ZVM.c CPU.h CPU.c Memory.h Memory.c Opcodes.h debug.h)

add_executable(zvm main.c ${SOURCE_FILES})

# Tests

enable_testing()

add_executable(zvm_test tests/test.c ${SOURCE_FILES})

macro(zvm_add_test TEST_NAME)
    add_test(NAME ${TEST_NAME}
             COMMAND ${CMAKE_COMMAND}
             -DTEST_PROG=${CMAKE_CURRENT_SOURCE_DIR}/build/zvm_test
             -DZVM_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}
             -DTEST_NAME=${TEST_NAME}
             -P ${CMAKE_CURRENT_SOURCE_DIR}/runtest.cmake)
endmacro()

zvm_add_test("VSET")
zvm_add_test("VMOV")
zvm_add_test("VST")
zvm_add_test("VLD")
zvm_add_test("VSTB")
zvm_add_test("VLDB")

zvm_add_test("VADD")
zvm_add_test("VSUB")
zvm_add_test("VMUL")
