#include "autoVariables.hpp"

double PI = 3.1415926535897;

// Control switch
bool endAuto = false; // Indicates if autonomous ended
bool autoControl = true; // Indicates if drive controlled by coordination system or hard code
int driveTurn = 0; // 0 drive, 1 turn

// Global position + heading
double heading = 0;
double globalX = 0;
double globalY = 0;

// Desired position + heading
double desX;
double desY;
double desHeading;

// Offset vector
double offsetAngle;
double offsetAngleGlobal;
double offsetDistance;

// Drive power
double drivePower;
double drivePowerMulti = 2;

// Turn power
double turnPower;
double turnRestrict;
double turnPowerMulti = 3;
double turnSpotMulti = 2;
