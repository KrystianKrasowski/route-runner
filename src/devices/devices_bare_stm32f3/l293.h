#ifndef _DEVICE_STM32F3XX_L293_H
#define _DEVICE_STM32F3XX_L293_H

#include "gpio.h"
#include "tim.h"
#include <devices/l293.h>

/**
 * @brief A L293 driver instance for bidirectional mode. Single channel
 *
 * The instance internals are exposed as module-private because of:
 *  - separation creation from initialization
 *  - prevent from "construct" functions with all the instance fields anyway
 */
typedef struct
{
    gpio_t const        driver_channel_1;
    gpio_t const        driver_channel_2;
    tim_t const         pwm_timer;
    tim_channel_t const pwm_channel;
} l293_instance_t;

void
l293_init(void);

void
l293_create(device_l293_t handle, l293_instance_t *p_instance);

#endif
