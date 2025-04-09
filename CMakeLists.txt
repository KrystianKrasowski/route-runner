cmake_minimum_required(VERSION 3.28)

project(route-runner VERSION 0.7.0)

enable_language(C ASM)

include(FetchContent)

# For some reason this has to be defined in a top level CMakeLists.txt
if(TARGET_ARCH STREQUAL "test")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -fdata-sections -ffunction-sections")
    include(CTest)
    enable_testing()
    include(${CMAKE_SOURCE_DIR}/cmake/dependencies-test.cmake)
endif()

add_subdirectory(app)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)