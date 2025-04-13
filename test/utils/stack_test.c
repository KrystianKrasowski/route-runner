#include <utils/stack.h>
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
should_successfully_push_element_on_stack(void)
{
    // given
    stack_t s = stack(3);

    // when
    stack_result_t result;
    result = stack_push(&s, 100);

    // then
    TEST_ASSERT_EQUAL(STACK_SUCCESS, result);

    int16_t expected_element;
    stack_get_element(&s, 0, &expected_element);
    TEST_ASSERT_EQUAL(100, expected_element);
}

void
should_increase_top_index_while_pushing_on_stack(void)
{
    // given
    stack_t st = stack(3);

    // when
    stack_result_t result;
    stack_push(&st, 100);
    stack_push(&st, 200);
    result = stack_push(&st, 300);

    // then
    TEST_ASSERT_EQUAL(STACK_SUCCESS, result);
}

void
should_fail_while_pushing_on_full_stack(void)
{
    // given
    stack_t s = stack(2);

    // when
    stack_result_t result;
    stack_push(&s, 100);
    stack_push(&s, 200);
    result = stack_push(&s, 300);

    // then
    TEST_ASSERT_EQUAL(STACK_FULL, result);
}

void
should_successfully_roll_while_pushing_on_stack(void)
{
    // given
    stack_t s = stack(3);

    // when
    stack_push(&s, 100);
    stack_push(&s, 200);
    stack_push(&s, 300);
    stack_push_rolling(&s, 400);
    stack_push_rolling(&s, 500);

    // then
    int16_t bottom;
    stack_get_element(&s, 0, &bottom);
    TEST_ASSERT_EQUAL(300, bottom);

    // when
    int16_t top;
    stack_pop(&s, &top);
    TEST_ASSERT_EQUAL(500, top);
}

void
should_successfully_pop_from_stack(void)
{
    // given
    stack_t st = stack(3);

    // when
    stack_push(&st, 100);
    stack_push(&st, 200);
    stack_push(&st, 300);

    // when
    int16_t last_in;
    stack_result_t result = stack_pop(&st, &last_in);

    // then
    TEST_ASSERT_EQUAL(STACK_SUCCESS, result);
    TEST_ASSERT_EQUAL(300, last_in);
    
}

void
should_fail_while_popping_from_empty_stack(void)
{
    // given
    stack_t st = stack(3);

    // when
    int16_t last_in;
    stack_result_t result = stack_pop(&st, &last_in);

    TEST_ASSERT_EQUAL(STACK_EMPTY, result);
}

void
should_successfully_peek_stack(void)
{
    // given
    stack_t st = stack(3);
    stack_push(&st, 100);
    stack_push(&st, 200);
    stack_push(&st, 300);

    // when
    int16_t element;
    stack_result_t result = stack_peek(&st, &element);

    // then
    TEST_ASSERT_EQUAL(STACK_SUCCESS, result);
    TEST_ASSERT_EQUAL(300, element);
    TEST_ASSERT_TRUE(stack_is_full(&st));
}

void
should_fail_while_peeking_empty_stack(void)
{
    // given
    stack_t st = stack(3);

    // when
    int16_t element;
    stack_result_t result = stack_peek(&st, &element);

    // then
    TEST_ASSERT_EQUAL(STACK_EMPTY, result);
}

void
should_sum_stack(void)
{
    // given
    stack_t st = stack(3);
    stack_push(&st, 1);
    stack_push(&st, 2);
    stack_push(&st, 3);

    // when
    int16_t sum = stack_sum(&st);

    // then
    TEST_ASSERT_EQUAL(6, sum);
}

void
should_sum_incomplete_stack(void)
{
    // given
    stack_t st = stack(10);
    stack_push(&st, 1);
    stack_push(&st, 2);
    stack_push(&st, 3);

    // when
    int16_t sum = stack_sum(&st);

    // then
    TEST_ASSERT_EQUAL(6, sum);
}

void
should_sum_empty_stack(void)
{
    // given
    stack_t st = stack(3);

    // when
    int16_t sum = stack_sum(&st);

    // then
    TEST_ASSERT_EQUAL(0, sum);
}

int
main(void)
{
    UNITY_BEGIN();
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