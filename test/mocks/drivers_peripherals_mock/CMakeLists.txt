add_library(drivers_peripherals_mock STATIC
    tim2_mock.h
    tim2_mock.c
    tim3_mock.h
    tim3_mock.c
    spi_mock.h
    spi_mock.c
    gpio_mock.h
    gpio_mock.c
    adc_mock.h
    adc_mock.c
)

target_include_directories(drivers_peripherals_mock PUBLIC "./")

target_link_libraries(drivers_peripherals_mock PUBLIC drivers_peripherals)