#include "pdumbbrain.h"

#include "helpers.h"
#include "globals.h"

PDumbBrain::PDumbBrain()
{}

void PDumbBrain::registerEntity(Entity& entity)
{
    Node node;
    node.id = entity.getId();

    if (
        (node.dumbBrain = entity.getComponent<CDumbBrain>()) &&
        (node.position = entity.getComponent<CPosition>()) &&
        (node.surroundings = entity.getComponent<CSurroundings>()) &&
        (node.alive = entity.getComponent<CAlive>()) &&
        (node.spawn = entity.getComponent<CSpawn>()) &&
        (node.eat = entity.getComponent<CEat>()) &&
        (node.movement = entity.getComponent<CMovement>())
       )
    {
        nodes.push_back(node);
    }
}

void PDumbBrain::unregisterEntity(EntityId id)
{
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
                               [&id](Node& node){ return node.id == id; }),
                nodes.end());
}

void PDumbBrain::update(int timeStep)
{
    sf::Clock timer;

    for (auto node = nodes.begin();
         node != nodes.end(); ++node)
    {        
        if (node->alive->energy >= node->spawn->energyRequired)
        {
            node->spawn->active = true;
            node->spawn->pos = randomAdjacentTile(node->position->pos.floor());
        }
        else if (node->alive->energy < node->alive->energyMax &&
                 node->surroundings->numberOf(node->eat->food) > 0)
        {
            node->eat->active = true;
            node->eat->dir = node->surroundings->directionTowards(node->eat->food);
        }
        else
        {
            node->movement->active = true;
        }

        node->alive->updateEnergy(-1);
    }
    std::cout << "PDumbBrain:\t" << timer.restart().asMicroseconds() << std::endl;
}
