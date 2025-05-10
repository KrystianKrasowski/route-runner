#include <string.h>
#include <utils/stack.h>

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

stack_t
stack_of(uint8_t size, ...)
{
    stack_t st = stack(size);

    va_list elements;
    va_start(elements, size);

    for (uint8_t i = 0; i < size; i++)
    {
        stack_push(&st, va_arg(elements, int));
    }

    va_end(elements);

    return st;
}

stack_result_t
// cppcheck-suppress unusedFunction
stack_pop(stack_t *p_self, int16_t *p_element)
{
    if (stack_is_empty(p_self))
    {
        return STACK_EMPTY;
    }

    *p_element = p_self->elements[p_self->top--];

    return STACK_SUCCESS;
}

stack_result_t
stack_peek(stack_t const *p_self, int16_t *p_element)
{
    if (stack_is_empty(p_self))
    {
        return STACK_EMPTY;
    }

    *p_element = p_self->elements[p_self->top];

    return STACK_SUCCESS;
}

stack_result_t
// cppcheck-suppress unusedFunction
stack_push(stack_t *p_self, int16_t element)
{
    if (p_self->top >= p_self->size - 1)
    {
        return STACK_FULL;
    }

    p_self->elements[++p_self->top] = element;

    return STACK_SUCCESS;
}

void
stack_push_rolling(stack_t *p_self, int16_t element)
{
    if (p_self->top >= p_self->size - 1)
    {
        for (uint8_t i = 1; i < p_self->size; i++)
        {
            p_self->elements[i - 1] = p_self->elements[i];
        }

        p_self->elements[p_self->size - 1] = element;
    }
    else
    {
        p_self->elements[++p_self->top] = element;
    }
}

bool
// cppcheck-suppress staticFunction
stack_is_empty(stack_t const *p_self)
{
    return p_self->top == -1;
}

bool
// cppcheck-suppress unusedFunction
stack_is_full(stack_t const *p_self)
{
    return p_self->top == p_self->size - 1;
}

uint8_t
// cppcheck-suppress unusedFunction
stack_get_size(stack_t const *p_self)
{
    return p_self->size;
}

uint8_t
// cppcheck-suppress unusedFunction
stack_get_length(stack_t const *p_self)
{
    return p_self->top + 1;
}

stack_result_t
// cppcheck-suppress unusedFunction
stack_get_element(stack_t const *p_self, uint8_t index, int16_t *p_element)
{
    if (index > p_self->top)
    {
        return STACK_ELEMENT_OUT_OF_BOUNDS;
    }

    *p_element = p_self->elements[index];

    return STACK_SUCCESS;
}

int16_t
stack_sum(stack_t const *p_self)
{
    int16_t sum = 0;

    for (uint8_t i = 0; i <= p_self->top; i++)
    {
        sum += p_self->elements[i];
    }

    return sum;
}
