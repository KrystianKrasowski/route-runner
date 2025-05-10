add_library(pathbot STATIC
    pathbot.c
    mode.c
    coords.c
    commands.c
)

target_include_directories(pathbot
    PUBLIC
        "./inc"
)

target_link_libraries(pathbot
    PRIVATE
        utils
)
