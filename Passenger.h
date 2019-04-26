// Elevator.h
#ifndef PASSENGER_H
#define PASSENGER_H
#include "ncurses.h"

using namespace std;
class Floor;

class Passenger
{
    public:
    Passenger(Floor* floorWantsToGo, Floor* floorSpawnedOn);
    Floor* getFlootWantsToGo();
    const int getDirection();
    const char getSprite();

    private:
    Floor* floorWantsToGo;
    int direction;
    char sprite;
};

#endif