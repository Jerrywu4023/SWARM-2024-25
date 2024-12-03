#include "driverCode.hpp"

int leftPower;
int rightPower;
int intakeForward;
int intakeRev;

bool clampState = false;
bool clampButton;
bool prevClamp = false;

void tankDrive () {
    leftPower = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    rightPower = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    intakeForward = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    intakeRev = master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
    clampButton = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);

    movePL(leftPower);
    movePR(rightPower);

    if (intakeForward)
        intake.move(127);
    else if (intakeRev)
        intake.move(-127);
    else
        intake.move(0);

    if (clampButton && !prevClamp) 
        clampState = !clampState;
    
    clamp.set_value(clampState);
    prevClamp = clampButton;
}