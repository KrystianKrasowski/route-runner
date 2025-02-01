add_library(adapter_motion STATIC adapter_motion_usart.c)

target_link_libraries(adapter_motion
    PRIVATE
        core_port
        usart2
)