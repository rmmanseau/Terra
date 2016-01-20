#ifndef FACTORY_H
#define FACTORY_H

#include "common.h"
#include "entity.h"
#include "component.h"
#include "vec2.h"

#include <map>
#include "yaml-cpp/yaml.h"

template <typename T>
std::shared_ptr<Component> createComponent()
{
    return std::make_shared<T>();
}

template <typename T>
struct ComponentRegister;

class Factory
{
    template <typename T> friend class ComponentRegister;

    typedef std::unordered_map<std::string, std::shared_ptr<Component>(*)()> FunctionMap;
    typedef std::map<EntityType, YAML::Node> YAMLNodeMap;
    
    Grid& rGrid;
    ProcessVec& rProcesses;
    EntityMap& rEntities;

    EntityId nextId;
    std::vector<EntityId> newEntities;
    std::vector<EntityId> deadEntities;

    YAMLNodeMap blueprints;    
    static FunctionMap* componentCreators;

    std::shared_ptr<Component> assembleComponent(const std::string& name, const YAML::Node& initNode);
    int newId();
    static FunctionMap* getComponentCreators();

public:
    Factory(Terrarium& owner);

    void assembleEntity(EntityType type, Vec2i pos);
    void disassembleEntity(EntityId id);
    void update();
};

template <typename T>
struct ComponentRegister
{
    ComponentRegister(std::string const& name)
    {
        Factory::getComponentCreators()->insert(std::make_pair(name, &createComponent<T>));
    }
};

#endif // FACTORY_H
