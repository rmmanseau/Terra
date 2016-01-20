#ifndef HELPERS_H
#define HELPERS_H

#include "vec2.h"
#include "common.h"

#include <cstdlib>

template <typename T>
T clamp(T x, T lower, T upper)
{
    x = (x > upper) ? upper : x;
    x = (x < lower) ? lower : x;
    return x;
}

inline Vec2i randomAdjacentTile(Vec2i tile)
{
    Vec2i random(rand()%3 - 1, rand()%3 - 1);
    return tile + random;
}

#endif // HELPERS_H

