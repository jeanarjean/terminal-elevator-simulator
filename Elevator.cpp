#include "Elevator.h"
#include "Constants.h"
#include "Floor.h"

Elevator::Elevator()
{
    state = ELEVATOR_STATE_GOING_UP;
    requestedFloors = new map<int, Floor*>;
}

// HOLY FINITE STATE AUTOMATA

void Elevator::Update(map<int, Floor*> *floors)
{
    switch (state)
    {
    case ELEVATOR_STATE_IDLE:
        Idle();
        break;
    case ELEVATOR_STATE_GOING_DOWN:
        GoDown(floors);
        break;
    case ELEVATOR_STATE_GOING_UP:
        GoUp(floors);
        break;
    case ELEVATOR_STATE_READJUSTING:
        Readjusting();
        break;
    case ELEVATOR_STATE_STOPPED:
        Stopped();
        break;

    default:
        break;
    }
}

void Elevator::GoUp(map<int, Floor*> *floors)
{
    map<int, Floor*>::iterator floorIt;
    if (y > 3)
    {
        y--;
    }
    floorIt = floors->find(y); 
    if(floorIt != floors->end())
    {
        Stop();
        std::next(floorIt);
        addch(floorIt->second->GetHeight());
    }
}

void Elevator::GoDown(map<int, Floor*> *floors)
{
    if (y < LINES)
    {
        y++;
    }
}

void Elevator::Readjusting()
{
    //TODO, change readjustingHeight
    int readjustingHeight = 2;
    if (y < readjustingHeight)
    {
        y++;
        if (y == readjustingHeight)
        {
            state = ELEVATOR_STATE_GOING_UP;
        }
    }
    else if (y > readjustingHeight)
    {
        y--;
        if (y == readjustingHeight)
        {
            state = ELEVATOR_STATE_GOING_DOWN;
        }
    }
}

void Elevator::Stopped()
{
    ++ticksWaited;
    ticksWaited = ticksWaited + 1;
    move(0, 0);
    if (ticksWaited > TICKS_TO_STOP)
    {
        state = previous_state;
    }
}

void Elevator::Idle()
{
}

void Elevator::Stop()
{
    ticksWaited = 0;
    previous_state = state;
    state = ELEVATOR_STATE_STOPPED;
}

// RENDER
void Elevator::Render()
{
    EraseElevatorRenderLag(y + 1);
    EraseElevatorRenderLag(y - ELEVATOR_HEIGHT);
    mvwin(win, y - ELEVATOR_HEIGHT + 1, 0);
    wrefresh(win);
}

void Elevator::InitRender()
{
    x = ELEVATOR_STATE_GOING_DOWN;
    y = LINES;
    win = newwin(ELEVATOR_HEIGHT, ELEVATOR_WIDTH, y - ELEVATOR_HEIGHT + 1, x);
    leaveok(win, true);
    box(win, 0, 0);
    wrefresh(win);
    refresh();
}

void Elevator::EraseElevatorRenderLag(int height)
{
    move(height, 0);
    for (int i = 0; i < ELEVATOR_WIDTH; ++i)
    {
        addch(' ');
    }
    move(height, 0);
}

map<int, Floor*> * Elevator::GetRequestFloors()
{
    return requestedFloors;
}