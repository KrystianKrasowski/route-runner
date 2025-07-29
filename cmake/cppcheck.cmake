find_program(CPPCHECK_EXECUTABLE cppcheck)

if(CPPCHECK_EXECUTABLE)
    add_custom_target(
        cppcheck
        COMMAND ${CPPCHECK_EXECUTABLE} --enable=all --inconclusive --std=c++17
                -I${CMAKE_SOURCE_DIR}/src
                -I${CMAKE_SOURCE_DIR}/extern
                --suppress=missingIncludeSystem
                --suppress=missingInclude
                --check-level=exhaustive
                --inline-suppr
                ${CMAKE_SOURCE_DIR}/src
                ${CMAKE_SOURCE_DIR}/apps
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running cppcheck on project sources..."
    )
else()
    message(WARNING "cppcheck not found — skipping static analysis target 'run_cppcheck'")
endif()
