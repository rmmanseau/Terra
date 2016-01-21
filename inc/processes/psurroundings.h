#ifndef PSURROUNDINGS_H
#define PSURROUNDINGS_H

#include "common.h"
#include "process.h"
#include "grid.h"

#include "entity.h"
#include "cposition.h"
#include "csurroundings.h"

class PSurroundings : public Process
{
    struct Node
    {
        EntityId id;

        std::shared_ptr<CPosition> position;
        std::shared_ptr<CSurroundings> surroundings;
    };

    std::vector<Node> nodes;
    Grid& rGrid;

    std::vector<Vec2i> dirVec2s;

public:
    PSurroundings(Grid& grid);

    virtual void registerEntity(Entity& entity);
    virtual void unregisterEntity(EntityId id);
    virtual void update(int timeStep);
};

#endif // PSURROUNDINGS_H
