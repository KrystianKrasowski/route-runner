add_library(core STATIC 
    core_vehicle.c
    core_motion.c
    core_motion_factory.c
    core_coords.c
    core_position.c
    core_position_regulator.c
    core_mode.c
    core_control.c
)

target_include_directories(core PUBLIC "./inc")

target_link_libraries(core
    PUBLIC
        utils
)