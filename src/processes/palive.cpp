#include "palive.h"

PAlive::PAlive(Factory& factory)
    : rFactory(factory)
{}


void PAlive::registerEntity(Entity& entity)
{
    Node node;
    node.id = entity.getId();

    if (
        (node.alive = entity.getComponent<CAlive>())
       )
    {
        nodes.push_back(node);
    }
}

void PAlive::unregisterEntity(EntityId id)
{
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
                               [&id](Node& node){ return node.id == id; }),
                nodes.end());
}

void PAlive::update()
{
    for (auto node = nodes.begin();
         node != nodes.end(); ++node)
    {        
        if (node->alive->getHealth() == 0)
        {
            rFactory.disassembleEntity(node->id);
        }

        if (node->alive->getEnergy() == 0)
            node->alive->updateHealth(-1);
    }
}
