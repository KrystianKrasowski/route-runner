#include <unity.h>
#include <unity_config.h>
#include <utils/queue.h>

void
setUp(void)
{
}

void
tearDown(void)
{
}

void
should_initialize_queue(void)
{
    // given
    queue_t queue;
    uint8_t size = QUEUE_MAX_SIZE;

    // when
    queue_result_t result = queue_init(&queue, size, sizeof(uint8_t));

    // then
    TEST_ASSERT_EQUAL(QUEUE_SUCCESS, result);
}

void
should_return_error_on_queue_too_large(void)
{
    // given
    queue_t queue;
    uint8_t size = QUEUE_MAX_SIZE + 1;

    // when
    queue_result_t result = queue_init(&queue, size, sizeof(uint8_t));

    // then
    TEST_ASSERT_EQUAL(QUEUE_SIZE_TOO_LARGE, result);
}

void
should_enqueue_elements(void)
{
    // given
    queue_t queue;
    queue_init(&queue, 3, sizeof(uint16_t));

    uint16_t       element;
    queue_result_t result;

    // when
    element = 111;
    result  = queue_push(&queue, &element);

    // then
    TEST_ASSERT_EQUAL(QUEUE_SUCCESS, result);
    TEST_ASSERT_EQUAL(0, queue_get_head(&queue));
    TEST_ASSERT_EQUAL(1, queue_get_tail(&queue));

    // when
    element = 222;
    result  = queue_push(&queue, &element);

    // then
    TEST_ASSERT_EQUAL(QUEUE_SUCCESS, result);
    TEST_ASSERT_EQUAL(0, queue_get_head(&queue));
    TEST_ASSERT_EQUAL(2, queue_get_tail(&queue));

    // when
    element = 333;
    result  = queue_push(&queue, &element);

    // then
    TEST_ASSERT_EQUAL(QUEUE_SUCCESS, result);
    TEST_ASSERT_EQUAL(0, queue_get_head(&queue));
    TEST_ASSERT_EQUAL(3, queue_get_tail(&queue));
}

void
should_not_enqueue_on_full(void)
{
    // given
    queue_t queue;

    uint16_t element_1 = 111;
    uint16_t element_2 = 222;
    uint16_t element_3 = 333;

    queue_init(&queue, 3, sizeof(uint16_t));
    queue_push(&queue, &element_1);
    queue_push(&queue, &element_2);
    queue_push(&queue, &element_3);

    // when
    uint16_t       element_4 = 444;
    queue_result_t result    = queue_push(&queue, &element_4);

    // then
    TEST_ASSERT_EQUAL(QUEUE_FULL, result);
}

void
should_dequeue_elements(void)
{
    // given
    queue_t        queue;
    queue_result_t result;
    uint16_t       actual_1, actual_2, actual_3;

    uint16_t element_1 = 111;
    uint16_t element_2 = 222;
    uint16_t element_3 = 333;

    queue_init(&queue, 3, sizeof(uint16_t));
    queue_push(&queue, &element_1);
    queue_push(&queue, &element_2);
    queue_push(&queue, &element_3);

    // when
    result = queue_pull(&queue, &actual_1);

    // then
    TEST_ASSERT_EQUAL(QUEUE_SUCCESS, result);
    TEST_ASSERT_EQUAL(111, actual_1);
    TEST_ASSERT_EQUAL(1, queue_get_head(&queue));
    TEST_ASSERT_EQUAL(3, queue_get_tail(&queue));

    // when
    result = queue_pull(&queue, &actual_2);

    // then
    TEST_ASSERT_EQUAL(QUEUE_SUCCESS, result);
    TEST_ASSERT_EQUAL(222, actual_2);
    TEST_ASSERT_EQUAL(2, queue_get_head(&queue));
    TEST_ASSERT_EQUAL(3, queue_get_tail(&queue));

    // when
    result = queue_pull(&queue, &actual_3);

    // then
    TEST_ASSERT_EQUAL(QUEUE_SUCCESS, result);
    TEST_ASSERT_EQUAL(333, actual_3);
    TEST_ASSERT_EQUAL(3, queue_get_head(&queue));
    TEST_ASSERT_EQUAL(3, queue_get_tail(&queue));
}

void
should_not_dequeue_on_empty(void)
{
    // given
    queue_t queue;
    queue_init(&queue, 3, sizeof(uint16_t));

    // when
    uint16_t       element;
    queue_result_t result = queue_pull(&queue, &element);

    // then
    TEST_ASSERT_EQUAL(QUEUE_EMPTY, result);
}

void
should_enqueue_circular(void)
{
    // given
    queue_t        queue;
    uint16_t       actual_1;

    uint16_t element_1 = 111;
    uint16_t element_2 = 222;
    uint16_t element_3 = 333;

    queue_init(&queue, 3, sizeof(uint16_t));
    queue_push(&queue, &element_1);
    queue_push(&queue, &element_2);
    queue_push(&queue, &element_3);

    // when
    queue_pull(&queue, &actual_1);
    queue_push(&queue, &element_2);

    // then
    TEST_ASSERT_EQUAL(1, queue_get_head(&queue));
    TEST_ASSERT_EQUAL(0, queue_get_tail(&queue));
}

void
should_clear(void)
{
    // given
    queue_t        queue;
    uint16_t element_1 = 111;
    uint16_t element_2 = 222;
    uint16_t element_3 = 333;

    queue_init(&queue, 3, sizeof(uint16_t));
    queue_push(&queue, &element_1);
    queue_push(&queue, &element_2);
    queue_push(&queue, &element_3);

    // when
    queue_clear(&queue);

    // then
    TEST_ASSERT_EQUAL(0, queue_get_head(&queue));
    TEST_ASSERT_EQUAL(0, queue_get_tail(&queue));
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_return_error_on_queue_too_large);
    RUN_TEST(should_initialize_queue);
    RUN_TEST(should_enqueue_elements);
    RUN_TEST(should_not_enqueue_on_full);
    RUN_TEST(should_dequeue_elements);
    RUN_TEST(should_not_dequeue_on_empty);
    RUN_TEST(should_enqueue_circular);
    RUN_TEST(should_clear);
    return UNITY_END();
}