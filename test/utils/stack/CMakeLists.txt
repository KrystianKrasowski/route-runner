add_executable(stack_test stack_test.c)

target_link_libraries(stack_test PRIVATE stack unity)
target_include_directories(stack_test PUBLIC ${CMAKE_SOURCE_DIR}/test/include)

add_test(stack_test stack_test)
