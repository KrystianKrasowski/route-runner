#include "utils/stack.h"
#include <string.h>

stack_t
stack(uint8_t size)
{
    if (size > STACK_MAX_SIZE)
    {
        size = STACK_MAX_SIZE;
    }

    stack_t stack;
    memset(&stack, 0, sizeof(stack));
    stack.size = size;
    stack.top  = -1;
    
    return stack;
}

stack_result_t
stack_init(stack_t *self, uint8_t size)
{
    if (size > STACK_MAX_SIZE)
    {
        return STACK_SIZE_EXCEEDED;
    }

    memset(self->elements, 0, sizeof(self->elements));
    self->size = size;
    self->top  = -1;

    return STACK_SUCCESS;
}

stack_result_t
stack_pop(stack_t *self, int16_t *element)
{
    if (stack_is_empty(self))
    {
        return STACK_EMPTY;
    }

    *element = self->elements[self->top--];

    return STACK_SUCCESS;
}

stack_result_t
stack_peek(stack_t *self, int16_t *element)
{
    if (stack_is_empty(self))
    {
        return STACK_EMPTY;
    }

    *element = self->elements[self->top];

    return STACK_SUCCESS;
}

stack_result_t
stack_peek_bottom(stack_t *self, int16_t *element)
{
    if (stack_is_empty(self))
    {
        return STACK_EMPTY;
    }

    *element = self->elements[0];

    return STACK_SUCCESS;
}

stack_result_t
stack_push(stack_t *self, int16_t element)
{
    if (self->top >= self->size - 1)
    {
        return STACK_FULL;
    }

    self->elements[++self->top] = element;

    return STACK_SUCCESS;
}

void
stack_push_rolling(stack_t *self, int16_t element)
{
    if (self->top >= self->size - 1)
    {
        for (uint8_t i = 1; i < self->size; i++)
        {
            self->elements[i - 1] = self->elements[i];
        }

        self->elements[self->size - 1] = element;
    }
    else
    {
        self->elements[++self->top] = element;
    }
}

bool
stack_is_empty(stack_t *self)
{
    return self->top == -1;
}

bool
stack_is_full(stack_t *self)
{
    return self->top == self->size - 1;
}

int8_t
stack_get_top_index(stack_t *self)
{
    return self->top;
}

uint8_t
stack_get_size(stack_t *self)
{
    return self->size;
}

uint8_t
stack_get_length(stack_t *self)
{
    return self->top + 1;
}

stack_result_t
stack_get_element(stack_t *self, uint8_t index, int16_t *element)
{
    if (index > self->top)
    {
        return STACK_ELEMENT_OUT_OF_BOUNDS;
    }

    *element = self->elements[index];

    return STACK_SUCCESS;
}

int16_t
stack_sum(stack_t *self)
{
    int16_t sum = 0;

    for (uint8_t i = 0; i <= self->top; i++)
    {
        sum += self->elements[i];
    }

    return sum;
}