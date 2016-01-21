#ifndef PMOVEMENT_H
#define PMOVEMENT_H

#include "common.h"
#include "process.h"

#include "entity.h"
#include "ctranslate.h"
#include "cmovement.h"

class PMovement : public Process
{
    struct Node
    {
        EntityId id;

        std::shared_ptr<CTranslate> translate;
        std::shared_ptr<CMovement> movement;
    };

    std::vector<Node> nodes;

public:
    PMovement();

    virtual void registerEntity(Entity& entity);
    virtual void unregisterEntity(EntityId id);
    virtual void update(int timeStep);
};

#endif // PMOVEMENT_H
