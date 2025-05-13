add_library(pathbot_application STATIC
    handle_commands.c
    store.c
)

set_property(TARGET pathbot_application PROPERTY C_STANDARD 11)

target_include_directories(pathbot_application
    PUBLIC
        "./inc"
)

target_link_libraries(pathbot_application
    PUBLIC
        pathbot_domain
    PRIVATE
        utils
)
