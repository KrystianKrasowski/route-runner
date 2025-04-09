add_library(tasks STATIC tasks.c mq.c)

target_include_directories(tasks PUBLIC "./inc")

target_link_libraries(tasks 
    PRIVATE 
        linebot
        utils
)