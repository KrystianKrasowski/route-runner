#include "tim.h"
#include "sysclock.h"
#include <errno.h>
#include <stm32f3xx.h>
#include <utils/pool.h>
#include <utils/result.h>

#define TIM_USAGE_SIZE 1

typedef struct
{
    TIM_TypeDef *TIMx;
} tim_instance_t;

POOL_DECLARE(tim, tim_instance_t, TIM_USAGE_SIZE)

static tim_pool_t pool;

static inline void
init_rcc(void);

static inline void
create_all_instances(void);

static inline void
configure_control(tim_instance_t *p_self, tim_base_conf_t *p_conf);

static inline void
configure_event_generation(tim_instance_t *p_self, tim_base_conf_t *p_conf);

static inline void
set_out_compare_treshold(tim_instance_t *p_self,
                         tim_channel_t   channel,
                         uint32_t        treshold);

static inline void
configure_out_compare_mode(tim_instance_t         *p_self,
                           tim_channel_t           channel,
                           tim_out_compare_conf_t *p_conf);

static inline void
enable_out_compare(tim_instance_t *p_self, tim_channel_t channel);

static inline void
disable_out_compare(tim_instance_t *p_self, tim_channel_t channel);

static inline TIM_TypeDef *
match_tim_port(tim_t h_tim);

void
tim_init(void)
{
    init_rcc();
    tim_pool_init(&pool);
    create_all_instances();
}

int
tim_configure_base(tim_t h_self, tim_base_conf_t *p_conf)
{
    tim_instance_t *p_self = tim_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    p_self->TIMx->PSC = sysclock_get_prescaller_base(p_conf->resolution) - 1;
    p_self->TIMx->ARR = p_conf->auto_reload_at - 1;

    configure_control(p_self, p_conf);
    configure_event_generation(p_self, p_conf);

    return RESULT_OK;
}

int
tim_configure_out_compare(tim_t                   h_self,
                          tim_channel_t           channel,
                          tim_out_compare_conf_t *p_conf)
{
    tim_instance_t *p_self = tim_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    set_out_compare_treshold(p_self, channel, p_conf->default_compare_value);
    configure_out_compare_mode(p_self, channel, p_conf);

    return RESULT_OK;
}

int
tim_enable(tim_t h_self)
{
    tim_instance_t *p_self = tim_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    p_self->TIMx->CR1 |= TIM_CR1_CEN;

    return RESULT_OK;
}

int
tim_run_out_compare(tim_t h_self, tim_channel_t channel, uint32_t treshold)
{
    tim_instance_t *p_self = tim_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    set_out_compare_treshold(p_self, channel, treshold);
    enable_out_compare(p_self, channel);

    return RESULT_OK;
}

int
tim_stop_out_compare(tim_t h_self, tim_channel_t channel)
{
    tim_instance_t *p_self = tim_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    disable_out_compare(p_self, channel);

    return RESULT_OK;
}

static inline void
init_rcc(void)
{
    // enable clock access to TIM3
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
}

static inline void
create_all_instances(void)
{
    for (uint8_t h_tim = 0; h_tim < TIM_USAGE_SIZE; h_tim++)
    {
        if (tim_pool_alloc(&pool, &h_tim))
        {
            tim_instance_t *p_tim = tim_pool_get(&pool, h_tim);

            p_tim->TIMx = match_tim_port(h_tim);
        }
    }
}

static inline void
configure_control(tim_instance_t *p_self, tim_base_conf_t *p_conf)
{
    // disable timer before configuration
    p_self->TIMx->CR1 &= ~TIM_CR1_CEN;

    // configure alignment mode
    if (PERIPH_TIM_EDGE_ALIGNED == p_conf->center_aligned_mode)
    {
        p_self->TIMx->CR1 &= ~(TIM_CR1_CMS);
    }
    else
    {
        p_self->TIMx->CR1 |= (p_conf->center_aligned_mode << TIM_CR1_CMS_Pos);
    }
}

