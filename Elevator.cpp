#include "Elevator.h"
#include <iostream>

using namespace std;

Elevator::Elevator() : number_of_floors(5), current_floor(0) {}

Elevator::Elevator(int floor) : number_of_floors(floor), current_floor(0) {}

void Elevator::tick() 
{
  cout << "ELEVATOR TICK - CURRENT FLOOR: " << current_floor << endl;
}

int Elevator::GetCurrentFloor()
{
    return current_floor;
}

int Elevator::GetNumberOfFloors()
{
    return number_of_floors;
}