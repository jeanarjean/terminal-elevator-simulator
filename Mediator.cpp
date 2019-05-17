#include "Mediator.h"
#include "Elevator.h"
#include "Floor.h"
#include "Constants.h"
#include <ncurses.h>

Mediator::Mediator()
{
    elevator = new Elevator();

    floors = new map<int, Floor>;
    for (int i = LINES - 1; i > ELEVATOR_HEIGHT; i = i - FLOOR_HEIGHT)
    {
        Floor floor(i);
        floors->insert({i, floor});
    }
}

void Mediator::Run()
{
    while (1)
    {
        Update();
        Render();
    }
}

void Mediator::Update()
{
    elevator->Update();
}

void Mediator::Render()
{
}