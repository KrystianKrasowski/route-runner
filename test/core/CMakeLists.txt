add_subdirectory(ports_mock)

set(TEST_SUITE
    core_task_remote_control_receive_test.c
    core_task_motion_update_test.c
    core_task_state_indicator_update_test.c
    core_task_line_position_receive_test.c
    core_vehicle_test.c
    core_vehicle_update_state_test.c
    core_vehicle_update_motion_test.c
    core_vehicle_update_command_test.c
)

foreach(FILE ${TEST_SUITE})
    get_filename_component(TEST_NAME ${FILE} NAME_WE)

    add_executable(${TEST_NAME} ${FILE})

    target_include_directories(${TEST_NAME}
        PRIVATE
            ${CMAKE_SOURCE_DIR}/test/include
    )

    target_link_libraries(${TEST_NAME}
        PRIVATE
            core
            core_port_mock
            utils
            unity
    )   

    add_test(${TEST_NAME} ${TEST_NAME})
endforeach()
