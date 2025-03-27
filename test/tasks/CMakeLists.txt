set(TEST_SUITE
    mq_test.c
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
            tasks
            unity
    )
    add_test(${TEST_NAME} ${TEST_NAME})
endforeach()

