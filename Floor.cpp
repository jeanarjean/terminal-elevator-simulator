#include "Floor.h"
#include "Constants.h"
#include "ncurses.h"

Floor::Floor(int height)
{
    Floor::height = height;
    passengers = new vector<Passenger*>;
}

void Floor::Update()
{
}

void Floor::Render()
{
    move(height, ELEVATOR_WIDTH);
    hline(ACS_HLINE, FLOOR_WIDTH);
    vector<Passenger*>::iterator passengerIt;
    int i = 0;
    for(passengerIt = passengers->begin(); passengerIt < passengers->end(); passengerIt++)
    {
        move(height - 1, ELEVATOR_WIDTH + i);
        addch('a');
        ++i;
    }
}

int Floor::GetHeight()
{
    return height;
}

void Floor::AddPassenger(Passenger *passenger)
{
    passengers->insert(passengers->end(), passenger);
}

