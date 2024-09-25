#include "subsystems/wings.h"
#include "constants.h"
#include "comets/math.h"
#include "pros/motors.h"

Wings::Wings() : m_left(constants::wings::LEFT_PORT),
                 m_right(constants::wings::RIGHT_PORT),
                 m_left_task(pros::Task::create(std::bind(Wings::task_handler, std::ref(m_left)))),
                 m_right_task(pros::Task::create(std::bind(Wings::task_handler, std::ref(m_right))))
{
    m_left.set_gearing(constants::wings::MOTOR_GEARSET);
    m_left.set_encoder_units(pros::motor_encoder_units_e::E_MOTOR_ENCODER_ROTATIONS);
    m_right.set_gearing(constants::wings::MOTOR_GEARSET);
    m_right.set_encoder_units(pros::motor_encoder_units_e::E_MOTOR_ENCODER_ROTATIONS);
}

void Wings::toggle_left()
{
    m_left_task.notify();
}

void Wings::toggle_right()
{
    m_right_task.notify();
}

void Wings::toggle_motor(pros::Motor &motor)
{
    const auto position = motor.get_position();
    const auto velocity = motor.get_actual_velocity();
    const bool is_stored = comets::in_range(position, -0.1, +0.1);

    if (is_stored)
    {
        motor.move_absolute(constants::wings::DOWN_POSITION, 100);
    }
    else
    {
        motor.move_absolute(-0.05, 100);
    }
}

void Wings::task_handler(pros::Motor &motor)
{
    while (pros::Task::notify_take(true, TIMEOUT_MAX))
    {
        Wings::toggle_motor(motor);
    }
}
