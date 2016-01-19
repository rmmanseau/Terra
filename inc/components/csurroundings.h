#ifndef CSURROUNDINGS_H
#define CSURROUNDINGS_H

#include "common.h"
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
    int numberFull();
};

#endif // CSURROUNDINGS_H
