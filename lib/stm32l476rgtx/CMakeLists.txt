cmake_minimum_required(VERSION 3.28)

project(stm32l476rgtx)

enable_language(C ASM)

add_library(${PROJECT_NAME} STATIC 
    src/system_stm32l4xx.c
    src/syscalls.c
    src/sysmem.c
    src/startup_stm32l476xx.s
)

target_include_directories(${PROJECT_NAME} PUBLIC
    inc/cmsis/device/st/stm32l4xx/include
    inc/cmsis/include
)

target_compile_definitions(${PROJECT_NAME} PUBLIC 
	STM32L476xx
    $<$<CONFIG:Debug>:DEBUG>
)