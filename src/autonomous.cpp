#include "autonomous.hpp"

/**
 * @brief Begin necessary tasks for autonomous 
 */
void autoStart (int x, int y, int heading) {
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
    setHeading(90);
    pros::delay (3000);

    setHeading(225);
    pros::delay (3000);

    setHeading(180);
    pros::delay (3000);

    setHeading(0);
    pros::delay (300000);
}

/**
 * @brief 15 inch skills run main route
 */
void skills_15 () {
    // intake release
    intake.move(-127);
    pros::delay(200);

    // ring 0-1
    intake.move(127);
    setPos(0, 12);
    pros::delay(600);

    setPos(0, -5);
    pros::delay(500);
    
    autoControl = false;
    moveL(0);
    moveR(0);
    pros::delay(400);
    intake.move(0);
    pros::delay(200);
    intake.move(127);
    pros::delay(250);
    intake.move(-127);
    pros::delay(200);
    autoControl = true;

    // ring 1-2
    setPos(-23, 40);
    intake.move(127);
    pros::delay(1200);

    // goal 1
    setHeading(90);
    pros::delay(800);
    intake.move(0);

    setPos(-60, 42);
    pros::delay(800);
    clamp.set_value(false);
    pros::delay(300);

    // ring 1-3
    setHeading(0);
    intake.move(127);
    pros::delay(500);
    
    setPos(-50, 70);
    pros::delay(1000);

    // ring 1-4
    setPos(-65, 42);
    pros::delay(500);

    setHeading(350);
    pros::delay(500);
    
    setPos(-63, 65);
    pros::delay(600);

    // ring 1-5
    setPos(-50, 35);
    pros::delay(1000);

    setHeading(180);
    pros::delay(800);

    setPos(-45, 10);
    pros::delay(800);
    
    // ring 1-6
    setHeading(225);
    pros::delay(800);

    setPos(-67, -7);
    pros::delay(1000);

    // corner 1
    setPos(-55, 15);
    pros::delay(1000);
    
    setHeading(45);
    pros::delay(500);
    
    setPos(-70, -5);
    pros::delay(1000);
    clamp.set_value(true);
    intake.move(0);

    // reset 1
    setPos(-45, 20);
    pros::delay(500);

    setPos(-45, 50);
    pros::delay(500);

    setPos(-45, 85);
    pros::delay(800);

    // goal 2
    setHeading(225);
    pros::delay(800);

    setPos(-21, 90);
    pros::delay(800);
    clamp.set_value(false);
    pros::delay(300);

    // rings 2-1~4
    setHeading(135);
    pros::delay(800);
    intake.move(127);

    setPos(0, 70);
    pros::delay(1000);
    setPos(10, 70);
    pros::delay(800);

    setPos(-8, 70);
    pros::delay(800);

    setPos(0, 60);
    pros::delay(1300);
    setPos(10, 60);
    pros::delay(300);

    // ring 2-5
    setHeading(135);
    pros::delay(600);

    setPos(30, 30);
    pros::delay(800);

    // ring 2-6
    setPos(60, 10);
    pros::delay(800);

    // ring 2-7
    setPos(70, -8);
    pros::delay(1300);

    // corner 2
    setPos(60, 10);
    pros::delay(1000);
    
    setHeading(315);
    pros::delay(800);

    setPos(80, -10);
    pros::delay(1000);
    clamp.set_value(true);
    intake.move(0);

    // reset 2
    setPos(60, 15);
    pros::delay(500);

    setHeading(180);
    pros::delay(800);

    // climb
    setPos(5, 0);
    pros::delay(2000);

    setHeading(180);

    intake.move(0);
    pros::delay(200000);
}