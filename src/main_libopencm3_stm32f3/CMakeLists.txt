include(${CMAKE_SOURCE_DIR}/cmake/libopencm3-stm32f3.cmake)

add_executable(${PROJECT_NAME}
    main.c
)

target_link_libraries(${PROJECT_NAME} stm32f303)

target_link_options(${PROJECT_NAME}
    PRIVATE
    -T "${CMAKE_SOURCE_DIR}/config/stm32f303.ld"
)

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND arm-none-eabi-size ${PROJECT_NAME}.elf
)

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMAND arm-none-eabi-objcopy -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
)

add_custom_target(flash
    COMMAND st-flash write ${PROJECT_NAME}.bin 0x08000000
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src/main_libopencm3_stm32f3
    COMMENT "Flashing ${PROJECT_NAME}.bin"
)
