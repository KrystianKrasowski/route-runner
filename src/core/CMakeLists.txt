# add_subdirectory(line-follower)

set(TARGET core)

add_library(${TARGET} STATIC core.c)

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_SOURCE_DIR}/inc/core
)