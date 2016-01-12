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
        bool invalid;
        std::weak_ptr<CTranslate> translate;
        std::weak_ptr<CMovement> movement;

        Node(std::weak_ptr<CTranslate> translate,
             std::weak_ptr<CMovement> movement);
    };

    std::vector<Node> nodes;

    void removeInvalidNodes();

public:
    PMovement();

    virtual void registerEntity(Entity& entity);
    virtual void update();
};

#endif // PMOVEMENT_H
