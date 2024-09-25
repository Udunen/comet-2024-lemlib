#ifndef __TASKS_TELEOP_H__
#define __TASKS_TELEOP_H__

#include "pros/misc.hpp"
#ifdef __cplusplus
extern "C"
{
#endif

pros::Controller controller();

void opcontrol(void);
void opcontrol_initialize(void);

#ifdef __cplusplus
}
#endif

#endif