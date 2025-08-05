add_executable(mappers_test)

target_compile_features(mappers_test PRIVATE cxx_std_23)

target_sources(
    mappers_test
        PRIVATE
            dualshock2_mapper_remote_control_test.cpp
            qtrhd06a_mapper_coordinates_test.cpp
)

target_link_libraries(
    mappers_test
        PRIVATE
            mappers
            devices
            linebot
            Catch2::Catch2WithMain
)

catch_discover_tests(
    mappers_test
        ADD_TAGS_AS_LABELS
)
