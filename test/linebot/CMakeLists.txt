add_executable(linebot_test)

# Test scope, go nuts ;)
target_compile_features(linebot_test PRIVATE cxx_std_23)

target_sources(
    linebot_test
        PRIVATE
            name_helpers.cpp
            api_attempt_maneuver_manual_test.cpp
)

target_include_directories(
    linebot_test
        PRIVATE
        ${fakeit_SOURCE_DIR}/single_header/catch
)

target_link_libraries(
    linebot_test
        PRIVATE
            Catch2::Catch2WithMain
            linebot
)

catch_discover_tests(linebot_test)
