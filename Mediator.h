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
};

#endif