#include "linebot/domain/coordinates.hpp"
#include <cstdint>

namespace linebot
{

static constexpr uint8_t DETECTION_TRESHOLD = 3;

coordinates
coordinates::of_6(
    uint8_t l3, uint8_t l2, uint8_t l1, uint8_t r1, uint8_t r2, uint8_t r3
)
{
    etl::array<uint8_t, max_length> values{l3, l2, l1, r1, r2, r3};
    etl::array<int8_t, max_length>  weights{-100, -40, -20, 20, 40, 100};

    return {values, weights, max_length};
}

bool
coordinates::is_on_route()
{
    for (auto value : values_)
    {
        if (value >= DETECTION_TRESHOLD)
        {
            return true;
        }
    }

    return false;
}

bool
coordinates::is_on_finish()
{
    uint8_t last_index = length_ - 1;
    uint8_t mid_index  = length_ / 2;

    bool first_on_route = values_[0] >= DETECTION_TRESHOLD;
    bool last_on_route  = values_[last_index] >= DETECTION_TRESHOLD;
    bool mid_off_route  = false;

    if ((length_ & 1) == 0)
    {
        mid_off_route = values_[mid_index] < DETECTION_TRESHOLD
                     && values_[mid_index - 1] < DETECTION_TRESHOLD;
    }
    else
    {
        mid_off_route = values_[mid_index + 1] < DETECTION_TRESHOLD
                     && values_[mid_index] < DETECTION_TRESHOLD
                     && values_[mid_index - 1] < DETECTION_TRESHOLD;
    }

    return first_on_route && mid_off_route && last_on_route;
}

bool
coordinates::operator==(const coordinates& other) const
{
    return values_ == other.values_ && weights_ == other.weights_
        && length_ == other.length_;
}

} // namespace linebot
