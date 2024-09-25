#pragma once

#include "comets/vendor.h"

class Wings final
{
public:
    Wings();

    void toggle_left();
    void toggle_right();

    double position_left() const
    {
        return m_left.get_position();
    }
    double position_right() const
    {
        return m_right.get_position();
    }

private:
    mutable pros::Motor m_left, m_right;
    mutable pros::Task m_left_task, m_right_task;

    static void
    toggle_motor(pros::Motor &motor);
    static void
    task_handler(pros::Motor &motor);
};
