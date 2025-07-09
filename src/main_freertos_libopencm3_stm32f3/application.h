#ifndef _APPLICATION_FREERTOS_LIBOPENCM3_STM32F3_H
#define _APPLICATION_FREERTOS_LIBOPENCM3_STM32F3_H

#ifdef __cplusplus
extern "C"
{
#endif

void
app_handle_manual_control(void *p_params);

void
app_handle_route_tracking(void *p_params);

void
app_handle_immediate_stop(void *p_params);

void
app_handle_domain_dump(void *p_params);

#ifdef __cplusplus
}
#endif

#endif
