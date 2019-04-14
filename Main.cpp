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
  Elevator elevator(5);

  mediator.start();

  endwin();
  return 0;
}

