add_subdirectory(devices_interface)

if (TARGET_ARCH STREQUAL "libopencm3_stm32f3")
    add_subdirectory(devices_libopencm3_stm32f3)
endif()
