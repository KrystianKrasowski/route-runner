add_library(hardware)

target_sources(
    hardware
        PRIVATE
            isr_registry.cpp
            isr_handler_tim2.cpp
            isr_handler_tim7.cpp
            isr_handler_tim15.cpp
            isr_handler_dma1_channel1.cpp
            isr_handler_dma1_channel2.cpp
            isr_handler_usart2.cpp
            peripherals.cpp
            toggle_sequence_gpio.cpp
            data_store.cpp
            dualshock2.cpp
            qtrhd06a.cpp
            l293.cpp
            timeout.cpp
            shell.cpp
            tree.cpp
)

target_link_libraries(
    hardware
        PRIVATE
            etl
            libopencm3_stm32f3
            devices
            configuration
)

