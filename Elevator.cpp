#include "Elevator.h"

Elevator::Elevator() : floor(0) { }

Elevator::Elevator(int floor): floor(floor) {}

int Elevator::getFloor()
{
 return floor;
} 