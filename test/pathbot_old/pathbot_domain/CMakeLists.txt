set(TEST_SUITE
    pathbot_update_mode_manual_test.c
    pathbot_update_mode_tracking_test.c
    pathbot_update_motion_manual_test.c
    pathbot_compute_position_error_test.c
    pathbot_create_motion_pid_test.c
)

# extract some function here
foreach(FILE ${TEST_SUITE})
    get_filename_component(TEST_NAME ${FILE} NAME_WE)

    add_executable(${TEST_NAME} ${FILE})

    target_include_directories(${TEST_NAME}
        PRIVATE
            ${CMAKE_SOURCE_DIR}/test/include
    )

    target_link_libraries(${TEST_NAME}
        PRIVATE
            pathbot_domain
            pathbot_fixtures
            utils
            unity
    )   

    add_test(${TEST_NAME} ${TEST_NAME})
endforeach()
