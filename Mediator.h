#ifndef MEDIATOR_H
#define MEDIATOR_H
#include "map"

using namespace std;

class Elevator;
class Floor;

class Mediator
{
public:
    Mediator();
    void Run();

private:
    void Update();
    void Render();
    void InitRender();

    Elevator *elevator;
    map<int, Floor> *floors;

};

#endif