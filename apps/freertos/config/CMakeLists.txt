add_library(configuration INTERFACE)

target_include_directories(configuration
    INTERFACE
        "./"
)

add_library(freertos_config ALIAS configuration)

