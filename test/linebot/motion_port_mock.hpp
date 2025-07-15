#pragma once

#include "linebot/motion_port.hpp"
#include "gmock/gmock.h"

namespace linebot
{

class motion_port_mock : public motion_port
{
public:

    MOCK_METHOD(void, apply, (maneuver & motion), (override));
};

} // namespace linebot
