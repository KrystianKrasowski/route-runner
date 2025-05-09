add_subdirectory(linebot)
add_subdirectory(utils)
add_subdirectory(devices)
add_subdirectory(adapters)
add_subdirectory(pathbot)

if(TARGET_ARCH STREQUAL "opencm3_stm32f3")
    add_subdirectory(main_libopencm3_stm32f3)
endif()
