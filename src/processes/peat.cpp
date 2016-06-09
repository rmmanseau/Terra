#include "peat.h"

PEat::PEat(EntityMap& entities)
    : rEntities(entities)
{}

void PEat::registerEntity(Entity& entity)
{
    Node node;
    node.id = entity.getId();

    if (
        (node.eat = entity.getComponent<CEat>()) &&
        (node.alive = entity.getComponent<CAlive>()) &&
        (node.surroundings = entity.getComponent<CSurroundings>())
       )
    {
        nodes.push_back(node);
    }
}

void PEat::unregisterEntity(EntityId id)
{
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
                               [&id](Node& node){ return node.id == id; }),
                nodes.end());
}

void PEat::update(int timeStep)
{
    sf::Clock timer;
    for (auto node = nodes.begin();
         node != nodes.end(); ++node)
    {        
        if (node->eat->active)
        {
            EntityType type = node->surroundings->typeAt(node->eat->dir);
            EntityId id = node->surroundings->idAt(node->eat->dir);

            std::shared_ptr<CAlive> prey = rEntities.at(id).getComponent<CAlive>();
            prey->kill();

            node->alive->updateEnergy(node->eat->energyFromFood.at(type));
        }
        node->eat->active = false;
    }
    std::cout << "PEat:\t\t" << timer.restart().asMicroseconds() << std::endl;
 }
