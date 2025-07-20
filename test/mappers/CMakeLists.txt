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

add_executable(mappers_test)

target_compile_features(mappers_test PRIVATE cxx_std_23)

target_sources(
    mappers_test
        PRIVATE
            dualshock2_mapper_commands_test.cpp
)

target_link_libraries(
    mappers_test
        PRIVATE
            mappers
            idevices
            linebot
            Catch2::Catch2WithMain
)

catch_discover_tests(mappers_test)
