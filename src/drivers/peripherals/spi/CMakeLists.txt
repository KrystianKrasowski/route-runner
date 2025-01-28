add_library(spi INTERFACE spi.h)

target_include_directories(spi
    INTERFACE
        "./"
)

add_library(spi_stm32f303x8 spi_stm32f303x8.c)

target_link_libraries(spi_stm32f303x8 
    INTERFACE spi
    PRIVATE stm32f303x8
)