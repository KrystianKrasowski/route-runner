set(TEST_SUITE
    adapter_motion_l293_test.c
    adapter_mode_listener_test.c
    adapter_dump_serial_test.c
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
            adapters
            unity
    )   

    add_test(${TEST_NAME} ${TEST_NAME})
endforeach()

add_executable(adapters_test)

target_compile_features(adapters_test PRIVATE cxx_std_23)

target_sources(
    adapters_test
        PRIVATE
            motion_adapter_l293_test.cpp
)

target_link_libraries(
    adapters_test
        PRIVATE
            linebot
            adapters
            devices_mock
            Catch2::Catch2WithMain
)

catch_discover_tests(adapters_test)
