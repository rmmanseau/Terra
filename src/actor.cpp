#include "actor.h"

Actor::Actor(ActorId _id)
    : id(_id) {}

ActorId Actor::getId()
{
    return id;
}

void Actor::addComponent(std::shared_ptr<Component> component)
{
    if (component != nullptr)
    {
        components.insert(std::make_pair(std::type_index(typeid(*component)),
                                         component));
    }
}
