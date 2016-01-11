#ifndef FACTORY_H
#define FACTORY_H

#include "common.h"
#include "entity.h"
#include "component.h"
#include "vec2.h"

#include "yaml-cpp/yaml.h"

typedef std::shared_ptr<Component> (*componentCreatorFunction)();
typedef std::unordered_map<std::string, componentCreatorFunction> FunctionMap;
typedef std::unordered_map<std::string, YAML::Node> YAMLNodeMap;

class Factory
{
    Grid& rGrid;
    ProcessVec& rProcesses;
    EntityMap& rEntities;

    EntityId nextId;

    YAMLNodeMap blueprints;
    FunctionMap componentCreatorFunctions;

    inline int newId() {return nextId++;}

public:
    Factory(Terrarium& owner);
    void assembleEntity(std::string entityName, Vec2 pos);
};

#endif // FACTORY_H
