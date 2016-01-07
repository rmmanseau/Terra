#ifndef GRID_H
#define GRID_H

#include "common.h"
#include "vec2.h"
#include <vector>

class Grid 
{
    std::vector<ActorId> g;
    int width;
    int height;

    ActorId at(Vec2 v);

public:
    Grid();
    Grid(int w, int h);

    ActorId getIdAt(Vec2 v);
    void setIdAt(Vec2 v, int id);
    void erase(Vec2 v);
    bool inside(Vec2 v);
    bool empty(Vec2 v);
};

#endif // GRID_H
