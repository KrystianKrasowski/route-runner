add_library(devices INTERFACE)

target_include_directories(
    devices
        INTERFACE
            "./inc"
)

target_link_libraries(
    devices
        INTERFACE
            etl
)
