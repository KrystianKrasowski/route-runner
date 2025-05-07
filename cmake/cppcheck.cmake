find_program(CPPCHECK_EXECUTABLE cppcheck)

if(CPPCHECK_EXECUTABLE)
    add_custom_target(
        cppcheck
        COMMAND ${CPPCHECK_EXECUTABLE} --enable=all --inconclusive --std=c23
                -I${CMAKE_SOURCE_DIR}/src
                -I${CMAKE_SOURCE_DIR}/src/utils/inc
                --suppress=missingIncludeSystem
                --check-level=exhaustive
                --inline-suppr
                ${CMAKE_SOURCE_DIR}/app/stm32f303x8/main.c
                ${CMAKE_SOURCE_DIR}/app/stm32f303x8/task.c
                ${CMAKE_SOURCE_DIR}/src
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running cppcheck on project sources..."
    )
else()
    message(WARNING "cppcheck not found — skipping static analysis target 'run_cppcheck'")
endif()
