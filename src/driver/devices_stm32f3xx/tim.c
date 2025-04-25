#include "interrupts.h"
#include "sysclock.h"
#include "tim.h"
#include <errno.h>
#include <stm32f3xx.h>
#include <utils/pool.h>
#include <utils/result.h>

#define TIM_USAGE_SIZE 2

typedef struct
{
    TIM_TypeDef *TIMx;
    IRQn_Type    IRQn;
} tim_instance_t;

POOL_DECLARE(tim, tim_instance_t, TIM_USAGE_SIZE)

static tim_pool_t pool;

static inline void
rcc_init(void);

static inline void
all_instances_create(void);

static inline void
oc_set_treshold(tim_instance_t *p_self,
                tim_channel_t   channel,
                uint32_t        treshold);

static inline void
oc_configure_mode(tim_instance_t *p_self,
                  tim_channel_t   channel,
                  tim_oc_conf_t  *p_conf);

static inline void
oc_enable(tim_instance_t *p_self, tim_channel_t channel);

static inline void
oc_disable(tim_instance_t *p_self, tim_channel_t channel);

static inline TIM_TypeDef *
tim_port_match(tim_t h_tim);

static inline IRQn_Type
tim_irqn_match(tim_t h_tim);

void
tim_init(void)
{
    rcc_init();
    tim_pool_init(&pool);
    all_instances_create();
}

int
tim_base_configure(tim_t h_self, tim_base_conf_t *p_conf)
{
    tim_instance_t *p_self = tim_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    p_self->TIMx->PSC = sysclock_get_prescaller_base(p_conf->resolution) - 1;
    p_self->TIMx->ARR = p_conf->auto_reload_at - 1;

    return RESULT_OK;
}

int
tim_control_configure(tim_t h_self, tim_control_conf_t *p_conf)
{
    tim_instance_t *p_self = tim_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

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

    return RESULT_OK;
}

int
tim_event_gen_configure(tim_t h_self, tim_event_gen_conf_t *p_conf)
{
    tim_instance_t *p_self = tim_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    // configure counter reinitialization on update event
    if (p_conf->reinit_on_update)
    {
        p_self->TIMx->EGR |= TIM_EGR_UG;
    }

    return RESULT_OK;
}

int
tim_oc_configure(tim_t h_self, tim_channel_t channel, tim_oc_conf_t *p_conf)
{
    tim_instance_t *p_self = tim_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    oc_set_treshold(p_self, channel, p_conf->default_oc_treshold);
    oc_configure_mode(p_self, channel, p_conf);

    return RESULT_OK;
}

int
tim_oc_run(tim_t h_self, tim_channel_t channel, uint32_t treshold)
{
    tim_instance_t *p_self = tim_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    oc_set_treshold(p_self, channel, treshold);
    oc_enable(p_self, channel);

    return RESULT_OK;
}

int
tim_oc_stop(tim_t h_self, tim_channel_t channel)
{
    tim_instance_t *p_self = tim_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    oc_disable(p_self, channel);

    return RESULT_OK;
}

int
tim_interrupt_update_enable(tim_t h_self)
{
    tim_instance_t *p_self = tim_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    p_self->TIMx->SR &= ~TIM_SR_UIF;
    p_self->TIMx->DIER |= TIM_DIER_UIE;

    NVIC_EnableIRQ(p_self->IRQn);

    return RESULT_OK;
}

