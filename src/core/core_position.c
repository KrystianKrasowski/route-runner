#include "core/position.h"
#include <stdbool.h>
#include <string.h>

#define WL3 -100
#define WL2 -40
#define WL1 -20
#define WR1 20
#define WR2 40
#define WR3 100

static inline bool
is_on_line(core_position_t *self);

void
core_position_init(core_position_t *self)
{
    memset(self, 0, sizeof(*self));
}

core_position_status_t
core_position_get_status(core_position_t *self)
{
    if (is_on_line(self))
    {
        return CORE_POSITION_ON_LINE;
    }
    else
    {
        return CORE_POSITION_NO_LINE;
    }
}

int16_t
core_position_compute_error(core_position_t *self)
{
    int16_t sum = self->left_3 + self->left_2 + self->left_1 + self->right_1 +
                  self->right_2 + self->right_3;

    if (sum == 0)
    {
        return 0;
    }

    int16_t left_3_weight  = WL3 * self->left_3;
    int16_t left_2_weight  = WL2 * self->left_2;
    int16_t left_1_weight  = WL1 * self->left_1;
    int16_t right_1_weight = WR1 * self->right_1;
    int16_t right_2_weight = WR2 * self->right_2;
    int16_t right_3_weight = WR3 * self->right_3;

    int16_t weight_sum = left_3_weight + left_2_weight + left_1_weight +
                         right_1_weight + right_2_weight + right_3_weight;

    return weight_sum / sum;
}

uint8_t
core_position_get_by_place(core_position_t *self, core_position_place_t place)
{
    switch (place)
    {
        case CORE_POSITION_PLACE_LEFT_3:
            return self->left_3;
        case CORE_POSITION_PLACE_LEFT_2:
            return self->left_2;
        case CORE_POSITION_PLACE_LEFT_1:
            return self->left_1;
        case CORE_POSITION_PLACE_RIGHT_1:
            return self->right_1;
        case CORE_POSITION_PLACE_RIGHT_2:
            return self->right_2;
        case CORE_POSITION_PLACE_RIGHT_3:
            return self->right_3;
        default:
            return 0;
    }
}

void
core_position_set_by_place(core_position_t      *self,
                           core_position_place_t place,
                           uint8_t               position)
{
    switch (place)
    {
        case CORE_POSITION_PLACE_LEFT_3:
            self->left_3 = position;
            break;
        case CORE_POSITION_PLACE_LEFT_2:
            self->left_2 = position;
            break;
        case CORE_POSITION_PLACE_LEFT_1:
            self->left_1 = position;
            break;
        case CORE_POSITION_PLACE_RIGHT_1:
            self->right_1 = position;
            break;
        case CORE_POSITION_PLACE_RIGHT_2:
            self->right_2 = position;
            break;
        case CORE_POSITION_PLACE_RIGHT_3:
            self->right_3 = position;
            break;
        default:
            return;
    }
}

bool
core_position_equals(core_position_t *self, core_position_t *other)
{
    return self->left_1 == other->left_1 && self->left_2 == other->left_2 &&
           self->left_3 == other->left_3 && self->right_1 == other->right_1 &&
           self->right_2 == other->right_2 && self->right_3 == other->right_3;
}

static inline bool
is_on_line(core_position_t *self)
{
    return self->left_3 >= CORE_POSITION_DETECTION_TRESHOLD ||
           self->left_2 >= CORE_POSITION_DETECTION_TRESHOLD ||
           self->left_1 >= CORE_POSITION_DETECTION_TRESHOLD ||
           self->right_1 >= CORE_POSITION_DETECTION_TRESHOLD ||
           self->right_2 >= CORE_POSITION_DETECTION_TRESHOLD ||
           self->right_3 >= CORE_POSITION_DETECTION_TRESHOLD;
}