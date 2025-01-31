add_library(motion STATIC motion.h motion_dummy.c)

target_include_directories(motion PUBLIC "./")

target_link_libraries(motion
    PRIVATE
        queue
        usart2
)