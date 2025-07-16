add_executable(linebot_test)

# Test scope, go nuts ;)
target_compile_features(linebot_test PRIVATE cxx_std_23)

target_sources(
    linebot_test
        PRIVATE
            name_helpers.cpp
            motion_manual_update_test.cpp
            motion_manual_skip_test.cpp
)

target_link_libraries(
    linebot_test
        PRIVATE
            GTest::gtest_main
            GTest::gmock_main
            linebot
)

gtest_discover_tests(linebot_test)
