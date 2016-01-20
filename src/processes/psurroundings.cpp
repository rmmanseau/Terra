#include "psurroundings.h"

PSurroundings::PSurroundings(Grid& grid)
    : rGrid(grid)
{
    dirVec2s.push_back(Vec2i( 0, -1)); // N
    dirVec2s.push_back(Vec2i( 1, -1)); // NE
    dirVec2s.push_back(Vec2i( 1,  0)); // E
    dirVec2s.push_back(Vec2i( 1,  1)); // SE
    dirVec2s.push_back(Vec2i( 0,  1)); // S
    dirVec2s.push_back(Vec2i(-1,  1)); // SW
    dirVec2s.push_back(Vec2i(-1,  0)); // W
    dirVec2s.push_back(Vec2i(-1, -1)); // NW
}

void PSurroundings::registerEntity(Entity& entity)
{
    Node node;
    node.id = entity.getId();

    if (
        (node.position = entity.getComponent<CPosition>()) &&
        (node.surroundings = entity.getComponent<CSurroundings>())
       )
    {
        nodes.push_back(node);
    }
}

void PSurroundings::unregisterEntity(EntityId id)
{
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
                               [&id](Node& node){ return node.id == id; }),
                nodes.end());
}

void PSurroundings::update()
{
    for (auto node = nodes.begin();
         node != nodes.end(); ++node)
    {   
        for (int i = 0; i < 8; ++i)
        {
            Vec2i surroundingPos = node->position->pos.floor() + dirVec2s[i];
            EntityId id = rGrid.getIdAt(surroundingPos);
            EntityType type = rGrid.getTypeAt(surroundingPos);
            node->surroundings->setInfo(i, id, type);
        }
    }
}
