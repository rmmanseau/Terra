#ifndef CSURROUNDINGS_H
#define CSURROUNDINGS_H

#include "common.h"
#include "glbl_constants.h"
#include "component.h"

class CSurroundings : public Component
{
    INC_FACTORY_REGISTER(CSurroundings);
    
    std::vector<EntityId> ids;
    std::vector<EntityType> types;

public:
    virtual bool init(YAML::Node node);

    void setInfo(int dir, EntityId id, EntityType type);
    int numberOf(EntityType type);
    int numberOf(std::vector<EntityType> otherTypes);
    int numberFull();
    Dir directionTowards(EntityType type);
    Dir directionTowards(std::vector<EntityType> otherTypes);
    EntityId idAt(Dir dir);
    EntityType typeAt(Dir dir);
};

#endif // CSURROUNDINGS_H
