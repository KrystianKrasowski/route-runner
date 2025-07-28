# "freertos" variable comes from previous implementation, where there was also superloop variant
if(TARGET_HARDWARE STREQUAL "stm32f3_libopencm3" AND TARGET_RUNTIME STREQUAL "freertos")
    add_subdirectory(freertos_stm32f3_libopencm3)
endif()
