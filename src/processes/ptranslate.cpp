#include "ptranslate.h"

PTranslate::PTranslate(Grid& grid)
    : rGrid(grid)
{}

PTranslate::Node::Node(EntityId id, EntityType type, std::weak_ptr<CPosition> position,
                                                     std::weak_ptr<CTranslate> translate)
    : id(id)
    , type(type)
    , invalid(false)
    , position(position)
    , translate(translate)
{}

void PTranslate::removeInvalidNodes()
{
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
                               [](Node& node) { return node.invalid; }),
                nodes.end());
}

void PTranslate::registerEntity(Entity& entity)
{
    std::weak_ptr<CPosition> position = entity.getComponent<CPosition>();
    std::weak_ptr<CTranslate> translate = entity.getComponent<CTranslate>();

    if (position.lock() && translate.lock())
        nodes.push_back(Node(entity.getId(), entity.getType(), 
                             position, translate));
}

void PTranslate::update()
{
    for (auto itr = nodes.begin();
        itr != nodes.end(); ++itr)
    {        
        std::shared_ptr<CPosition> position = itr->position.lock();
        std::shared_ptr<CTranslate> translate = itr->translate.lock();

        if (translate && position)
        {
            Vec2 newPos = position->getPos() + translate->getDisplacement();

            if (position->getPos().floor() == newPos.floor())
            {
                position->setPos(newPos);
            }
            else if (rGrid.empty(newPos.floor()) && rGrid.inside(newPos.floor()))
            {
                rGrid.erase(position->getPos().floor());
                rGrid.setInfoAt(newPos.floor(), itr->id, itr->type);
                position->setPos(newPos);
            }
        }
        else
        {
            itr->invalid = true;
        }
    }
    removeInvalidNodes();
}
