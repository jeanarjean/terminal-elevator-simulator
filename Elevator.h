#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <ncurses.h>

class Elevator
{
public:
    Elevator();

    void Update();
    void Render();
    void InitRender();

private:
    int y;
    int x;
    WINDOW *win;
};

#endif