add_library(stm32f303x8 INTERFACE)

target_include_directories(stm32f303x8 INTERFACE
    inc/cmsis/device/st/stm32f3xx/include
    inc/cmsis/include
)

target_compile_definitions(stm32f303x8 INTERFACE 
    STM32F303x8
    $<$<CONFIG:Debug>:DEBUG>
)