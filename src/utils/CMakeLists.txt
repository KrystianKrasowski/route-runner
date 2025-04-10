add_library(utils STATIC
    stack.c
)

set_property(TARGET utils PROPERTY C_STANDARD 11)

target_include_directories(utils PUBLIC "./inc")