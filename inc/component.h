#ifndef COMPONENT_H
#define COMPONENT_H

#include "common.h"
#include "factory.h"
#include "yaml-cpp/yaml.h"

#define INC_FACTORY_REGISTER(NAME) static ComponentRegister<NAME> reg
#define SRC_FACTORY_REGISTER(NAME) ComponentRegister<NAME> NAME::reg(#NAME)

struct Component
{
    virtual bool init(YAML::Node node) = 0;
    virtual ~Component() {}
};

#endif // COMPONENT_H
