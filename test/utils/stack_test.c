#include <stack.h>
#include <unity.h>
#include <unity_config.h>

void
setUp(void)
{
}

void
tearDown(void)
{
}

void
should_fail_while_initializing_too_big_stack(uint8_t size)
{
    // given
    stack_t stack;

    // when
    stack_result_t result = stack_init(&stack, size);

    // then
    TEST_ASSERT_EQUAL(STACK_SIZE_EXCEEDED, result);
}

void
should_successfully_init_stack(void)
{
    // given
    stack_t stack;

    // when
    stack_result_t result = stack_init(&stack, 5);

    // then
    TEST_ASSERT_EQUAL(STACK_SUCCESS, result);
    TEST_ASSERT_EQUAL(5, stack_get_size(&stack));
    TEST_ASSERT_EQUAL(-1, stack_get_top_index(&stack));
    TEST_ASSERT_TRUE(stack_is_empty(&stack));
}

void
should_successfully_push_element_on_stack(void)
{
    // given
    stack_t stack;
    stack_init(&stack, 3);

    // when
    stack_result_t result;
    result = stack_push(&stack, 100);

    // then
    TEST_ASSERT_EQUAL(STACK_SUCCESS, result);
    TEST_ASSERT_EQUAL(0, stack_get_top_index(&stack));

    uint16_t expected_element;
    stack_get_element(&stack, 0, &expected_element);
    TEST_ASSERT_EQUAL(100, expected_element);
}

void
should_increase_top_index_while_pushing_on_stack(void)
{
    // given
    stack_t stack;
    stack_init(&stack, 3);

    // when
    stack_result_t result;
    stack_push(&stack, 100);
    stack_push(&stack, 200);
    result = stack_push(&stack, 300);

    // then
    TEST_ASSERT_EQUAL(STACK_SUCCESS, result);
    TEST_ASSERT_EQUAL(2, stack_get_top_index(&stack));
}

void
should_fail_while_pushing_on_full_stack(void)
{
    // given
    stack_t stack;
    stack_init(&stack, 2);

    // when
    stack_result_t result;
    stack_push(&stack, 100);
    stack_push(&stack, 200);
    result = stack_push(&stack, 300);

    // then
    TEST_ASSERT_EQUAL(STACK_FULL, result);
}

void
should_successfully_roll_while_pushing_on_stack(void)
{
    // given
    stack_t stack;
    stack_init(&stack, 3);

    // when
    stack_push(&stack, 100);
    stack_push(&stack, 200);
    stack_push(&stack, 300);
    stack_push_rolling(&stack, 400);
    stack_push_rolling(&stack, 500);

    // then
    uint16_t bottom;
    stack_peek_bottom(&stack, &bottom);
    TEST_ASSERT_EQUAL(300, bottom);

    // when
    uint16_t top;
    stack_pop(&stack, &top);
    TEST_ASSERT_EQUAL(500, top);
}

void
should_successfully_pop_from_stack(void)
{
    // given
    stack_t stack;
    stack_init(&stack, 3);

    // when
    stack_push(&stack, 100);
    stack_push(&stack, 200);
    stack_push(&stack, 300);

    // then
    TEST_ASSERT_EQUAL(2, stack_get_top_index(&stack));

    // when
    uint16_t last_in;
    stack_result_t result = stack_pop(&stack, &last_in);

    // then
    TEST_ASSERT_EQUAL(STACK_SUCCESS, result);
    TEST_ASSERT_EQUAL(300, last_in);
    TEST_ASSERT_EQUAL(1, stack_get_top_index(&stack));
    
}

void
should_fail_while_popping_from_empty_stack(void)
{
    // given
    stack_t stack;
    stack_init(&stack, 3);

    // when
    uint16_t last_in;
    stack_result_t result = stack_pop(&stack, &last_in);

    TEST_ASSERT_EQUAL(STACK_EMPTY, result);
}

void
should_successfully_peek_stack(void)
{
    // given
    stack_t stack;
    stack_init(&stack, 3);
    stack_push(&stack, 100);
    stack_push(&stack, 200);
    stack_push(&stack, 300);

    // when
    uint16_t element;
    stack_result_t result = stack_peek(&stack, &element);

    // then
    TEST_ASSERT_EQUAL(STACK_SUCCESS, result);
    TEST_ASSERT_EQUAL(300, element);
    TEST_ASSERT_TRUE(stack_is_full(&stack));
}

void
should_fail_while_peeking_empty_stack(void)
{
    // given
    stack_t stack;
    stack_init(&stack, 3);

    // when
    uint16_t element;
    stack_result_t result = stack_peek(&stack, &element);

    // then
    TEST_ASSERT_EQUAL(STACK_EMPTY, result);
}

void
should_sum_stack(void)
{
    // given
    stack_t stack;
    stack_init(&stack, 3);
    stack_push(&stack, 1);
    stack_push(&stack, 2);
    stack_push(&stack, 3);

    // when
    int16_t sum = stack_sum(&stack);

    // then
    TEST_ASSERT_EQUAL(6, sum);
}

void
should_sum_incomplete_stack(void)
{
    // given
    stack_t stack;
    stack_init(&stack, 10);
    stack_push(&stack, 1);
    stack_push(&stack, 2);
    stack_push(&stack, 3);

    // when
    int16_t sum = stack_sum(&stack);

    // then
    TEST_ASSERT_EQUAL(6, sum);
}

void
should_sum_empty_stack(void)
{
    // given
    stack_t stack;
    stack_init(&stack, 10);

    // when
    int16_t sum = stack_sum(&stack);

    // then
    TEST_ASSERT_EQUAL(0, sum);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_PARAM_TEST(should_fail_while_initializing_too_big_stack, 16);
    RUN_PARAM_TEST(should_fail_while_initializing_too_big_stack, 17);
    RUN_PARAM_TEST(should_fail_while_initializing_too_big_stack, 18);
    RUN_PARAM_TEST(should_fail_while_initializing_too_big_stack, 19);
    RUN_TEST(should_successfully_init_stack);
    RUN_TEST(should_successfully_push_element_on_stack);
    RUN_TEST(should_increase_top_index_while_pushing_on_stack);
    RUN_TEST(should_fail_while_pushing_on_full_stack);
    RUN_TEST(should_successfully_roll_while_pushing_on_stack);
    RUN_TEST(should_successfully_pop_from_stack);
    RUN_TEST(should_fail_while_popping_from_empty_stack);
    RUN_TEST(should_successfully_peek_stack);
    RUN_TEST(should_fail_while_peeking_empty_stack);
    RUN_TEST(should_sum_stack);
    RUN_TEST(should_sum_incomplete_stack);
    RUN_TEST(should_sum_empty_stack);
    return UNITY_END();
}