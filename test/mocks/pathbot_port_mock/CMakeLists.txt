add_library(pathbot_port_mock STATIC
    pathbot_port_mock_mode.c
    pathbot_port_mock_motion.c
)

target_include_directories(pathbot_port_mock
    PUBLIC
        "./inc"
)

target_link_libraries(pathbot_port_mock
    PRIVATE
        pathbot
        utils
)
