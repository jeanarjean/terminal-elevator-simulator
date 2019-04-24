#include "Elevator.h"
#include "Constants.h"
#include <iostream>

using namespace std;

Elevator::Elevator() : current_floor(0)
{
  number_of_floors = LINES / 5;
  InitRender();
  // direction = DIRECTION_UP;
  direction = DIRECTION_DOWN;
  ticksWaited = 0;
  stopped = false;
}


void Elevator::InitRender()
{
  x = 0;
  y = 20;
  // y = LINES;
  win = newwin(ELEVATOR_HEIGHT, ELEVATOR_WIDTH, y-ELEVATOR_HEIGHT+1, x);
  leaveok(win, true);
  box(win, 0, 0);
  wrefresh(win);
  refresh();
}

void Elevator::Tick()
{
  if(stopped)
  {
    ++ticksWaited;
    ticksWaited = ticksWaited + 1;
    move(0,0);
    if (ticksWaited > TICKS_TO_STOP)
    {
      stopped = false;
      Render();
    }
  }
  else
  {
    Render();
  }
}

void Elevator::Render()
{
  if(direction == DIRECTION_UP)
  {
    MoveUpRender();
  }
  else
  {
    MoveDownRender();
  }
  wrefresh(win);
}

void Elevator::MoveUpRender()
{
  //TODO: Once state implemented,  Y will not be changed here
  // Replace y with last floor position
  if (y > 3)
  {
    EraseElevatorLag(y);
    mvwin(win, --y-ELEVATOR_HEIGHT+1, 0);
  }
}

void Elevator::MoveDownRender()
{
  //TODO: Once state implemented,  Y will not be changed here
  if (y < LINES - 1)
  {
    EraseElevatorLag(y-ELEVATOR_HEIGHT+1);
    mvwin(win, ++y-ELEVATOR_HEIGHT+1, 0);
  }
}

void Elevator::EraseElevatorLag(int y)
{
    move(y, 0);
    for(int i = 0; i < ELEVATOR_WIDTH; ++i)
    {
      addch(' ');
    }
    move(y, 0);
}

int Elevator::GetHeight()
{
  return y;
}

int Elevator::GetDirection()
{
  return direction;
}


void Elevator::Stop()
{
  ticksWaited = 0;
  stopped = true;
}

bool Elevator::IsStopped()
{
  return stopped;
}