add_library(core STATIC 
    core.h 
    core_vehicle.c
    core_motion.c
    core_task_remote_control_receive.c
    core_task_motion_update.c
    core_task_state_indicator_update.c
    core_task_line_position_receive.c
    core_task_vehicle_state_update.c
)

target_include_directories(core PUBLIC "./")

target_link_libraries(core
    PUBLIC
        utils
)