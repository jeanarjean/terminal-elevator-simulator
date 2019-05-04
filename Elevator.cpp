#include "Elevator.h"
#include "Passenger.h"
#include "Constants.h"
#include <iostream>

using namespace std;

Elevator::Elevator() : current_floor(0)
{
  number_of_floors = LINES / 5;
  InitRender();
  // direction = DIRECTION_UP;
  direction = DIRECTION_UP;
  ticksWaited = 0;
  stopped = false;
  passengers = new std::vector<Passenger>;
}

void Elevator::InitRender()
{
  x = 0;
  // y = 20;
  y = LINES;
  win = newwin(ELEVATOR_HEIGHT, ELEVATOR_WIDTH, y - ELEVATOR_HEIGHT + 1, x);
  leaveok(win, true);
  box(win, 0, 0);
  wrefresh(win);
  refresh();
}

void Elevator::Tick()
{
  if (stopped)
  {
    ++ticksWaited;
    ticksWaited = ticksWaited + 1;
    move(0, 0);
    if (ticksWaited > TICKS_TO_STOP)
    {
      stopped = false;
    }
  }
  else if (direction == DIRECTION_READJUSTING)
  {
    if (y < readjustingHeight)
    {
      y++;
      if (y == readjustingHeight)
      {
        direction = DIRECTION_UP;
      }
    }
    else if (y > readjustingHeight)
    {
      y--;
      if (y == readjustingHeight)
      {
        direction = DIRECTION_DOWN;
      }
    }
  }
  else if (direction == DIRECTION_DOWN)
  {
    if (y < LINES - 1)
    {
      y++;
    }
  }
  else if (direction == DIRECTION_UP)
  {
    if (y > 3)
    {
      y--;
    }
  }
  else if (direction == DIRECTION_IDLE)
  {
  }

  Render();
}

void Elevator::Render()
{
  int i = 0;
  std::vector<Passenger>::iterator passengerIt;
  for (passengerIt = passengers->begin(); passengerIt < passengers->end(); passengerIt++)
  {
    move(y - 1, ++i);
    addch(passengerIt->getSprite());
  }

  EraseElevatorLag(y + 1);
  EraseElevatorLag(y - ELEVATOR_HEIGHT);
  mvwin(win, y - ELEVATOR_HEIGHT + 1, 0);
  wrefresh(win);
}

void Elevator::EraseElevatorLag(int y)
{
  move(y, 0);
  for (int i = 0; i < ELEVATOR_WIDTH; ++i)
  {
    addch(' ');
  }
  move(y, 0);
}

const int Elevator::GetHeight()
{
  return y;
}

const int Elevator::GetDirection()
{
  return direction;
}

void Elevator::SetDirection(int newDirection)
{
  direction = newDirection;
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

std::vector<Passenger> *Elevator::getPassengers()
{
  return passengers;
}

void Elevator::Readjust(int readjustHeight)
{
  direction = DIRECTION_READJUSTING;
  readjustingHeight = readjustHeight;
}