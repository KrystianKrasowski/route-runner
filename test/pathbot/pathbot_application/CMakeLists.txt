set(TEST_SUITE
    pathbot_handle_commands_test.c
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
            pathbot_application
            pathbot_fixtures
            pathbot_port_mock
            utils
            unity
    )   

    add_test(${TEST_NAME} ${TEST_NAME})
endforeach()
