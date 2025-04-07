add_library(linebot STATIC 
    linebot.c
    motion.c
    motion_factory.c
    position.c
    position_regulator.c
    coords.c
    mode.c
)

target_include_directories(linebot PUBLIC "./inc")

target_link_libraries(linebot
    PUBLIC
        utils
)