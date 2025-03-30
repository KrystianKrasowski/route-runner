add_library(core STATIC 
    core_vehicle.c
    core_vehicle_mode_apply.c
    core_vehicle_manual_motion_apply.c
    core_vehicle_tracking_motion_apply.c
    core_motion.c
    core_coords.c
    core_position.c
)

target_include_directories(core PUBLIC "./inc")

target_link_libraries(core
    PUBLIC
        utils
)