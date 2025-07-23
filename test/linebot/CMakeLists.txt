add_executable(linebot_test)

# Test scope, go nuts ;)
target_compile_features(linebot_test PRIVATE cxx_std_23)

target_sources(
    linebot_test
        PRIVATE
            name_helpers.cpp
            api_attempt_maneuver_by_remote_test.cpp
            api_attempt_maneuver_by_line_position_test.cpp
            api_attempt_mode_switch_by_remote_test.cpp
            api_attempt_mode_switch_by_line_position_test.cpp
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
