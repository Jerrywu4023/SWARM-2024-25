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

// Skills right side
void skillsR () {
    // Start autonomous
    autoStart(0, 0, 0);

    // 1. Move to middle 6 balls right side
    setIntakeLow(-80);
    setIntakeHigh(127);
    setPos(-4, 30);
    pros::delay(700);

    setIntakeLow(60);

    setPos(5, 55);
    pros::delay(1200);

    setHeading(70);
    pros::delay(300);

    setIntakeLow(127);

    // 2. Intake middle 6 balls right side
    for (int i = 0; i < 8; i++) {
        if (i == 3) setIntakeHigh(127);

        setPos(10 + i * 3, 48);
        pros::delay(200);
    }

    setIntakeHigh(0);
    pros::delay(200);
    setIntakeLow(0);

    // 3. Move to right long goal
    setPos(15, 25);
    pros::delay(1000);

    setPos(38, 10);
    pros::delay(1500);

    setHeading(180);
    pros::delay(1500);

    setPos(38, 45);
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

    setPos(40, -10);
    pros::delay(1000);

    setPos(globalX, globalY + 1);
    pros::delay(400);
    setPos(globalX, globalY - 6);
    pros::delay(2000);

    setIntakeLow(0);
    setIntakeHigh(0);

    setPos(50, 10);
    pros::delay(800);

    for (int i = 0; i < 3; i++) {
        setPos(52, 40 + i * 20);
        pros::delay(500);
    }

    setPos(36, 100);
    pros::delay(1000);

    setHeading(0);
    pros::delay(1000);

    setPos(35, 70);
    pros::delay(1000);

    // 8. Score ball
    setIntakeHigh(127);
    setIntakeLow(127);
    pros::delay(2000);

    setPos(globalX, globalY);
    pros::delay(2000);

    setIntakeHigh(0);

    // 9. Intake match loader right far
    setTorch(true);

    setPos(34, 120);
    pros::delay(1000);

    setPos(globalX, globalY - 1);
    pros::delay(500);
    setPos(globalX, globalY + 5);
    pros::delay(2000);

    setPos(34, 100);
    pros::delay(1000);

    setTorch (false);

}