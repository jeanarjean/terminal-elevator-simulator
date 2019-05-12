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

    void Run();
    void Update();
    void Render();

  private:
    Elevator *elevator;
    std::vector<Floor> *floors;
    int ticksToSpawnPassenger;

    void DetermineElevatorDirection();
    bool DetermineIfShouldStopForPassengers(Elevator *elevator, Floor *floor);

    void SpawnPassenger();
};

#endif