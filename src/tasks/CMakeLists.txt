add_library(tasks STATIC tasks.c mq.c)

set_property(TARGET tasks PROPERTY C_STANDARD 23)

target_include_directories(tasks PUBLIC "./inc")

target_link_libraries(tasks 
    PRIVATE 
        linebot
        utils
)