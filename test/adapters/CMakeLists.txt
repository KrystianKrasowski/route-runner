set(TEST_SUITE
    adapter_motion_l293_test.c
    adapter_mode_indicator_and_guard_test.c
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
            linebot
            adapters
            drivers_components
            drivers_peripherals_mock
            unity
    )   

    add_test(${TEST_NAME} ${TEST_NAME})
endforeach()