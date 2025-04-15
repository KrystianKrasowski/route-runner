#include <unity.h>
#include <unity_config.h>
#include <utils/queue.h>

QUEUE_DECLARE(dummy, uint16_t, 3)

void
setUp(void)
{
}

void
tearDown(void)
{
}

void
should_enqueue_elements(void)
{
    // given
    dummy_queue_t queue;
    dummy_queue_init(&queue);

    uint16_t element;
    int      result;

    // when
    element = 111;
    result  = dummy_queue_push(&queue, &element);

    // then
    TEST_ASSERT_EQUAL(0, result);

    // when
    element = 222;
    result  = dummy_queue_push(&queue, &element);

    // then
    TEST_ASSERT_EQUAL(0, result);

    // when
    element = 333;
    result  = dummy_queue_push(&queue, &element);

    // then
    TEST_ASSERT_EQUAL(0, result);
}

void
should_not_enqueue_on_full(void)
{
    // given
    dummy_queue_t queue;

    uint16_t element_1 = 111;
    uint16_t element_2 = 222;
    uint16_t element_3 = 333;

    dummy_queue_init(&queue);
    dummy_queue_push(&queue, &element_1);
    dummy_queue_push(&queue, &element_2);
    dummy_queue_push(&queue, &element_3);

    // when
    uint16_t element_4 = 444;
    int      result    = dummy_queue_push(&queue, &element_4);

    // then
    TEST_ASSERT_EQUAL(-ENOBUFS, result);
}

void
should_dequeue_elements(void)
{
    // given
    dummy_queue_t queue;
    int           result;
    uint16_t      actual_1, actual_2, actual_3;

    uint16_t element_1 = 111;
    uint16_t element_2 = 222;
    uint16_t element_3 = 333;

    dummy_queue_init(&queue);
    dummy_queue_push(&queue, &element_1);
    dummy_queue_push(&queue, &element_2);
    dummy_queue_push(&queue, &element_3);

    // when
    result = dummy_queue_pull(&queue, &actual_1);

    // then
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(111, actual_1);

    // when
    result = dummy_queue_pull(&queue, &actual_2);

    // then
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(222, actual_2);

    // when
    result = dummy_queue_pull(&queue, &actual_3);

    // then
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(333, actual_3);
}

void
should_not_dequeue_on_empty(void)
{
    // given
    dummy_queue_t queue;
    dummy_queue_init(&queue);

    // when
    uint16_t element;
    int      result = dummy_queue_pull(&queue, &element);

    // then
    TEST_ASSERT_EQUAL(-ENODATA, result);
}

void
should_enqueue_circular(void)
{
    // given
    dummy_queue_t queue;
    uint16_t      actual_1;
    int           result;

    uint16_t element_1 = 111;
    uint16_t element_2 = 222;
    uint16_t element_3 = 333;
    uint16_t element_4 = 444;

    dummy_queue_init(&queue);
    dummy_queue_push(&queue, &element_1);
    dummy_queue_push(&queue, &element_2);
    dummy_queue_push(&queue, &element_3);

    // when
    result = dummy_queue_push(&queue, &element_4);
    TEST_ASSERT_EQUAL(-ENOBUFS, result);

    // when
    dummy_queue_pull(&queue, &actual_1);
    result = dummy_queue_push(&queue, &element_4);

    // then
    TEST_ASSERT_EQUAL(0, result);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_enqueue_elements);
    RUN_TEST(should_not_enqueue_on_full);
    RUN_TEST(should_dequeue_elements);
    RUN_TEST(should_not_dequeue_on_empty);
    RUN_TEST(should_enqueue_circular);
    return UNITY_END();
}