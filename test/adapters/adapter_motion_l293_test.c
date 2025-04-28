#include "devices/l293.h"
#include "linebot/motion.h"
#include <adapters/motion_l293.h>
#include <assert.h>
#include <devices/l293_mock.h>
#include <linebot/motion.h>
#include <linebot/port.h>
#include <stdint.h>
#include <unity.h>
#include <unity_config.h>
#include <utils/result.h>

static linebot_port_motion_t h_adapter;

void
setUp(void)
{
    devices_l293_mock_init();
    linebot_motion_init();
    adapter_motion_l293_init();

    assert(RESULT_OK == adapter_motion_l293_acquire(DEVICES_L293_CHANNEL_12,
                                                    DEVICES_L293_CHANNEL_34,
                                                    &h_adapter));
}

void
tearDown(void)
{
    devices_l293_mock_deinit();
    adapter_motion_l293_release(h_adapter);
}

void
should_set_state(linebot_motion_direction_t direction,
                 uint8_t                    correction,
                 l293_t                     h_l293_channel,
                 l293_mock_state_t          expected_state,
                 uint8_t                    expected_duty_cycle)
{
    // given
    linebot_motion_t h_motion;
    assert(RESULT_OK ==
           linebot_motion_acquire(direction, correction, &h_motion));

    // when
    linebot_port_motion_apply(h_motion);

    // then
    TEST_ASSERT_EQUAL(expected_state,
                      devices_l293_mock_get_state(h_l293_channel));
    TEST_ASSERT_EQUAL(expected_duty_cycle,
                      devices_l293_mock_get_ducy_cycle(h_l293_channel));

    // release
    linebot_motion_release(h_motion);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_set_state,
                   LINEBOT_MOTION_NONE,
                   0,
                   DEVICES_L293_CHANNEL_12,
                   L293_MOCK_STATE_STOP,
                   0);

    RUN_PARAM_TEST(should_set_state,
                   LINEBOT_MOTION_NONE,
                   0,
                   DEVICES_L293_CHANNEL_34,
                   L293_MOCK_STATE_STOP,
                   0);

    return UNITY_END();
}
