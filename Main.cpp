#include <iostream>
#include "Elevator.h"

using namespace std;

int main ()
{
  cout << "Hello, world!" << endl;
  Elevator elevator(5);
  cout << elevator.getFloor() << endl;
  return 0;
}