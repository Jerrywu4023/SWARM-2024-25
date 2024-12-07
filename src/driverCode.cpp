#include "driverCode.hpp"

int leftPower;
int rightPower;
int curveChange = 0;

bool curveIncrease, prevIncrease = false;
bool curveDecrease, prevDecrease = false;

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

    curveIncrease = master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
    curveDecrease = master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);

    intakeButton = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    intakeRev = master.get_digital(pros::E_CONTROLLER_DIGITAL_L2);

    clampOn = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    clampOff = master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

    // Drive control - exponential tank
    if (curveIncrease && !prevIncrease && curveChange < 5) 
        curveChange++;
    if (curveDecrease && !prevDecrease && curveChange > -8) 
        curveChange--;

    leftPower = (abs(leftPower)/leftPower) * ((1-curveChange) * pow(fabs(leftPower)/50, 3) + (1+0.1463*curveChange) * pow(fabs(leftPower)/12, 2));
    rightPower = (abs(rightPower)/rightPower) * ((1-curveChange) * pow(fabs(rightPower)/50, 3) + (1+0.1463*curveChange) * pow(fabs(rightPower)/12, 2));

    movePL(leftPower);
    movePR(rightPower);

    prevIncrease = curveIncrease;
    prevDecrease = curveDecrease;

    // Intake control
    if (intakeButton && !prevIntake) 
        intakeOn = !intakeOn;

    if (intakeRev)
        intake.move(-127);
    else if (intakeOn)
        intake.move(127);
    else
        intake.move(0);

    prevIntake = intakeButton;

    // Clamp Control 
    if (clampOn) clamp.set_value(true);
    else if (clampOff) clamp.set_value(false);
}