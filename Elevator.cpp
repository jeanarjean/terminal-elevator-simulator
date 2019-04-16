#include "Elevator.h"
#include "Constants.h"
#include <iostream>

using namespace std;

Elevator::Elevator() : current_floor(0)
{
  number_of_floors = LINES / 5;
  InitRender();
  direction = DIRECTION_UP;
}

void Elevator::Tick()
{
  Render();
}

void Elevator::InitRender()
{
  x = 0;
  y = LINES-ELEVATOR_HEIGHT;
  win = newwin(ELEVATOR_HEIGHT, ELEVATOR_WIDTH, y, x);
  leaveok(win, true);
  box(win, 0, 0);
  wrefresh(win);
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
  refresh();
}

void Elevator::MoveUpRender()
{
  //TODO: Once state implemented,  Y will not be changed here
  // Replace y with last floor position
  if (y > 3)
  {
    EraseElevatorLag(y + ELEVATOR_HEIGHT - 1);
    mvwin(win, --y, 0);
  }
}

void Elevator::MoveDownRender()
{
  //TODO: Once state implemented,  Y will not be changed here
  if (y < LINES - ELEVATOR_HEIGHT - 1)
  {
    EraseElevatorLag(y);
    mvwin(win, ++y, 0);
  }
}

void Elevator::EraseElevatorLag(int y)
{
    move(y, 0);
    for(int i = 0; i < ELEVATOR_WIDTH; ++i)
    {
      addch(' ');
    }
}
