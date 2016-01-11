#include "pmovement.h"

PMovement::PMovement()
{}

PMovement::Node::Node(EntityId id, std::weak_ptr<CTranslate> translate,
                      std::weak_ptr<CMovement> movement)
    : id(id)
    , invalid(false)
    , translate(translate)
    , movement(movement)
{}

void PMovement::removeInvalidNodes()
{
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
                               [](Node& node) { return node.invalid; }),
                nodes.end());
}

void PMovement::registerEntity(Entity& entity)
{
    std::weak_ptr<CTranslate> translate = entity.getComponent<CTranslate>();
    std::weak_ptr<CMovement> movement = entity.getComponent<CMovement>();

    if (translate.lock() && movement.lock())
        nodes.push_back(Node(entity.getId(), translate, movement));
}

void PMovement::update()
{
    for (auto itr = nodes.begin();
        itr != nodes.end(); ++itr)
    {        
        std::shared_ptr<CTranslate> translate = itr->translate.lock();
        std::shared_ptr<CMovement> movement = itr->movement.lock();

        if (translate && movement)
        {
            translate->setDirection(movement->getUpdatedDirection());
            translate->setVelocity(movement->getUpdatedVelocity());
        }
        else
        {
            itr->invalid = true;
        }
    }
    removeInvalidNodes();
}
