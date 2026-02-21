#include "driverCode.hpp"

#define E 2.7182819
#define analog(joystick) master.get_analog(joystick)
#define digital(button) master.get_digital(button)

// Drive
int leftPower;
int rightPower;

// Drive for tank
double curveChange = -3.6;
bool driveReverse = false;

bool curveIncrease, prevIncrease = false;
bool curveDecrease, prevDecrease = false;

// Intake
bool intakeFwd, intakeRev, scoreBall;

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

    curveIncrease = digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
    curveDecrease = digital(pros::E_CONTROLLER_DIGITAL_LEFT);

    intakeFwd = digital(pros::E_CONTROLLER_DIGITAL_L1);
    intakeRev = digital(pros::E_CONTROLLER_DIGITAL_L2);

    scoreBall = digital(pros::E_CONTROLLER_DIGITAL_R1);

    pneumaticsBtn = digital(pros::E_CONTROLLER_DIGITAL_X);


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

    // Lower intake control
    if (intakeRev) setIntakeLow(-127);
    else if (intakeFwd) setIntakeLow(127);
    else setIntakeLow(0);

    // Upper intake control
    if (scoreBall) setIntakeHigh(127);
    else setIntakeHigh(0);

    // Pneumatics control
    if (pneumaticsBtn && !prevPneumaticsBtn) pneumaticsState = !pneumaticsState;
    setIntakeRaise(pneumaticsState);

    prevPneumaticsBtn = pneumaticsBtn;

    master.print(0, 0, "Curve adjust: %.2lf", curveChange);
}

/**
 * @brief Split arcade drive
 */
void splitArcade () {
    // Contoller values
    leftPower = analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    rightPower = analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * 1.2;

    intakeFwd = digital(pros::E_CONTROLLER_DIGITAL_L1);
    intakeRev = digital(pros::E_CONTROLLER_DIGITAL_L2);

    scoreBall = digital(pros::E_CONTROLLER_DIGITAL_R1);

    pneumaticsBtn = digital(pros::E_CONTROLLER_DIGITAL_X);

    // Drive control
    movePL(leftPower + rightPower);
    movePR(leftPower - rightPower);

    // Lower intake control
    if (intakeRev) setIntakeLow(-127);
    else if (intakeFwd) setIntakeLow(127);
    else setIntakeLow(0);

    // Upper intake control
    if (scoreBall) setIntakeHigh(127);
    else setIntakeHigh(0);

    // Pneumatics control
    if (pneumaticsBtn && !prevPneumaticsBtn) pneumaticsState = !pneumaticsState;
    setIntakeRaise(pneumaticsState);

    prevPneumaticsBtn = pneumaticsBtn;
}