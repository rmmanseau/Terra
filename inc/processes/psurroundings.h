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
        bool invalid;
        std::weak_ptr<CPosition> position;
        std::weak_ptr<CSurroundings> surroundings;

        Node(std::weak_ptr<CPosition> position,
             std::weak_ptr<CSurroundings> surroundings);
    };

    std::vector<Node> nodes;
    Grid& rGrid;

    std::vector<Vec2> dirVec2s;

    void removeInvalidNodes();

public:
    PSurroundings(Grid& grid);

    virtual void registerEntity(Entity& entity);
    virtual void update();
};

#endif // PSURROUNDINGS_H