int
tim_interrupt_oc_enable(tim_t h_self, tim_channel_t channel)
{
    tim_instance_t *p_self = tim_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    switch (channel)
    {
        case PERIPH_TIM_CHANNEL_1:
            p_self->TIMx->DIER |= TIM_DIER_CC1IE;
            break;

        case PERIPH_TIM_CHANNEL_3:
            p_self->TIMx->DIER |= TIM_DIER_CC3IE;
            break;

        case PERIPH_TIM_CHANNEL_4:
            p_self->TIMx->DIER |= TIM_DIER_CC4IE;
            break;
    }

    NVIC_EnableIRQ(p_self->IRQn);

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

void
// cppcheck-suppress unusedFunction
TIM2_IRQHandler(void)
{
    if (TIM2->SR & TIM_SR_UIF)
    {
        TIM2->SR &= ~TIM_SR_UIF;
        tim2_on_update_isr();
    }
}

static inline void
rcc_init(void)
{
    // enable clock access to TIM2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // enable clock access to TIM3
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
}

// TODO: Should explicitly create every instance
static inline void
all_instances_create(void)
{
    for (uint8_t h_tim = 0; h_tim < TIM_USAGE_SIZE; h_tim++)
    {
        if (tim_pool_alloc(&pool, &h_tim))
        {
            tim_instance_t *p_tim = tim_pool_get(&pool, h_tim);

            p_tim->TIMx = tim_port_match(h_tim);
            p_tim->IRQn = tim_irqn_match(h_tim);
        }
    }
}

static inline void
oc_set_treshold(tim_instance_t *p_self,
                tim_channel_t   channel,
                uint32_t        treshold)
{
    switch (channel)
    {
        case PERIPH_TIM_CHANNEL_1:
            p_self->TIMx->CCR1 = treshold;
            break;

        case PERIPH_TIM_CHANNEL_3:
            p_self->TIMx->CCR3 = treshold;
            break;

        case PERIPH_TIM_CHANNEL_4:
            p_self->TIMx->CCR4 = treshold;
            break;
    }
}

static inline void
oc_configure_mode(tim_instance_t *p_self,
                  tim_channel_t   channel,
                  tim_oc_conf_t  *p_conf)
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
        case PERIPH_TIM_CHANNEL_1:
            CCMRx        = &p_self->TIMx->CCMR1;
            CCMRx_OCxM_0 = TIM_CCMR1_OC1M_0;
            CCMRx_OCxM_1 = TIM_CCMR1_OC1M_1;
            CCMRx_OCxM_2 = TIM_CCMR1_OC1M_2;
            CCMRx_OCxM_3 = TIM_CCMR1_OC1M_3;
            CCMRx_OCxPE  = TIM_CCMR1_OC1PE;
            break;

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
    switch (p_conf->oc_mode)
    {
        case PERIPH_TIM_OC_PWM_1:
            *CCMRx |= (CCMRx_OCxM_2 | CCMRx_OCxM_1);
            break;

        case PERIPH_TIM_OC_FROZEN:
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
oc_enable(tim_instance_t *p_self, tim_channel_t channel)
{
    switch (channel)
    {
        case PERIPH_TIM_CHANNEL_1:
            p_self->TIMx->CCER |= TIM_CCER_CC1E;
            break;

        case PERIPH_TIM_CHANNEL_3:
            p_self->TIMx->CCER |= TIM_CCER_CC3E;
            break;

        case PERIPH_TIM_CHANNEL_4:
            p_self->TIMx->CCER |= TIM_CCER_CC4E;
    }
}

static inline void
oc_disable(tim_instance_t *p_self, tim_channel_t channel)
{
    switch (channel)
    {
        case PERIPH_TIM_CHANNEL_1:
            p_self->TIMx->CCER &= ~TIM_CCER_CC1E;
            break;

        case PERIPH_TIM_CHANNEL_3:
            p_self->TIMx->CCER &= ~TIM_CCER_CC3E;
            break;

        case PERIPH_TIM_CHANNEL_4:
            p_self->TIMx->CCER &= ~TIM_CCER_CC4E;
            break;
    }
}

static inline TIM_TypeDef *
tim_port_match(tim_t h_tim)
{
    switch (h_tim)
    {
        case PERIPH_TIM2:
            return TIM2;

        case PERIPH_TIM3:
        default:
            return TIM3;
    }
}

static inline IRQn_Type
tim_irqn_match(tim_t h_tim)
{
    switch (h_tim)
    {
        case PERIPH_TIM2:
            return TIM2_IRQn;

        case PERIPH_TIM3:
        default:
            return TIM3_IRQn;
    }
}
