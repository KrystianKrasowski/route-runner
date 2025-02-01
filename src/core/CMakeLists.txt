add_library(core_port INTERFACE core_port.h core_type.h)
target_include_directories(core_port INTERFACE "./")

add_library(core STATIC 
    core.h 
    core.c
    core_task_remote_control_receive.c
    core_task_motion_update.c
)

target_include_directories(core PUBLIC "./")

target_link_libraries(core
    PRIVATE
        queue
        core_port
)