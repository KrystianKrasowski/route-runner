cmake_minimum_required(VERSION 3.28)

project(stm32f303x8)

enable_language(C ASM)

add_library(${PROJECT_NAME} STATIC 
    src/system_stm32f3xx.c
    src/syscalls.c
    src/sysmem.c
    src/startup_stm32f303x8.s
)

target_include_directories(${PROJECT_NAME} PUBLIC
    inc/cmsis/device/st/stm32f3xx/include
    inc/cmsis/include
)

target_compile_definitions(${PROJECT_NAME} PUBLIC 
    STM32F303x8
    $<$<CONFIG:Debug>:DEBUG>
)