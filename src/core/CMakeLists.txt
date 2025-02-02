add_library(core_port INTERFACE)

target_sources(core_port
    INTERFACE
        FILE_SET
        HEADERS
        FILES
            core_port.h
            core_type.h
)

add_library(core STATIC 
    core.h 
    core.c
    core_task_remote_control_receive.c
    core_task_motion_update.c
)

target_include_directories(core PUBLIC "./")

# add_library(core STATIC)

# target_sources(
#     PUBLIC
#         FILE_SET
#         HEADERS
#         FILES
#             core.h
#     PRIVATE
#         core.c
#         core_task_remote_control_receive.c
#         core_task_motion_update.c
# )

target_link_libraries(core
    PRIVATE
        queue
        core_port
)