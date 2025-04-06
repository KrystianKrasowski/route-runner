add_library(adapters STATIC
    adapter_control_dualshock2.c
    adapter_motion_l293.c
    adapter_mode_indicator_and_guard.c
    adapter_coords_qtrhd06a.c
)

target_link_libraries(adapters
    PRIVATE
        core
        drivers_components
        drivers_peripherals
)