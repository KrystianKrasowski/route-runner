add_library(tim3 STATIC tim3.c tim3.h)

target_include_directories(tim3 PUBLIC "./")

target_link_libraries(tim3 
    PRIVATE 
        stm32f303x8
)