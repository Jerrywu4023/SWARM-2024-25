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

bool intakeGoal, intakeLB, raiseLB, scoreLB;
bool intakeRev;
bool prevIntake = false;
bool intakeOn = false;

bool clampButton, prevClamp = false;
bool clampState = false;
bool clampOn, clampOff;

bool reacherButton, prevReacher = false;
bool reacherState = false;

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

    intakeGoal = digital(pros::E_CONTROLLER_DIGITAL_L1);
    intakeLB = digital(pros::E_CONTROLLER_DIGITAL_UP);

    intakeRev = digital(pros::E_CONTROLLER_DIGITAL_L2);

    raiseLB = digital(pros::E_CONTROLLER_DIGITAL_A);
    scoreLB = digital(pros::E_CONTROLLER_DIGITAL_X);

    clampButton = digital(pros::E_CONTROLLER_DIGITAL_R1);
    clampOff = digital(pros::E_CONTROLLER_DIGITAL_R2);

    reacherButton = digital(pros::E_CONTROLLER_DIGITAL_R2);


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

    // Intake control + wall stake
    if (intakeRev)
        setIntake(-127);
    else if (intakeGoal && !prevIntake) {
        intakeOn = !intakeOn;
        LBState = 0;
    }
    else if (intakeLB) {
        setIntake(127);
        LBState = 1;
    }
    else if (raiseLB) {
        setIntake(-100);
        LBState = 2;
    }
    else if (scoreLB) {
        setIntake(-100);
        LBState = 3;
    }
    else
        setIntake(0);

    prevIntake = intakeGoal;

    // Intake to goal
    if (LBState == 0 && !intakeRev) {
        if (intakeOn) setIntake(127);
        else setIntake(0);
    } else intakeOn = false;


    // Clamp Control
    if (clampButton && !prevClamp) clampState = !clampState;
    setClamp(clampState);

    prevClamp = clampButton;

    // Reacher Control
    if(reacherButton && !prevReacher) reacherState = !reacherState;
    setReacher(reacherState);

    prevReacher = reacherButton;

    current = getAvgCurrent();
    pros::lcd::print(2, "drive current: %d", current);
    master.print(0, 0, "Curve adjust: %.2lf", curveChange);
}

/**
 * @brief Split arcade drive
 */
void splitArcade () {
    // Contoller values
    leftPower = analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    rightPower = analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * 1.2;

    intakeGoal = digital(pros::E_CONTROLLER_DIGITAL_L1);
    intakeLB = digital(pros::E_CONTROLLER_DIGITAL_UP);

    intakeRev = digital(pros::E_CONTROLLER_DIGITAL_L2);

    raiseLB = digital(pros::E_CONTROLLER_DIGITAL_A);
    scoreLB = digital(pros::E_CONTROLLER_DIGITAL_X);

    clampButton = digital(pros::E_CONTROLLER_DIGITAL_R1);
    clampOff = digital(pros::E_CONTROLLER_DIGITAL_R2);

    reacherButton = digital(pros::E_CONTROLLER_DIGITAL_R2);

    // Drive control
    movePL(leftPower + rightPower);
    movePR(leftPower - rightPower);

    // Intake control + wall stake
    if (intakeRev)
        setIntake(-127);
    else if (intakeGoal) {
        setIntake(127);
        LBState = 0;
    }
    else if (intakeLB) {
        setIntake(127);
        LBState = 1;
    }
    else if (raiseLB) {
        setIntake(0);
        LBState = 2;
    }
    else if (scoreLB) {
        setIntake(0);
        LBState = 3;
    }
    else
        setIntake(0);


    // Clamp Control
    if (clampButton && !prevClamp) clampState = !clampState;
    setClamp(clampState);

    prevClamp = clampButton;

    // Reacher Control
    if(reacherButton && !prevReacher) reacherState = !reacherState;
    setReacher(reacherState);

    prevReacher = reacherButton;

    // Disable colour sort
    //if (digital(pros::E_CONTROLLER_DIGITAL_B)) sortColour = false;
}