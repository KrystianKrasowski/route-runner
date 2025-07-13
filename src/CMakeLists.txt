add_subdirectory(pathbot)
add_subdirectory(utils)
add_subdirectory(idevices)
add_subdirectory(hardware)
add_subdirectory(devices)
add_subdirectory(mappers)
add_subdirectory(adapters)

if(TARGET_ARCH STREQUAL "libopencm3_stm32f3" AND TARGET_RUNTIME STREQUAL "superloop")
    add_subdirectory(main_sloop_libopencm3_stm32f3)
endif()

if(TARGET_ARCH STREQUAL "libopencm3_stm32f3" AND TARGET_RUNTIME STREQUAL "freertos")
    add_subdirectory(main_freertos_libopencm3_stm32f3)
endif()

if(TARGET_RUNTIME STREQUAL "sandbox")
    add_subdirectory(main_sandbox)
endif()
