add_library(core_port_mock STATIC core_port_mock.h core_port_mock.c)

target_include_directories(core_port_mock PUBLIC "./")

target_link_libraries(core_port_mock
    PUBLIC
        core_port
)