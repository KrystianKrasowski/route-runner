add_library(drivers STATIC)

target_sources(drivers
    PRIVATE
        spi.c
        tim3.c
        usart2.c
        dualshock2.c
        gpio.c
    PUBLIC
        FILE_SET
        HEADERS
        FILES
            spi.h
            tim3.h
            usart2.h
            dualshock2.h
            gpio.h
)

target_link_libraries(drivers
    PRIVATE
        stm32f303x8
        queue
)