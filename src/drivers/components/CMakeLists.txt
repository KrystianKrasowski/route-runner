add_library(drivers_components STATIC
    dualshock2.h
    dualshock2.c
)

target_include_directories(drivers_components PUBLIC "./")

target_link_libraries(drivers_components 
    PRIVATE
        drivers_peripherals
        queue
)