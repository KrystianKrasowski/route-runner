set(MAIN_EXECUTABLE ${PROJECT_NAME})

add_executable(${MAIN_EXECUTABLE} main.c)

target_link_libraries(${MAIN_EXECUTABLE} PRIVATE stm32l476rgtx)

add_custom_command(TARGET ${MAIN_EXECUTABLE}
    POST_BUILD
    COMMAND arm-none-eabi-size ${MAIN_EXECUTABLE}.elf
)

add_custom_command(TARGET ${MAIN_EXECUTABLE}
    POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex ${MAIN_EXECUTABLE}.elf ${PROJECT_NAME}.hex
    COMMAND arm-none-eabi-objcopy -O binary ${MAIN_EXECUTABLE}.elf ${PROJECT_NAME}.bin
)