add_library(devices_mock STATIC
    device_l293_mock.c
    device_dualshock2_mock.c
    device_qtrhd06a_mock.c
    device_blink_mock.c
    device_timeout_guard_mock.c
)

target_include_directories(devices_mock
    PUBLIC
        "./inc"
)

target_link_libraries(devices_mock
    PUBLIC
        devices
        utils
)
