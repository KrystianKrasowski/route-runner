add_library(adapters STATIC
    adapter_remote_control_dualshock2.c
    adapter_motion_l293.c
    adapter_mode_indicator_led.c
    adapter_coords_qtrhd06a.c
    adapter_debug_usart.c
    adapter_route_guard_tim15.c
)

target_link_libraries(adapters
    PRIVATE
        core
        drivers_components
        drivers_peripherals
)