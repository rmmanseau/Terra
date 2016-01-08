#include "entity.h"

Entity::Entity(EntityId _id)
    : id(_id) {}

EntityId Entity::getId()
{
    return id;
}

void Entity::addComponent(std::shared_ptr<Component> component)
{
    if (component != nullptr)
    {
        components.insert(std::make_pair(std::type_index(typeid(*component)),
                                         component));
    }
}
