#include "data_store.h"
#include "notification.h"
#include "serial.h"
#include <errno.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/f3/usart.h>
#include <libopencm3/stm32/usart.h>
#include <stdint.h>
#include <string.h>
#include <utils/pool.h>
#include <utils/queue.h>
#include <utils/result.h>

QUEUE_DECLARE(character, char, DATA_STORE_SERIAL_TXBUFF_LENGTH)

typedef struct
{
    notification_t    notification_id;
    uint32_t          dma_port;
    uint8_t           dma_channel;
    uint32_t          usart_data_address;
    character_queue_t chars_to_send;
} serial_instance_t;

POOL_DECLARE(serial, serial_instance_t, DEVICE_SERIAL_INSTANCES_NUM)

static serial_pool_t pool;

static inline uint8_t
dump_character_queue(serial_instance_t *p_self);

int
device_serial_read(device_serial_t const h_self, char const command)
{
    serial_instance_t const *p_self = serial_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    volatile char serial_request = data_store_get_serial_request();

    if (serial_request == command && notification_take(p_self->notification_id))
    {
        return RESULT_OK;
    }

    return RESULT_NOT_READY;
}

int
device_serial_send(device_serial_t const h_self, char const message[])
{
    serial_instance_t *p_self = serial_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    uint8_t char_index = 0;

    while (message[char_index] != '\0')
    {
        character_queue_push(&p_self->chars_to_send, &message[char_index]);
        char_index++;
    }

    return RESULT_OK;
}

void
serial_init(void)
{
    serial_pool_init(&pool);
}

int
serial_create(device_serial_t const h_self, serial_conf_t const *p_conf)
{
    if (!serial_pool_alloc_at(&pool, h_self))
    {
        return -ENOMEM;
    }

    serial_instance_t *p_self = serial_pool_get(&pool, h_self);

    p_self->notification_id    = p_conf->notification_id;
    p_self->dma_port           = p_conf->dma_port;
    p_self->dma_channel        = p_conf->dma_channel;
    p_self->usart_data_address = p_conf->usart_data_address;

    character_queue_init(&p_self->chars_to_send);

    return RESULT_OK;
}

int
serial_transmit(device_serial_t const h_self)
{
    serial_instance_t *p_self = serial_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (character_queue_empty(&p_self->chars_to_send))
    {
        return RESULT_NOT_READY;
    }

    uint8_t  data_length     = dump_character_queue(p_self);
    uint32_t dma             = p_self->dma_port;
    uint8_t  channel         = p_self->dma_channel;
    uint32_t usart_data_addr = p_self->usart_data_address;
    uint32_t txbuff_addr     = data_store_get_serial_txbuff_addr();

    dma_disable_channel(dma, channel);
    dma_channel_reset(dma, channel);
    dma_set_peripheral_address(dma, channel, usart_data_addr);
    dma_set_memory_address(dma, channel, txbuff_addr);
    dma_set_number_of_data(dma, channel, data_length);
    dma_set_read_from_memory(dma, channel);
    dma_enable_memory_increment_mode(dma, channel);
    dma_set_peripheral_size(dma, channel, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(dma, channel, DMA_CCR_MSIZE_8BIT);
    dma_enable_channel(dma, channel);

    return RESULT_OK;
}

static inline uint8_t
dump_character_queue(serial_instance_t *p_self)
{
    data_store_clear_serial_txbuff();

    volatile char *txbuff     = data_store_get_serial_txbuff();
    uint8_t        char_index = 0;

    while (!character_queue_empty(&p_self->chars_to_send))
    {
        char chr;
        character_queue_pull(&p_self->chars_to_send, &chr);
        txbuff[char_index] = chr;
        char_index++;
    }

    return char_index;
}
