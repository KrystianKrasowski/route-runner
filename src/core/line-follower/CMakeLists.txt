set(TARGET line_follower)

add_library(${TARGET} STATIC line_follower.c)

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_SOURCE_DIR}/inc/core/line-follower
)