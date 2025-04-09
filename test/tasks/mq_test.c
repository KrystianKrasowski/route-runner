#include "mq.h"
#include <unity.h>
#include <stdio.h>

#define TOPIC MQ_TOPIC_REMOTE_CONTROL

void
setUp(void)
{
    mq_init();
}

void
tearDown(void)
{
    mq_clear(TOPIC);
}

void
should_initialize_successfully(void)
{
    // when
    mq_result_t result = mq_init();

    // then
    TEST_ASSERT_EQUAL(MQ_SUCCESS, result);
}

void
should_enqueue(void)
{
    // when
    mq_message_t message_in1 = mq_create_command_message(11);
    mq_result_t  result      = mq_push(TOPIC, message_in1);

    // then
    TEST_ASSERT_EQUAL(MQ_SUCCESS, result);
}

void
should_dequeue_in_FIFO_order(void)
{
    // given
    mq_push(TOPIC, mq_create_command_message(11));
    mq_push(TOPIC, mq_create_command_message(22));
    mq_push(TOPIC, mq_create_command_message(33));

    // when
    mq_message_t message1;
    mq_message_t message2;
    mq_message_t message3;

    mq_pull(TOPIC, &message1);
    mq_pull(TOPIC, &message2);
    mq_pull(TOPIC, &message3);

    // then
    TEST_ASSERT_EQUAL(11, message1.payload.command);
    TEST_ASSERT_EQUAL(22, message2.payload.command);
    TEST_ASSERT_EQUAL(33, message3.payload.command);
}

void
should_not_enqueue_in_full_queue(void)
{
    // given
    for (int i = 0; i < MQ_SIZE; i++)
    {
        mq_push(TOPIC, mq_create_command_message(i + 10));
    }

    // when
    mq_result_t result = mq_push(TOPIC, mq_create_command_message(20));

    // then
    TEST_ASSERT_EQUAL(MQ_FULL, result);
}

void
should_dequeue_null_from_empty_queue(void)
{
    // when
    mq_message_t *message = NULL;
    mq_result_t   result  = mq_pull(TOPIC, message);

    // then
    TEST_ASSERT_NULL(message);
    TEST_ASSERT_EQUAL(MQ_EMPTY, result);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_initialize_successfully);
    RUN_TEST(should_enqueue);
    RUN_TEST(should_dequeue_in_FIFO_order);
    RUN_TEST(should_not_enqueue_in_full_queue);
    RUN_TEST(should_dequeue_null_from_empty_queue);
    return UNITY_END();
}