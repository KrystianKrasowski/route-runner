#include "adapter/status_indicator_toggle_sequence.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"
#include "device/toggle_sequence_mock.hpp"
#include "linebot/domain/mode.hpp"
#include <tuple>

namespace adapter
{

TEST_CASE("should indicate linebot mode", "[adapter][mode][toggle_sequence]")
{
    device::toggle_sequence_mock blink;

    auto adapter = status_indicator_toggle_sequence::of(blink);

    SECTION("apply toggle sequence")
    {
        using params_type = std::tuple<linebot::mode, uint8_t>;

        auto params = GENERATE(
            params_type{linebot::mode::MANUAL, 0b00000001},
            params_type{linebot::mode::LINE_DETECTED, 0b00000101},
            params_type{linebot::mode::FOLLOWING, 0b01010101},
            params_type{linebot::mode::RECOVERING, 0b01010101}
        );

        // given
        auto mode              = std::get<0>(params);
        auto expected_sequence = std::get<1>(params);

        // when
        adapter.apply(mode);
        auto actual_sequence = blink.applied_value_;

        // then
        REQUIRE(actual_sequence.has_value());
        CHECK(actual_sequence.value() == expected_sequence);
    }
}

} // namespace adapter
