#include <core.h>
#include <core_port_mock.h>
#include <queue.h>
#include <unity.h>
#include <unity_config.h>

void
setUp(void)
{
}

void
tearDown(void)
{
    core_port_mock_reset();
}

void
should_not_update_motion_on_same_command(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_command(&vehicle, CORE_REMOTE_CONTROL_FORWARD);
    core_vehicle_update_motion(&vehicle);

    // when
    core_vehicle_set_command(&vehicle, CORE_REMOTE_CONTROL_FORWARD);
    core_task_motion_update(&vehicle);

    // then
    TEST_ASSERT_FALSE(core_port_mock_verify_motion_applied());
}

void
should_update_motion_on_different_command(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_command(&vehicle, CORE_REMOTE_CONTROL_NONE);
    core_vehicle_update_motion(&vehicle);

    // when
    core_vehicle_set_command(&vehicle, CORE_REMOTE_CONTROL_FORWARD);
    core_task_motion_update(&vehicle);

    // then
    TEST_ASSERT_TRUE(core_port_mock_verify_motion_applied());
}

int
main()
{
    UNITY_BEGIN();
    RUN_TEST(should_not_update_motion_on_same_command);
    RUN_TEST(should_update_motion_on_different_command);
    return UNITY_END();
}