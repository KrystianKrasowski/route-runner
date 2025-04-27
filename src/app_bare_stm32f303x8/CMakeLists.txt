set(MAIN_EXECUTABLE ${PROJECT_NAME})

add_executable(${MAIN_EXECUTABLE} 
    startup_stm32f303x8.s
    syscalls.c
    sysmem.c
    system_stm32f3xx.c
    # task.c
    # main.c
    # sandbox_legacy_devices.c
    sandbox_devices.c
)

target_link_libraries(${MAIN_EXECUTABLE} 
    PRIVATE
        linebot
        devices
        devices_stm32f3xx
        stm32f303x8
)

add_custom_command(TARGET ${MAIN_EXECUTABLE}
    POST_BUILD
    COMMAND arm-none-eabi-size ${MAIN_EXECUTABLE}.elf
)

add_custom_command(TARGET ${MAIN_EXECUTABLE}
    POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex ${MAIN_EXECUTABLE}.elf ${PROJECT_NAME}.hex
    COMMAND arm-none-eabi-objcopy -O binary ${MAIN_EXECUTABLE}.elf ${PROJECT_NAME}.bin
)

add_custom_target(flash
    COMMAND st-flash write ${MAIN_EXECUTABLE}.bin 0x08000000
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src/app_bare_stm32f303x8
    COMMENT "Flashing ${MAIN_EXECUTABLE}.bin"
)
