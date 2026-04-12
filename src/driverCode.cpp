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
double curveChange = -6;

bool curveIncrease, prevIncrease = false;
bool curveDecrease, prevDecrease = false;

// Intake
bool intakeFwd, intakeRev, scoreBall, outtakeBall;
bool fastScoreButton, slowScoreButton;
int scorePower = 127;

// Intake for tank
bool prevIntake = false;
bool intakeOn = false;

// Pneumatics
bool pneumaticsBtn, prevPneumaticsBtn = false;
bool pneumaticsState = false;

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

    intakeFwd = digital(pros::E_CONTROLLER_DIGITAL_L1);
    intakeRev = digital(pros::E_CONTROLLER_DIGITAL_L2);

    scoreBall = digital(pros::E_CONTROLLER_DIGITAL_R1);
    outtakeBall = digital(pros::E_CONTROLLER_DIGITAL_R2);

    fastScoreButton = digital(pros::E_CONTROLLER_DIGITAL_A);
    slowScoreButton = digital(pros::E_CONTROLLER_DIGITAL_Y);

    pneumaticsBtn = digital(pros::E_CONTROLLER_DIGITAL_X);


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

    if (outtakeBall) {
        setIntakeLow(-127);
        setIntakeHigh(-127);
    } else if (scoreBall) {
        setIntakeLow(127);
        setIntakeHigh(scorePower);
    } else if (intakeRev) {
        setIntakeLow(-127);
        setIntakeHigh(0);
    } else if (intakeFwd) {
        setIntakeLow(127);
        setIntakeHigh(0);
    } else {
        setIntakeLow(0);
        setIntakeHigh(0);
    }

    // Pneumatics control
    if (pneumaticsBtn && !prevPneumaticsBtn) pneumaticsState = !pneumaticsState;
    setTorch(pneumaticsState);

    prevPneumaticsBtn = pneumaticsBtn;

    master.print(0, 0, "Curve adjust: %.2lf", curveChange);
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
    intakeRev = digital(pros::E_CONTROLLER_DIGITAL_L2);

    scoreBall = digital(pros::E_CONTROLLER_DIGITAL_L1);

    fastScoreButton = digital(pros::E_CONTROLLER_DIGITAL_A);
    slowScoreButton = digital(pros::E_CONTROLLER_DIGITAL_Y);

    pneumaticsBtn = digital(pros::E_CONTROLLER_DIGITAL_X);


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
    else if (slowScoreButton) scorePower = 90;

    if (intakeRev) {
        setIntakeLow(-127);
        setIntakeHigh(-127);
    } else if (scoreBall) {
        setIntakeLow(127);
        setIntakeHigh(scorePower);
    } else if (intakeFwd) {
        setIntakeLow(127);
        intake3.move_velocity(250);
    } else {
        setIntakeLow(0);
        setIntakeHigh(0);
    }

    // Pneumatics control
    if (pneumaticsBtn && !prevPneumaticsBtn) pneumaticsState = !pneumaticsState;
    setTorch(pneumaticsState);

    prevPneumaticsBtn = pneumaticsBtn;
}

/**
 * @brief Robot Testing
 */
void robotTesting () {
    // Contoller values
    leftPower = analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    rightPower = analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    curveIncrease = digital(pros::E_CONTROLLER_DIGITAL_UP);
    curveDecrease = digital(pros::E_CONTROLLER_DIGITAL_DOWN);

    intakeFwd = digital(pros::E_CONTROLLER_DIGITAL_R1);
    intakeRev = digital(pros::E_CONTROLLER_DIGITAL_R2);

    scoreBall = digital(pros::E_CONTROLLER_DIGITAL_L1);

    fastScoreButton = digital(pros::E_CONTROLLER_DIGITAL_A);
    slowScoreButton = digital(pros::E_CONTROLLER_DIGITAL_Y);

    pneumaticsBtn = digital(pros::E_CONTROLLER_DIGITAL_X);


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
    else if (slowScoreButton) scorePower = 90;

    if (scorePower == 90) {
        intake3.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        intake3.brake();
    } else {
        intake3.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        if (intakeFwd) intake3.move(127);
        else if (intakeRev) intake3.move(-127);
        else intake3.move(0);
    }

    intake1.move(leftPower);
    intake2.move(rightPower);

    // Pneumatics control
    if (pneumaticsBtn && !prevPneumaticsBtn) pneumaticsState = !pneumaticsState;
    setTorch(pneumaticsState);

    prevPneumaticsBtn = pneumaticsBtn;
}