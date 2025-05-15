add_library(pathbot_fixtures STATIC
    fixtures.c
)

target_include_directories(pathbot_fixtures
    PUBLIC
        "./inc"
)

target_link_libraries(pathbot_fixtures
    PRIVATE
        pathbot_domain
)
