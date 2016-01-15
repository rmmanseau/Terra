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
        bool invalid;
        std::weak_ptr<CPlantBrain> plantBrain;
        std::weak_ptr<CPosition> position;
        std::weak_ptr<CAlive> alive;
        std::weak_ptr<CSurroundings> surroundings;
        std::weak_ptr<CSpawn> spawn;

        Node(std::weak_ptr<CPlantBrain> plantBrain,
             std::weak_ptr<CPosition> position,
             std::weak_ptr<CAlive> alive,
             std::weak_ptr<CSurroundings> surroundings,
             std::weak_ptr<CSpawn> spawn);
    };

    std::vector<Node> nodes;

    void removeInvalidNodes();

public:
    PPlantBrain();

    virtual void registerEntity(Entity& entity);
    virtual void update();
};

#endif // PPLANTBRAIN_H
