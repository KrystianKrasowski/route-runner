#ifndef _DEVICES_STM32F303XX_TIM_H
#define _DEVICES_STM32F303XX_TIM_H

/**
 * @brief TIMx driver
 *
 * Acronyms:
 * - OC - Output Compare
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    PERIPH_TIM2,
    PERIPH_TIM3,
} tim_t;

typedef enum
{
    PERIPH_TIM_CHANNEL_1,
    PERIPH_TIM_CHANNEL_3,
    PERIPH_TIM_CHANNEL_4,
} tim_channel_t;

typedef enum
{
    PERIPH_TIM_EDGE_ALIGNED     = 0,
    PERIPH_TIM_CENTER_ALIGNED_1 = 1,
} tim_center_aligned_mode_t;

typedef enum
{
    PERIPH_TIM_OC_FROZEN = 0,
    PERIPH_TIM_OC_PWM_1  = 6,
} tim_oc_mode_t;

typedef struct
{
    uint32_t resolution;
    uint32_t auto_reload_at;
} tim_base_conf_t;

typedef struct
{
    tim_center_aligned_mode_t center_aligned_mode;
} tim_control_conf_t;

typedef struct
{
    bool reinit_on_update;
} tim_event_gen_conf_t;

typedef struct
{
    uint32_t      default_oc_treshold;
    tim_oc_mode_t oc_mode;
    bool          preload_enable;
} tim_oc_conf_t;

void
tim_init(void);

int
tim_base_configure(tim_t h_self, tim_base_conf_t *p_conf);

int
tim_control_configure(tim_t h_self, tim_control_conf_t *p_conf);

int
tim_event_gen_configure(tim_t h_self, tim_event_gen_conf_t *p_conf);

int
tim_oc_configure(tim_t h_self, tim_channel_t channel, tim_oc_conf_t *p_conf);

int
tim_oc_run(tim_t h_self, tim_channel_t channel, uint32_t treshold);

int
tim_oc_stop(tim_t h_self, tim_channel_t channel);

int
tim_interrupt_update_enable(tim_t h_self);

int
tim_interrupt_oc_enable(tim_t h_self, tim_channel_t channel);

int
tim_enable(tim_t h_self);

#endif