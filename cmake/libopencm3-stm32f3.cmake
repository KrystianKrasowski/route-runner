include(FetchContent)

FetchContent_Declare(libopencm3
    GIT_REPOSITORY https://github.com/libopencm3/libopencm3.git
    GIT_TAG master
)
FetchContent_MakeAvailable(libopencm3)
FetchContent_GetProperties(libopencm3)

add_custom_target(libopencm3 make TARGETS=stm32/f3 WORKING_DIRECTORY ${libopencm3_SOURCE_DIR})

add_library(opencm3_stm32f3 STATIC IMPORTED)
set_property(TARGET opencm3_stm32f3 PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${libopencm3_SOURCE_DIR}/include)
set_property(TARGET opencm3_stm32f3 PROPERTY IMPORTED_LOCATION ${libopencm3_SOURCE_DIR}/lib/libopencm3_stm32f3.a)
add_dependencies(opencm3_stm32f3 libopencm3)
target_link_directories(opencm3_stm32f3 INTERFACE ${libopencm3_SOURCE_DIR}/lib)

target_compile_definitions(opencm3_stm32f3 INTERFACE -DSTM32F3)

set(COMPILE_OPTIONS
    --static
    -nostartfiles
    -fno-common
    -mcpu=cortex-m4
    -mthumb
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
)

target_compile_options(opencm3_stm32f3 INTERFACE ${COMPILE_OPTIONS})
target_link_options(opencm3_stm32f3 INTERFACE ${COMPILE_OPTIONS})
