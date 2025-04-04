set(TEST_SUITE
    core_position_test.c
    core_vehicle_apply_manual_motion_test.c
    core_vehicle_change_mode_by_control_test.c
    core_vehicle_apply_following_motion_test.c
    core_vehicle_change_mode_by_coords_test.c
    core_vehicle_apply_route_guard_motion_test.c
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
            core_ports_mock
            utils
            unity
    )   

    add_test(${TEST_NAME} ${TEST_NAME})
endforeach()
