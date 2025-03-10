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
    TEST_ASSERT_TRUE(
        core_position_equals(&initial_position, &vehicle.position));
    TEST_ASSERT_TRUE(core_vehicle_is_position_updated(&vehicle));
}

void
should_receive_line_position_from_queue(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    uint8_t         position[6] = {0, 0, 100, 100, 0, 0};
    queue_message_t message     = queue_message_create_line_position(position);
    queue_push(QUEUE_TOPIC_LINE_POSITION, message);

    // when
    core_task_line_position_receive(&vehicle);

    // then
    core_position_t vehicle_position = core_vehicle_get_line_position(&vehicle);
    TEST_ASSERT_EQUAL(0,
                      core_position_get_by_place(&vehicle_position,
                                                 CORE_POSITION_PLACE_LEFT_3));
    TEST_ASSERT_EQUAL(0,
                      core_position_get_by_place(&vehicle_position,
                                                 CORE_POSITION_PLACE_LEFT_2));
    TEST_ASSERT_EQUAL(100,
                      core_position_get_by_place(&vehicle_position,
                                                 CORE_POSITION_PLACE_LEFT_1));
    TEST_ASSERT_EQUAL(100,
                      core_position_get_by_place(&vehicle_position,
                                                 CORE_POSITION_PLACE_RIGHT_1));
    TEST_ASSERT_EQUAL(0,
                      core_position_get_by_place(&vehicle_position,
                                                 CORE_POSITION_PLACE_RIGHT_2));
    TEST_ASSERT_EQUAL(0,
                      core_position_get_by_place(&vehicle_position,
                                                 CORE_POSITION_PLACE_RIGHT_3));
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_not_receive_anything_on_empty_queue);
    RUN_TEST(should_receive_line_position_from_queue);
    return UNITY_END();
}