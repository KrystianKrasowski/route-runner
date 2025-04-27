add_library(devices INTERFACE)

set_property(TARGET devices PROPERTY C_STANDARD 11)

target_include_directories(devices
    INTERFACE
        "./inc"
)