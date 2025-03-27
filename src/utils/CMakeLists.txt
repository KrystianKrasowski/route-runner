add_library(utils STATIC
    stack.c
    queue.c
)

target_include_directories(utils PUBLIC "./inc")