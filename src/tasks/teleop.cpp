#include "comets/controls.h"
#include "comets/vendor.h"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "subsystems.h"
#include "tasks/teleop.h"
#include "constants.h"

using namespace pros;


static void drivebase_controls(Controller &controller);
static void catapult_controls(Controller &controller);
static void intake_controls(Controller &controller);
static void wing_controls(Controller &controller);
static comets::EdgeDetector xDetector, yDetector;
static comets::EdgeDetector l1Detector, upDetector;
static comets::EdgeDetector lDetectorWing, rDetectorWing;

void opcontrol_initialize()
{
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
    Controller controller(pros::E_CONTROLLER_MASTER);

    while (true)
    {
        
        controller.print(0, 1, "X: %f", drivebase->getPose().x);
        controller.print(1, 1, "Y: %f", drivebase->getPose().y);
        controller.print(2, 1, "Theta: %f", drivebase->getPose().theta);
        controller.print(3, 1, "Imu: %f", drivebase->getIMU().get_yaw());
        controller.clear();

        // pros::lcd::print(0, "Battery: %2.3f V", pros::battery::get_voltage() / 1000.0f);
        // pros::lcd::print(1, "arm pos %2.3f deg", catapult->get_leftMotor().get_position());

        // pros::lcd::print(2, "Wing L %f", wings->position_left());
        // pros::lcd::print(3, "Wing R %f", wings->position_right());

        catapult->periodic();

        xDetector.monitor(controller.get_digital(DIGITAL_X));
        yDetector.monitor(controller.get_digital(DIGITAL_Y));
        l1Detector.monitor(controller.get_digital(DIGITAL_L1));
        upDetector.monitor(controller.get_digital(DIGITAL_UP));

        drivebase_controls(controller);
        catapult_controls(controller);
        intake_controls(controller);
        wing_controls(controller);

        pros::delay(constants::TELEOP_POLL_TIME);
    }
}

static void drivebase_controls(Controller &controller)
{
    if constexpr (constants::USE_TANK)
    {
        drivebase->tankDrive(
            controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),
            controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));
    }
    else
    {
        drivebase->errorDrive(
            controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),
            controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_X));
    }
}

static void catapult_controls(Controller &controller)
{
    if (l1Detector.isPushed())
    {
        catapult->fire_and_wind();
    }
    if (controller.get_digital(DIGITAL_R2))
    {
        catapult->fire();
    }
    if (controller.get_digital(DIGITAL_R1))
    {
        catapult->wind_back();
    }
    if (controller.get_digital(DIGITAL_B))
    {
        catapult->zero_position();
    }
    if (upDetector.getCurrent())
    {
        catapult->manual(8);
    }
    if (upDetector.isReleased())
    {
        catapult->stop();
    }
}

static void intake_controls(Controller &controller)
{
    if(controller.get_digital(DIGITAL_X)) {
        intake->forward();
    } else if (controller.get_digital(DIGITAL_Y)) {
        intake->reverse();
    } else {
        intake->stop();
    }
}

static void wing_controls(pros::Controller &controller)
{
    // These buttons seem arbitrary but are at equal heights on the controller
    // so the driver can easily activate both wings at the same time.
    lDetectorWing.monitor(controller.get_digital(DIGITAL_LEFT));
    rDetectorWing.monitor(controller.get_digital(DIGITAL_A));

    if (lDetectorWing.isPushed())
    {
        wings->toggle_left();
    }

    if (rDetectorWing.isPushed())
    {
        wings->toggle_right();
    }
}
