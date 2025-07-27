add_library(
    adapters 
        STATIC
            motion_l293.cpp
            status_indicator_toggle_sequence.cpp
            route_guard_timeout.cpp
            printer_shell.cpp
)

target_link_libraries(
    adapters
        PRIVATE
            devices
            linebot
            etl
)

target_include_directories(
    adapters
        PUBLIC
            "./inc"
)
