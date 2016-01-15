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
        bool invalid;
        EntityId id;
        std::weak_ptr<CAlive> alive;

        Node(EntityId id, std::weak_ptr<CAlive> alive);
    };

    std::vector<Node> nodes;
    Factory& rFactory;

    void removeInvalidNodes();

public:
    PAlive(Factory& factory);

    virtual void registerEntity(Entity& entity);
    virtual void update();
};

#endif // PALIVE_H
