#include "autonomous.hpp"

/**
 * @brief Begin necessary tasks for autonomous 
 */
void autoStart (int x, int y, int heading) {
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
    intakeControl(-127);
    pros::delay(200);

    // ring 0-1
    intakeControl(127);
    setPos(0, 12);
    pros::delay(600);

    setPos(0, -10);
    pros::delay(500);
    
    autoControl = false;
    moveL(0);
    moveR(0);
    pros::delay(400);
    //intakeControl(0);
    pros::delay(200);
    intakeControl(100);
    pros::delay(400);
    intakeControl(-127);
    pros::delay(200);
    autoControl = true;

    // ring 1-2
    setPos(-25, 45);
    intakeControl(127);
    pros::delay(1000);

    // goal 1
    setHeading(90);
    pros::delay(700);
    intakeControl(0);

    setPos(-60, 45);
    pros::delay(800);
    clamp.set_value(false);
    pros::delay(300);

    // ring 1-3
    setHeading(0);
    intakeControl(127);
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

    intakeControl(0);
    setHeading(180);
    pros::delay(800);
    intakeControl(127);

    setPos(-45, 10);
    pros::delay(800);
    
    // ring 1-6
    setHeading(230);
    pros::delay(800);

    setPos(-76, -7);
    pros::delay(1000);

    // corner 1
    setPos(-55, 15);
    pros::delay(1000);
    
    setHeading(45);
    pros::delay(500);
    
    setPos(-70, -5);
    pros::delay(1000);
    clamp.set_value(true);
    intakeControl(0);

    // reset 1
    setPos(-45, 20);
    pros::delay(500);

    setPos(-45, 50);
    pros::delay(500);

    setPos(-45, 85);
    pros::delay(800);

    // goal 2
    setHeading(226);
    pros::delay(800);

    setPos(-19, 93);
    pros::delay(1000);
    clamp.set_value(false);
    pros::delay(300);

    // rings 2-1~4
    setHeading(135);
    pros::delay(800);
    intakeControl(127);

    setPos(10, 65);
    pros::delay(1500);

    setPos(13, 55);
    pros::delay(500);

    // ring 2-5
    setHeading(140);
    pros::delay(600);

    setPos(30, 30);
    pros::delay(1200);

    // ring 2-6
    setPos(60, 10);
    pros::delay(2000);

    // ring 2-7
    setPos(70, -8);
    pros::delay(1500);

    // corner 2
    setPos(60, 10);
    pros::delay(1000);
    
    setHeading(315);
    pros::delay(800);

    setPos(80, -10);
    pros::delay(1000);
    clamp.set_value(true);
    intakeControl(0);

    // reset 2
    setPos(60, 15);
    pros::delay(500);

    setHeading(270);
    pros::delay(600);

    autoControl = false;
    movePL(-100);
    movePR(-100);
    pros::delay(1000);
    globalX = 70;
    globalY = 10;
    autoControl = true;

    // Goal 3
    setHeading(128);
    pros::delay(1200);

    setPos(48, 47);
    pros::delay(1100);
    clamp.set_value(false);
    pros::delay(200);

    // Ring 3-1
    setHeading(5);
    pros::delay(800);

    intakeControl(127);
    setPos(52, 70);
    pros::delay(800);

    // Ring 3-2
    setPos(52, 95);
    pros::delay(800);
    
    // Corner 3
    setPos(70, 70);
    pros::delay(500);

    setHeading(210);
    pros::delay(800);

    setPos(76, 130);
    pros::delay(200);
    clamp.set_value(true);
    pros::delay(1300);

    setPos(60, 110);
    pros::delay(1000);

    setHeading(300);
    pros::delay(800);

    setPos(20, 140);
    pros::delay(1000);

    // Goal 4
    setHeading(50);
    pros::delay(1000);

    setPos(-10, 105);
    pros::delay(900);
    clamp.set_value(false);
    pros::delay(200);

    // Ring 4-1
    setHeading(270);
    pros::delay(700);

    setPos(-30, 115);
    pros::delay(800);

    // Corner 4
    setHeading(120);
    pros::delay(1700);
    
    setPos(-75, 145);
    pros::delay(200);
    clamp.set_value(true);
    pros::delay(1300);

    setHeading(115);
    endAuto = true;

    movePL(30);
    movePR(30);
    

    /*// climb
    setPos(0, globalY - 10);
    pros::delay(1500);

    autoControl = false;
    movePL(0);
    movePR(0);
    autoControl = true;

    setHeading(180);

    intakeControl(0);
    pros::delay(200000);*/
}

/**
 * @brief 15 inch skills run main route
 */
void driverSkills () {
    // intake release
    intakeControl(-127);
    pros::delay(200);

    // ring 0-1
    intakeControl(127);
    setPos(0, 12);
    pros::delay(600);

    setPos(0, -10);
    pros::delay(500);
    
    autoControl = false;
    moveL(0);
    moveR(0);
    pros::delay(400);
    intakeControl(0);
    pros::delay(200);
    intakeControl(100);
    pros::delay(300);
    intakeControl(-127);
    pros::delay(200);
    autoControl = true;

    // ring 1-2
    setPos(-25, 45);
    intakeControl(127);
    pros::delay(1000);

    // goal 1
    setHeading(90);
    pros::delay(700);
    intakeControl(0);

    setPos(-60, 45);
    pros::delay(800);
    clamp.set_value(false);
    pros::delay(300);

    // ring 1-3
    setHeading(5);
    intakeControl(127);
    pros::delay(500);
}