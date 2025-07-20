add_library(mappers STATIC
    mapper_dualshock2_control.c
    mapper_qtrhd06a_coords.c
)

target_include_directories(mappers
    PUBLIC
        "./inc"
)

target_link_libraries(mappers
    PRIVATE
        devices
        idevices
        pathbot
        linebot
)
