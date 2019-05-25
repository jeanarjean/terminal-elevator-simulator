#include "Passenger.h"
#include "Constants.h"
#include <random>

Passenger::Passenger(int requestedFloorHeight, int direction)
{
    Passenger::direction = direction;
    Passenger::requestedFloorHeight = direction;
}

int Passenger::rand_between(int min, int max)
{
    return rand() % max + min;
}
