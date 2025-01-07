set(TARGET core_test)

add_executable(${TARGET} 
    core_test.c 
    core_interface_mock.c 
    core_interface_mock.h
)

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_SOURCE_DIR}/inc/core
    ${CMAKE_SOURCE_DIR}/test/inc
)

target_link_libraries(${TARGET} PUBLIC core unity)

add_test(${TARGET} ${TARGET})