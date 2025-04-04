#ifndef _CORE_FIXTURES_H
#define _CORE_FIXTURES_H

#include <core/control.h>
#include <core/coords.h>
#include <core/mode.h>

#define COORDS_ON_ROUTE  core_coords(0, 0, 100, 100, 0, 0)
#define COORDS_OFF_ROUTE core_coords(0, 0, 0, 0, 0, 0)

#define MODE_MANUAL         core_mode(CORE_MODE_MANUAL)
#define MODE_LINE_DETECTED  core_mode(CORE_MODE_LINE_DETECTED)
#define MODE_LINE_FOLLOWING core_mode(CORE_MODE_LINE_FOLLOWING)

#define CONTROL_NONE     core_control(CORE_CONTROL_NONE)
#define CONTROL_FORWARD  core_control(CORE_CONTROL_FORWARD)
#define CONTROL_BACKWARD core_control(CORE_CONTROL_BACKWARD)
#define CONTROL_LEFT     core_control(CORE_CONTROL_LEFT)
#define CONTROL_RIGHT    core_control(CORE_CONTROL_RIGHT)
#define CONTROL_BREAK    core_control(CORE_CONTROL_BREAK)
#define CONTROL_FOLLOW   core_control(CORE_CONTROL_FOLLOW)
#define CONTROL_FORWARD_LEFT                                                   \
    core_control(CORE_CONTROL_FORWARD | CORE_CONTROL_LEFT)
#define CONTROL_FORWARD_RIGHT                                                  \
    core_control(CORE_CONTROL_FORWARD | CORE_CONTROL_RIGHT)
#define CONTROL_BACKWARD_LEFT                                                  \
    core_control(CORE_CONTROL_BACKWARD | CORE_CONTROL_LEFT)
#define CONTROL_BACKWARD_RIGHT                                                 \
    core_control(CORE_CONTROL_BACKWARD | CORE_CONTROL_RIGHT)

#define MOTION_NONE core_motion(CORE_MOTION_NONE, 0)

#endif