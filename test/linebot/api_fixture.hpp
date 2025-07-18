#pragma once

#include "linebot/api.hpp"
#include "linebot/data_store.hpp"
#include "motion_port_mock.hpp"

namespace linebot
{

struct api_fixture
{
    data_store       store_;
    motion_port_mock motion_port_;
    api              api_;

    api_fixture()
        : api_{api::of(store_, motion_port_)}
    {
    }
};

} // namespace linebot
