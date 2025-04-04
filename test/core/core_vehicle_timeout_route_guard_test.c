#include <core/vehicle.h>
#include <core_port_mock_route_guard.h>
#include <unity.h>
#include <unity_config.h>

void
setUp(void)
{
    core_port_mock_route_guard_init();
}

void
tearDown(void)
{
}

void
should_stop_route_guard_on_timeout(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_vehicle_timeout_route_guard_old(&vehicle);

    // then
    TEST_ASSERT_EQUAL(1, core_port_mock_route_guard_verify_stop_calls());
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_stop_route_guard_on_timeout);
    return UNITY_END();
}