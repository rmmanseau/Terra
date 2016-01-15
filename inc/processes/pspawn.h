#ifndef PSPAWN_H
#define PSPAWN_H

#include "common.h"
#include "process.h"
#include "factory.h"
#include "grid.h"

#include "entity.h"
#include "cspawn.h"

class PSpawn : public Process
{
    struct Node
    {
        bool invalid;
        std::weak_ptr<CSpawn> spawn;

        Node(std::weak_ptr<CSpawn> spawn);
    };

    std::vector<Node> nodes;
    Factory& rFactory;
    Grid& rGrid;

    void removeInvalidNodes();

public:
    PSpawn(Grid& grid, Factory& factory);

    virtual void registerEntity(Entity& entity);
    virtual void update();
};

#endif // PSPAWN_H
