#include "pros/misc.h"
#include "pros/misc.hpp"
#include "subsystems.h"
#include "subsystems/drivebase.h"
#include "auton.h"


enum class AutonMode
{
    REGULAR,
    TEST,
    SKILLS,
};

inline constexpr AutonMode MODE = AutonMode::REGULAR;
pros::Controller controller (pros::E_CONTROLLER_MASTER);

void autonomous() {
    drivebase->setPose({0, 0}, 0);
    drivebase->turnToHeading(90, 100000);

    // pros::lcd::clear();
    pros::delay(500);
    pros::lcd::print(0, "X: %f", drivebase->getPose().x);
    pros::lcd::print(1, "Y: %f", drivebase->getPose().y);
    pros::lcd::print(2, "Theta: %f", drivebase->getPose().theta);
    pros::lcd::print(3, "IMU: %f", drivebase->getIMU().get_yaw());
};

void autonomous_initialize() {
    drivebase->calibrateChassis(true);
};

void autonomousSkills() {};

void autonomousRegular() {};

void autonomousTest() {};