static inline void
configure_event_generation(tim_instance_t *p_self, tim_base_conf_t *p_conf)
{
    // configure counter reinitialization on update event
    if (p_conf->reinitialize_on_update)
    {
        p_self->TIMx->EGR |= TIM_EGR_UG;
    }
}

static inline void
set_out_compare_treshold(tim_instance_t *p_self,
                         tim_channel_t   channel,
                         uint32_t        treshold)
{
    switch (channel)
    {
        case PERIPH_TIM_CHANNEL_3:
            p_self->TIMx->CCR3 = treshold;
            break;
        case PERIPH_TIM_CHANNEL_4:
            p_self->TIMx->CCR4 = treshold;
            break;
    }
}

static inline void
configure_out_compare_mode(tim_instance_t         *p_self,
                           tim_channel_t           channel,
                           tim_out_compare_conf_t *p_conf)
{
    // Determine mode register and masks
    uint32_t volatile *CCMRx;

    uint32_t CCMRx_OCxM_0;
    uint32_t CCMRx_OCxM_1;
    uint32_t CCMRx_OCxM_2;
    uint32_t CCMRx_OCxM_3;
    uint32_t CCMRx_OCxPE;

    switch (channel)
    {
        case PERIPH_TIM_CHANNEL_3:
            CCMRx        = &p_self->TIMx->CCMR2;
            CCMRx_OCxM_0 = TIM_CCMR2_OC3M_0;
            CCMRx_OCxM_1 = TIM_CCMR2_OC3M_1;
            CCMRx_OCxM_2 = TIM_CCMR2_OC3M_2;
            CCMRx_OCxM_3 = TIM_CCMR2_OC3M_3;
            CCMRx_OCxPE  = TIM_CCMR2_OC3PE;
            break;

        case PERIPH_TIM_CHANNEL_4:
            CCMRx        = &p_self->TIMx->CCMR2;
            CCMRx_OCxM_0 = TIM_CCMR2_OC4M_0;
            CCMRx_OCxM_1 = TIM_CCMR2_OC4M_1;
            CCMRx_OCxM_2 = TIM_CCMR2_OC4M_2;
            CCMRx_OCxM_3 = TIM_CCMR2_OC4M_3;
            CCMRx_OCxPE  = TIM_CCMR2_OC4PE;
            break;

        default:
            return; // TODO: Some error handling?
    }

    // set output compare mode
    switch (p_conf->output_compare_mode)
    {
        case PERIPH_TIM_OUTPUT_COMPARE_PWM_1:
            *CCMRx |= (CCMRx_OCxM_2 | CCMRx_OCxM_1);
            break;

        case PERIPH_TIM_OUTPUT_COMPARE_FROZEN:
        default:
            *CCMRx &=
                ~(CCMRx_OCxM_3 | CCMRx_OCxM_2 | CCMRx_OCxM_1 | CCMRx_OCxM_0);
    }

    // set preload enable
    if (p_conf->preload_enable)
    {
        *CCMRx |= CCMRx_OCxPE;
    }
}

static inline void
enable_out_compare(tim_instance_t *p_self, tim_channel_t channel)
{
    switch (channel)
    {
        case PERIPH_TIM_CHANNEL_3:
            p_self->TIMx->CCER |= TIM_CCER_CC3E;
            break;

        case PERIPH_TIM_CHANNEL_4:
            p_self->TIMx->CCER |= TIM_CCER_CC4E;
    }
}

static inline void
disable_out_compare(tim_instance_t *p_self, tim_channel_t channel)
{
    switch (channel)
    {
        case PERIPH_TIM_CHANNEL_3:
            p_self->TIMx->CCER &= ~TIM_CCER_CC3E;
            break;

        case PERIPH_TIM_CHANNEL_4:
            p_self->TIMx->CCER &= ~TIM_CCER_CC4E;
    }
}

static inline TIM_TypeDef *
match_tim_port(tim_t h_tim)
{
    switch (h_tim)
    {
        case PERIPH_TIM3:
        default:
            return TIM3;
    }
}