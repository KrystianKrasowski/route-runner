add_subdirectory(linebot)
add_subdirectory(utils)
add_subdirectory(devices)
add_subdirectory(adapters)

if (TARGET_ARCH STREQUAL "stm32f303x8")
    add_subdirectory(app_bare_stm32f303x8)
endif()

if(TARGET_ARCH STREQUAL "opencm3_stm32f3")
    add_subdirectory(main_libopencm3_stm32f3)
endif()
