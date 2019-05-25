#ifndef MEDIATOR_H
#define MEDIATOR_H
#include <map>

using namespace std;

class Elevator;
class Floor;

class Mediator
{
public:
    Mediator();
    void Run();

private:
    Elevator *elevator;
    map<int, Floor *> *floors;

    void Update();
    void Render();
    void InitRender();
    void SpawnPassenger();
    int rand_between(int min, int max);
};

#endif