#ifndef FACTORY_H
#define FACTORY_H

#include "common.h"
#include "entity.h"
#include "component.h"
#include "vec2.h"

#include <map>
#include "yaml-cpp/yaml.h"

typedef std::shared_ptr<Component> (*componentCreatorFunction)();
typedef std::unordered_map<std::string, componentCreatorFunction> FunctionMap;
typedef std::unordered_map<std::string, EntityType> EntityTypeMap;
typedef std::map<EntityType, YAML::Node> YAMLNodeMap;

class Factory
{
    Grid& rGrid;
    ProcessVec& rProcesses;
    EntityMap& rEntities;

    EntityId nextId;

    YAMLNodeMap blueprints;
    FunctionMap componentCreatorFunctions;
    EntityTypeMap entityTypes;

    inline int newId() {return nextId++;}

public:
    Factory(Terrarium& owner);
    void assembleEntity(EntityType type, Vec2 pos);
};

#endif // FACTORY_H
