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

// Skills right side
void skillsR () {
    // Start autonomous
    autoStart(0, 0, 0);

    // 1. Move to middle 6 balls right side
    setIntakeLow(-80);
    setIntakeHigh(127);
    setPos(-3, 30);
    pros::delay(700);

    setIntakeLow(60);

    setPos(6, 57);
    pros::delay(1200);

    setIntakeHigh(60);
    setIntakeLow(60);
    setHeading(80);
    pros::delay(800);

    setIntakeHigh(127);
    setIntakeLow(127);

    // 2. Intake middle 6 balls right side
    for (int i = 0; i < 8; i++) {
        if (i == 3) setIntakeHigh(127);

        setPos(10 + i * 3, 50);
        pros::delay(200);
    }

    setIntakeHigh(0);
    pros::delay(200);
    setIntakeLow(0);

    // 3. Move to right long goal
    setPos(15, 25);
    pros::delay(1000);

    setPos(37, 10);
    pros::delay(1500);

    setHeading(180);
    pros::delay(1500);

    setPos(37, 45);
    pros::delay(1000);

    // 4. Score ball
    setPos(globalX, globalY);

    setIntakeHigh(127);
    setIntakeLow(127);
    pros::delay(6000);

    setIntakeHigh(0);
    setIntakeLow(0);

    // 5. Intake match loader right close
    setTorch(true);

    setIntakeLow(127);
    setIntakeHigh(127);

    setPos(40, -14);
    pros::delay(1000);

    setPos(globalX, globalY + 1);
    pros::delay(400);
    setPos(globalX, globalY - 6);
    pros::delay(2000);

    setIntakeLow(0);
    setIntakeHigh(0);

    setPos(50, 10);
    pros::delay(1000);

    setTorch (false);

    // 6. Move to other side of goal

    for (int i = 0; i < 3; i++) {
        setPos(50, 40 + i * 20);
        pros::delay(500);
    }

    setPos(33, 100);
    pros::delay(1000);

    setHeading(0);
    pros::delay(1200);

    setPos(35, 70);
    pros::delay(1000);

    // 7. Score ball
    setIntakeHigh(127);
    setIntakeLow(127);
    pros::delay(2000);

    setPos(globalX, globalY);
    pros::delay(4000);

    // 8. Intake match loader right far
    setTorch(true);

    setPos(32.5, 118);
    pros::delay(1000);

    setPos(globalX, globalY - 1);
    pros::delay(500);
    setPos(globalX, globalY + 6);
    pros::delay(2000);

    setIntakeHigh(0);
    setIntakeLow(0);

    setPos(34, 100);
    pros::delay(1000);

    setTorch (false);

    setPos(35, 70);
    pros::delay(1000);

    // 9. Score ball
    setIntakeHigh(127);
    setIntakeLow(127);
    pros::delay(2000);

    setPos(globalX, globalY);
    pros::delay(2000);

    setIntakeHigh(0);

    // 10. Park
    setIntakeHigh(0);
    setIntakeLow(0);

    setPos(35, 120);
    pros::delay(800);

    setHeading(300);
    pros::delay(800);

    setPos(0, 118);
    pros::delay(2000);

    setHeading(270);
    pros::delay(800);

    setTorch(true);

    setPos(-5, 125);
    pros::delay(800);
    
    setPos(-80, 140);
    pros::delay(800);

    setPos(globalX, globalY);
    pros::delay(500);

    setTorch(false);
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