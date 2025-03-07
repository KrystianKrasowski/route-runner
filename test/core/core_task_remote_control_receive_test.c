#include <core.h>
#include <queue.h>
#include <unity.h>
#include <unity_config.h>

void
setUp(void)
{
    queue_clear(QUEUE_TOPIC_REMOTE_CONTROL);
}

void
tearDown(void)
{
}

void
should_receive_nothing_on_empty_queue()
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_task_remote_control_receive(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_REMOTE_CONTROL_NONE, vehicle.command);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_receive_nothing_on_empty_queue);
    return UNITY_END();
}