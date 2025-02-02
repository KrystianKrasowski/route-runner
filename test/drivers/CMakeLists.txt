set(TEST_SUITE
    spi_test.c
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
            drivers
            unity
            stm32f303x8
    )   

    add_test(${TEST_NAME} ${TEST_NAME})
endforeach()