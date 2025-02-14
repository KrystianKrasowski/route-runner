add_library(drivers_peripherals INTERFACE
    spi.h
    tim3.h
    usart2.h
    gpio.h
)

target_include_directories(drivers_peripherals 
    INTERFACE 
        "./"
)

add_library(drivers_stm32f303x8 STATIC
    spi_transfer.h
    spi_transfer.c
    spi.c
    tim1.c
    tim3.c
    usart2.c
    gpio.c
)

target_link_libraries(drivers_stm32f303x8
    PUBLIC
        drivers_peripherals
    PRIVATE
        queue
        stm32f303x8
)