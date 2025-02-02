add_library(adapters STATIC
    adapter_remote_control_dualshock2.c
    adapter_motion_usart.c
)

target_link_libraries(adapters
    PRIVATE
        core
        usart2
        dualshock2
)