add_library(utils STATIC
    stack.c
)

target_include_directories(utils PUBLIC "./inc")