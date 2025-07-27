add_library(devices_mock INTERFACE)

target_include_directories(
    devices_mock
        INTERFACE
            "./inc"
)

target_link_libraries(
    devices_mock
        INTERFACE
            devices
)
