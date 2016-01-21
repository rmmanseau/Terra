#ifndef PALIVE_H
#define PALIVE_H

#include "common.h"
#include "process.h"
#include "factory.h"

#include "entity.h"
#include "calive.h"

class PAlive : public Process
{
    struct Node
    {
        EntityId id;

        std::shared_ptr<CAlive> alive;
    };

    std::vector<Node> nodes;
    Factory& rFactory;

public:
    PAlive(Factory& factory);

    virtual void registerEntity(Entity& entity);
    virtual void unregisterEntity(EntityId id);
    virtual void update(int timeStep);
};

#endif // PALIVE_H
