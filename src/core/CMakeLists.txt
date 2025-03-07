add_library(core STATIC 
    core_vehicle.c
    core_motion.c
    core_position.c
    core_task_remote_control_receive.c
    core_task_motion_update.c
    core_task_state_indicator_update.c
    core_task_line_position_receive.c
    core_task_vehicle_state_update.c
    core_remote_control_apply_chain.c
    core_vehicle_state_transition_chain.c
)

target_include_directories(core PUBLIC "./inc")

target_link_libraries(core
    PUBLIC
        utils
)