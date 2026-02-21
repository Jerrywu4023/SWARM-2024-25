#ifndef _DRIVE_
#define _DRIVE_

#include "globals.hpp"

void moveL(int velocity);

void moveR(int velocity);

void movePL(int power);

void movePR(int power);

void HardBreak();

void driveTare();

void setIntakeHigh(int power);

void setIntakeLow(int power);

void setIntakeRaise(bool state);

#endif