cmake_minimum_required(VERSION 3.28)

project(route-runner)

include(FetchContent)

add_subdirectory(src)

if(CMAKE_CROSSCOMPILING)
    add_subdirectory(lib/stm32l476rgtx)
    add_subdirectory(app)
else()
    include(dependencies-test.cmake)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif()