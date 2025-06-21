FetchContent_MakeAvailable(libopencm3)
FetchContent_GetProperties(libopencm3)

add_custom_target(libopencm3 
    COMMAND make TARGETS=stm32/f3 
    WORKING_DIRECTORY ${libopencm3_SOURCE_DIR}
    COMMENT "Building libopencm3 library"
)

add_library(libopencm3_stm32f3 STATIC IMPORTED GLOBAL)

set_target_properties(libopencm3_stm32f3 PROPERTIES
    IMPORTED_LOCATION ${libopencm3_SOURCE_DIR}/lib/libopencm3_stm32f3.a
    INTERFACE_INCLUDE_DIRECTORIES ${libopencm3_SOURCE_DIR}/include
)

add_dependencies(libopencm3_stm32f3 libopencm3)

target_link_directories(libopencm3_stm32f3 INTERFACE ${libopencm3_SOURCE_DIR}/lib)

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
