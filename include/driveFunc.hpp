#ifndef _DRIVE_
#define _DRIVE_

#include "globals.hpp"

// Drive
void moveL(int velocity);
void moveR(int velocity);
void movePL(int power);
void movePR(int power);

void HardBreak();
void driveTare();
int getAvgCurrent();

// Intake
void intakeControl ();
void setIntake(int power);
void setFrontIntake(int power);
void setBackIntake(int power);

// Wallstake
void wallStakeControl ();

// Pneumatics
void setClamp(bool state);
void setIntakeRaise(bool state);

// Intake control variables
extern const int redAlliance;
extern const int blueAlliance;

extern int intakePowerF;
extern int intakePowerB;
extern int sortColourHue;
extern bool controlIntake;
extern bool sortColour;

// Wall stake variables
extern int LBState;

#endif