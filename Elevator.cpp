#include "Elevator.h"
#include "Passenger.h"
#include "Constants.h"
#include <iostream>

using namespace std;

Elevator::Elevator() : current_floor(0)
{
  number_of_floors = LINES / 5;
  InitRender();
  // state = ELEVATOR_STATE_GOING_UP;
  state = ELEVATOR_STATE_GOING_UP;
  ticksWaited = 0;
  stopped = false;
  passengers = new std::vector<Passenger>;
}

void Elevator::InitRender()
{
  x = ELEVATOR_STATE_GOING_DOWN;
  // y = 20;
  y = LINES;
  win = newwin(ELEVATOR_HEIGHT, ELEVATOR_WIDTH, y - ELEVATOR_HEIGHT + 1, x);
  leaveok(win, true);
  box(win, 0, 0);
  wrefresh(win);
  refresh();
}

void Elevator::Update()
{
  switch (state)
  {
  case ELEVATOR_STATE_IDLE:
    /* code */
    break;

  case ELEVATOR_STATE_GOING_DOWN:
    if (y < LINES - 1)
    {
      y++;
    }
    break;
  case ELEVATOR_STATE_GOING_UP:
    if (y > 3)
    {
      y--;
    }
    break;
  case ELEVATOR_STATE_READJUSTING:
    if (y < readjustingHeight)
    {
      y++;
      if (y == readjustingHeight)
      {
        state = ELEVATOR_STATE_GOING_UP;
      }
    }
    else if (y > readjustingHeight)
    {
      y--;
      if (y == readjustingHeight)
      {
        state = ELEVATOR_STATE_GOING_DOWN;
      }
    }
    break;
  case ELEVATOR_STATE_STOPPED:
    ++ticksWaited;
    ticksWaited = ticksWaited + 1;
    move(0, 0);
    if (ticksWaited > TICKS_TO_STOP)
    {
      state = previous_state;
    }
    break;

  default:
    break;
  }
}

void Elevator::Render()
{
  int elevatorCapacity = ELEVATOR_HEIGHT * ELEVATOR_WIDTH;
  for (int i = 0; i < elevatorCapacity; i++)
  {
    move(i / ELEVATOR_WIDTH - 1, i % ELEVATOR_WIDTH);
    addch(' ');
  }

  int i = 0;
  std::vector<Passenger>::iterator passengerIt;
  for (passengerIt = passengers->begin(); passengerIt < passengers->end(); passengerIt++)
  {
    ++i;
    move(y - i / ELEVATOR_WIDTH - 1, i % ELEVATOR_WIDTH);
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

const int Elevator::GetState()
{
  return state;
}

void Elevator::SetState(int newState)
{
  state = newState;
}

void Elevator::Stop()
{
  ticksWaited = 0;
  previous_state = state;
  state = ELEVATOR_STATE_STOPPED;
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
  state = ELEVATOR_STATE_READJUSTING;
  readjustingHeight = readjustHeight;
}