add_subdirectory(config)

set(FREERTOS_PORT GCC_ARM_CM4F CACHE STRING "")
set(FREERTOS_HEAP 4)

FetchContent_MakeAvailable(freertos_kernel)
