add_subdirectory(pathbot)
add_subdirectory(utils)
add_subdirectory(devices)
add_subdirectory(mappers)
add_subdirectory(adapters)

if(TARGET_ARCH STREQUAL "opencm3_stm32f3")
    add_subdirectory(main_libopencm3_stm32f3)
endif()
