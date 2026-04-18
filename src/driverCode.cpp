#include "driverCode.hpp"
#include "driveFunc.hpp"
#include "globals.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include <cstdint>

#define E 2.7182819
#define analog(joystick) master.get_analog(joystick)
#define digital(button) master.get_digital(button)

// Drive
int leftPower;
int rightPower;

// Drive for tank
double curveChange1 = -1;
double curveChange2 = -1;

bool curveIncrease, prevIncrease = false;
bool curveDecrease, prevDecrease = false;

// Intake
bool intakeFwd, intakeRev;

// Lever
bool leverFwd, fastLever;
double leverPwr;

double kp1 = 1.5;
double kp2 = 2.5;

// Pneumatics
bool torchBtn, torchPrev;
bool alignerBtn, alignerPrev;;
bool heightBtn, heightPrev;
bool descoreBtn;

bool torchAlignState = false;
bool heightState = true;
bool alignerState = true;

// Delay counters
int gateCounter = 100000;
int torchCounter = 100000;
int alignerCounter = 100000;
int heightCounter = 100000;
int downScoreCounter = 100000;

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

    curveIncrease = digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
    curveDecrease = digital(pros::E_CONTROLLER_DIGITAL_LEFT);

    intakeFwd = digital(pros::E_CONTROLLER_DIGITAL_R1);
    intakeRev = digital(pros::E_CONTROLLER_DIGITAL_R2);

    leverFwd = digital(pros::E_CONTROLLER_DIGITAL_L1);
    fastLever = digital(pros::E_CONTROLLER_DIGITAL_B);

    torchBtn = digital(pros::E_CONTROLLER_DIGITAL_UP);
    alignerBtn = digital(pros::E_CONTROLLER_DIGITAL_DOWN);
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
    if (heightState) leverPwr = (175 - lever2.get_position()) / kp1;
    else leverPwr = (175 - lever2.get_position()) / kp2;

    if (leverFwd) {
        setLever(leverPwr);
        gateCounter = 0;
    }
    else if (fastLever) {
        setLever(127);
        gateCounter = 0;
    }
    else {
        setLever(-20);
    }

    if (!heightState && !leverFwd && !fastLever) downScoreCounter = 0;

    if (gateCounter < 200 && downScoreCounter > 20) setGate(false);
    else setGate(true);

    // Torch Aligner control
    if (torchBtn && !torchPrev) {
        if (torchAlignState) alignerCounter = 0;
        else torchCounter = 0;
        torchAlignState = !torchAlignState;
    }

    if (torchCounter < 35 || !heightState) setTorch(false);
    else setTorch(torchAlignState);

    if (alignerCounter < 35 || !alignerState) setAligner(false);
    else setAligner(!torchAlignState);

    if (alignerBtn && !alignerPrev) alignerState = !alignerState;

    torchPrev = torchBtn;
    alignerPrev = alignerBtn;

    // Height control
    if (heightBtn && !heightPrev) {
        heightState = !heightState;
        
        if(torchAlignState) {
            heightCounter = 0;
            torchCounter = 0;
        }
    }

    if (heightCounter < 35) setHeight(true);
    else setHeight(heightState);
    heightPrev = heightBtn;

    // Descore
    setDescore(descoreBtn);

    // Update counter
    gateCounter++;
    torchCounter++;
    alignerCounter++;
    heightCounter++;
    downScoreCounter++;

    master.print(0, 0, "CurveAdj1: %.2lf", curveChange1);
}

/**
 * @brief Split arcade drive
 */
void splitArcade () {
    // Contoller values
    leftPower = analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    rightPower = analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    curveIncrease = digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
    curveDecrease = digital(pros::E_CONTROLLER_DIGITAL_LEFT);

    intakeFwd = digital(pros::E_CONTROLLER_DIGITAL_R1);
    intakeRev = digital(pros::E_CONTROLLER_DIGITAL_R2);

    leverFwd = digital(pros::E_CONTROLLER_DIGITAL_L1);
    fastLever = digital(pros::E_CONTROLLER_DIGITAL_B);

    torchBtn = digital(pros::E_CONTROLLER_DIGITAL_UP);
    alignerBtn = digital(pros::E_CONTROLLER_DIGITAL_DOWN);
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
    if (heightState) leverPwr = (170 - lever2.get_position()) / kp1;
    else leverPwr = (170 - lever2.get_position()) / kp2;

    if (leverFwd) {
        setLever(leverPwr);
        gateCounter = 0;
    }
    else if (fastLever) {
        setLever(127);
        gateCounter = 0;
    }
    else {
        setLever(-20);
    }

    if (gateCounter < 200) setGate(false);
    else setGate(true);

    // Torch Aligner control
    if (torchBtn && !torchPrev) {
        if (torchAlignState) alignerCounter = 0;
        else torchCounter = 0;
        torchAlignState = !torchAlignState;
    }

    if (torchCounter < 50 || !heightState) setTorch(false);
    else setTorch(torchAlignState);

    if (alignerCounter < 50 || alignerBtn) setAligner(false);
    else setAligner(!torchAlignState);

    torchPrev = torchBtn;

    // Height control
    if (heightBtn && !heightPrev) heightState = !heightState;
    setHeight(heightState);
    heightPrev = heightBtn;

    // Descore
    setDescore(descoreBtn);

    // Update counter
    gateCounter++;
    torchCounter++;
    alignerCounter++;

    master.print(0, 0, "CurveAdj1: %.2lf", curveChange1);
}