add_library(tasks STATIC tasks.c)

target_include_directories(tasks PUBLIC "./inc")

target_link_libraries(tasks 
    PRIVATE 
        core
        utils
)