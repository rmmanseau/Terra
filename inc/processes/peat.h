#ifndef PEAT_H
#define PEAT_H

#include "common.h"
#include "process.h"

#include "entity.h"
#include "ceat.h"
#include "calive.h"
#include "csurroundings.h"
// Component Includes

class PEat : public Process
{
    struct Node
    {
        EntityId id;

        std::shared_ptr<CEat> eat;
        std::shared_ptr<CAlive> alive;
        std::shared_ptr<CSurroundings> surroundings;
    };

    std::vector<Node> nodes;
    EntityMap& rEntities;

public:
    PEat(EntityMap& entities);

    virtual void registerEntity(Entity& entity);
    virtual void unregisterEntity(EntityId id);
    virtual void update();
};

#endif // PEAT_H
