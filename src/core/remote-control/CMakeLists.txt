add_library(remote-control STATIC remote-control.h remote-control_dummy.c)

target_include_directories(remote-control PUBLIC "./")

target_link_libraries(remote-control
    PRIVATE
        tim3
        queue
)