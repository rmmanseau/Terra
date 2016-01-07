#include "grid.h"

Grid::Grid()
    : width(1)
    , height(1)
{}

Grid::Grid(int w, int h)
    : width(w)
    , height(h)
{
    int size = width*height;
    for (int i = 0; i < size; ++i)
        g.push_back(0);
}

ActorId Grid::at(Vec2 v)
{
    return g[v.y*width + v.x];
}

bool Grid::inside(Vec2 v)
{
    return v.x >= 0 && v.y >= 0 && v.x < width && v.y < height;
}

ActorId Grid::getIdAt(Vec2 v)
{
    if (inside(v))
        return at(v);
    else
        return -1;
}

void Grid::setIdAt(Vec2 v, int id)
{
    if (inside(v))
    {
        g[v.y*width + v.x] = id;
    }
}

void Grid::erase(Vec2 v)
{
    setIdAt(v, 0);
}

bool Grid::empty(Vec2 v)
{
    return inside(v) && at(v) == 0;
}
