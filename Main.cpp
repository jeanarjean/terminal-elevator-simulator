#include <iostream>
#include <curses.h>
#include "Elevator.h"
#include "Mediator.h"

using namespace std;

int main()
{
  Mediator mediator;
  Elevator elevator(5);
  cout << "Number of Floors: " << elevator.GetNumberOfFloors() << endl;
  cout << "Current Floor: " << elevator.GetCurrentFloor() << endl;

  mediator.start();
  return 0;
}

