cmake_minimum_required(VERSION 3.28)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(route-runner VERSION 3.0.0)

enable_language(C CXX ASM)

include(${CMAKE_SOURCE_DIR}/cmake/compile-common-options.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/cppcheck.cmake)
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
# For some reason this has to be defined in a top level CMakeLists.txt
if(TARGET_HARDWARE STREQUAL "native_host")
    include(CTest)
    enable_testing()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(__DEBUG)
endif()

add_subdirectory(apps)
add_subdirectory(src)
add_subdirectory(extern)
add_subdirectory(tests)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
)
