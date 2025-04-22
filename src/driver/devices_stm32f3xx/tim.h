#ifndef _DEVICES_STM32F303XX_TIM_H
#define _DEVICES_STM32F303XX_TIM_H

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    PERIPH_TIM3,
} tim_t;

typedef enum
{
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
    PERIPH_TIM_OUTPUT_COMPARE_FROZEN = 0,
    PERIPH_TIM_OUTPUT_COMPARE_PWM_1  = 6,
} tim_output_compare_mode_t;

typedef struct
{
    uint32_t                  resolution;
    uint32_t                  auto_reload_at;
    tim_center_aligned_mode_t center_aligned_mode;
    bool                      reinitialize_on_update;
} tim_base_conf_t;

typedef struct
{
    uint32_t                  default_compare_value;
    tim_output_compare_mode_t output_compare_mode;
    bool                      preload_enable;
} tim_out_compare_conf_t;

void
tim_init(void);

int
tim_configure_base(tim_t h_self, tim_base_conf_t *p_conf);

int
tim_configure_out_compare(tim_t                   h_self,
                          tim_channel_t           channel,
                          tim_out_compare_conf_t *p_conf);

int
tim_enable(tim_t h_self);

int
tim_run_out_compare(tim_t h_self, tim_channel_t channel, uint32_t treshold);

int
tim_stop_out_compare(tim_t h_self, tim_channel_t channel);

#endif