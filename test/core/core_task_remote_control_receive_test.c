#include "core.h"
#include "core_task.h"
#include "queue.h"
#include "unity.h"
#include "unity_config.h"

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

void
should_reveice_remote_control(uint16_t command)
{
    // given
    queue_message_t message = queue_message_create_command(command);
    queue_push(QUEUE_TOPIC_REMOTE_CONTROL, message);

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_task_remote_control_receive(&vehicle);

    // then
    TEST_ASSERT_EQUAL(command, vehicle.command);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_receive_nothing_on_empty_queue);
    RUN_PARAM_TEST(should_reveice_remote_control, CORE_REMOTE_CONTROL_NONE);
    RUN_PARAM_TEST(should_reveice_remote_control, CORE_REMOTE_CONTROL_FORWARD);
    RUN_PARAM_TEST(should_reveice_remote_control, CORE_REMOTE_CONTROL_BACKWARD);
    RUN_PARAM_TEST(should_reveice_remote_control, CORE_REMOTE_CONTROL_LEFT);
    RUN_PARAM_TEST(should_reveice_remote_control, CORE_REMOTE_CONTROL_RIGHT);
    return UNITY_END();
}