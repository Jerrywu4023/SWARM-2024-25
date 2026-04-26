#include "driverCode.hpp"
#include "driveFunc.hpp"
#include "pros/misc.h"
#include "pros/motors.h"

#define E 2.7182819
#define analog(joystick) master.get_analog(joystick)
#define digital(button) master.get_digital(button)

// Drive
int leftPower;
int rightPower;

// Drive for tank
double curveChange = 0;

bool curveIncrease, prevIncrease = false;
bool curveDecrease, prevDecrease = false;

// Intake
bool intakeFwd, intakeRev, intakeBottom, outtakeBall;
bool fastScoreButton, slowScoreButton;
int scorePower = 127;

// Intake for tank
bool prevIntake = false;
bool intakeOn = false;

// Pneumatics
bool torchBtn, torchPrev;
bool gateBtn, gatePrev;
bool descoreBtn, descorePrev;

bool torchState = false;
bool gateState = false;
bool descoreState = false;

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

    curveIncrease = digital(pros::E_CONTROLLER_DIGITAL_UP);
    curveDecrease = digital(pros::E_CONTROLLER_DIGITAL_DOWN);

    intakeFwd = digital(pros::E_CONTROLLER_DIGITAL_R1);
    intakeRev = digital(pros::E_CONTROLLER_DIGITAL_R2);

    torchBtn = digital(pros::E_CONTROLLER_DIGITAL_L2);
    gateBtn = digital(pros::E_CONTROLLER_DIGITAL_R2);
    descoreBtn = digital(pros::E_CONTROLLER_DIGITAL_Y);

    // Drive control - exponential tank
    if (curveIncrease && !prevIncrease && curveChange < -1) 
        curveChange += 0.25;
    if (curveDecrease && !prevDecrease) 
        curveChange -= 0.25;

    // Drive power calculate
    leftPower = powerCalculate(leftPower);
    rightPower = powerCalculate(rightPower);

    // Drive power output
    movePL(leftPower);
    movePR(rightPower);

    prevIncrease = curveIncrease;
    prevDecrease = curveDecrease;

    // Intake control
    if (fastScoreButton) scorePower = 127;
    else if (slowScoreButton) scorePower = 80;

    if (intakeRev) {
        setIntakeLow(-127);
        setIntakeHigh(-127);
    } else if (intakeFwd) {
        setIntakeLow(127);
        setIntakeHigh(127);
    } else {
        setIntakeLow(0);
        setIntakeHigh(0);
    }

    // Pneumatics control
    if (torchBtn && !torchPrev) torchState = !torchState;
    setTorch(torchState);

    torchPrev = torchBtn;

    if (gateBtn && !gatePrev) gateState = !gateState;
    setTorch(gateState);

    gatePrev = gateBtn;

    if (descoreBtn && !descorePrev) descoreState = !descoreState;
    setTorch(descoreState);

    descorePrev = descoreBtn;

    master.print(0, 0, "Curve adjust: %.2lf", curveChange);
}

/**
 * @brief Split arcade drive
 */
void splitArcade () {
    // Contoller values
    leftPower = -analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    rightPower = analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 1.5;

    curveIncrease = digital(pros::E_CONTROLLER_DIGITAL_UP);
    curveDecrease = digital(pros::E_CONTROLLER_DIGITAL_DOWN);

    intakeFwd = digital(pros::E_CONTROLLER_DIGITAL_R2);
    intakeBottom = digital(pros::E_CONTROLLER_DIGITAL_R1);
    intakeRev = digital(pros::E_CONTROLLER_DIGITAL_L1);

    torchBtn = digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
    gateBtn = digital(pros::E_CONTROLLER_DIGITAL_L2);
    descoreBtn = digital(pros::E_CONTROLLER_DIGITAL_Y);

    // Drive control - exponential tank
    if (curveIncrease && !prevIncrease && curveChange < -1) 
        curveChange += 0.25;
    if (curveDecrease && !prevDecrease) 
        curveChange -= 0.25;

    // Drive power calculate
    rightPower = powerCalculate(rightPower);

    // Drive power output
    movePL(leftPower + rightPower);
    movePR(leftPower - rightPower);

    prevIncrease = curveIncrease;
    prevDecrease = curveDecrease;

    // Intake control
    if (fastScoreButton) scorePower = 127;
    else if (slowScoreButton) scorePower = 80;

    if (intakeRev) {
        setIntakeLow(-127);
        setIntakeHigh(-127);
    } else if (intakeFwd) {
        setIntakeLow(127);
        setIntakeHigh(127);
    } else if (intakeBottom) {
        setIntakeLow(127);
        setIntakeHigh(0);
    } else {
        setIntakeLow(0);
        setIntakeHigh(0);
    }

    // Pneumatics control
    if (torchBtn && !torchPrev) torchState = !torchState;
    setTorch(torchState);

    torchPrev = torchBtn;

    if (gateBtn && !gatePrev) gateState = !gateState;
    setGate(gateState);

    gatePrev = gateBtn;

    if (descoreBtn && !descorePrev) descoreState = !descoreState;
    setDescore(descoreState);

    descorePrev = descoreBtn;
}