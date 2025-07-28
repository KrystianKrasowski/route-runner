if(TARGET_HARDWARE STREQUAL "native_host")
    add_subdirectory(catch2)
endif()

if(TARGET_HARDWARE STREQUAL "stm32f3_libopencm3")
    add_subdirectory(libopencm3)
endif()

if(TARGET_RUNTIME STREQUAL "freertos")
    add_subdirectory(freertos_kernel)
endif()

add_subdirectory(etl)
