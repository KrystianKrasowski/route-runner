#ifndef _LINEBOT_POSITION_REGULATOR_H
#define _LINEBOT_POSITION_REGULATOR_H

#include "position.h"

int8_t
position_regulate_pid(position_t const position);

#endif