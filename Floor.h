#ifndef FLOOR_H
#define FLOOR_H
#include "vector"

using namespace std;

class Passenger;

class Floor
{
public:
    Floor(int height);
    void Update();
    void Render();
    void AddPassenger(Passenger *passenger);

    // DEBUG
    int GetHeight();

private:
    int height;
    vector<Passenger*> *passengers;
};

#endif