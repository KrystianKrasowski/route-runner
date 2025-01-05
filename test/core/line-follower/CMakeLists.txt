set(TARGET line_follower_test)

add_executable(${TARGET} line_follower_test.c)

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_SOURCE_DIR}/inc/core/line-follower
)

target_link_libraries(${TARGET} PUBLIC line_follower unity)

add_test(${TARGET} ${TARGET})