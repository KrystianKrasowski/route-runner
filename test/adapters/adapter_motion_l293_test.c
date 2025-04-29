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

#define MOTOR_LEFT     DEVICES_L293_CHANNEL_12
#define MOTOR_RIGHT    DEVICES_L293_CHANNEL_34
#define ROTATION_LEFT  L293_MOCK_ROTATION_LEFT
#define ROTATION_RIGHT L293_MOCK_ROTATION_RIGHT
#define ROTATION_STOP  L293_MOCK_ROTATION_STOP

static linebot_port_motion_t h_adapter;

void
setUp(void)
{
    devices_l293_mock_init();
    adapter_motion_l293_init();

    assert(RESULT_OK ==
           adapter_motion_l293_acquire(MOTOR_LEFT, MOTOR_RIGHT, &h_adapter));
}

void
tearDown(void)
{
    devices_l293_mock_deinit();
    adapter_motion_l293_release(h_adapter);
}

void
should_apply_motion(int8_t                      correction,
                    linebot_direction_t         direction,
                    device_l293_t               h_motor,
                    uint8_t                     expected_duty_cycle,
                    device_l293_mock_rotation_t expected_rotation)
{
    // given
    linebot_motion_t motion = {
        .correction = correction,
        .direction  = direction,
    };

    // when
    linebot_port_motion_apply(h_adapter, &motion);

    // then
    TEST_ASSERT_EQUAL(expected_duty_cycle,
                      devices_l293_mock_verify_duty_cycle(h_motor));
    TEST_ASSERT_EQUAL(expected_rotation,
                      devices_l293_mock_verify_rotation(h_motor));
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_apply_motion,
                   -100,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   -90,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   80,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   -80,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   60,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   -70,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   40,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   -60,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   20,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   -50,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   0,
                   ROTATION_STOP);

    RUN_PARAM_TEST(should_apply_motion,
                   -40,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   20,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   -30,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   40,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   -20,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   60,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   -10,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   80,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   0,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   10,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   20,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   30,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   40,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   50,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   60,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   70,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   80,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   90,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   100,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   -100,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   -90,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   -80,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   -70,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   -60,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   -50,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   -40,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   -30,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   -20,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   -10,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   0,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   10,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   80,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   20,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   60,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   30,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   40,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   40,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   20,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   50,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   0,
                   ROTATION_STOP);

    RUN_PARAM_TEST(should_apply_motion,
                   60,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   20,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   70,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   40,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   80,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   60,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   90,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   80,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   100,
                   LINEBOT_DIRECTION_FORWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   -100,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   -90,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   80,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   -80,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   60,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   -70,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   40,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   -60,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   20,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   -50,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   0,
                   ROTATION_STOP);

    RUN_PARAM_TEST(should_apply_motion,
                   -40,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   20,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   -30,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   40,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   -20,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   60,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   -10,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   80,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   0,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   10,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   20,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   30,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   40,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   50,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   60,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   70,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   80,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   90,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   100,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_LEFT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   -100,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   -90,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   -80,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   -70,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   -60,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   -50,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   -40,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   -30,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   -20,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   -10,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   0,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   10,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   80,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   20,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   60,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   30,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   40,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   40,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   20,
                   ROTATION_LEFT);

    RUN_PARAM_TEST(should_apply_motion,
                   50,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   0,
                   ROTATION_STOP);

    RUN_PARAM_TEST(should_apply_motion,
                   60,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   20,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   70,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   40,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   80,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   60,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   90,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   80,
                   ROTATION_RIGHT);

    RUN_PARAM_TEST(should_apply_motion,
                   100,
                   LINEBOT_DIRECTION_BACKWARD,
                   MOTOR_RIGHT,
                   100,
                   ROTATION_RIGHT);

    return UNITY_END();
}
