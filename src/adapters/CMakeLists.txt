add_library(adapters STATIC
    adapter_remote_control_dualshock2.c
    adapter_motion_l293.c
    adapter_state_indicator_led.c
    adapter_line_position_qtrhd06a.c
)

target_link_libraries(adapters
    PRIVATE
        core
        drivers_components
        drivers_peripherals
)