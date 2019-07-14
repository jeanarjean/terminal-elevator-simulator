#include "Passenger.h"
#include "Constants.h"
#include <random>

Passenger::Passenger(int requestedFloorHeight, int direction)
{
    Passenger::direction = direction;
    Passenger::requestedFloorHeight = direction;
    int r = std::rand() % 26;
    sprite = 'a' + r;
}

int Passenger::rand_between(int min, int max)
{
    return rand() % max + min;
}

int Passenger::GetDirection()
{
    return direction;
}

int Passenger::GetRequestedFloorHeight()
{
    return requestedFloorHeight;
}

const char Passenger::GetSprite()
{
    return sprite;
}