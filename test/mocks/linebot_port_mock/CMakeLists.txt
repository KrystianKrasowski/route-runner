add_library(linebot_ports_mock STATIC
    linebot_port_mock_mode.c
    linebot_port_mock_motion.c
    linebot_port_mock_control.c
    linebot_port_mock_coords.c
)

target_include_directories(linebot_ports_mock PUBLIC "./inc")

target_link_libraries(linebot_ports_mock
    PUBLIC
        linebot
)