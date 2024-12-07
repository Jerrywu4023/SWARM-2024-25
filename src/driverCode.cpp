#include "driverCode.hpp"

int leftPower;
int rightPower;
int curveChange = 0;

bool curveIncrease, prevIncrease = false;
bool curveDecrease, prevDecrease = false;

bool climbUp;
bool climbDown;

bool ptoOn;
bool ptoOff;

void tankDrive () {
    // Contoller values
    leftPower = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    rightPower = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    curveIncrease = master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
    curveDecrease = master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);

    climbUp = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    climbDown = master.get_digital(pros::E_CONTROLLER_DIGITAL_L2);

    ptoOn = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    ptoOff = master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

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

    // Climb control
    if (climbDown) {
        moveL(-127);
        moveR(-127);
    }
    else if (climbUp) {
        moveL(127);
        moveR(127);
    }

    // PTO Control 
    if (ptoOn) PTO.set_value(true);
    else if (ptoOff) PTO.set_value(false);
}