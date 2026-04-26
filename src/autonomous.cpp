#include "autonomous.hpp"
#include "autoVariables.hpp"
#include "driveFunc.hpp"
#include "drivefunc.hpp"

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
    setPos(20, 30);
    pros::delay(3000);

    setPos(20, -20);
    pros::delay(3000);
    
    setPos(-10, 20);
    pros::delay(3000);
    
    setPos(0, 0);
    pros::delay(3000);

    setHeading(90);
    pros::delay(1500);

    autoControl = false;
    moveL(100);
    moveR(100);
    pros::delay(500);
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
    // 1
    setHeight(true);
    setLever(-127);
    setPos(0, 43);
    pros::delay(1200);
    setLever(0);

    setHeading(270);
    pros::delay(800);
    setTorch(true);
    pros::delay(500);

    setIntake(127);
    setPos(-17, 37);
    pros::delay(1000);

    for(int i = 0; i < 2; i++) {
        setPos(globalX + 20, 37);
        pros::delay(500);
        setPos(-20, 37);
        pros::delay(1200);
    }

    setTorch(false);
    setPos(10, 35);
    pros::delay(800);

    setAligner(true);
    setPos(20, 35);
    pros::delay(1000);

    setGate(false);
    setLever(127);
    pros::delay(1000);

    setLever(-127);
    setGate(true);
    setAligner(false);
    setPos(0, 35);
    pros::delay(800);

    // 2
    setTorch(true);
    setIntake(127);
    setPos(-25, 37);
    pros::delay(1500);
    setLever(0);

    for(int i = 0; i < 2; i++) {
        setPos(globalX + 20, globalY);
        pros::delay(500);
        setPos(-25, globalY);
        pros::delay(1200);
    }

    setPos(10, 35);
    pros::delay(500);

    setGate(false);
    setLever(127);
    pros::delay(1000);
    setLever(-127);
    pros::delay(500);

    // 3
    setPos(-25, 37);
    pros::delay(1500);
    setLever(0);

    for(int i = 0; i < 4; i++) {
        setPos(globalX + 20, globalY);
        pros::delay(500);
        setPos(-25, globalY);
        pros::delay(1200);
    }

    setTorch(false);
    setPos(10, 35);
    pros::delay(800);

    setAligner(true);
    setPos(20, 35);
    pros::delay(1000);

    setGate(false);
    setLever(127);
    pros::delay(1000);
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