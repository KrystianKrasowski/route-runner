cmake_minimum_required(VERSION 3.28)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(route-runner VERSION 1.2.x)

enable_language(C ASM)

include(${CMAKE_SOURCE_DIR}/cmake/compile-common-options.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/cppcheck.cmake)
include(FetchContent)

# For some reason this has to be defined in a top level CMakeLists.txt
if(TARGET_ARCH STREQUAL "test")
    include(CTest)
    enable_testing()
    include(${CMAKE_SOURCE_DIR}/cmake/dependencies-test.cmake)
endif()

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
)
