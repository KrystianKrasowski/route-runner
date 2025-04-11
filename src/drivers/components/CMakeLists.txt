add_library(drivers_components STATIC
    dualshock2.h
    dualshock2.c
    l293.h
    l293.c
    qtrhd06a.h
    qtrhd06a.c
)

set_property(TARGET drivers_components PROPERTY C_STANDARD 11)

target_include_directories(drivers_components PUBLIC "./")

target_link_libraries(drivers_components 
    PRIVATE
        drivers_peripherals
        mq
)