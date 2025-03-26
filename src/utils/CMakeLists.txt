add_library(utils STATIC
    stack.h
    stack.c
)

target_include_directories(utils PUBLIC "./")