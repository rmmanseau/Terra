#include "ptranslate.h"

PTranslate::PTranslate(Grid& grid)
    : rGrid(grid)
{}

void PTranslate::registerEntity(Entity& entity)
{
    Node node;
    node.id = entity.getId();

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

void PTranslate::update()
{
    for (auto node = nodes.begin();
        node != nodes.end(); ++node)
    {        
        Vec2 newPos = node->position->getPos() + node->translate->getDisplacement();

        if (node->position->getPos().floor() == newPos.floor())
        {
            node->position->setPos(newPos);
        }
        else if (rGrid.empty(newPos.floor()) && rGrid.inside(newPos.floor()))
        {
            rGrid.erase(node->position->getPos().floor());
            rGrid.setInfoAt(newPos.floor(), node->id, node->type);
            node->position->setPos(newPos);
        }
    }
}
