#ifndef ACTOR_H
#define ACTOR_H

#include "common.h"
#include "component.h"
#include <unordered_map>
#include <string>

class Actor
{
    ActorId id;
    ComponentMap components;

public:
    Actor(ActorId _id);

    ActorId getId();

    void addComponent(std::shared_ptr<Component> component);

    template <typename T>
    std::weak_ptr<T> getComponent()
    {
        std::type_index index(typeid(T));
        if (components.count(std::type_index(typeid(T))) != 0)
        {
            std::weak_ptr<T> weak = std::static_pointer_cast<T>(components[index]);
            return weak;
        }
        else
        {
            return std::weak_ptr<T>();
        }
    }
};

#endif // ACTOR_H
