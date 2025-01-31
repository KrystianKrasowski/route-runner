add_executable(task_rc_receive_test task_rc_receive_test.c)

target_link_libraries(task_rc_receive_test
    PRIVATE
        unity
)