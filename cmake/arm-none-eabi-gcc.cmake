# Target
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Compilers
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

# Toolchain
set(CMAKE_LINKER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(CMAKE_SIZE arm-none-eabi-size)

# Executable output naming
set(CMAKE_EXECUTABLE_SUFFIX_ASM ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")

# Disable toolchain test programs linking against host
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# CPU and floating-point options
set(ARM_CPU_FLAGS "-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections")

# Common compile flags
set(CMAKE_C_FLAGS "${ARM_CPU_FLAGS}")
set(CMAKE_CXX_FLAGS "${ARM_CPU_FLAGS} -fno-exceptions -fno-rtti -fno-use-cxa-atexit -ffunction-sections -fdata-sections -fno-threadsafe-statics")
set(CMAKE_ASM_FLAGS "${ARM_CPU_FLAGS}")

# Build type-specific optimization
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Og -g3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og -g3")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os")
endif()

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS "--specs=nano.specs --specs=nosys.specs -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections -Wl,--print-memory-usage -Wl,--start-group -lc -lm -Wl,--end-group")
