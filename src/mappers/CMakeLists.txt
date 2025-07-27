add_library(mappers INTERFACE)

target_include_directories(
    mappers
        INTERFACE
            "./inc"
)

target_link_libraries(
    mappers
        INTERFACE
            devices
            linebot
)
