add_library(utils STATIC
    queue.h
    queue.c
    stack.h
    stack.c
)

target_include_directories(utils PUBLIC "./")