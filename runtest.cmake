execute_process(COMMAND ${TEST_PROG} ${ZVM_SOURCE_DIR}/tests/${TEST_NAME}/test
        RESULT_VARIABLE HAD_ERROR
        OUTPUT_FILE ${ZVM_SOURCE_DIR}/tests/${TEST_NAME}/result.txt)

if(HAD_ERROR)
    message(FATAL_ERROR "Test failed")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} -E compare_files
        ${ZVM_SOURCE_DIR}/tests/${TEST_NAME}/expected.txt ${ZVM_SOURCE_DIR}/tests/${TEST_NAME}/result.txt
        RESULT_VARIABLE DIFFERENT)
if(DIFFERENT)
    message(FATAL_ERROR "Test failed - files differ")
endif()