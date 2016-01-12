#include "entity.h"

Entity::Entity(EntityId id, EntityType type)
    : id(id), type(type) {}

EntityId Entity::getId()
{
    return id;
}
EntityType Entity::getType()
{
    return type;
}

void Entity::addComponent(std::shared_ptr<Component> component)
{
    if (component != nullptr)
    {
        components.insert(std::make_pair(std::type_index(typeid(*component)),
                                         component));
    }
}
