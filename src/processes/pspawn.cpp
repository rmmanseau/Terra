#include "pspawn.h"

PSpawn::PSpawn(Grid& grid, Factory& factory)
    : rFactory(factory)
    , rGrid(grid)
{}

void PSpawn::registerEntity(Entity& entity)
{
    Node node;
    node.id = entity.getId();

    if (
        (node.spawn = entity.getComponent<CSpawn>())
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

void PSpawn::update()
{
    for (auto node = nodes.begin();
         node != nodes.end(); ++node)
    {        
        if (node->spawn->active && rGrid.empty(node->spawn->pos))
        {
            rFactory.assembleEntity(node->spawn->type, node->spawn->pos);
        }
        node->spawn->active = false;
    }
}
