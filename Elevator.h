#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <ncurses.h>
#include <map>

using namespace std;

class Floor;

class Elevator
{
public:
    Elevator();

    void Update(map<int, Floor*> *floors);
    void Render();
    void InitRender();
    map<int, Floor*> * GetRequestFloors();

private:
    int state;
    int y;
    int x;
    int ticksWaited;
    int previous_state;
    WINDOW *win;
    map<int, Floor*> *requestedFloors;

    void GoUp(map<int, Floor*> *floors);
    void GoDown(map<int, Floor*> *floors);
    void Idle();
    void Readjusting();
    void Stopped();

    void Stop();

    void EraseElevatorRenderLag(int y);
};

#endif