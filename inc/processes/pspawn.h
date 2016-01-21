#ifndef PSPAWN_H
#define PSPAWN_H

#include "common.h"
#include "process.h"
#include "factory.h"
#include "grid.h"

#include "entity.h"
#include "cspawn.h"
#include "calive.h"

class PSpawn : public Process
{
    struct Node
    {
        EntityId id;

        std::shared_ptr<CSpawn> spawn;
        std::shared_ptr<CAlive> alive;
    };

    std::vector<Node> nodes;
    Factory& rFactory;
    Grid& rGrid;
    EntityMap& rEntities;

public:
    PSpawn(Grid& grid, Factory& factory, EntityMap& entities);

    virtual void registerEntity(Entity& entity);
    virtual void unregisterEntity(EntityId id);
    virtual void update(int timeStep);
};

#endif // PSPAWN_H
