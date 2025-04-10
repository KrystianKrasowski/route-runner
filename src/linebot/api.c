#include "command.h"
#include "coords.h"
#include "linebot.h"
#include "mode.h"
#include "motion_factory.h"
#include "position.h"
#include <linebot/api.h>
#include <linebot/port.h>
#include <string.h>
#include <utils/pool.h>

void
linebot_init(void)
{
    linebot_port_mode_init();
    linebot_port_coords_init();
    linebot_port_motion_init();
    linebot_port_control_init();
}