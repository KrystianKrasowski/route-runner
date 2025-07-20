#include "adapter/status_indicator_dummy.hpp"
#include "linebot/domain/mode.hpp"

namespace adapter
{

status_indicator_dummy&
status_indicator_dummy::of()
{
    static status_indicator_dummy adapter;
    return adapter;
}

void
status_indicator_dummy::apply(linebot::mode mode)
{
}

} // namespace adapter
