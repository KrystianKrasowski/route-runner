add_library(pathbot STATIC
    handle_commands.c
    handle_coords.c
    handle_route_guard_timeout.c
    handle_store_dump.c
    mode.c
    motion.c
    commands.c
    coords.c
    store.c
)

set_property(TARGET pathbot PROPERTY C_STANDARD 11)

target_include_directories(pathbot
    PUBLIC
        "./inc"
)

target_link_libraries(pathbot
    PUBLIC
        utils
)
