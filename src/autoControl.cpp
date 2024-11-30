#include "autoControl.hpp"

/**
 * @brief Set the desired coordinate of robot
 * 
 * @param x - desired X value
 * @param y - desired Y value
 */
void setPos (double x, double y) {
    desX = x;
    desY = y;
    driveTurn = 1;
}

/**
 * @brief Set the desired heading of robot
 * 
 * @param heading - desired heading in degrees
 */
void setHeading (double heading) {
    desHeading = heading;
    driveTurn = 0;
}

/**
 * @brief Calculates the magnitude and direction of offset vector 
 */
void vectorCalculation () {
    // Get angle offset
    offsetAngleGlobal = atan2(desX - globalX, desY - globalY) * 180 / PI;
    offsetAngle = offsetAngleGlobal - heading;

    // Adjust angle within [-180, 180]
    while (offsetAngle > 180) offsetAngle -= 180;
    while (offsetAngle < 180) offsetAngle += 180;

    // Get distance
    offsetDistance = sqrt(pow(desX - globalX, 2) + pow(desY - globalY, 2));
}

/**
 * @brief Calculates the drive and turn power for each drive motor based on the angle and distance 
 */
void driveControl () {
    while (!endAuto) {
        if (driveTurn == 1) {
            // Get offset vecotr
            vectorCalculation();

            // Calculate turn restriction multiplier
            turnRestrict = fabs(offsetAngle) / 30;
            if (turnRestrict > 30) turnRestrict = 30;

            // Desired pos ahead of robot
            if (fabs(offsetAngle) < 90) {
                drivePower = offsetDistance * drivePowerMulti;
                turnPower = offsetAngle * turnPowerMulti;
            }

            // Desired pos behind and left of robot
            else if (offsetAngle < 0) {
                drivePower = offsetDistance * drivePowerMulti * -1;
                turnPower = (offsetAngle + 180) * turnPowerMulti;
            }

            // Desired pos behind and right of robot
            else {
                drivePower = offsetDistance * drivePowerMulti * -1;
                turnPower = (offsetAngle - 180) * turnPowerMulti;
            }

            // Update turn power with power restrict - reduce quick turning when close to destination
            turnPower *= turnRestrict;
        }

        pros::delay(5);
    }
}


/**
 * @brief Calculates the turn velocity of robot for turning on the spot
 */
void turnControl () {
    int headingDiff; // Positive difference in heading from current to desired
    while (!endAuto) {
        if (driveTurn == 0) {
            headingDiff = fabs(desHeading - heading);

            // Desired heading less than current heading
            if (desHeading < heading) {
                if (headingDiff < 180) // turning left closer
                    turnPower = -1 * headingDiff * turnSpotMulti;
                else // turning right closer
                    turnPower = -1 * (headingDiff - 360) * turnSpotMulti;
            }

            // Desired heading greater than current heading
            else {
                if (headingDiff < 180) // turning right closer
                    turnPower = headingDiff * turnSpotMulti;
                else // turning left closer
                    turnPower = (headingDiff - 360) * turnSpotMulti;
            }
        }

        pros::delay(5);
    }
}

/**
 * @brief Runs drive motors based on calculated power
 *        - For driving to a point, move power used
 *        - For turning on the spot, move velocity used
 *        Idk man it just works better...
 */

void powerOutput () {
    while (!endAuto) {
        if (autoControl) {
            if (driveTurn == 0) { // Move to a point
                movePL(drivePower + turnPower);
                movePR(drivePower - turnPower);
            }

            else { // Move on the spot
                moveL(turnPower);
                moveR(turnPower * -1);
            }
        }

        pros::delay(5);
    }
}