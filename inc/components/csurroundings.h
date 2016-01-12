#ifndef CSURROUNDINGS_H
#define CSURROUNDINGS_H

#include "common.h"
#include "component.h"

class CSurroundings : public Component
{
    std::vector<EntityId> ids;
    std::vector<EntityType> types;

public:
    virtual bool init(YAML::Node node);

    void setInfo(int dir, EntityId id, EntityType type);
    int numberOf(EntityType type);
};

inline std::shared_ptr<Component> createCSurroundings()
{
    return std::make_shared<CSurroundings>();
}

#endif // CSURROUNDINGS_H
