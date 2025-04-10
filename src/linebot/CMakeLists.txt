add_library(linebot STATIC 
    api.c
    motion.c
    motion_factory.c
    position.c
    position_regulator.c
    coords.c
    mode.c
    command.c
)

set_property(TARGET linebot PROPERTY C_STANDARD 11)

target_include_directories(linebot PUBLIC "./inc")

target_link_libraries(linebot
    PUBLIC
        utils
)