if(TARGET_ARCH STREQUAL "libopencm3_stm32f3")
    add_subdirectory(libopencm3)
endif()

if(TARGET_ARCH STREQUAL "test")
    add_subdirectory(unity)
endif()

#add_subdirectory(freertos_kernel)
