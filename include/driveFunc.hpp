#ifndef _DRIVE_
#define _DRIVE_

#include "globals.hpp"

void moveL(int velocity);

void moveR(int velocity);

void movePL(int power);

void movePR(int power);

void HardBreak();

void driveTare();

int getAvgCurrent();

void intakeControl ();
void setIntake(int power);

void wallStakeControl ();

void setClamp(bool state);

void setReacher(bool state);

// Intake control variables
extern const int redAlliance;
extern const int blueAlliance;

extern int intakePower;
extern int sortColourHue;
extern bool controlIntake;
extern bool sortColour;

// Wall stake variables
extern int LBState;

#endif