set(TEST_SUITE
    linebot_apply_manual_motion_test.c
    linebot_change_mode_by_control_test.c
    linebot_apply_following_motion_test.c
)

# extract some function here
foreach(FILE ${TEST_SUITE})
    get_filename_component(TEST_NAME ${FILE} NAME_WE)

    add_executable(${TEST_NAME} fixtures.c ${FILE})

    target_include_directories(${TEST_NAME}
        PRIVATE
            ${CMAKE_SOURCE_DIR}/test/include
    )

    target_link_libraries(${TEST_NAME}
        PRIVATE
            linebot
            linebot_ports_mock
            utils
            unity
    )   

    add_test(${TEST_NAME} ${TEST_NAME})
endforeach()
