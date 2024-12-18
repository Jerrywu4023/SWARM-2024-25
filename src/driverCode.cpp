#include "driverCode.hpp"

#define E 2.7182819
#define analog(joystick) master.get_analog(joystick)
#define digital(button) master.get_digital(button)

int leftPower;
int rightPower;
double curveChange = -5.1;

bool curveIncrease, prevIncrease = false;
bool curveDecrease, prevDecrease = false;

bool climbUp;
bool climbDown;

bool ptoOn;
bool ptoOff;

int current;

double powerCalculate (int value) {
    double p1 = pow(E, curveChange / 10);
    double p2 = pow(E, ((double) abs(value) - 127) / 10);
    return value * (p1 + p2 * (1 - p1));
}

void tankDrive () {
    // Contoller values
    leftPower = analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    rightPower = analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    curveIncrease = digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
    curveDecrease = digital(pros::E_CONTROLLER_DIGITAL_LEFT);

    climbUp = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    climbDown = master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

    ptoOn = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    ptoOff = master.get_digital(pros::E_CONTROLLER_DIGITAL_L2);

    // Drive control - exponential tank
    if (curveIncrease && !prevIncrease && curveChange < -1) 
        curveChange += 0.25;
    if (curveDecrease && !prevDecrease) 
        curveChange -= 0.25;

    leftPower = powerCalculate(leftPower);
    rightPower = powerCalculate(rightPower);

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

    // Check drive current draw
    current = getAvgCurrent();
    pros::lcd::print(2, "drive current: %d", current);
}