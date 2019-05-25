#ifndef PASSENGER_H
#define PASSENGER_H
#include "Floor.h"
#include <map>

using namespace std;

class Passenger
{
public:
    Passenger(int requestedFloorHeight, int direction);
    int direction;
    int requestedFloorHeight;

private:
    int rand_between(int min, int max);
};

#endif