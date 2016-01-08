#ifndef COMPONENT_H
#define COMPONENT_H

#include "common.h"
#include "yaml-cpp/yaml.h"

struct Component
{
    virtual bool init(YAML::Node node) = 0;
    virtual ~Component() {}
};

/* 
 *  All new components must provide a creation function
 *  that returns a shared pointer to an instance of the
 *  component. This function is used by the factory 
 *  when entities are being assembled. i.e.
 *  
 *  std::shared_ptr<Component> createCSomething()
 *  {
 *      return std::make_shared<CSomething>();
 *  }
 *  
 *  This function will need to be added to the factories
 *  component creator map during the factories init.
 */

#endif // COMPONENT_H
