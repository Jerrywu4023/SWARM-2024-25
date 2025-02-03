#include "odometry.hpp"

// ODOM VARIABLES
// tracking wheel dist to center
double Sl = 0.5;
double Ss = 1.6;

// tracking wheel diameters (inches)
double wheelL = 2;
double wheelS = 2;

// encoder values (centi degrees)
double totalL = 0;
double totalS = 0;

// actual total distance (inches)
double currL = 0;
double currS = 0;

// previous total distance (inches)
double prevL = 0;
double prevS = 0;

// tracking dist change (inches)
double deltL = 0;
double deltS = 0;

// angles (radians)
double thetaReset = 0; // inital starting angle
double deltTheta; // change in angle
double theta1 = 0; // abs orientation
double theta0 = 0; // previous abs orientation
double thetaMean = 0; // avg orientation, angle for local offset

// local offset
double deltX;
double deltY;

// global offset
double globalDeltX;
double globalDeltY;

// polar conversion of offset var
double offTheta; // rad angle of offset
double offRadius; // magnitude of offset vector


// ODOM FUNCTION
void odometry () {    
    // Constant loop to update odom values
    while (!endAuto) {
        // Get encoder values
        totalL = trackingL.get_position();
        totalS = trackingS.get_position() * -1;

        // Convert encoder values to distance traveled
        currL = totalL * (PI / 36000) * (wheelL);
        currS = totalS * (PI / 36000) * (wheelS);

        // Get the change in tracking wheel distance
        deltL = currL - prevL;
        deltS = currS - prevS;

        // Update previous tracking wheel distances
        prevL = currL;
        prevS = currS;

        // Get absoulte orientation
        theta1 = thetaReset + (imu1.get_rotation() * imu1Multi * PI / 180);
        heading = theta1 * (180 / PI);

        // Get change in angle
        deltTheta = theta1 - theta0;

        // Get average orientation (half angle) for calculating global offset
        thetaMean = (theta0 + theta1) / 2;

        // Update previous angle
        theta0 = theta1;

        // Calculate offset distance of local curves - local offset
        if (deltTheta == 0) { // no angle change
            deltX = deltS;
            deltY = deltL;
        } else { // angle change
            deltX = (2 * sin(-deltTheta / 2)) * (-deltS / deltTheta - Ss);
			deltY = (2 * sin(deltTheta / 2)) * (deltL / deltTheta - Sl);
        }

        // Convert local offset to global offset
        offTheta = atan2f(deltY, deltX);
        offRadius = sqrt(pow(deltX, 2) + pow(deltY, 2));
        offTheta -= thetaMean; // get offTheta according to current orientation
        globalDeltX = cos(offTheta) * offRadius;
        globalDeltY = sin(offTheta) * offRadius;

        // Add the current global offset to the previous global position
        globalX += globalDeltX;
        globalY += globalDeltY;

        // Convert heading to the range [0, 360)
        while (heading > 360) {
			heading -= 360;
		}
        while (heading < 0) {
            heading += 360;
        }

        // Print values
        pros::lcd::print(0, "currL: %f", currL);
        pros::lcd::print(1, "currS: %f", currS);
        pros::lcd::print(3, "X: %f", globalX);
        pros::lcd::print(4, "Y: %f", globalY);
        pros::lcd::print(5, "Heading: %f", heading);

        // Delay
        pros::delay(5);
    }
}