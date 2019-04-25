#include "Passenger.h"
#include "Constants.h"
#include "Floor.h"

Passenger::Passenger(Floor* floorWants, Floor* floorSpawned)
{
    floorWantsToGo = floorWants;
    if(floorWantsToGo->GetHeight() > floorSpawned->GetHeight())
    {
       direction = DIRECTION_DOWN; 
    }
    else
    {
       direction = DIRECTION_UP; 
    }
}