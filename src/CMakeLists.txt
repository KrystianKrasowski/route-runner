add_subdirectory(linebot)
add_subdirectory(devices)
add_subdirectory(hardware)
add_subdirectory(mappers)
add_subdirectory(adapters)

# "freertos" variable comes from previous implementation, where there was a superloop variant
if(TARGET_HARDWARE STREQUAL "stm32f3_libopencm3" AND TARGET_RUNTIME STREQUAL "freertos")
    add_subdirectory(main_freertos_libopencm3_stm32f3)
endif()

