add_library(pathbot_domain STATIC
    pathbot.c
    mode.c
    coords.c
    commands.c
    motion.c
)

target_include_directories(pathbot_domain
    PUBLIC
        "./inc"
)

target_link_libraries(pathbot_domain
    PRIVATE
        utils
)
