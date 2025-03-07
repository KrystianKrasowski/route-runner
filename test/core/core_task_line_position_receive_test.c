#include <core.h>
#include <queue.h>
#include <unity.h>

void
setUp(void)
{
}

void
tearDown(void)
{
}

void
should_not_receive_anything_on_empty_queue(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    core_position_t initial_position;
    core_position_init(&initial_position);

    // when
    core_task_line_position_receive(&vehicle);

    // then
    TEST_ASSERT_EQUAL(initial_position.left, vehicle.position.left);
    TEST_ASSERT_EQUAL(initial_position.middle, vehicle.position.middle);
    TEST_ASSERT_EQUAL(initial_position.right, vehicle.position.right);
}

void
should_receive_line_position_from_queue(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    uint8_t         position[3] = {15, 110, 15};
    queue_message_t message     = queue_message_create_line_position(position);
    queue_push(QUEUE_TOPIC_LINE_POSITION, message);

    // when
    core_task_line_position_receive(&vehicle);

    // then
    TEST_ASSERT_EQUAL(15, vehicle.position.left);
    TEST_ASSERT_EQUAL(110, vehicle.position.middle);
    TEST_ASSERT_EQUAL(15, vehicle.position.right);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_not_receive_anything_on_empty_queue);
    RUN_TEST(should_receive_line_position_from_queue);
    return UNITY_END();
}