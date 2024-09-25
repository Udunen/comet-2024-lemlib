#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstddef>
#include <map>
#include "comets/vendor.h"
#include "comets/types.h"

namespace constants
{
    using namespace pros;
    inline constexpr bool USE_TANK = false;

    namespace drivebase
    {
        inline constexpr std::array<int8_t, 3> LEFT_PORTS = {
            7,
            -2,
            11,
        };
        inline constexpr std::array<int8_t, 3> RIGHT_PORTS = {
            -6,
            17,
            -8,
        };

        inline constexpr double DRIVETRAIN_WIDTH = 11.25;
        inline constexpr int8_t IMU_PORT = 5;

        inline constexpr auto CHASSIS_INTERNAL_GEARSET = pros::v5::MotorGears::blue;
    }

    namespace catapult
    {
        inline constexpr int8_t LEFT_PORT = 3;
        inline constexpr int8_t RIGHT_PORT = -10;
        inline constexpr double TOLERANCE = 3;
        inline constexpr auto POS_PIDF = comets::PIDF_Value{
            .P = 0.01,
            .I = 0.0,
            .D = 0.0,
            .F = 0.05};

        inline constexpr auto VEL_PIDF = comets::PIDF_Value{
            .P = 0.03,
            .I = 0.0,
            .D = 0.02,
            .F = 0.10};

        inline constexpr auto STORED_POSITION = 0.0;
        inline constexpr auto EXTENDED_POSITION = 350.0;
        inline constexpr auto MOTOR_GEARSET = pros::v5::MotorGears::red;
    } // namespace catapult

    namespace intake
    {
        inline constexpr int8_t LEFT_PORT = -12;
        inline constexpr int8_t RIGHT_PORT = 19;
        inline constexpr auto MOTOR_GEARSET = pros::v5::MotorGears::red;
        inline constexpr auto SPEED_MULTIPLIER = 1.0;
    }

    namespace wings
    {
        inline constexpr int8_t LEFT_PORT = -4;
        inline constexpr int8_t RIGHT_PORT = 15;
        inline constexpr auto MOTOR_GEARSET = pros::v5::MotorGears::red;
        inline constexpr double DOWN_POSITION = 0.23;
    }

    // Max velocity of auton, in RPM
    inline constexpr double TURN_VEL_MULT = 0.3;

    inline constexpr double TELEOP_POLL_TIME = 10.0; // ms
}
#endif