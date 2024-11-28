#include "main.h"

extern double PI;

// Control switch
extern bool endAuto;
extern bool autoControl;
extern int driveTurn;

// Global position + heading
extern double heading;
extern double globalX;
extern double globalY;

// Desired position + heading
extern double desX;
extern double desY;
extern double desHeading;

// Offset vector
extern double offsetAngle;
extern double offsetAngleGlobal;
extern double offsetDistance;

// Drive power
extern double drivePower;
extern double drivePowerMulti;

// Turn power
extern double turnPower;
extern double turnRestrict;
extern double turnPowerMulti;
extern double turnSpotMulti;