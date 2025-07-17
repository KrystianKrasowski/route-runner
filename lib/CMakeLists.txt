if(TARGET_ARCH STREQUAL "libopencm3_stm32f3")
    add_subdirectory(libopencm3)
endif()

if(TARGET_ARCH STREQUAL "test")
    add_subdirectory(unity)
endif()

if(TARGET_RUNTIME STREQUAL "freertos")
    add_subdirectory(freertos_kernel)
endif()

add_subdirectory(etl)
