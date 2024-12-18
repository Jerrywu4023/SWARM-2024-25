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
 * @brief auto elevation
 */
void autoClimb () {
    climbTrack.reset_position();
    pros::delay(200);
    
    // Climb first and second bar
    for (int i = 0; i < 2; i++) {
        movePL(127);
        movePR(127);
        while (climbTrack.get_position() < 100000) pros::delay(20);
        movePL(0);
        movePR(0);
        pros::delay(200);
        movePL(-127);
        movePR(-127);
        while (climbTrack.get_position() > 1000) pros::delay(20);
        movePL(0);
        movePR(0);
        pros::delay(200);
    }

    // Climb third bar
    movePL(127);
    movePR(127);
    while (climbTrack.get_position() < 200000) pros::delay(20);
    movePL(0);
    movePR(0);
    hardBrake();

    pros::delay(200000);
}

/**
 * @brief 24 inch skills run main route
 */
void skills_24 () {
    // Wait for 15
    setHeading(270);
    pros::delay(10000);

    // Move to elevation, slowly
    setPos(-50, 0);
    pros::delay(5000);

    setHeading(0);
    pros::delay(2000);

    setPos(-50, 50);
    pros::delay(3000);

    // Hold robot still
    autoControl = false;
    hardBrake();
    pros::delay(20000);

    // Climb
    autoClimb();

    pros::delay(200000);
}