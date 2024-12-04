#include "driverCode.hpp"

int leftPower;
int rightPower;

bool intakeButton;
bool intakeRev;
bool prevIntake = false;
bool intakeOn = false;

bool clampOn;
bool clampOff;

void tankDrive () {
    // Contoller values
    leftPower = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    rightPower = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    intakeButton = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    intakeRev = master.get_digital(pros::E_CONTROLLER_DIGITAL_L2);

    clampOn = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    clampOff = master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

    // Drive control - tank
    movePL(leftPower);
    movePR(rightPower);

    // Intake control
    if (intakeButton && !prevIntake) 
        intakeOn = !intakeOn;

    if (intakeRev)
        intake.move(-127);
    else if (intakeOn)
        intake.move(127);
    else
        intake.move(0);

    // Clamp Control 
    if (clampOn) clamp.set_value(true);
    else if (clampOff) clamp.set_value(false);
}