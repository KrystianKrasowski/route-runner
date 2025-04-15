cmake_minimum_required(VERSION 3.28)

project(route-runner VERSION 1.0.1)

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

add_subdirectory(app)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)