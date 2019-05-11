#include <iostream>
#include <ncurses.h>
#include "Elevator.h"
#include "Mediator.h"

using namespace std;

int main()
{
  initscr();
  noecho();

  Mediator mediator;

  mediator.Run();

  endwin();
  return 0;
}

