// Elevator.h
#ifndef PASSENGER_H
#define PASSENGER_H
#include "ncurses.h"

using namespace std;
class Floor;

class Passenger
{
    public:
    Passenger(Floor* spawnedFloor, Floor* floorWantsToGo);

    private:
    Floor* spawnedFloor;
    Floor* floorWantsToGo;
    int direction;

};

#endif