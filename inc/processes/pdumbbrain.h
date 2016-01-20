#ifndef PDUMBBRAIN_H
#define PDUMBBRAIN_H

#include "common.h"
#include "process.h"
#include "grid.h"

#include "entity.h"
#include "cdumbbrain.h"
#include "cposition.h"
#include "csurroundings.h"
#include "calive.h"
#include "cspawn.h"
#include "ceat.h"
#include "cmovement.h"

class PDumbBrain : public Process
{
    struct Node
    {
        EntityId id;

        std::shared_ptr<CDumbBrain> dumbBrain;
        std::shared_ptr<CPosition> position;
        std::shared_ptr<CSurroundings> surroundings;
        std::shared_ptr<CAlive> alive;
        std::shared_ptr<CSpawn> spawn;
        std::shared_ptr<CEat> eat;
        std::shared_ptr<CMovement> movement;
    };

    std::vector<Node> nodes;

public:
    PDumbBrain();

    virtual void registerEntity(Entity& entity);
    virtual void unregisterEntity(EntityId id);
    virtual void update();
};

#endif // PDUMBBRAIN_H
