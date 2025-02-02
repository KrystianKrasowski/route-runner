add_library(usart2)

target_sources(usart2
    PRIVATE
        usart2.c
    PUBLIC 
        FILE_SET 
        HEADERS 
        FILES
            usart2.h
)

target_link_libraries(usart2
    PRIVATE
        stm32f303x8
)