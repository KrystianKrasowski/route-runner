add_library(adapters STATIC
    adapter_motion_l293.c
)

set_property(TARGET adapters PROPERTY C_STANDARD 11)

target_include_directories(adapters
    PUBLIC
        "./inc"
)

target_link_libraries(adapters
    PRIVATE
        linebot
        devices
        utils
)
