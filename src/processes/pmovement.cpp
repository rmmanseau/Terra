#include "pmovement.h"

PMovement::PMovement()
{}

void PMovement::registerEntity(Entity& entity)
{
    Node node;
    node.id = entity.getId();

    if (
        (node.translate = entity.getComponent<CTranslate>()) &&
        (node.movement = entity.getComponent<CMovement>())
       )
    {
        nodes.push_back(node);
    }
}

void PMovement::unregisterEntity(EntityId id)
{
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
                               [&id](Node& node){ return node.id == id; }),
                nodes.end());
}

void PMovement::update(int timeStep)
{
    sf::Clock timer;
    for (auto node = nodes.begin();
        node != nodes.end(); ++node)
    {
        if (node->movement->active)
        {
            node->translate->direction = node->movement->getUpdatedDirection();
            node->translate->velocity = node->movement->getUpdatedVelocity();
        }
        node->movement->active = false;
    }
    std::cout << "PMovement:\t" << timer.restart().asMicroseconds() << std::endl;
}
