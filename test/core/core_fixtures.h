#ifndef _CORE_FIXTURES_H
#define _CORE_FIXTURES_H

#include <core/control.h>
#include <core/coords.h>
#include <core/mode.h>

#define COORDS_ON_ROUTE  core_coords(0, 0, 100, 100, 0, 0)
#define COORDS_OFF_ROUTE core_coords(0, 0, 0, 0, 0, 0)
#define COORDS_ON_FINISH core_coords(5, 0, 0, 0 ,0 ,5)

#define MODE_MANUAL     core_mode(CORE_MODE_MANUAL)
#define MODE_DETECTED   core_mode(CORE_MODE_DETECTED)
#define MODE_FOLLOWING  core_mode(CORE_MODE_FOLLOWING)
#define MODE_RECOVERING core_mode(CORE_MODE_RECOVERING)

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

#define STACK_EMPTY(size) stack(size)

#define POSITION_STARTING core_position(COORDS_OFF_ROUTE, STACK_EMPTY(20))

#define VEHICLE                                                                \
    core_vehicle(MODE_MANUAL, core_position(COORDS_OFF_ROUTE, STACK_EMPTY(20)))

#endif