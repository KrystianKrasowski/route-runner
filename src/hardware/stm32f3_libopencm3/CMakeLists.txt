add_library(hardware)

target_sources(hardware
    PRIVATE
        isr_registry.cpp
        isr_handler_tim7.cpp
        toggle_sequence_gpio.cpp
        peripherals.cpp
        tree.cpp
)

target_link_libraries(hardware
    PUBLIC
        idevices
        libopencm3_stm32f3
    PRIVATE
        etl
)

target_include_directories(hardware
    PUBLIC
        "./inc"
)
