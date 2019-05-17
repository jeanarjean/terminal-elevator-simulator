#ifndef FLOOR_H
#define FLOOR_H

class Floor
{
public:
    Floor(int height);
    void Update();
    void Render();

private:
    int height;
};

#endif