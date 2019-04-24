#include "Mediator.h"
#include "Elevator.h"
#include "Floor.h"
#include <iostream>
#include "Constants.h"
#include <time.h>

Mediator::Mediator()
{
    elevator = new Elevator();
    floors = new std::vector<Floor>;
    for (int i = LINES - 1; i > ELEVATOR_HEIGHT; i = i - FLOOR_HEIGHT)
    {
        Floor floor(i);
        // floor.PressDownButton();
        floor.PressUpButton();
        floors->insert(floors->end(), floor);
    }
}

Mediator::~Mediator()
{
    delete elevator;
}

void Mediator::Start()
{
    int milisec = 200; // length of time to sleep, in miliseconds
    struct timespec req = {0};
    req.tv_sec = 0;
    req.tv_nsec = milisec * 1000000L;
    while (1)
    {
        nanosleep(&req, (struct timespec *)NULL);
        elevator->Tick();

        std::vector<Floor>::iterator ptr;
        for (ptr = floors->begin(); ptr < floors->end(); ptr++)
        {
            ptr->Tick();
            if (!elevator->IsStopped())
            {
                if (ptr->UpButtonPressed() && elevator->GetDirection() == DIRECTION_UP && ptr->GetHeight() == elevator->GetHeight())
                {
                    move(elevator->GetHeight(), ELEVATOR_HEIGHT);
                    printw("sup");
                    ptr->ResetUpButton();
                    elevator->Stop();
                }
                if (ptr->DownButtonPressed() && elevator->GetDirection() == DIRECTION_DOWN && ptr->GetHeight() == elevator->GetHeight())
                {
                    move(elevator->GetHeight(), ELEVATOR_HEIGHT);
                    printw("sup");
                    ptr->ResetDownButton();
                    elevator->Stop();
                }
            }
        }
        refresh();
    }
}