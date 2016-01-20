#ifndef CTRANSLATE_H
#define CTRANSLATE_H

#include "common.h"
#include "component.h"
#include "vec2.h"

#include <cstdlib>
#include <map>

class CTranslate : public Component
{
    INC_FACTORY_REGISTER(CTranslate);
    
public:
    Dir direction;
    double velocity;

    virtual bool init(YAML::Node node);
};

#endif // CTRANSLATE_H
