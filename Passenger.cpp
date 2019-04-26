#include "Passenger.h"
#include "Constants.h"
#include "Floor.h"
#include <iostream>

Passenger::Passenger(Floor* floorWants, Floor* floorSpawned)
{
    floorWantsToGo = floorWants;
    if(floorWantsToGo->GetHeight() > floorSpawned->GetHeight())
    {
       direction = DIRECTION_DOWN; 
       if(!floorSpawned->DownButtonPressed())
       {
         floorSpawned->PressDownButton();
       }
    }
    else
    {
       direction = DIRECTION_UP; 
       if(!floorSpawned->UpButtonPressed())
       {
         floorSpawned->PressUpButton();
       }
    }
    direction = DIRECTION_DOWN; 
    int r = std::rand() % 26;   // generate a random number
    sprite = 'a' + r;
}

Floor* Passenger::getFlootWantsToGo()
{
   return floorWantsToGo;
}


const int Passenger::getDirection()
{
   return direction;
}

const char Passenger::getSprite()
{
   return sprite;
}