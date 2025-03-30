add_library(core STATIC 
    core_vehicle.c
    core_motion.c
    core_coords.c
    core_position.c
    core_mode.c
)

target_include_directories(core PUBLIC "./inc")

target_link_libraries(core
    PUBLIC
        utils
)