#include "Floor.h"
#include "Passenger.h"
#include "Constants.h"
#include "ncurses.h"

Floor::Floor(int height)
{
    Floor::height = height;
    passengers = new vector<Passenger *>;
    upButtonPressed = false;
    downButtonPressed = false;
}

void Floor::Update()
{
}

// Render
void Floor::Render()
{
    if (upButtonPressed)
    {
        move(height - 3, ELEVATOR_WIDTH);
        addch(ACS_UARROW);
    }
    else
    {
        move(height - 3, ELEVATOR_WIDTH);
        addch(' ');
    }
    if (downButtonPressed)
    {
        move(height - 2, ELEVATOR_WIDTH);
        addch(ACS_DARROW);
    }
    else
    {
        move(height - 2, ELEVATOR_WIDTH);
        addch(' ');
    }

    move(height, ELEVATOR_WIDTH);
    hline(ACS_HLINE, FLOOR_WIDTH);
    vector<Passenger *>::iterator passengerIt;

    for (int i = 0; i < FLOOR_WIDTH; i++)
    {
        move(height - 1, ELEVATOR_WIDTH + i);
        addch(' ');
    }

    int i = 0;
    for (passengerIt = passengers->begin(); passengerIt < passengers->end(); passengerIt++)
    {
        move(height - 1, ELEVATOR_WIDTH + i);
        addch((*passengerIt)->GetSprite());
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

bool Floor::GetUpButtonState()
{
    return upButtonPressed;
}

bool Floor::GetDownButtonState()
{
    return downButtonPressed;
}

void Floor::CallElevatorUp()
{
    upButtonPressed = true;
}

void Floor::CallElevatorDown()
{
    downButtonPressed = true;
}

void Floor::ResetUpButton()
{
    upButtonPressed = false;
}

void Floor::ResetDownButton()
{
    downButtonPressed = false;
}
vector<Passenger *> *Floor::GetPassengers()
{
    return passengers;
}