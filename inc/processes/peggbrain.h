#ifndef PEGGBRAIN_H
#define PEGGBRAIN_H

#include "common.h"
#include "process.h"

#include "entity.h"
#include "ceggbrain.h"
#include "calive.h"
#include "cposition.h"
#include "cspawn.h"

class PEggBrain : public Process
{
    struct Node
    {
        EntityId id;

        std::shared_ptr<CEggBrain> eggBrain;
        std::shared_ptr<CAlive> alive;
        std::shared_ptr<CPosition> position;
        std::shared_ptr<CSpawn> spawn;
    };

    std::vector<Node> nodes;

public:
    PEggBrain();

    virtual void registerEntity(Entity& entity);
    virtual void unregisterEntity(EntityId id);
    virtual void update(int timeStep);
};

#endif // PEGGBRAIN_H
