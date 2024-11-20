#include "driverCode.hpp"

int leftPower;
int rightPower;
int intakeButton;

void tankDrive () {
    leftPower = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    rightPower = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    intakeButton = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);

    movePL(leftPower);
    movePR(rightPower);

    if (intakeButton)
        intake.move(127);
    else
        intake.move(0);
}