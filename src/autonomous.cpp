#include "autonomous.hpp"

void test () {
    movePL(127);
    movePR(20);
    pros::delay(3000);
    movePL(0);
    movePR(0);
}