#ifndef _STACK_H
#define _STACK_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#define STACK_MAX_SIZE 50

typedef enum
{
    STACK_SUCCESS,
    STACK_EMPTY,
    STACK_FULL,
    STACK_SIZE_EXCEEDED,
    STACK_ELEMENT_OUT_OF_BOUNDS,
} stack_result_t;

typedef struct stack
{
    int16_t elements[STACK_MAX_SIZE];
    int8_t  top;
    uint8_t size;
} stack_t;

stack_t
stack(uint8_t size);

stack_t
stack_of(uint8_t size, ...);

stack_result_t
stack_pop(stack_t *p_self, int16_t *p_element);

stack_result_t
stack_peek(stack_t const *p_self, int16_t *p_element);

int16_t
stack_peek_or(stack_t const *p_self, int16_t default_value);

stack_result_t
stack_push(stack_t *p_self, int16_t element);

void
stack_push_rolling(stack_t *p_self, int16_t element);

bool
stack_is_empty(stack_t const *p_self);

bool
stack_is_full(stack_t const *p_self);

uint8_t
stack_get_size(stack_t const *p_self);

uint8_t
stack_get_length(stack_t const *p_self);

stack_result_t
stack_get_element(stack_t const *p_self, uint8_t index, int16_t *p_element);

int16_t
stack_sum(stack_t const *p_self);

#endif
