add_library(
    adapters 
        STATIC
            adapter_motion_l293.c
            adapter_mode_listener.c
            adapter_dump_serial.c
            motion_l293.cpp
            status_indicator_dummy.cpp
)

target_link_libraries(
    adapters
        PRIVATE
            pathbot
            devices
            utils
            linebot
            idevices
            etl
)

target_include_directories(
    adapters
        PUBLIC
            "./inc"
)
