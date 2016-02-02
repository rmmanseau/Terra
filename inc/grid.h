#ifndef GRID_H
#define GRID_H

#include "common.h"
#include "globals.h"
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

    GridInfo& at(Vec2i v);

public:
    Grid();
    void init(int w, int h);

    EntityId getIdAt(Vec2i v);
    EntityType getTypeAt(Vec2i v);
    void setInfoAt(Vec2i v, EntityId id, EntityType type);
    bool inside(Vec2i v);
    void erase(Vec2i v);
    bool empty(Vec2i v);
};

#endif // GRID_H
