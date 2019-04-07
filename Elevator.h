// Elevator.h
#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <stack>


using namespace std;

class Elevator
{
  private:
    int current_floor;
    int number_of_floors;
    stack<int> floorOrdered;

  public:
    Elevator();
    Elevator(int numberOfFloors);
    void tick();
    int GetNumberOfFloors();
    int GetCurrentFloor();
};

#endif