#ifndef PPLANTBRAIN_H
#define PPLANTBRAIN_H

#include "common.h"
#include "process.h"

#include "entity.h"
#include "cplantbrain.h"
#include "cposition.h"
#include "calive.h"
#include "csurroundings.h"
#include "cspawn.h"

class PPlantBrain : public Process
{
    struct Node
    {
        EntityId id;

        std::shared_ptr<CPlantBrain> plantBrain;
        std::shared_ptr<CPosition> position;
        std::shared_ptr<CAlive> alive;
        std::shared_ptr<CSurroundings> surroundings;
        std::shared_ptr<CSpawn> spawn;
    };

    std::vector<Node> nodes;

public:
    PPlantBrain();

    virtual void registerEntity(Entity& entity);
    virtual void unregisterEntity(EntityId id);
    virtual void update();
};

#endif // PPLANTBRAIN_H
