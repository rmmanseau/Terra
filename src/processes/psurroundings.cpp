#include "psurroundings.h"

PSurroundings::PSurroundings(Grid& grid)
    : rGrid(grid)
{
    dirVec2s.push_back(Vec2( 0, -1)); // N
    dirVec2s.push_back(Vec2( 1, -1)); // NE
    dirVec2s.push_back(Vec2( 1,  0)); // E
    dirVec2s.push_back(Vec2( 1,  1)); // SE
    dirVec2s.push_back(Vec2( 0,  1)); // S
    dirVec2s.push_back(Vec2(-1,  1)); // SW
    dirVec2s.push_back(Vec2(-1,  0)); // W
    dirVec2s.push_back(Vec2(-1, -1)); // NW
}

PSurroundings::Node::Node(std::weak_ptr<CPosition> position,
                          std::weak_ptr<CSurroundings> surroundings)
    : invalid(false)
    , position(position)
    , surroundings(surroundings)
{}

void PSurroundings::removeInvalidNodes()
{
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
                               [](Node& node) { return node.invalid; }),
                nodes.end());
}

void PSurroundings::registerEntity(Entity& entity)
{
    std::weak_ptr<CPosition> position = entity.getComponent<CPosition>();
    std::weak_ptr<CSurroundings> surroundings = entity.getComponent<CSurroundings>();

    if (position.lock() && surroundings.lock())
        nodes.push_back(Node(position, surroundings));
}

void PSurroundings::update()
{
    for (auto itr = nodes.begin();
         itr != nodes.end(); ++itr)
    {
        std::shared_ptr<CPosition> position = itr->position.lock();
        std::shared_ptr<CSurroundings> surroundings = itr->surroundings.lock();
        
        if (position && surroundings)
        {
            for (int i = 0; i < 8; ++i)
            {

                Vec2 surroundingPos = position->getPos().floor() + dirVec2s[i];
                EntityId id = rGrid.getIdAt(surroundingPos);
                EntityType type = rGrid.getTypeAt(surroundingPos);
                surroundings->setInfo(i, id, type);
            }
        }
        else
        {
            itr->invalid = true;
        }
    }
    removeInvalidNodes();
}
