#include "pspawn.h"
#include "helpers.h"

PSpawn::PSpawn(Grid& grid, Factory& factory, EntityMap& entities)
    : rFactory(factory)
    , rGrid(grid)
    , rEntities(entities)
{}

void PSpawn::registerEntity(Entity& entity)
{
    Node node;
    node.id = entity.getId();

    if (
        (node.spawn = entity.getComponent<CSpawn>()) &&
        (node.alive = entity.getComponent<CAlive>())
       )
    {
        nodes.push_back(node);
    }
}

void PSpawn::unregisterEntity(EntityId id)
{
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
                               [&id](Node& node){ return node.id == id; }),
                nodes.end());
}

void PSpawn::update(int timeStep)
{
    sf::Clock timer;
    for (auto node = nodes.begin();
         node != nodes.end(); ++node)
    {        
        if (node->spawn->active &&
            vectorContains(node->spawn->canSpawnOn,
                           rGrid.getTypeAt(node->spawn->pos)))
        {
            if (rGrid.getTypeAt(node->spawn->pos) != EntityType::Empty)
            {
                EntityId id = rGrid.getIdAt(node->spawn->pos);
                rEntities.at(id).getComponent<CAlive>()->kill();
            }

            rFactory.assembleEntity(node->spawn->type, node->spawn->pos);
            node->alive->updateEnergy(-(node->spawn->energyCost));
        }
        node->spawn->active = false;
    }
    std::cout << "PSpawn: " << timer.restart().asMicroseconds() << std::endl;
}
