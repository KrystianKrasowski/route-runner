#ifndef _TASK_H
#define _TASK_H

#include <linebot/api.h>

void
task_handle_manual_control(linebot_t const linebot);

void
task_handle_route_tracking(linebot_t const linebot);

void
task_handle_immediate_stop(linebot_t const linebot);

#endif