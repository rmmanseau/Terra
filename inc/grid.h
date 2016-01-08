#ifndef GRID_H
#define GRID_H

#include "common.h"
#include "vec2.h"
#include <vector>

class Grid 
{
    std::vector<EntityId> g;
    int width;
    int height;

    Grid() {}
    EntityId at(Vec2 v);

public:
    Grid(int w, int h);

    EntityId getIdAt(Vec2 v);
    void setIdAt(Vec2 v, int id);
    void erase(Vec2 v);
    bool inside(Vec2 v);
    bool empty(Vec2 v);
};

#endif // GRID_H
