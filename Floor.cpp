#include "Floor.h"
#include "Constants.h"
#include "Passenger.h"
#include <ncurses.h>

Floor::Floor(int height) : height(height)
{
   InitRender();
   upButtonPresed = false;
   downButtonPresed = false;
   passengers = new std::vector<Passenger>;
}

void Floor::InitRender()
{
   move(height, ELEVATOR_WIDTH);
   hline(ACS_HLINE, FLOOR_WIDTH);
}

void Floor::Tick()
{
   if (upButtonPresed)
   {
      move(height - 3, ELEVATOR_WIDTH);
      addch(ACS_UARROW);
   }
   else
   {
      move(height - 3, ELEVATOR_WIDTH);
      addch(' ');
   }
   if (downButtonPresed)
   {
      move(height - 2, ELEVATOR_WIDTH);
      addch(ACS_DARROW);
   }
   else
   {
      move(height - 2, ELEVATOR_WIDTH);
      addch(' ');
   }
        std::vector<Passenger>::iterator passengerIt;
        for (passengerIt = passengers->begin(); passengerIt < passengers->end(); passengerIt++)
        {
           move(height - 1, ELEVATOR_WIDTH);
           addch('a');
        }
}

void Floor::PressUpButton()
{
   upButtonPresed = true;
}

void Floor::ResetUpButton()
{
   upButtonPresed = false;
}

void Floor::PressDownButton()
{
   downButtonPresed = true;
}

void Floor::ResetDownButton()
{
   downButtonPresed = false;
}

int Floor::GetHeight()
{
   return height;
}

bool Floor::UpButtonPressed()
{
   return upButtonPresed;
}

bool Floor::DownButtonPressed()
{
   return downButtonPresed;
}

std::vector<Passenger>* Floor::getPassengers()
{
   return passengers;
}