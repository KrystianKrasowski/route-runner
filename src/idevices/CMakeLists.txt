add_library(idevices INTERFACE)

target_include_directories(
    idevices
        INTERFACE
            "./inc"
)

target_link_libraries(
    idevices
        INTERFACE
            etl
)
