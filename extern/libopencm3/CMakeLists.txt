add_custom_target(
    libopencm3 
        COMMAND make TARGETS=stm32/f3 
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libopencm3-src
        COMMENT "Building libopencm3 library"
)

add_library(libopencm3_stm32f3 STATIC IMPORTED GLOBAL)

set_target_properties(libopencm3_stm32f3 PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libopencm3-src/lib/libopencm3_stm32f3.a
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/libopencm3-src/include
)

add_dependencies(libopencm3_stm32f3 libopencm3)

target_link_directories(libopencm3_stm32f3 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/libopencm3-src/lib)

target_compile_definitions(libopencm3_stm32f3 INTERFACE -DSTM32F3)

set(COMPILE_OPTIONS
    --static
    -nostartfiles
    -fno-common
    -mcpu=cortex-m4
    -mthumb
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
)

target_compile_options(libopencm3_stm32f3 INTERFACE ${COMPILE_OPTIONS})

target_link_options(libopencm3_stm32f3 INTERFACE ${COMPILE_OPTIONS})
