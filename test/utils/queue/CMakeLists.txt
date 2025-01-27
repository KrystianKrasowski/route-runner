add_executable(queue_test queue_test.c)

target_link_libraries(queue_test PRIVATE queue unity)

add_test(queue_test queue_test)
