#include "autonomous.hpp"

/**
 * @brief Begin necessary tasks for autonomous 
 */
void autoStart (int x, int y, double heading, int hue) {
    autoControl = true;
    endAuto = false;
    globalX = x;
    globalY = y;
    thetaReset = heading;
    sortColourHue = hue;

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
    autoStart(0, 0, 0, redAlliance);

    setPos(20, 30, false);
    pros::delay(3000);

    setPos(20, -20, false);
    pros::delay(3000);
    
    setPos(-10, 20, true);
    pros::delay(3000);
    
    setPos(0, 0, false);
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
    autoStart(0, 0, 0, redAlliance);

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
 * @brief Skills
 */
void skills () {
    autoStart(0, 0, 0, redAlliance);

    // Red alliance stake
    LBState = 1;
    setIntake(127);
    setPos(0, 15, true);
    pros::delay(1000);

    setHeading(50);
    pros::delay(200);
    setHeading(180);
    pros::delay(800);

    setIntake(0);
    setIntakeRaise(true);
    LBState = 4;

    setPos(0, -15, true);
    pros::delay(500);

    setPos(0, 5, true);
    pros::delay(200);
    LBState = 5;
    pros::delay(500);

    setPos(-30, 15, true);
    pros::delay(800);
    
    setHeading(140);
    pros::delay(300);

    // Goal 1
    LBState = 0;
    setIntakeRaise(false);

    setPos(-42, 32, false);
    pros::delay(1000);

    setHeading(140);
    pros::delay(300);

    setPos(-48, 38, true);
    pros::delay(600);
    setClamp(true);
    pros::delay(200);

    // Ring 1-1
    setHeading(0);
    pros::delay(700);
    setIntake(127);

    setPos(-46, 60, true);
    pros::delay(1000);

    // Ring 1-2
    setPos(-65, 25, false);
    pros::delay(600);

    setHeading(90);
    pros::delay(700);

    setPos(-16, 33, true);
    pros::delay(1000);

    // Ring 1-3
    setHeading(45);
    pros::delay(1000);

    setPos(0, 56, true);
    pros::delay(300);
    setBackIntake(0);
    pros::delay(800);

    // Ring 1-4
    setPos(-30, 27, true);
    pros::delay(800);

    setIntake(127);
    setHeading(225);
    pros::delay(800);

    setPos(-50, 5, true);
    pros::delay(800);

    // Ring 1-5
    setPos(-65, -5, true);
    pros::delay(1500);

    // Corner 1
    setPos(-40, 15, true);
    pros::delay(700);

    setHeading(45);
    pros::delay(500);

    setPos(-65, -5, false);
    pros::delay(800);
    clamp.set_value(false);
    pros::delay(200);

    setPos(-40, 15, false);
    pros::delay(500);
    setHeading(0);
    pros::delay(700);

    // Wall stake 1
    setBackIntake(0);
    setPos(-54, 70, true);
    pros::delay(1500);

    LBState = 1;
    setBackIntake(127);
    setPos(-30, 63, false);
    pros::delay(700);

    setIntakeRaise(true);
    setHeading(270);
    pros::delay(800);

    LBState = 2;
    setIntake(0);
    setPos(-60, 63, true);
    pros::delay(800);

    LBState = 3;
    pros::delay(500);
    setPos(-35, 63, true);
    pros::delay(500);
    
    // Goal 2
    LBState = 0;
    setHeading(230);
    pros::delay(800);

    setPos(-15, 84, true);
    pros::delay(800);
    setClamp(true);
    pros::delay(1000);

    // Ring 2-1
    setHeading(270);
    setIntake(127);
    setPos(-40, 84, true);
    pros::delay(1300);

    setIntakeRaise(false);
    pros::delay(800);

    // Ring 2-2
    setIntakeRaise(true);
    setHeading(0);
    pros::delay(800);

    setIntake(127);
    setPos(-47, 110, true);
    pros::delay(1300);

    setIntakeRaise(false);
    pros::delay(800);

    // Ring 2-3
    setIntakeRaise(true);
    setPos(-62, 120, false);
    pros::delay(300);

    setPos(-62, 120, true);
    pros::delay(1000);

    setIntakeRaise(false);
    pros::delay(800);

    // Corner 2
    setPos(-40, 110, true);
    pros::delay(700);

    setHeading(135);
    pros::delay(700);

    setPos(-62, 120, false);
    pros::delay(800);
    clamp.set_value(false);
    pros::delay(200);

}