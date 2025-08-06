add_subdirectory(config)

add_executable(${PROJECT_NAME}
    main.cpp
    isr_event_emitter_adapter.cpp
    manual_control_dispatch_task.cpp
    manual_motion_task.cpp
    manual_mode_switch_task.cpp
    manual_pid_tune_task.cpp
    task_route_tracking.cpp
    task_immediate_stop.cpp
    task_shell_command.cpp
    task_domain_dump.cpp
    task_factory.cpp
    stack_overflow_handler.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        devices
        hardware
        linebot
        adapters
        mappers
        freertos_kernel
        etl
)

target_link_options(${PROJECT_NAME}
    PRIVATE
    -T "${CMAKE_SOURCE_DIR}/scripts/stm32f3_libopencm3.ld"
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
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/apps/freertos
    COMMENT "Flashing ${PROJECT_NAME}.bin"
)
