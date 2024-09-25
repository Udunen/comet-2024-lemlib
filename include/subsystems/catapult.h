#ifndef __SUBSYSTEMS_CATAPULT_H__
#define __SUBSYSTEMS_CATAPULT_H__

#include "pros/motors.hpp"

/**
 * This code just implements an two position arm, but the real mechanism has
 * rubber bands pulling the arm to the zero position.
 */
class Catapult
{
public:
    Catapult();

    pros::Motor get_leftMotor();
    bool is_motor_idle() noexcept;
    void wind_back(bool auton = false);
    void wind_back_partly(bool auton = false);
    void manual(int velocity);
    void fire();
    void fire_and_wind();
    void fire_and_wind_partly();
    void stop();

    void zero_position();
    double get_position();

    void periodic(bool auton = false);


private:
    pros::Motor m_leftMotor;
    pros::Motor m_rightMotor;
    std::pair<double, int16_t> targetPositionVelocity;
    bool movingToPosition = false;
    bool fireAndWind = false;
    bool fireAndWindPartly = false;

    void set_position(double position);
};

#endif