#include "autonomous.hpp"

void test () {
    moveL(600);
    moveR(200);
    pros::delay(3000);
    moveL(0);
    moveR(0);
}