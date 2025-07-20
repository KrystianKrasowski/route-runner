#include "pathbot/domain.h"
#include <devices/l293_mock.h>
#include <pathbot/api.h>
#include <pathbot/port.h>
#include <stdint.h>
#include <unity.h>
#include <unity_config.h>
#include <utils/result.h>

#define MOTOR_LEFT     DEVICE_L293_CHANNEL_12
#define MOTOR_RIGHT    DEVICE_L293_CHANNEL_34
#define ROTATION_LEFT  DEVICE_L293_ROTATION_LEFT
#define ROTATION_RIGHT DEVICE_L293_ROTATION_RIGHT
#define ROTATION_STOP  DEVICE_L293_ROTATION_STOP

void
setUp(void)
{
    device_l293_mock_init();
}

void
tearDown(void)
{
    device_l293_mock_deinit();
}

void
should_apply_motion(
    int8_t                 correction,
    pathbot_direction_t    direction,
    device_l293_t          h_motor,
    uint8_t                expected_duty_cycle,
    device_l293_rotation_t expected_rotation
)
{
    // given
    pathbot_motion_t motion = {
        .correction = correction,
        .direction  = direction,
    };

    // when
    pathbot_port_motion_apply(&motion);

    // then
    TEST_ASSERT_EQUAL(
        expected_duty_cycle, device_l293_mock_verify_duty_cycle(h_motor)
    );
    TEST_ASSERT_EQUAL(
        expected_rotation, device_l293_mock_verify_rotation(h_motor)
    );
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(
        should_apply_motion,
        -100,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -90,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        80,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -80,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        60,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -70,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        40,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -60,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        20,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -50,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        0,
        ROTATION_STOP
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -40,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        20,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -30,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        40,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -20,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        60,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -10,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        80,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        0,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        10,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        20,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        30,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        40,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        50,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        60,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        70,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        80,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        90,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        100,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_LEFT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -100,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -90,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -80,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -70,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -60,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -50,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -40,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -30,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -20,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -10,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        0,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        10,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        80,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        20,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        60,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        30,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        40,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        40,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        20,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        50,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        0,
        ROTATION_STOP
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        60,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        20,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        70,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        40,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        80,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        60,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        90,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        80,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        100,
        PATHBOT_DIRECTION_FORWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -100,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        100,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -90,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        80,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -80,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        60,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -70,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        40,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -60,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        20,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -50,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        0,
        ROTATION_STOP
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -40,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        20,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -30,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        40,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -20,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        60,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -10,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        80,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        0,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        10,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        20,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        30,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        40,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        50,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        60,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        70,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        80,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        90,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        100,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_LEFT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -100,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -90,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -80,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -70,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -60,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -50,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -40,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -30,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -20,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        -10,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        0,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        10,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        80,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        20,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        60,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        30,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        40,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        40,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        20,
        ROTATION_LEFT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        50,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        0,
        ROTATION_STOP
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        60,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        20,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        70,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        40,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        80,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        60,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        90,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        80,
        ROTATION_RIGHT
    );

    RUN_PARAM_TEST(
        should_apply_motion,
        100,
        PATHBOT_DIRECTION_BACKWARD,
        MOTOR_RIGHT,
        100,
        ROTATION_RIGHT
    );

    return UNITY_END();
}
