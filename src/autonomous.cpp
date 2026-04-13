#include "autonomous.hpp"
#include "autoVariables.hpp"
#include "driveFunc.hpp"

/**
 * @brief Begin necessary tasks for autonomous 
 */
void autoStart (int x, int y, double heading) {
    autoControl = true;
    endAuto = false;
    globalX = x;
    globalY = y;
    thetaReset = heading;

    driveTare();

    pros::Task odom(odometry);
    pros::Task move(driveControl);
	pros::Task turning(turnControl);
	pros::Task out(powerOutput);
    pros::delay(20);
}

/**
 * @brief Test drive to point, control disable, turning
 */
void testDrive () {
    autoStart(0, 0, 0);

    setPos(20, 30);
    pros::delay(3000);

    setPos(20, -20);
    pros::delay(3000);
    
    setPos(-10, 20);
    pros::delay(3000);
    
    setPos(0, 0);
    pros::delay(3000);

    setHeading(90);
    pros::delay(1000);

    autoControl = false;
    moveL(100);
    moveR(100);
    pros::delay(1000);
    moveL(0);
    moveR(0);
    pros::delay(500);
    autoControl = true;

    setHeading(0);
    pros::delay(100000);
}

/**
 * @brief Test turn on spot accuracy 
 */
void testTurn () {
    autoStart(0, 0, 0);

    setHeading(90);
    pros::delay (3000);

    setHeading(225);
    pros::delay (3000);

    setHeading(180);
    pros::delay (3000);

    setHeading(0);
    pros::delay (300000);
}

// Match Auto
void matchAuto () {
    // Start autonomous
    autoStart(0, 0, 0);
}

// Skills right side
void skillsR () {
    // Start autonomous
    autoStart(0, 0, 0);
}

// Skills park Zone
void skillsP () {
    moveL(100);
    moveR(100);
    pros::delay(800);
    moveL(0);
    moveR(0);
    pros::delay(1500);
    moveL(100);
    moveR(100);
    pros::delay(800);
    moveL(0);
    moveR(0);
}

// Skills 1 motor move
void skills1M () {
    moveL(100);
    pros::delay(200);
}