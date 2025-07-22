add_library(linebot)

target_sources(
    linebot
        PRIVATE
            api.cpp
            coordinates.cpp
)

target_include_directories(
    linebot
        PUBLIC
            "./inc"
)

target_link_libraries(
    linebot
        PUBLIC
            etl
)
