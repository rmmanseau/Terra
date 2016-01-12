#ifndef GRID_H
#define GRID_H

#include "common.h"
#include "vec2.h"
#include <vector>

class Grid 
{
    struct GridInfo
    {
        EntityId id;
        EntityType type;

        GridInfo();
    };

    std::vector<GridInfo> g;
    int width;
    int height;

    Grid() {}
    GridInfo& at(Vec2 v);

public:
    Grid(int w, int h);

    EntityId getIdAt(Vec2 v);
    EntityType getTypeAt(Vec2 v);
    void setInfoAt(Vec2 v, EntityId id, EntityType type);
    void erase(Vec2 v);
    bool inside(Vec2 v);
    bool empty(Vec2 v);
};

#endif // GRID_H
