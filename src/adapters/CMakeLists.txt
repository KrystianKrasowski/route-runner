add_library(adapters STATIC
    adapter_motion_l293.c
    adapter_mode_listener.c
    adapter_dump_serial.c
)

set_property(TARGET adapters PROPERTY C_STANDARD 11)

target_link_libraries(adapters
    PRIVATE
        pathbot
        devices
        utils
)
