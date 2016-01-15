#include "pspawn.h"

PSpawn::PSpawn(Grid& grid, Factory& factory)
    : rFactory(factory)
    , rGrid(grid)
{}

PSpawn::Node::Node(std::weak_ptr<CSpawn> spawn)
    : invalid(false)
    , spawn(spawn)
{}

void PSpawn::removeInvalidNodes()
{
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
                               [](Node& node) { return node.invalid; }),
                nodes.end());
}

void PSpawn::registerEntity(Entity& entity)
{
    std::weak_ptr<CSpawn> spawn = entity.getComponent<CSpawn>();

    if (spawn.lock())
        nodes.push_back(Node(spawn));
}

void PSpawn::update()
{
    for (auto itr = nodes.begin();
         itr != nodes.end(); ++itr)
    {        
        std::shared_ptr<CSpawn> spawn = itr->spawn.lock();

        if (spawn)
        {
            if (spawn->active && rGrid.empty(spawn->pos))
            {
                rFactory.assembleEntity(spawn->type, spawn->pos);
            }
            spawn->active = false;
        }
        else
        {
            itr->invalid = true;
        }
    }
    removeInvalidNodes();
}
