include(${CMAKE_SOURCE_DIR}/cmake/libopencm3-stm32f3.cmake)

add_library(devices_opencm3_stm32f3 STATIC
    devices.c
    l293.c
    dualshock2.c
    isr_dispatch.c
    data_store.c
    qtrhd06a.c
    systick.c
    peripherals.c
    blink.c
    notification.c
    timeout_guard.c
    serial.c
)

set_property(TARGET devices_opencm3_stm32f3 PROPERTY C_STANDARD 11)

target_link_libraries(devices_opencm3_stm32f3
    PUBLIC
        opencm3_stm32f3
        devices
    PRIVATE
        utils
)
