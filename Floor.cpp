#include "Floor.h"
#include "Constants.h"
#include <ncurses.h>

Floor::Floor(int height) : height(height)
{
   InitRender();
}

void Floor::InitRender()
{
   move(height,ELEVATOR_WIDTH);
   hline(ACS_HLINE, FLOOR_WIDTH);
}

void Floor::Tick()
{
}

void Floor::PressUpButton()
{
   upButtonPresed = true;
}

void Floor::PressDownButton()
{
   downButtonPresed = true;
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