add_executable(adapters_test)

target_compile_features(adapters_test PRIVATE cxx_std_23)

target_sources(
    adapters_test
        PRIVATE
            motion_l293_test.cpp
            status_indicator_toggle_sequence_test.cpp
)

target_link_libraries(
    adapters_test
        PRIVATE
            linebot
            adapters
            devices_mock
            Catch2::Catch2WithMain
)

catch_discover_tests(
    adapters_test
        ADD_TAGS_AS_LABELS
)
