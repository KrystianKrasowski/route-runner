add_library(queue STATIC queue.c)
target_include_directories(queue PUBLIC ${CMAKE_SOURCE_DIR}/inc/utils)