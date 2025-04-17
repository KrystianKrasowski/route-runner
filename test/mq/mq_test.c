#include <errno.h>
#include <mq.h>
#include <stdio.h>
#include <string.h>
#include <unity.h>

#define TOPIC MQ_TOPIC_REMOTE_CONTROL

static inline mq_message_t
create_int_message(int const payload)
{
    return mq_create_message(&payload, sizeof(payload));
}

static inline int
parse_payload(mq_message_t const *p_message)
{
    int payload;
    memcpy(&payload, &p_message->payload, sizeof(payload));

    return payload;
}

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
should_enqueue(void)
{
    // when
    mq_message_t message_in1 = create_int_message(11);
    int          result      = mq_push(TOPIC, &message_in1);

    // then
    TEST_ASSERT_EQUAL(0, result);
}

void
should_dequeue_in_FIFO_order(void)
{
    // given
    mq_message_t in1 = create_int_message(11);
    mq_message_t in2 = create_int_message(22);
    mq_message_t in3 = create_int_message(33);

    mq_push(TOPIC, &in1);
    mq_push(TOPIC, &in2);
    mq_push(TOPIC, &in3);

    // when
    mq_message_t out1;
    mq_message_t out2;
    mq_message_t out3;

    mq_pull(TOPIC, &out1);
    mq_pull(TOPIC, &out2);
    mq_pull(TOPIC, &out3);

    // then
    TEST_ASSERT_EQUAL(11, parse_payload(&out1));
    TEST_ASSERT_EQUAL(22, parse_payload(&out2));
    TEST_ASSERT_EQUAL(33, parse_payload(&out3));
}

void
should_not_enqueue_in_full_queue(void)
{
    // given
    for (int i = 0; i < MQ_SIZE; i++)
    {
        mq_message_t message = create_int_message(i + 10);
        mq_push(TOPIC, &message);
    }

    // when
    mq_message_t message = create_int_message(20);
    int          result  = mq_push(TOPIC, &message);

    // then
    TEST_ASSERT_EQUAL(-ENOBUFS, result);
}

void
should_not_dequeue_from_empty_queue(void)
{
    // when
    mq_message_t message;
    int          result = mq_pull(TOPIC, &message);

    // then
    TEST_ASSERT_EQUAL(-ENODATA, result);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_enqueue);
    RUN_TEST(should_dequeue_in_FIFO_order);
    RUN_TEST(should_not_enqueue_in_full_queue);
    RUN_TEST(should_not_dequeue_from_empty_queue);
    return UNITY_END();
}