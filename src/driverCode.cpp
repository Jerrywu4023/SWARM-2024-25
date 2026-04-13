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
double curveChange1 = -6;
double curveChange2 = -6;

bool curveIncrease, prevIncrease = false;
bool curveDecrease, prevDecrease = false;

// Intake
bool intakeFwd, intakeRev;

// Lever
bool leverFwd, fastLever;
double leverPwr;

// Pneumatics
bool torchBtn, torchPrev;
bool heightBtn, heightPrev;
bool descoreBtn;

bool torchState = false;
bool heightState = true;

/**
 * @brief Calculates the motors powers with tank drive curve
 * 
 * @param value - joystick value
 * @return motor power
 */
double powerCalculate (int value, double curveChange) {
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

    leverFwd = digital(pros::E_CONTROLLER_DIGITAL_L1);
    fastLever = digital(pros::E_CONTROLLER_DIGITAL_B);

    torchBtn = digital(pros::E_CONTROLLER_DIGITAL_UP);
    heightBtn = digital(pros::E_CONTROLLER_DIGITAL_L2);
    descoreBtn = digital(pros::E_CONTROLLER_DIGITAL_X);


    // Drive control - exponential tank
    if (curveIncrease && !prevIncrease && curveChange1 < -1) 
        curveChange1 += 0.25;
    if (curveDecrease && !prevDecrease) 
        curveChange1 -= 0.25;

    // Drive power calculate
    leftPower = powerCalculate(leftPower, curveChange1);
    rightPower = powerCalculate(rightPower, curveChange2);

    // Drive power output
    movePL(leftPower);
    movePR(rightPower);

    prevIncrease = curveIncrease;
    prevDecrease = curveDecrease;

    // Intake control
    if (intakeRev) setIntake(-127);
    else if (intakeFwd) setIntake(127);
    else setIntake(0);

    // Lever control
    leverPwr = (170 - lever2.get_position()) / 1.5;

    if (leverFwd) {
        setLever(leverPwr);
        setBallBlock(false);
    }
    else if (fastLever) {
        setLever(127);
        setBallBlock(false);
    }
    else {
        setLever(-20);
        setBallBlock(true);
    }

    // Torch control
    if (torchBtn && !torchPrev) torchState = !torchState;
    setTorch(torchState);
    torchPrev = torchBtn;

    // Height control
    if (heightBtn && !heightPrev) heightState = !heightState;
    setHeight(heightState);
    heightPrev = heightBtn;

    // Descore
    setDescore(descoreBtn);

    master.print(0, 0, "Curve adjust 1: %.2lf", curveChange1);
}

/**
 * @brief Split arcade drive
 */
void splitArcade () {
    // Contoller values
    leftPower = -analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    rightPower = analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    curveIncrease = digital(pros::E_CONTROLLER_DIGITAL_UP);
    curveDecrease = digital(pros::E_CONTROLLER_DIGITAL_DOWN);

    intakeFwd = digital(pros::E_CONTROLLER_DIGITAL_R1);
    intakeRev = digital(pros::E_CONTROLLER_DIGITAL_R2);

    leverFwd = digital(pros::E_CONTROLLER_DIGITAL_L1);
    fastLever = digital(pros::E_CONTROLLER_DIGITAL_B);

    torchBtn = digital(pros::E_CONTROLLER_DIGITAL_UP);
    heightBtn = digital(pros::E_CONTROLLER_DIGITAL_L2);
    descoreBtn = digital(pros::E_CONTROLLER_DIGITAL_X);


    // Drive control - exponential tank
    if (curveIncrease && !prevIncrease && curveChange1 < -1) 
        curveChange1 += 0.25;
    if (curveDecrease && !prevDecrease) 
        curveChange1 -= 0.25;

    // Drive power calculate
    rightPower = powerCalculate(rightPower, curveChange1);

    // Drive power output
    movePL(leftPower + rightPower);
    movePR(leftPower - rightPower);

    prevIncrease = curveIncrease;
    prevDecrease = curveDecrease;

    // Intake control
    if (intakeRev) setIntake(-127);
    else if (intakeFwd) setIntake(127);
    else setIntake(0);

    // Lever control
    leverPwr = (170 - lever2.get_position()) / 1.5;

    if (leverFwd) {
        setLever(leverPwr);
        setBallBlock(false);
    }
    else if (fastLever) {
        setLever(127);
        setBallBlock(false);
    }
    else {
        setLever(-20);
        setBallBlock(true);
    }

    // Torch control
    if (torchBtn && !torchPrev) torchState = !torchState;
    setTorch(torchState);
    torchPrev = torchBtn;

    // Height control
    if (heightBtn && !heightPrev) heightState = !heightState;
    setHeight(heightState);
    heightPrev = heightBtn;

    // Descore
    setDescore(descoreBtn);

    master.print(0, 0, "Curve adjust 1: %.2lf", curveChange1);
}