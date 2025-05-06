#include "blink.h"
#include "data_store.h"
#include "devices/blink.h"
#include "dualshock2.h"
#include "isr_dispatch.h"
#include "l293.h"
#include "notification.h"
#include "peripherals.h"
#include "qtrhd06a.h"
#include "spi_transmittion.h"
#include "timeout_guard.h"
#include <devices/devices.h>
#include <devices/dualshock2.h>
#include <devices/qtrhd06a.h>
#include <devices/timeout_guard.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/timer.h>
#include <stdint.h>

static inline int
l293_create_channel_12(void);

static inline int
l293_create_channel_34(void);

static inline int
dualshock2_create_device(void);

static inline int
qtrhd06a_create_device(void);

static inline int
blink_create_device(void);

static inline int
timeout_guard_route_create_device(void);

void
devices_init(void)
{
    isr_dispatch_init();
    peripherals_init();

    l293_init();
    dualshock2_init();
    spi_transmittion_init();
    qtrhd06a_init();
    blink_init();
    timeout_guard_route_create_device();

    // TODO: error handling
    (void)l293_create_channel_12();
    (void)l293_create_channel_34();
    (void)dualshock2_create_device();
    (void)qtrhd06a_create_device();
    (void)blink_create_device();
    (void)timeout_guard_route_create_device();
}

static inline int
l293_create_channel_12(void)
{
    l293_conf_t conf = {
        .gpio_port_1 = GPIOA,
        .gpio_pin_1  = GPIO12,
        .gpio_port_2 = GPIOA,
        .gpio_pin_2  = GPIO10,
        .pwm_timer   = TIM3,
        .pwm_channel = TIM_OC3,
    };

    return l293_create(DEVICE_L293_CHANNEL_12, &conf);
}

static inline int
l293_create_channel_34(void)
{
    l293_conf_t conf = {
        .gpio_port_1 = GPIOB,
        .gpio_pin_1  = GPIO6,
        .gpio_port_2 = GPIOB,
        .gpio_pin_2  = GPIO7,
        .pwm_timer   = TIM3,
        .pwm_channel = TIM_OC4,
    };

    return l293_create(DEVICE_L293_CHANNEL_34, &conf);
}

static inline int
dualshock2_create_device(void)
{
    dualshock2_conf_t conf = {
        .device_select_port = GPIOF,
        .device_select_pin  = GPIO0,
        .spi_port           = SPI1,
    };

    return dualshock2_create(DEVICE_DUALSHOCK2_1, &conf);
}

static inline int
qtrhd06a_create_device(void)
{
    qtrhd06a_conf_t conf = {
        .p_raw_values      = data_store_get_route_read_buffer(),
        .raw_values_length = DATA_STORE_ROUTE_BUFFER_LENGTH,
    };

    return qtrhd06a_create(DEVICE_QTRHD06A_1, &conf);
}

static inline int
blink_create_device(void)
{
    blink_conf_t conf = {
        .timer       = TIM1,
        .toggles_num = 2,
    };

    return blink_create(DEVICE_BLINK_1, &conf);
}

static inline int
timeout_guard_route_create_device(void)
{
    timeout_guard_conf_t conf = {
        .timer                = TIM15,
        .timeout_notification = NOTIFICATION_TIMEOUT_GUARD_ROUTE,
    };

    return timeout_guard_create(DEVICE_TIEMOUT_GUARD_ROUTE, &conf);
}
