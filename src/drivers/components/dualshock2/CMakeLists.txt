add_library(dualshock2 STATIC dualshock2.h dualshock2.c)

target_include_directories(dualshock2 PUBLIC "./")

target_link_libraries(dualshock2
    PRIVATE
        queue
        tim3
)