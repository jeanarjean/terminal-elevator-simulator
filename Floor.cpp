#include "Floor.h"
#include "Constants.h"
#include "Passenger.h"
#include <ncurses.h>

Floor::Floor(int height) : height(height)
{
   InitRender();
   upButtonPressed = false;
   downButtonPressed = false;
   passengers = new std::vector<Passenger>;
}

void Floor::InitRender()
{
   move(height, ELEVATOR_WIDTH);
   hline(ACS_HLINE, FLOOR_WIDTH);
}

void Floor::Update()
{
   if (upButtonPressed)
   {
      move(height - 3, ELEVATOR_WIDTH);
      addch(ACS_UARROW);
   }
   else
   {
      move(height - 3, ELEVATOR_WIDTH);
      addch(' ');
   }
   if (downButtonPressed)
   {
      move(height - 2, ELEVATOR_WIDTH);
      addch(ACS_DARROW);
   }
   else
   {
      move(height - 2, ELEVATOR_WIDTH);
      addch(' ');
   }

   for (int i = 0; i < FLOOR_WIDTH; i++)
   {
      move(height - 1, ELEVATOR_WIDTH + i);
      addch(' ');
   }
   std::vector<Passenger>::iterator passengerIt;
   int i = 0;
   for (passengerIt = passengers->begin(); passengerIt < passengers->end(); passengerIt++)
   {
      move(height - 1, ELEVATOR_WIDTH + i);
      addch(passengerIt->getSprite());
      ++i;
   }
}

void Floor::PressUpButton()
{
   upButtonPressed = true;
}

void Floor::ResetUpButton()
{
   upButtonPressed = false;
}

void Floor::PressDownButton()
{
   downButtonPressed = true;
}

void Floor::ResetDownButton()
{
   downButtonPressed = false;
}

int Floor::GetHeight()
{
   return height;
}

bool Floor::UpButtonPressed()
{
   return upButtonPressed;
}

bool Floor::DownButtonPressed()
{
   return downButtonPressed;
}

std::vector<Passenger> *Floor::getPassengers()
{
   return passengers;
}