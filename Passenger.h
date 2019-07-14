#ifndef PASSENGER_H
#define PASSENGER_H
#include "Floor.h"
#include <map>

using namespace std;

class Passenger
{
public:
    Passenger(int requestedFloorHeight, int direction);
    int GetDirection();
    int GetRequestedFloorHeight();
    const char GetSprite();

private:
    int rand_between(int min, int max);
    int requestedFloorHeight;
    int direction;
    char sprite;
};

#endif