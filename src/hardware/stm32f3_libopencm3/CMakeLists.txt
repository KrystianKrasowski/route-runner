add_library(hardware)

target_sources(hardware
    PRIVATE
        isr_registry.cpp
        isr_handler_tim2.cpp
        isr_handler_tim7.cpp
        isr_handler_dma1_channel2.cpp
        peripherals.cpp
        toggle_sequence_gpio.cpp
        data_store.cpp
        dualshock2.cpp
        l293.cpp
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
