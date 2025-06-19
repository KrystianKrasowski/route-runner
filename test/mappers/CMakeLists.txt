set(TEST_SUITE
    mapper_dualshock2_control_test.c
    mapper_qtrhd06a_coords_test.c
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
            pathbot
            devices_mock
            mappers
            unity
    )   

    add_test(${TEST_NAME} ${TEST_NAME})
endforeach()
