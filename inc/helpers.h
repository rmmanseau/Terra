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

template <typename T>
bool vectorContains(std::vector<T> vec, T x)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == x)
            return true;
    }
    return false;
}

template <typename T>
bool vectorContains(std::vector<T> vec, std::vector<T> x)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        for (int j = 0; j < x.size(); ++j)
        {
            if (vec[i] == x[j])
                return true;
        }
    }
    return false;
}

template <typename T>
int vectorContainsCount(std::vector<T> vec, T x)
{
    int count = 0;
    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == x)
            ++count;
    }
    return count;
}

template <typename T>
int vectorContainsCount(std::vector<T> vec, std::vector<T> x)
{
    int count = 0;
    for (int i = 0; i < vec.size(); ++i)
    {
        for (int j = 0; j < x.size(); ++j)
        {
            if (vec[i] == x[j])
            {
                ++count;
                break;
            }
        }
    }
    return count;
}

template <typename T>
int vectorIndexContaining(std::vector<T> vec, T x)
{
    std::vector<int> indices;
    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == x)
            indices.push_back(i);
    }
    return indices.at(rand() % indices.size());
}

template <typename T>
int vectorIndexContaining(std::vector<T> vec, std::vector<T> x)
{
    std::vector<int> indices;
    for (int i = 0; i < vec.size(); ++i)
    {
        for (int j = 0; j < x.size(); ++j)
        {
            if (vec[i] == x[j])
            {
                indices.push_back(i);
                break;
            }
        }
    }
    return indices.at(rand() % indices.size());
}

inline Vec2i randomAdjacentTile(Vec2i tile)
{
    Vec2i random(rand()%3 - 1, rand()%3 - 1);
    return tile + random;
}

#endif // HELPERS_H

