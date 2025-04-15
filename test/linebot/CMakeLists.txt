set(TEST_SUITE
    linebot_handle_manual_control_test.c
    linebot_handle_route_tracking_test.c
    linebot_stop_test.c
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
