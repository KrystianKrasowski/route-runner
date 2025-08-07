add_executable(linebot_test)

# Test scope, go nuts ;)
target_compile_features(linebot_test PRIVATE cxx_std_23)

target_sources(
    linebot_test
        PRIVATE
            name_helpers.cpp
            api_apply_motion_by_remote_test.cpp
            api_apply_motion_by_line_position_test.cpp
            api_switch_mode_by_remote_test.cpp
            api_switch_mode_by_line_position.cpp
            api_toggle_route_guard_test.cpp
            api_halt_test.cpp
            api_dump_store_test.cpp
            api_tune_pid_test.cpp
            api_query_remote_control_test.cpp
            api_query_line_position_test.cpp
)

target_link_libraries(
    linebot_test
        PRIVATE
            Catch2::Catch2WithMain
            linebot
)

catch_discover_tests(
    linebot_test
        ADD_TAGS_AS_LABELS
)
