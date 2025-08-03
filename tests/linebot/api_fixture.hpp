#pragma once

#include "linebot/api.hpp"
#include "linebot/data_store.hpp"
#include "motion_port_mock.hpp"
#include "printer_port_mock.hpp"
#include "route_guard_port_mock.hpp"
#include "status_indicator_port_mock.hpp"

namespace linebot
{

struct api_fixture
{
    data_store                 store_;
    motion_port_mock           motion_;
    status_indicator_port_mock status_indicator_;
    route_guard_port_mock      route_guard_;
    printer_port_mock          printer_;
    api                        api_;

    api_fixture()
        : store_{data_store::of()},
          api_{api::of(
              store_, motion_, status_indicator_, route_guard_, printer_
          )}
    {
    }
};

} // namespace linebot
