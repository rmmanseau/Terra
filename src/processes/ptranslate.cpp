#include "ptranslate.h"

const std::map<Dir, Vec2f> PTranslate::dirMap = {
    {Dir::n,  Vec2f(0,     -1)},
    {Dir::ne, Vec2f(.707,  -.707)},
    {Dir::e,  Vec2f(1,      0)},
    {Dir::se, Vec2f(.707,   .707)},
    {Dir::s,  Vec2f(0,      1)},
    {Dir::sw, Vec2f(-.707,  .707)},
    {Dir::w,  Vec2f(-1,     0)},
    {Dir::nw, Vec2f(-.707, -.707)}
};

PTranslate::PTranslate(Grid& grid)
    : rGrid(grid)
{}

void PTranslate::registerEntity(Entity& entity)
{
    Node node;
    node.id = entity.getId();
    node.type = entity.getType();

    if (
        (node.position = entity.getComponent<CPosition>()) &&
        (node.translate = entity.getComponent<CTranslate>())
       )
    {
        nodes.push_back(node);
    }
}

void PTranslate::unregisterEntity(EntityId id)
{
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
                               [&id](Node& node){ return node.id == id; }),
                nodes.end());
}

void PTranslate::update(int timeStep)
{    
    sf::Clock timer;

    for (auto node = nodes.begin();
        node != nodes.end(); ++node)
    {        
        Vec2f displacement = dirMap.at(node->translate->direction)
                              * node->translate->velocity;

        Vec2f newPos = node->position->pos + displacement;
        
        node->translate->velocity = 0;

        if (node->position->pos.floor() == newPos.floor())
        {
            node->position->pos = newPos;
        }
        else if (rGrid.empty(newPos.floor()) && rGrid.inside(newPos.floor()))
        {
            rGrid.erase(node->position->pos.floor());
            rGrid.setInfoAt(newPos.floor(), node->id, node->type);
            node->position->pos = newPos;
        }
    }
    std::cout << "PTranslate:\t" << timer.restart().asMicroseconds() << std::endl;
}
