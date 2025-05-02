add_subdirectory(devices_interface)

if(TARGET_ARCH STREQUAL "stm32f303x8")
    add_subdirectory(devices_stm32f3xx)
endif()

if (TARGET_ARCH STREQUAL "opencm3_stm32f3")
    add_subdirectory(devices_opencm3_stm32f3)
endif()
