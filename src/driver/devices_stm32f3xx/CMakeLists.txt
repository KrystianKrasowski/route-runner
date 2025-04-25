if(TARGET_ARCH STREQUAL "stm32f303x8")
    add_library(devices_stm32f3xx STATIC
        devices.c
        sysclock.c
        gpio.c
        tim.c
        spi.c
        l293.c
        dualshock2.c
    )

    set_property(TARGET devices_stm32f3xx PROPERTY C_STANDARD 11)

    target_link_libraries(devices_stm32f3xx
        PRIVATE
            devices
            stm32f303x8
            utils
)
endif()
