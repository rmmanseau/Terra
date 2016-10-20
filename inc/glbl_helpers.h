#ifndef GLBL_HELPERS_H
#define GLBL_HELPERS_H

#include <cstdlib>
#include "common.h"
#include "vec2.h"

class Helpers
{
    std::map<Dir, Vec2i> directionToVectorMap;

public:
    Helpers() {}
    void init();

    Vec2i dirToVec(Dir dir);

    //==============================
    //start of template member funcs
    //==============================

    template <typename T>
    void getInput(T& input)
    {
        for (;;)
        {
            std::cout << "> ";
            std::cin >> input;
            std::cout << std::endl;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Bad Input, try again." << std::endl;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return;
            }
        }
    }

    template <typename T>
    T clamp(T x, T lower, T upper)
    {
        x = (x > upper) ? upper : x;
        x = (x < lower) ? lower : x;
        return x;
    }

    template <typename T>
    bool doesVecContain(std::vector<T> vec, T x)
    {
        for (int i = 0; i < vec.size(); ++i)
        {
            if (vec[i] == x)
                return true;
        }
        return false;
    }

    template <typename T>
    bool doesVecContain(std::vector<T> vec, std::vector<T> x)
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
    int vecContains(std::vector<T> vec, T x)
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
    int vecContains(std::vector<T> vec, std::vector<T> x)
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
    int indexContaining(std::vector<T> vec, T x)
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
    int indexContaining(std::vector<T> vec, std::vector<T> x)
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

    //============================
    //end of template member funcs
    //============================
};


namespace glbl
{
    extern Helpers helpers;
}

#endif // GLBL_HELPERS_H
