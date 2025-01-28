add_executable(spi_stm32f303x8_test spi_stm32f303x8_test.c)

target_link_libraries(spi_stm32f303x8_test 
    INTERFACE
        spi
    PUBLIC
        spi_stm32f303x8
        unity
        stm32f303x8
)

add_test(spi_stm32f303x8_test spi_stm32f303x8_test)