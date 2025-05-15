add_library(pathbot_domain STATIC
    pathbot.c
    mode.c
    coords.c
    commands.c
    motion.c
)

set_property(TARGET pathbot_domain PROPERTY C_STANDARD 11)

target_include_directories(pathbot_domain
    PUBLIC
        "./inc"
)

target_link_libraries(pathbot_domain
    PUBLIC
        utils
)
