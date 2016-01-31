#include "pplantbrain.h"

#include "helpers.h"

PPlantBrain::PPlantBrain()
{}

void PPlantBrain::registerEntity(Entity& entity)
{
    Node node;
    node.id = entity.getId();

    if (
        (node.plantBrain = entity.getComponent<CPlantBrain>()) &&
        (node.position = entity.getComponent<CPosition>()) &&
        (node.alive = entity.getComponent<CAlive>()) &&
        (node.surroundings = entity.getComponent<CSurroundings>()) &&
        (node.spawn = entity.getComponent<CSpawn>())
       )
    {
        nodes.push_back(node);
    }
}

void PPlantBrain::unregisterEntity(EntityId id)
{
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
                               [&id](Node& node){ return node.id == id; }),
                nodes.end());
}

void PPlantBrain::update(int timeStep)
{
    sf::Clock timer;
    for (auto node = nodes.begin();
         node != nodes.end(); ++node)
    {        
        int surroundingEntities = node->surroundings->numberFull();
        if (surroundingEntities != 7 && surroundingEntities != 6)
        {
            if (node->alive->energy >= node->spawn->energyRequired && surroundingEntities <= 4)
            {
                node->spawn->active = true;
                node->spawn->pos = randomAdjacentTile(node->position->pos.floor());
            }

            if      (surroundingEntities <= 0)
                node->alive->updateEnergy(3);
            else if (surroundingEntities <= 3)
                node->alive->updateEnergy(2);
            else if (surroundingEntities <= 5)
                node->alive->updateEnergy(1);
            else if (surroundingEntities <= 7)
                node->alive->updateEnergy(0);
            else if (surroundingEntities <= 8)
                node->alive->updateEnergy(-2);   
        }
    }
    std::cout << "PPlantBrain: " << timer.restart().asMicroseconds() << std::endl;
}
