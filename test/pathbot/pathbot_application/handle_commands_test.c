#include <pathbot/api.h>
#include <pathbot/domain.h>
#include <pathbot/store.h>
#include <stdint.h>
#include <unity.h>
#include <unity_config.h>

static pathbot_store_t *p_store;

void
setUp(void)
{
    p_store = pathbot_store_get();
}

void
tearDown(void)
{
}

void
should_do_nothing_on_same_command(void)
{
    // given
    uint16_t commands = PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT;
    p_store->commands = commands;

    // when
    int result = pathbot_handle_commands(commands);

    // then
    TEST_ASSERT_EQUAL(PATHBOT_RESULT_NOOP, result);
}

void
should_apply_manual_motion(pathbot_mode_t      current_mode,
                           uint16_t            current_commands,
                           uint16_t            commands,
                           pathbot_direction_t expected_direction,
                           int8_t              expected_correction)
{
    // given
    p_store->mode     = current_mode;
    p_store->commands = current_commands;

    // when
    int result = pathbot_handle_commands(commands);

    // then
    TEST_ASSERT_EQUAL(PATHBOT_RESULT_OK, result);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_TEST(should_do_nothing_on_same_command);

    RUN_PARAM_TEST(should_apply_manual_motion,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_NONE,
                   PATHBOT_COMMAND_FORWARD,
                   PATHBOT_DIRECTION_FORWARD,
                   0);

    return UNITY_END();
}
