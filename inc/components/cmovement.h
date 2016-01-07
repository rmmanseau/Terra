#ifndef CMOVEMENT_H
#define CMOVEMENT_H

#include "common.h"
#include "component.h"

#include <cstdlib>

class CMovement : public Component
{

public:
    Vec2 getDisplacement()
    {
        Vec2 displacement;

        switch (rand() % 4)
        {
            case 0:
                displacement = Vec2(1, 0);
                break;
            case 1:
                displacement = Vec2(0, 1);
                break;
            case 2:
                displacement = Vec2(-1, 0);
                break;
            case 3:
                displacement = Vec2(0, -1);
                break; 
        }
        return displacement;
    }
};

#endif // CMOVEMENT_H