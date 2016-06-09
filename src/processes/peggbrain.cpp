#include "peggbrain.h"

PEggBrain::PEggBrain()
{}

void PEggBrain::registerEntity(Entity& entity)
{
    Node node;
    node.id = entity.getId();

    if (
        (node.eggBrain = entity.getComponent<CEggBrain>()) &&
        (node.alive = entity.getComponent<CAlive>()) &&
        (node.position = entity.getComponent<CPosition>()) &&
        (node.spawn = entity.getComponent<CSpawn>())
       )
    {
        nodes.push_back(node);
    }
}

void PEggBrain::unregisterEntity(EntityId id)
{
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
                               [&id](Node& node){ return node.id == id; }),
                nodes.end());
}

void PEggBrain::update(int timeStep)
{
    sf::Clock timer;
    for (auto node = nodes.begin();
         node != nodes.end(); ++node)
    {
        if (node->alive->energy >= node->spawn->energyRequired)
        {
            node->spawn->active = true;
            node->spawn->pos = node->position->pos;
        }

        node->alive->updateEnergy(1);
    }
    std::cout << "PEggBrain:\t" << timer.restart().asMicroseconds() << std::endl;
}
