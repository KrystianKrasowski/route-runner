add_library(drivers_peripherals INTERFACE
    spi.h
    tim1.h
    tim2.h
    tim3.h
    tim6.h
    tim15.h
    usart2.h
    gpio.h
    adc.h
    sysclock.h
    systick.h
)

set_property(TARGET drivers_peripherals PROPERTY C_STANDARD 11)

target_include_directories(drivers_peripherals 
    INTERFACE 
        "./"
)

if(TARGET_ARCH STREQUAL "stm32f303x8")
    add_library(drivers_stm32f303x8 STATIC
        spi_transfer.h
        spi_transfer.c
        spi.c
        tim1.c
        tim2.c
        tim3.c
        tim6.c
        tim15.c
        usart2.c
        gpio.c
        adc.c
        sysclock.c
        systick.c
    )
    set_property(TARGET drivers_stm32f303x8 PROPERTY C_STANDARD 11)

    target_link_libraries(drivers_stm32f303x8
        PUBLIC
            drivers_peripherals
        PRIVATE
            utils
            stm32f303x8
    )
endif()