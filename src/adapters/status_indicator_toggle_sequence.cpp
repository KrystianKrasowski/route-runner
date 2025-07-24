#include "adapter/status_indicator_toggle_sequence.hpp"
#include "device/toggle_sequence.hpp"
#include "linebot/domain/mode.hpp"
#include <cstdint>

namespace adapter
{

static constexpr uint8_t ONE_BLINK   = 0b00000001;
static constexpr uint8_t TWO_BLINKS  = 0b00000101;
static constexpr uint8_t FOUR_BLINKS = 0b01010101;

status_indicator_toggle_sequence&
status_indicator_toggle_sequence::of(device::toggle_sequence& blink)
{
    static status_indicator_toggle_sequence adapter{blink};
    return adapter;
}

void
status_indicator_toggle_sequence::apply(linebot::mode mode)
{
    switch (mode)
    {
    case linebot::mode::LINE_DETECTED:
        blink_.change_sequence(TWO_BLINKS);
        break;

    case linebot::mode::FOLLOWING:
    case linebot::mode::RECOVERING:
        blink_.change_sequence(FOUR_BLINKS);
        break;

    case linebot::mode::MANUAL:
    default:
        blink_.change_sequence(ONE_BLINK);
    }
}

} // namespace adapter
