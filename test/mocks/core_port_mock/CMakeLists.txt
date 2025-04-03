add_library(core_ports_mock STATIC
    core_port_mock_motion.c
    core_port_mock_mode_indicator.c
)

target_include_directories(core_ports_mock PUBLIC "./inc")

target_link_libraries(core_ports_mock
    PUBLIC
        core
)