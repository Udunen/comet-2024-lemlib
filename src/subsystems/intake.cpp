#include "subsystems/intake.h"
#include "comets/math.h"
#include "constants.h"

using namespace constants::intake;

Intake::Intake() : m_motors({LEFT_PORT, RIGHT_PORT}, MOTOR_GEARSET)
{
    static_assert(comets::signum(LEFT_PORT) != comets::signum(RIGHT_PORT),
                  "Directions of motors must be opposite");
}

void Intake::forward() noexcept
{
    m_motors.move_voltage(8000);
}

void Intake::reverse() noexcept
{
    m_motors.move_voltage(-8000);
}

void Intake::stop() noexcept
{
    m_motors.move_voltage(0);
}

bool Intake::is_running() const noexcept
{
    return m_motors.get_target_velocity() == 0;
}
