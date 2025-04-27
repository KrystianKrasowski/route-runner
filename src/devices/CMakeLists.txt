add_subdirectory(devices_interface)

if(TARGET_ARCH STREQUAL "stm32f303x8")
    add_subdirectory(devices_stm32f3xx)
endif()
