#ifndef FLOOR_H
#define FLOOR_H

class Floor
{
    public: 
    Floor(int height);

    private:
    bool upButtonPresed;
    bool downButtonPresed;
    int height;

    void InitRender();
};

#endif