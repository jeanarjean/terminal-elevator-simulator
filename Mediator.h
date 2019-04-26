#ifndef MEDIATOR_H
#define MEDIATOR_H
#include <vector>

class Elevator;
class Floor;
class Mediator
{
  public:
    Mediator();
    ~Mediator();

    void Start();

  private:
    Elevator *elevator;
    std::vector<Floor> *floors;
    int ticksToSpawnPassenger;

    void TransferFromElevatorToFloor(Elevator* elevator, Floor* floor);
    void TransferFromFloorToElevator(Elevator* elevator, Floor* floor);

    void DetermineElevatorDirection();

    void SpawnPassenger();
};

#endif