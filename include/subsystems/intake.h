#ifndef __SUBSYSTEMS_INTAKE_H__
#define __SUBSYSTEMS_INTAKE_H__

#include "comets/vendor.h"


class Intake
{
public:
    Intake();
    void forward() noexcept;
    void reverse() noexcept;
    void stop() noexcept;
    bool is_running() const noexcept;

private:
    // mutable to allow reading voltage in const scope
    mutable pros::MotorGroup m_motors;
};

#endif
