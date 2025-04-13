add_library(mq STATIC mq.c)

set_property(TARGET mq PROPERTY C_STANDARD 11)

target_include_directories(mq PUBLIC "./inc")

target_link_libraries(mq 
    PRIVATE 
        linebot
        adapters
        utils
)