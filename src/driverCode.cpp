#include "driverCode.hpp"

#define E 2.7182819
#define analog(joystick) master.get_analog(joystick)
#define digital(button) master.get_digital(button)

int leftPower;
int rightPower;
double curveChange = -3.6;
bool driveReverse = false;

bool curveIncrease, prevIncrease = false;
bool curveDecrease, prevDecrease = false;

bool intakeButton;
bool intakeRev;
bool prevIntake = false;
bool intakeOn = false;

bool clampOn;
bool clampOff;

int current;

/**
 * @brief Calculates the motors powers with tank drive curve
 * 
 * @param value - joystick value
 * @return motor power
 */
double powerCalculate (int value) {
    double p1 = pow(E, curveChange / 10);
    double p2 = pow(E, ((double) abs(value) - 127) / 10);
    return value * (p1 + p2 * (1 - p1));
}

/**
 * @brief Tank drive with custom curves
 */
void tankDrive () {
    // Contoller values
    leftPower = analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    rightPower = analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    curveIncrease = digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
    curveDecrease = digital(pros::E_CONTROLLER_DIGITAL_LEFT);

    intakeButton = digital(pros::E_CONTROLLER_DIGITAL_L1);
    intakeRev = digital(pros::E_CONTROLLER_DIGITAL_L2);

    clampOn = digital(pros::E_CONTROLLER_DIGITAL_R1);
    clampOff = digital(pros::E_CONTROLLER_DIGITAL_R2);

    // Drive control - exponential tank
    if (curveIncrease && !prevIncrease && curveChange < -1) 
        curveChange += 0.25;
    if (curveDecrease && !prevDecrease) 
        curveChange -= 0.25;
    
    // Drive reverse
    if (digital(pros::E_CONTROLLER_DIGITAL_X)) driveReverse = false;
    else if (digital(pros::E_CONTROLLER_DIGITAL_B)) driveReverse = true;

    // Drive power calculate
    if (!driveReverse) {
        leftPower = powerCalculate(leftPower);
        rightPower = powerCalculate(rightPower);
    } else {
        leftPower = -powerCalculate(rightPower);
        rightPower = -powerCalculate(leftPower);
    }

    // Drive power output
    movePL(leftPower);
    movePR(rightPower);

    prevIncrease = curveIncrease;
    prevDecrease = curveDecrease;

    // Intake control
    if (intakeButton && !prevIntake) 
        intakeOn = !intakeOn;

    if (intakeRev)
        setIntake(-127);
    else if (intakeOn)
        setIntake(127);
    else
        setIntake(0);

    prevIntake = intakeButton;

    // Clamp Control 
    if (clampOn) clamp.set_value(false);
    else if (clampOff) clamp.set_value(true);

    current = getAvgCurrent();
    pros::lcd::print(2, "drive current: %d", current);
    master.print(0, 0, "Curve adjust: %.2lf", curveChange);
}

/**
 * @brief Split arcade drive
 */
void splitArcade () {
    // Contoller values
    leftPower = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    rightPower = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * 1.2;

    intakeButton = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    intakeRev = master.get_digital(pros::E_CONTROLLER_DIGITAL_L2);

    clampOn = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    clampOff = master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

    // Drive control
    movePL(leftPower + rightPower);
    movePR(leftPower - rightPower);

    // Intake control
    if (intakeButton && !prevIntake) 
        intakeOn = !intakeOn;

    if (intakeRev)
        setIntake(-127);
    else if (intakeButton)
        setIntake(127);
    else
        setIntake(0);

    prevIntake = intakeButton;

    // Clamp Control 
    if (clampOn) clamp.set_value(false);
    else if (clampOff) clamp.set_value(true);
}