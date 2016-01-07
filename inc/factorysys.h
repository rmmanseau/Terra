#ifndef FACTORYSYS_H
#define FACTORYSYS_H

#include "common.h"
#include "component.h"
#include "crender.h"
#include "cposition.h"
#include "cmovement.h"

#include "yaml-cpp/yaml.h"

typedef std::shared_ptr<Component> (FactorySys::*componentCreator)(YAML::Node); // function pointer type
typedef std::unordered_map<std::string, componentCreator> ComponentCreatorMap;
typedef std::unordered_map<std::string, YAML::Node> YAMLNodeMap;

class FactorySys
{
    Terrarium* pOwner;
    ActorId nextId;

    YAMLNodeMap blueprints;
    ComponentCreatorMap componentCreators;

    inline int newId() {return nextId++;}

    std::shared_ptr<Component> createCRender(YAML::Node node);
    std::shared_ptr<Component> createCPosition(YAML::Node node);
    std::shared_ptr<Component> createCMovement(YAML::Node node);

public:
    FactorySys() {}
    void init(Terrarium& owner);
    void assembleActor(ActorMap& actors, std::string actorName, Vec2 pos);
};

#endif // FACTORYSYS_H
