#ifndef _CORE_INTERFACE_MOCK_H
#define _CORE_INTERFACE_MOCK_H

#include "core_interface.h"
#include "unity.h"

#define TEST_ASSERT_VEHICLE_RUNNING(running)                                   \
    TEST_ASSERT_EQUAL(running, !core_mock_is_stopped())

#define TEST_ASSERT_VEHICLE_STATE(s)                                           \
    TEST_ASSERT_EQUAL(s, core_mock_get_applied_state())

#define TEST_ASSERT_VEHICLE_DIRECTION(direction)                               \
    TEST_ASSERT_EQUAL(direction, core_mock_get_applied_control_direction())

#define TEST_ASSERT_VEHICLE_ANGLE(angle)                                       \
    TEST_ASSERT_EQUAL(angle, core_mock_get_applied_control_angle())

void
core_mock_reset(void);

void
core_mock_set_line_detected(bool is_detected);

void
core_mock_set_command(core_command_t command);

void
core_mock_set_control(core_control_direction_t direction, uint8_t angle);

core_control_t
core_mock_get_applied_control(void);

core_control_direction_t
core_mock_get_applied_control_direction(void);

uint8_t
core_mock_get_applied_control_angle(void);

core_command_t
core_mock_get_applied_command(void);

core_state_t
core_mock_get_applied_state(void);

bool
core_mock_is_stopped(void);

#endif