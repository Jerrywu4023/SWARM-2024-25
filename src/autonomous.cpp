#include "autonomous.hpp"

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
    setPos(-3, 30);
    pros::delay(700);

    setIntakeLow(127);

    setPos(5, 50);
    pros::delay(1000);

    setHeading(60);
    pros::delay(700);

    // 2. Intake middle 6 balls right side
    for (int i = 0; i < 4; i++) {
        setPos(10 + i * 6, 48);
        pros::delay(400);
    }

    pros::delay(2000);

    // 3. Move to right long goal
    setPos(15, 25);
    pros::delay(1000);

    setPos(37, 10);
    pros::delay(1500);

    setHeading(180);
    pros::delay(1500);

    setPos(35, 30);
    pros::delay(1000);

    // 4. Score ball
    setIntakeHigh(127);
    pros::delay(4000);

    setIntakeHigh(0);

    // 5. Intake match loader right close
    setTorch(true);

    setPos(36, -10);
    pros::delay(5000);

    setPos(45, 0);
    pros::delay(800);

    // 6. Intake right wall 2 balls
    setTorch(false);
    
    setHeading(315);
    pros::delay(1000);

    setPos(45, -10);
    pros::delay(800);

    setHeading(40);
    pros::delay(800);

    setPos(55, 10);
    pros::delay(1000);

    setPos(55, 15);
    pros::delay(1500);

    // 7. Move to far side of right long goal

    for (int i = 0; i < 3; i++) {
        setPos(52, 40 + i * 20);
        pros::delay(500);
    }

    setPos(36, 100);
    pros::delay(1000);

    setHeading(0);
    pros::delay(1000);

    setPos(35, 77);
    pros::delay(1000);

    // 8. Score ball
    setIntakeHigh(127);
    pros::delay(4000);

    setIntakeHigh(0);

    // 9. Intake match loader right far
    setTorch(true);

    setPos(36, 120);
    pros::delay(3000);

    setPos(36, 100);
    pros::delay(1000);

    setTorch (false);

}