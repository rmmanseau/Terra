#ifndef PTRANSLATE_H
#define PTRANSLATE_H

#include "common.h"
#include "process.h"
#include "grid.h"

#include "entity.h"
#include "cposition.h"
#include "ctranslate.h"

class PTranslate : public Process
{
    struct Node
    {
        EntityId id;
        bool invalid;
        std::weak_ptr<CPosition> position;
        std::weak_ptr<CTranslate> translate;

        Node(EntityId id, std::weak_ptr<CPosition> position,
             std::weak_ptr<CTranslate> translate);
    };

    std::vector<Node> nodes;
    Grid& rGrid;

    void removeInvalidNodes();

public:
    PTranslate(Grid& grid);

    virtual void registerEntity(Entity& entity);
    virtual void update();
};

#endif // PTRANSLATE_H
